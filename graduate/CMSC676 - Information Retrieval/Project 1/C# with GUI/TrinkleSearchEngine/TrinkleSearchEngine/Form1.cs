using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TrinkleSearchEngine
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void parseinput_btn_Click(object sender, EventArgs e)
        {
            Boolean success = false;
            
            this.parseinput_btn.Enabled = false;
            this.success_lbl.Text = "0";
            this.failure_lbl.Text = "0";

            // I really need to pass it a directory and parse all the files in it.
            if (System.IO.Directory.Exists(this.m_sourcedirectory))
            {
                HTMLParser parser;
                int successCnt = 0;
                int failCnt = 0;

                List<string> files = System.IO.Directory.GetFiles(this.m_sourcedirectory, "*.html").ToList();

                this.progressBar1.Step = 100 / files.Count;

                foreach (string file in files)
                {
                    parser = new HTMLParser(file);

                    success = parser.tokenize();

                    if (success)
                    {
                        System.Console.WriteLine("Successfully tokenized: " + file);
                        successCnt++;
                        this.success_lbl.Text = successCnt.ToString();
                        this.success_lbl.Update();

                        int cnt = parser.getTokenCount();

                        for (int i = 0; i < cnt; ++i)
                        {
                            files_lv.Items.Add(parser.getToken());
                        }
                    }
                    else
                    {
                        System.Console.WriteLine("Failed to tokenize: " + file);
                        failCnt++;
                        this.failure_lbl.Text = failCnt.ToString();
                        this.success_lbl.Update();
                    }

                    this.progressBar1.PerformStep();
                    this.progressBar1.Update();
                }
            }

            if (!success)
            {
                this.parseinput_btn.Text = "Failed";
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void choose_src_btn_Click(object sender, EventArgs e)
        {
            DialogResult result = this.folderBrowserDialog1.ShowDialog();

            this.m_sourcedirectory = "";

            if (result == DialogResult.OK)
            {
                // set to a foldername somewhere
                this.m_sourcedirectory = this.folderBrowserDialog1.SelectedPath;

                this.sourcedir_lbl.Text = this.m_sourcedirectory;

                this.parseinput_btn.Enabled = true;
            }
            else
            {
                return;
            }
        }

        private string m_sourcedirectory;
    }
}
