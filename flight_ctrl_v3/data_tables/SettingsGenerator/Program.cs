using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace SettingsGenerator
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }

    public struct Variable
    {
        public string Type
        {
            get;
            set;
        }

        public string Name
        {
            get;
            set;
        }

        public string DefaultValue
        {
            get;
            set;
        }
    }
}
