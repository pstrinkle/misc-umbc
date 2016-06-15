namespace TrinkleSearchEngine
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.sourcedir_lbl = new System.Windows.Forms.Label();
            this.choose_src_btn = new System.Windows.Forms.Button();
            this.parseinput_btn = new System.Windows.Forms.Button();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.files_lv = new System.Windows.Forms.ListView();
            this.success_lbl = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.failure_lbl = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.sourcedir_lbl);
            this.groupBox1.Controls.Add(this.choose_src_btn);
            this.groupBox1.Controls.Add(this.parseinput_btn);
            this.groupBox1.Location = new System.Drawing.Point(34, 43);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(386, 131);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Primary Menu";
            // 
            // sourcedir_lbl
            // 
            this.sourcedir_lbl.AutoSize = true;
            this.sourcedir_lbl.Location = new System.Drawing.Point(166, 73);
            this.sourcedir_lbl.Name = "sourcedir_lbl";
            this.sourcedir_lbl.Size = new System.Drawing.Size(16, 13);
            this.sourcedir_lbl.TabIndex = 4;
            this.sourcedir_lbl.Text = "...";
            // 
            // choose_src_btn
            // 
            this.choose_src_btn.Location = new System.Drawing.Point(6, 73);
            this.choose_src_btn.Name = "choose_src_btn";
            this.choose_src_btn.Size = new System.Drawing.Size(133, 23);
            this.choose_src_btn.TabIndex = 3;
            this.choose_src_btn.Text = "Choose Source Folder";
            this.choose_src_btn.UseVisualStyleBackColor = true;
            this.choose_src_btn.Click += new System.EventHandler(this.choose_src_btn_Click);
            // 
            // parseinput_btn
            // 
            this.parseinput_btn.Location = new System.Drawing.Point(6, 102);
            this.parseinput_btn.Name = "parseinput_btn";
            this.parseinput_btn.Size = new System.Drawing.Size(75, 23);
            this.parseinput_btn.TabIndex = 0;
            this.parseinput_btn.Text = "Parse";
            this.parseinput_btn.UseVisualStyleBackColor = true;
            this.parseinput_btn.Click += new System.EventHandler(this.parseinput_btn_Click);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(320, 273);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(100, 23);
            this.progressBar1.TabIndex = 1;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(909, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(92, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.files_lv);
            this.groupBox2.Location = new System.Drawing.Point(518, 58);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(341, 398);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "groupBox2";
            // 
            // files_lv
            // 
            this.files_lv.Location = new System.Drawing.Point(6, 19);
            this.files_lv.Name = "files_lv";
            this.files_lv.Size = new System.Drawing.Size(329, 373);
            this.files_lv.TabIndex = 0;
            this.files_lv.UseCompatibleStateImageBehavior = false;
            this.files_lv.View = System.Windows.Forms.View.List;
            // 
            // success_lbl
            // 
            this.success_lbl.AutoSize = true;
            this.success_lbl.Location = new System.Drawing.Point(262, 200);
            this.success_lbl.Name = "success_lbl";
            this.success_lbl.Size = new System.Drawing.Size(13, 13);
            this.success_lbl.TabIndex = 4;
            this.success_lbl.Text = "0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(185, 200);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Successes";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(185, 230);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Failures";
            // 
            // failure_lbl
            // 
            this.failure_lbl.AutoSize = true;
            this.failure_lbl.Location = new System.Drawing.Point(262, 230);
            this.failure_lbl.Name = "failure_lbl";
            this.failure_lbl.Size = new System.Drawing.Size(13, 13);
            this.failure_lbl.TabIndex = 7;
            this.failure_lbl.Text = "0";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(909, 534);
            this.Controls.Add(this.failure_lbl);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.success_lbl);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button parseinput_btn;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Button choose_src_btn;
        private System.Windows.Forms.Label sourcedir_lbl;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.ListView files_lv;
        private System.Windows.Forms.Label success_lbl;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label failure_lbl;
    }
}

