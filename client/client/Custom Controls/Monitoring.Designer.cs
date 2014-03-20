namespace client
{
    partial class Monitoring
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.cpu = new System.Windows.Forms.Label();
            this.ram = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.ram_usage = new client.MyProgressBar();
            this.cpu_usage = new client.MyProgressBar();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // cpu
            // 
            this.cpu.AutoSize = true;
            this.cpu.Location = new System.Drawing.Point(6, 18);
            this.cpu.Name = "cpu";
            this.cpu.Size = new System.Drawing.Size(32, 13);
            this.cpu.TabIndex = 0;
            this.cpu.Text = "CPU";
            // 
            // ram
            // 
            this.ram.AutoSize = true;
            this.ram.Location = new System.Drawing.Point(6, 42);
            this.ram.Name = "ram";
            this.ram.Size = new System.Drawing.Size(34, 13);
            this.ram.TabIndex = 1;
            this.ram.Text = "RAM";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.ram_usage);
            this.groupBox1.Controls.Add(this.cpu_usage);
            this.groupBox1.Controls.Add(this.cpu);
            this.groupBox1.Controls.Add(this.ram);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(0, -2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(198, 60);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Server monitoring";
            // 
            // ram_usage
            // 
            this.ram_usage.CustomText = null;
            this.ram_usage.DisplayStyle = client.ProgressBarDisplayText.Percentage;
            this.ram_usage.Location = new System.Drawing.Point(44, 39);
            this.ram_usage.Name = "ram_usage";
            this.ram_usage.Size = new System.Drawing.Size(148, 18);
            this.ram_usage.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.ram_usage.TabIndex = 3;
            // 
            // cpu_usage
            // 
            this.cpu_usage.CustomText = null;
            this.cpu_usage.DisplayStyle = client.ProgressBarDisplayText.Percentage;
            this.cpu_usage.Location = new System.Drawing.Point(44, 15);
            this.cpu_usage.Name = "cpu_usage";
            this.cpu_usage.Size = new System.Drawing.Size(148, 18);
            this.cpu_usage.Style = System.Windows.Forms.ProgressBarStyle.Marquee;
            this.cpu_usage.TabIndex = 2;
            // 
            // Monitoring
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBox1);
            this.Name = "Monitoring";
            this.Size = new System.Drawing.Size(200, 60);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label cpu;
        private System.Windows.Forms.Label ram;
        private System.Windows.Forms.GroupBox groupBox1;
        private MyProgressBar ram_usage;
        private MyProgressBar cpu_usage;
    }
}
