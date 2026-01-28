#!/usr/bin/env python3
"""
Download .h, .cpp, and .pdf files from a Moodle assignment page.
Supports authentication via username/password or session cookie.
"""

import argparse
import os
import re
import sys
import time
from pathlib import Path
from urllib.parse import urljoin, urlparse

import requests
from bs4 import BeautifulSoup


class FileDownloader:
    def __init__(self, base_url, html_file, output_dir="downloads", max_retries=3):
        self.base_url = base_url
        self.html_file = html_file
        self.output_dir = Path(output_dir)
        self.max_retries = max_retries
        self.session = requests.Session()
        self.downloaded_files = set()
        
        # Create output directory
        self.output_dir.mkdir(parents=True, exist_ok=True)
    
    def login_with_credentials(self, username, password, login_url):
        """Login using username and password."""
        print(f"Logging in as {username}...")
        
        # Get the login page to extract any CSRF tokens
        response = self.session.get(login_url)
        soup = BeautifulSoup(response.text, 'html.parser')
        
        # Common Moodle login form data
        login_data = {
            'username': username,
            'password': password
        }
        
        # Look for hidden fields (like logintoken)
        for hidden in soup.find_all('input', type='hidden'):
            if hidden.get('name'):
                login_data[hidden['name']] = hidden.get('value', '')
        
        # Submit login
        response = self.session.post(login_url, data=login_data)
        
        if response.ok:
            print("✓ Login successful")
            return True
        else:
            print(f"✗ Login failed: {response.status_code}")
            return False
    
    def set_session_cookie(self, cookie_name, cookie_value):
        """Set session cookie for authentication."""
        print(f"Setting session cookie: {cookie_name}")
        self.session.cookies.set(cookie_name, cookie_value)
        print("✓ Session cookie set")
    
    def extract_file_links(self, extensions=None):
        """Extract all links with specified extensions from HTML file."""
        if extensions is None:
            extensions = ['.h', '.cpp', '.pdf']
        
        print(f"Parsing {self.html_file}...")
        
        with open(self.html_file, 'r', encoding='utf-8') as f:
            html_content = f.read()
        
        soup = BeautifulSoup(html_content, 'html.parser')
        links = []
        
        # Find all <a> tags with href
        for link in soup.find_all('a', href=True):
            href = link['href']
            
            # Check if link ends with any of the target extensions
            if any(href.lower().endswith(ext) for ext in extensions):
                # Resolve relative URLs to absolute
                absolute_url = urljoin(self.base_url, href)
                links.append(absolute_url)
        
        # Remove duplicates while preserving order
        links = list(dict.fromkeys(links))
        
        print(f"✓ Found {len(links)} file(s) to download")
        return links
    
    def get_filename_from_url(self, url):
        """Extract filename from URL."""
        parsed = urlparse(url)
        filename = os.path.basename(parsed.path)
        
        # If no filename, try to get from Content-Disposition header
        if not filename or '.' not in filename:
            filename = f"file_{hash(url)}"
        
        return filename
    
    def download_file(self, url, retry_count=0):
        """Download a single file with retry logic."""
        try:
            filename = self.get_filename_from_url(url)
            filepath = self.output_dir / filename
            
            # Skip if already downloaded
            if str(filepath) in self.downloaded_files:
                print(f"⊘ Skipping duplicate: {filename}")
                return True
            
            # Check if file already exists
            if filepath.exists():
                print(f"⊘ Already exists: {filename}")
                self.downloaded_files.add(str(filepath))
                return True
            
            print(f"↓ Downloading: {filename}... ", end='', flush=True)
            
            # Download with stream to handle large files
            response = self.session.get(url, stream=True, timeout=30)
            response.raise_for_status()
            
            # Get actual filename from Content-Disposition if available
            if 'Content-Disposition' in response.headers:
                cd = response.headers['Content-Disposition']
                filename_match = re.findall('filename="?([^"]+)"?', cd)
                if filename_match:
                    filename = filename_match[0]
                    filepath = self.output_dir / filename
            
            # Write file
            with open(filepath, 'wb') as f:
                for chunk in response.iter_content(chunk_size=8192):
                    if chunk:
                        f.write(chunk)
            
            file_size = filepath.stat().st_size
            print(f"✓ ({file_size:,} bytes)")
            self.downloaded_files.add(str(filepath))
            return True
            
        except requests.exceptions.RequestException as e:
            print(f"✗ Error: {e}")
            
            # Retry logic
            if retry_count < self.max_retries:
                wait_time = 2 ** retry_count  # Exponential backoff
                print(f"  Retrying in {wait_time}s... (attempt {retry_count + 1}/{self.max_retries})")
                time.sleep(wait_time)
                return self.download_file(url, retry_count + 1)
            else:
                print(f"  ✗ Failed after {self.max_retries} attempts")
                return False
        
        except Exception as e:
            print(f"✗ Unexpected error: {e}")
            return False
    
    def download_all(self, extensions=None):
        """Extract and download all files."""
        links = self.extract_file_links(extensions)
        
        if not links:
            print("No files found to download.")
            return
        
        print(f"\nDownloading to: {self.output_dir.absolute()}\n")
        
        success_count = 0
        failed_urls = []
        
        for i, url in enumerate(links, 1):
            print(f"[{i}/{len(links)}] ", end='')
            if self.download_file(url):
                success_count += 1
            else:
                failed_urls.append(url)
        
        # Summary
        print(f"\n{'='*60}")
        print(f"Download complete!")
        print(f"✓ Successful: {success_count}/{len(links)}")
        
        if failed_urls:
            print(f"✗ Failed: {len(failed_urls)}")
            print("\nFailed URLs:")
            for url in failed_urls:
                print(f"  - {url}")
        
        print(f"{'='*60}")


