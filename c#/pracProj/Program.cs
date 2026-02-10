using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace pracProj
{
    class Program
    {
        static void Main(string[] args)
        {
            // Your code here
            Console.Title = "Multiplication Table";
            string s = "32";
            if (test(s, out int result))
            {
                Console.WriteLine($"The result is: {result}");
            }
            else
            {
                Console.WriteLine("Invalid input.");
            }
            Console.WriteLine();
        }
        static bool test(string s, out int result)
        {
            result=Convert.ToInt32(s);
            return true;
        }
    }
}
