using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using System.ComponentModel;
using NAudio.Wave;

class RoundedButton : Button
{
    [Browsable(false)]
    [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
    public int BorderRadius { get; set; } = 20;

    [Browsable(false)]
    [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
    public Color ShadowColor { get; set; } = Color.FromArgb(100, 0, 0, 0);

    [Browsable(false)]
    [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
    public int ShadowOffset { get; set; } = 4;

    public RoundedButton()
    {
        DoubleBuffered = true;
        FlatStyle = FlatStyle.Flat;
        FlatAppearance.BorderSize = 0;
    }

    protected override void OnPaintBackground(PaintEventArgs pevent)
    {
        // Prevent default background painting to reduce flicker
    }

    protected override void OnPaint(PaintEventArgs pevent)
    {
        Graphics g = pevent.Graphics;
        g.SmoothingMode = SmoothingMode.AntiAlias;

        // Draw shadow
        using (GraphicsPath shadowPath = GetRoundRectPath(
            new Rectangle(ShadowOffset, ShadowOffset, Width - ShadowOffset, Height - ShadowOffset),
            BorderRadius))
        using (SolidBrush shadowBrush = new SolidBrush(ShadowColor))
        {
            g.FillPath(shadowBrush, shadowPath);
        }

        // Draw button background
        using (GraphicsPath buttonPath = GetRoundRectPath(ClientRectangle, BorderRadius))
        using (SolidBrush buttonBrush = new SolidBrush(BackColor))
        {
            g.FillPath(buttonBrush, buttonPath);
        }

        // Draw image if any
        if (Image != null)
        {
            int imageY = (Height - Image.Height) / 2;
            g.DrawImage(Image, 10, imageY, Image.Width, Image.Height);
        }

        // Draw text offset if image present
        int textOffsetX = Image != null ? Image.Width + 20 : 0;
        Rectangle textRect = new Rectangle(textOffsetX, 0, Width - textOffsetX, Height);
        TextRenderer.DrawText(g, Text, Font, textRect, ForeColor,
            TextFormatFlags.VerticalCenter | TextFormatFlags.Left);
    }

    private GraphicsPath GetRoundRectPath(Rectangle rect, int radius)
    {
        GraphicsPath path = new GraphicsPath();
        int diameter = radius * 2;

        path.AddArc(rect.Left, rect.Top, diameter, diameter, 180, 90);
        path.AddArc(rect.Right - diameter, rect.Top, diameter, diameter, 270, 90);
        path.AddArc(rect.Right - diameter, rect.Bottom - diameter, diameter, diameter, 0, 90);
        path.AddArc(rect.Left, rect.Bottom - diameter, diameter, diameter, 90, 90);
        path.CloseFigure();

        return path;
    }
}

class MyWindow : Form
{
    Size normalSize = new Size(70, 30);
    Size hoverSize = new Size(80, 40);

    System.Windows.Forms.Timer animTimer = new System.Windows.Forms.Timer();
    RoundedButton? animBtn;
    Size sizeGoal;
    Point posGoal;
    int stepCount = 8, stepNow;

    Panel mainPanel = new Panel();
    Panel settingsPanel = new Panel();
    Panel playPanel = new Panel();
    Panel currentPanel;

    // Image paths
    string mainBgPath = @"D:\OneDrive\Pictures\anime-your-name-hd-wallpaper-preview.jpg";
    string settingsBgPath = @"D:\OneDrive\Pictures\istockphoto-855022728-612x612.jpg";
    string playBgPath = @"D:\OneDrive\Pictures\images.jpeg";
    // Background music player (nullable)
    IWavePlayer? waveOutDevice;
    AudioFileReader? audioFileReader;
    string musicPath = @"D:\Games\TES - Skyrim - Anniversary Edition\Skyrim - OST\[07] - A Winter's Tale.mp3";

    public MyWindow()
    {
        Text = "Curved Buttons with Background Images, Slide Transitions & Music";
        Width = 800;
        Height = 600;
        BackColor = Color.LightBlue;

        // Setup panels
        mainPanel.Dock = DockStyle.Fill;
        settingsPanel.Dock = DockStyle.Fill;
        mainPanel.BackColor = Color.LightCyan;
        settingsPanel.BackColor = Color.LightGoldenrodYellow;
        playPanel.Dock = DockStyle.Fill;
        playPanel.BackColor = Color.LightCoral;

        Controls.Add(mainPanel);
        Controls.Add(settingsPanel);
        Controls.Add(playPanel);
        settingsPanel.Visible = false;
        playPanel.Visible = false;
        currentPanel = mainPanel;

        // Set background images with try-catch to avoid crashes if files missing
        try
        {
            mainPanel.BackgroundImage = Image.FromFile(mainBgPath);
            mainPanel.BackgroundImageLayout = ImageLayout.Stretch;
        }
        catch { }

        try
        {
            settingsPanel.BackgroundImage = Image.FromFile(settingsBgPath);
            settingsPanel.BackgroundImageLayout = ImageLayout.Stretch;
        }
        catch { }

        try
        {
            playPanel.BackgroundImage = Image.FromFile(playBgPath);
            playPanel.BackgroundImageLayout = ImageLayout.Stretch;
        }
        catch { }
        // Add buttons to main panel
        CreatePopButton("Play", 100, 150, Color.SteelBlue, mainPanel);
        CreatePopButton("Settings", 100, 220, Color.SeaGreen, mainPanel);
        CreatePopButton("Exit", 100, 290, Color.Firebrick, mainPanel);
        CreatePopButton("Back", 100, 220, Color.DarkSlateGray, settingsPanel);
        CreatePopButton("Back", 100, 220, Color.DarkSlateGray, playPanel);

        animTimer.Interval = 15;
        animTimer.Tick += Animate;

        // Start music playback
        try
        {
            waveOutDevice = new WaveOutEvent();
            audioFileReader = new AudioFileReader(musicPath);
            waveOutDevice.Init(audioFileReader);
            waveOutDevice.PlaybackStopped += OnPlaybackStopped;
            waveOutDevice.Play();
        }
        catch (Exception ex)
        {
            MessageBox.Show("Failed to play music:\n" + ex.Message);
        }
    }

    void CreatePopButton(string text, int x, int y, Color baseColor, Panel parent, string? imagePath = null)
    {
        RoundedButton btn = new RoundedButton()
        {
            Text = text,
            Size = normalSize,
            Location = new Point(x, y),
            BackColor = baseColor,
            ForeColor = Color.White,
            Font = new Font("Segoe UI", 12, FontStyle.Bold),
            BorderRadius = 20,
            ShadowColor = Color.FromArgb(120, 0, 0, 0),
            ShadowOffset = 5
        };

        if (imagePath != null)
        {
            try
            {
                btn.Image = Image.FromFile(imagePath);
            }
            catch { }
        }

        btn.MouseEnter += (s, e) =>
        {
            StartAnimation(btn, hoverSize, new Point(x - 15, y - 7));
        };

        btn.MouseLeave += (s, e) =>
        {
            StartAnimation(btn, normalSize, new Point(x, y));
        };

        btn.Click += (s, e) =>
        {
            if (btn.Text == "Exit")
            {
                waveOutDevice?.Stop();
                Close();
            }
            else if (btn.Text == "Settings")
                ShowPanelSlide(settingsPanel);
            else if (btn.Text == "Play")
                ShowPanelSlide(playPanel);
            else if (btn.Text == "Back")
                ShowPanelSlide(mainPanel);
            else
                MessageBox.Show($"You clicked {btn.Text}");
        };

        parent.Controls.Add(btn);
    }

    void ShowPanelSlide(Panel toShow)
    {
        if (toShow == currentPanel) return;

        Panel fromPanel = currentPanel;
        Panel nextPanel = toShow;

        nextPanel.Location = new Point(Width, 0);
        nextPanel.Visible = true;

        System.Windows.Forms.Timer slideTimer = new System.Windows.Forms.Timer { Interval = 15 };
        slideTimer.Tick += (s, e) =>
        {
            fromPanel.Left -= 30;
            nextPanel.Left -= 30;

            if (nextPanel.Left <= 0)
            {
                slideTimer.Stop();
                fromPanel.Visible = false;
                nextPanel.Left = 0;
                currentPanel = nextPanel;
            }
        };
        slideTimer.Start();
    }

    void StartAnimation(RoundedButton btn, Size targetSize, Point targetPos)
    {
        animBtn = btn;
        sizeGoal = targetSize;
        posGoal = targetPos;
        stepNow = 0;
        animTimer.Start();
    }

    private void Animate(object? sender, EventArgs e)
    {
        if (animBtn == null) return;

        stepNow++;

        animBtn.Size = new Size(
            animBtn.Size.Width + (int)((sizeGoal.Width - animBtn.Size.Width) * 0.3f),
            animBtn.Size.Height + (int)((sizeGoal.Height - animBtn.Size.Height) * 0.3f)
        );

        animBtn.Location = new Point(
            animBtn.Location.X + (int)((posGoal.X - animBtn.Location.X) * 0.3f),
            animBtn.Location.Y + (int)((posGoal.Y - animBtn.Location.Y) * 0.3f)
        );

        if (stepNow >= stepCount)
            animTimer.Stop();
    }

    private void OnPlaybackStopped(object? sender, StoppedEventArgs e)
    {
        // Loop the music
        if (audioFileReader != null && waveOutDevice != null)
        {
            audioFileReader.Position = 0;
            waveOutDevice.Play();
        }
    }

    protected override void OnFormClosing(FormClosingEventArgs e)
    {
        // Dispose audio resources properly
        waveOutDevice?.Stop();
        waveOutDevice?.Dispose();
        audioFileReader?.Dispose();

        base.OnFormClosing(e);
    }

    [STAThread]
    static void Main()
    {
        Application.EnableVisualStyles();
        Application.Run(new MyWindow());
    }
}
