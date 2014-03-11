﻿namespace client
{
    partial class MainForm
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.quitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripProgressBar1 = new System.Windows.Forms.ToolStripProgressBar();
            this.draw_status = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.panel5 = new System.Windows.Forms.Panel();
            this.panel6 = new System.Windows.Forms.Panel();
            this.panel7 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel9 = new System.Windows.Forms.Panel();
            this.propertyGrid = new System.Windows.Forms.PropertyGrid();
            this.panel8 = new System.Windows.Forms.Panel();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.view_x = new System.Windows.Forms.PictureBox();
            this.view_y = new System.Windows.Forms.PictureBox();
            this.view_z = new System.Windows.Forms.PictureBox();
            this.select_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.move_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.resize_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.zoomin_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.zoomout_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.sphere_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel3.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.panel4.SuspendLayout();
            this.panel5.SuspendLayout();
            this.panel7.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel9.SuspendLayout();
            this.panel8.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.view_x)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.view_y)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.view_z)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(750, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.saveToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.loadToolStripMenuItem,
            this.toolStripSeparator3,
            this.quitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // quitToolStripMenuItem
            // 
            this.quitToolStripMenuItem.Name = "quitToolStripMenuItem";
            this.quitToolStripMenuItem.Size = new System.Drawing.Size(97, 22);
            this.quitToolStripMenuItem.Text = "Quit";
            this.quitToolStripMenuItem.Click += new System.EventHandler(this.quitToolStripMenuItem_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripProgressBar1,
            this.toolStripStatusLabel1,
            this.draw_status});
            this.statusStrip1.Location = new System.Drawing.Point(0, 394);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(750, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripProgressBar1
            // 
            this.toolStripProgressBar1.Name = "toolStripProgressBar1";
            this.toolStripProgressBar1.Size = new System.Drawing.Size(100, 16);
            // 
            // draw_status
            // 
            this.draw_status.Name = "draw_status";
            this.draw_status.Size = new System.Drawing.Size(0, 17);
            // 
            // toolStrip1
            // 
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.select_toolstrip,
            this.move_toolstrip,
            this.resize_toolstrip,
            this.toolStripSeparator1,
            this.zoomin_toolstrip,
            this.zoomout_toolstrip,
            this.toolStripSeparator2,
            this.sphere_toolstrip});
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.toolStrip1.Size = new System.Drawing.Size(750, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "Pointer";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.panel3);
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 49);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(750, 345);
            this.panel1.TabIndex = 3;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.tableLayoutPanel1);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(0, 0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(550, 345);
            this.panel3.TabIndex = 1;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.panel4, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.panel5, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.panel6, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.panel7, 1, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(550, 345);
            this.tableLayoutPanel1.TabIndex = 5;
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.view_x);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel4.Location = new System.Drawing.Point(3, 3);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(269, 166);
            this.panel4.TabIndex = 0;
            // 
            // panel5
            // 
            this.panel5.Controls.Add(this.view_y);
            this.panel5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel5.Location = new System.Drawing.Point(278, 3);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(269, 166);
            this.panel5.TabIndex = 1;
            // 
            // panel6
            // 
            this.panel6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel6.Location = new System.Drawing.Point(3, 175);
            this.panel6.Name = "panel6";
            this.panel6.Size = new System.Drawing.Size(269, 167);
            this.panel6.TabIndex = 2;
            // 
            // panel7
            // 
            this.panel7.Controls.Add(this.view_z);
            this.panel7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel7.Location = new System.Drawing.Point(278, 175);
            this.panel7.Name = "panel7";
            this.panel7.Size = new System.Drawing.Size(269, 167);
            this.panel7.TabIndex = 3;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.panel9);
            this.panel2.Controls.Add(this.panel8);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel2.Location = new System.Drawing.Point(550, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(200, 345);
            this.panel2.TabIndex = 0;
            // 
            // panel9
            // 
            this.panel9.Controls.Add(this.propertyGrid);
            this.panel9.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel9.Location = new System.Drawing.Point(0, 21);
            this.panel9.Name = "panel9";
            this.panel9.Size = new System.Drawing.Size(200, 324);
            this.panel9.TabIndex = 1;
            // 
            // propertyGrid
            // 
            this.propertyGrid.Dock = System.Windows.Forms.DockStyle.Fill;
            this.propertyGrid.Location = new System.Drawing.Point(0, 0);
            this.propertyGrid.Name = "propertyGrid";
            this.propertyGrid.Size = new System.Drawing.Size(200, 324);
            this.propertyGrid.TabIndex = 0;
            this.propertyGrid.PropertyValueChanged += new System.Windows.Forms.PropertyValueChangedEventHandler(this.propertyGrid_PropertyValueChanged);
            // 
            // panel8
            // 
            this.panel8.Controls.Add(this.comboBox1);
            this.panel8.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel8.Location = new System.Drawing.Point(0, 0);
            this.panel8.Name = "panel8";
            this.panel8.Size = new System.Drawing.Size(200, 21);
            this.panel8.TabIndex = 0;
            // 
            // comboBox1
            // 
            this.comboBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(0, 0);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(200, 21);
            this.comboBox1.TabIndex = 42;
            this.comboBox1.TabStop = false;
            this.comboBox1.SelectedValueChanged += new System.EventHandler(this.comboBox1_SelectedValueChanged);
            // 
            // view_x
            // 
            this.view_x.Dock = System.Windows.Forms.DockStyle.Fill;
            this.view_x.Location = new System.Drawing.Point(0, 0);
            this.view_x.Name = "view_x";
            this.view_x.Size = new System.Drawing.Size(269, 166);
            this.view_x.TabIndex = 0;
            this.view_x.TabStop = false;
            this.view_x.Click += new System.EventHandler(this.view_x_Click);
            this.view_x.MouseDown += new System.Windows.Forms.MouseEventHandler(this.view_x_MouseDown);
            this.view_x.MouseMove += new System.Windows.Forms.MouseEventHandler(this.view_x_MouseMove);
            this.view_x.MouseUp += new System.Windows.Forms.MouseEventHandler(this.view_x_MouseUp);
            // 
            // view_y
            // 
            this.view_y.Dock = System.Windows.Forms.DockStyle.Fill;
            this.view_y.Location = new System.Drawing.Point(0, 0);
            this.view_y.Name = "view_y";
            this.view_y.Size = new System.Drawing.Size(269, 166);
            this.view_y.TabIndex = 0;
            this.view_y.TabStop = false;
            this.view_y.Click += new System.EventHandler(this.view_y_Click);
            this.view_y.MouseDown += new System.Windows.Forms.MouseEventHandler(this.view_y_MouseDown);
            this.view_y.MouseMove += new System.Windows.Forms.MouseEventHandler(this.view_y_MouseMove);
            this.view_y.MouseUp += new System.Windows.Forms.MouseEventHandler(this.view_y_MouseUp);
            // 
            // view_z
            // 
            this.view_z.Dock = System.Windows.Forms.DockStyle.Fill;
            this.view_z.Location = new System.Drawing.Point(0, 0);
            this.view_z.Name = "view_z";
            this.view_z.Size = new System.Drawing.Size(269, 167);
            this.view_z.TabIndex = 0;
            this.view_z.TabStop = false;
            this.view_z.Click += new System.EventHandler(this.view_z_Click);
            this.view_z.MouseDown += new System.Windows.Forms.MouseEventHandler(this.view_z_MouseDown);
            this.view_z.MouseMove += new System.Windows.Forms.MouseEventHandler(this.view_z_MouseMove);
            this.view_z.MouseUp += new System.Windows.Forms.MouseEventHandler(this.view_z_MouseUp);
            // 
            // select_toolstrip
            // 
            this.select_toolstrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.select_toolstrip.Image = global::client.Properties.Resources.pointer_btn;
            this.select_toolstrip.ImageTransparentColor = System.Drawing.Color.Red;
            this.select_toolstrip.Name = "select_toolstrip";
            this.select_toolstrip.Size = new System.Drawing.Size(23, 22);
            this.select_toolstrip.Text = "Select";
            this.select_toolstrip.Click += new System.EventHandler(this.toolStripButton2_Click);
            // 
            // move_toolstrip
            // 
            this.move_toolstrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.move_toolstrip.Enabled = false;
            this.move_toolstrip.Image = global::client.Properties.Resources.drag_btn;
            this.move_toolstrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.move_toolstrip.Name = "move_toolstrip";
            this.move_toolstrip.Size = new System.Drawing.Size(23, 22);
            this.move_toolstrip.Text = "Move";
            this.move_toolstrip.Click += new System.EventHandler(this.toolStripButton3_Click);
            // 
            // resize_toolstrip
            // 
            this.resize_toolstrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.resize_toolstrip.Enabled = false;
            this.resize_toolstrip.Image = global::client.Properties.Resources.resize_btn;
            this.resize_toolstrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.resize_toolstrip.Name = "resize_toolstrip";
            this.resize_toolstrip.Size = new System.Drawing.Size(23, 22);
            this.resize_toolstrip.Text = "Resize";
            this.resize_toolstrip.Click += new System.EventHandler(this.toolStripButton4_Click);
            // 
            // zoomin_toolstrip
            // 
            this.zoomin_toolstrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.zoomin_toolstrip.Image = global::client.Properties.Resources.zoomin_btn;
            this.zoomin_toolstrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.zoomin_toolstrip.Name = "zoomin_toolstrip";
            this.zoomin_toolstrip.Size = new System.Drawing.Size(23, 22);
            this.zoomin_toolstrip.Text = "Zoom In";
            this.zoomin_toolstrip.Click += new System.EventHandler(this.zoomin_toolstrip_Click);
            // 
            // zoomout_toolstrip
            // 
            this.zoomout_toolstrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.zoomout_toolstrip.Image = global::client.Properties.Resources.zoomout_btn;
            this.zoomout_toolstrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.zoomout_toolstrip.Name = "zoomout_toolstrip";
            this.zoomout_toolstrip.Size = new System.Drawing.Size(23, 22);
            this.zoomout_toolstrip.Text = "Zoom Out";
            this.zoomout_toolstrip.Click += new System.EventHandler(this.zoomout_toolstrip_Click);
            // 
            // sphere_toolstrip
            // 
            this.sphere_toolstrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.sphere_toolstrip.Image = global::client.Properties.Resources.circle_btn;
            this.sphere_toolstrip.ImageTransparentColor = System.Drawing.Color.White;
            this.sphere_toolstrip.Name = "sphere_toolstrip";
            this.sphere_toolstrip.Size = new System.Drawing.Size(23, 22);
            this.sphere_toolstrip.Text = "Sphere";
            this.sphere_toolstrip.Click += new System.EventHandler(this.toolStripButton1_Click);
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Image = global::client.Properties.Resources.red;
            this.toolStripStatusLabel1.Margin = new System.Windows.Forms.Padding(10, 3, 20, 2);
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(95, 17);
            this.toolStripStatusLabel1.Text = "Disconnected";
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(149, 6);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.saveToolStripMenuItem.Text = "Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.loadToolStripMenuItem.Text = "Load";
            this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Enabled = false;
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.saveAsToolStripMenuItem.Text = "Save As";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(750, 416);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.KeyPreview = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Distributed RayTracer";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainForm_KeyDown);
            this.Resize += new System.EventHandler(this.MainForm_Resize);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.panel4.ResumeLayout(false);
            this.panel5.ResumeLayout(false);
            this.panel7.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel9.ResumeLayout(false);
            this.panel8.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.view_x)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.view_y)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.view_z)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem quitToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripProgressBar toolStripProgressBar1;
        private System.Windows.Forms.ToolStripButton sphere_toolstrip;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton select_toolstrip;
        private System.Windows.Forms.ToolStripStatusLabel draw_status;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.PictureBox view_x;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.PictureBox view_y;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Panel panel7;
        private System.Windows.Forms.PictureBox view_z;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel9;
        private System.Windows.Forms.Panel panel8;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        public System.Windows.Forms.ToolStripButton move_toolstrip;
        public System.Windows.Forms.ToolStripButton resize_toolstrip;
        public System.Windows.Forms.PropertyGrid propertyGrid;
        private System.Windows.Forms.ToolStripButton zoomin_toolstrip;
        private System.Windows.Forms.ToolStripButton zoomout_toolstrip;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        public System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
    }
}

