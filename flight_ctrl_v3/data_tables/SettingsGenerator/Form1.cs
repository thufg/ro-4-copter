using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SettingsGenerator
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                OpenFileDialog ofd = new OpenFileDialog();
                ofd.InitialDirectory = @"C:\Users\Frank\Documents\Projects\quadrotor_helicopter\flight_ctrl_v3\data_tables";

                if (ofd.ShowDialog() != DialogResult.OK)
                    return;

                SaveFileDialog sfd = new SaveFileDialog();
                sfd.InitialDirectory = @"C:\Users\Frank\Documents\Projects\quadrotor_helicopter\flight_ctrl_v3";

                if (sfd.ShowDialog() != DialogResult.OK)
                    return;

                List<Variable> vars = new List<Variable>();

                StreamReader reader = new StreamReader(ofd.FileName);

                string l = reader.ReadLine();

                while (l != null)
                {
                    if (l.StartsWith("//") == false)
                    {
                        string[] parts = l.Split(',');

                        if (parts.Length >= 2)
                        {
                            string type = parts[0].Trim('"').Trim();
                            string name = parts[1].Trim('"').Trim();
                            string defVal = "";
                            string comment = "";

                            if (parts.Length >= 3)
                            {
                                defVal = parts[2].Trim('"').Trim();
                            }

                            if (parts.Length >= 4)
                            {
                                comment = parts[3].Trim('"').Trim();
                            }

                            if (string.IsNullOrEmpty(type) == false && string.IsNullOrEmpty(name) == false)
                            {
                                if (type.StartsWith("//") == false && name.StartsWith("//") == false)
                                {
                                    Variable v = new Variable() { Type = type, Name = name, DefaultValue = defVal };

                                    vars.Add(v);
                                }
                            }
                        }
                    }

                    l = reader.ReadLine();
                }
                reader.Close();

                StreamWriter writer = new StreamWriter(sfd.FileName);

                string fname = Path.GetFileNameWithoutExtension(sfd.FileName);
                writer.WriteLine("#ifndef {0}_h", fname);
                writer.WriteLine("#define {0}_h", fname);

                writer.WriteLine();

                //foreach (Variable v in vars)
                //{
                //    writer.WriteLine("#define {0}_defval {1}", v.Name, v.DefaultValue);
                //}

                //writer.WriteLine();

                writer.WriteLine("typedef struct Calibration_{");

                foreach (Variable v in vars)
                {
                    writer.WriteLine("\t{0} {1};", v.Type, v.Name);
                }

                writer.WriteLine("} Calibration;");

                writer.WriteLine();
                writer.WriteLine("// Var count: {0}", vars.Count);
                writer.WriteLine();

                writer.WriteLine("/*");

                writer.WriteLine("void calibration_default(Calibration * x)");
                writer.WriteLine("{");

                foreach (Variable v in vars)
                {
                    writer.WriteLine("\tx->{0} = {1};", v.Name, v.DefaultValue);
                }

                writer.WriteLine("}");

                writer.WriteLine("*/");

                writer.WriteLine();

                writer.WriteLine("#endif");

                writer.Close();

                MessageBox.Show("Done!");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.Message);
            }
        }
    }
}