def main():
    parser = argparse.ArgumentParser(
        description="Download .h, .cpp, and .pdf files from HTML page",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Using username and password
  python download_files.py dwnld.html --username your_username --password your_password

  # Using session cookie
  python download_files.py dwnld.html --cookie MoodleSession --value "abc123xyz..."

  # Specify custom output directory
  python download_files.py dwnld.html --username user --password pass --output my_downloads

  # Download only specific file types
  python download_files.py dwnld.html --username user --password pass --extensions .pdf .cpp
        """
    )
    
    parser.add_argument('html_file', help='Path to the HTML file to parse')
    parser.add_argument('--base-url', default='https://cse.buet.ac.bd/moodle/',
                        help='Base URL of the site (default: https://cse.buet.ac.bd/moodle/)')
    parser.add_argument('--login-url', 
                        help='Login URL (default: base_url + "login/index.php")')
    
    # Authentication options
    auth_group = parser.add_argument_group('Authentication (choose one)')
    auth_group.add_argument('--username', help='Username for login')
    auth_group.add_argument('--password', help='Password for login')
    auth_group.add_argument('--cookie', help='Session cookie name (e.g., MoodleSession)')
    auth_group.add_argument('--value', help='Session cookie value')
    
    # Download options
    parser.add_argument('--output', '-o', default='downloads',
                        help='Output directory (default: downloads)')
    parser.add_argument('--extensions', '-e', nargs='+', 
                        default=['.h', '.cpp', '.pdf'],
                        help='File extensions to download (default: .h .cpp .pdf)')
    parser.add_argument('--max-retries', type=int, default=3,
                        help='Maximum retry attempts for failed downloads (default: 3)')
    
    args = parser.parse_args()
    
    # Validate HTML file exists
    if not os.path.exists(args.html_file):
        print(f"Error: HTML file not found: {args.html_file}")
        sys.exit(1)
    
    # Validate authentication method
    has_credentials = args.username and args.password
    has_cookie = args.cookie and args.value
    
    if not has_credentials and not has_cookie:
        print("Error: Must provide either --username/--password OR --cookie/--value")
        parser.print_help()
        sys.exit(1)
    
    # Set login URL
    login_url = args.login_url or urljoin(args.base_url, 'login/index.php')
    
    # Initialize downloader
    downloader = FileDownloader(
        base_url=args.base_url,
        html_file=args.html_file,
        output_dir=args.output,
        max_retries=args.max_retries
    )
    
    # Authenticate
    if has_credentials:
        if not downloader.login_with_credentials(args.username, args.password, login_url):
            print("Authentication failed. Exiting.")
            sys.exit(1)
    else:
        downloader.set_session_cookie(args.cookie, args.value)
    
    # Download files
    try:
        downloader.download_all(args.extensions)
    except KeyboardInterrupt:
        print("\n\nDownload interrupted by user.")
        sys.exit(1)
    except Exception as e:
        print(f"\nError: {e}")
        sys.exit(1)


if __name__ == '__main__':
    main()
