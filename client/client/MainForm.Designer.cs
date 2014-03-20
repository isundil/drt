namespace client
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
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.quitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.projectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.connectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.redraw3DToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.progressbar = new System.Windows.Forms.ToolStripProgressBar();
            this.toolStripStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.draw_status = new System.Windows.Forms.ToolStripStatusLabel();
            this.errorlabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.select_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.move_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.resize_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.rotate_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.zoomin_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.zoomout_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.light_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.sphere_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.cylinder_toolstrip = new System.Windows.Forms.ToolStripButton();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.view_x = new System.Windows.Forms.PictureBox();
            this.panel5 = new System.Windows.Forms.Panel();
            this.view_y = new System.Windows.Forms.PictureBox();
            this.panel6 = new System.Windows.Forms.Panel();
            this.view_3d = new System.Windows.Forms.PictureBox();
            this.panel7 = new System.Windows.Forms.Panel();
            this.view_z = new System.Windows.Forms.PictureBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel9 = new System.Windows.Forms.Panel();
            this.panel10 = new System.Windows.Forms.Panel();
            this.monitoring1 = new client.Monitoring();
            this.propertyGrid = new System.Windows.Forms.PropertyGrid();
            this.panel8 = new System.Windows.Forms.Panel();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.show_server_mapping = new System.Windows.Forms.CheckBox();
            this.calculusWorker = new client.CalculusWorker();
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel3.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.panel4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.view_x)).BeginInit();
            this.panel5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.view_y)).BeginInit();
            this.panel6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.view_3d)).BeginInit();
            this.panel7.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.view_z)).BeginInit();
            this.panel2.SuspendLayout();
            this.panel9.SuspendLayout();
            this.panel10.SuspendLayout();
            this.panel8.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.projectToolStripMenuItem,
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
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.saveToolStripMenuItem.Text = "&Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Enabled = false;
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.S)));
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.saveAsToolStripMenuItem.Text = "Save &As";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.L)));
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.loadToolStripMenuItem.Text = "&Load";
            this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(183, 6);
            // 
            // quitToolStripMenuItem
            // 
            this.quitToolStripMenuItem.Name = "quitToolStripMenuItem";
            this.quitToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.quitToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.quitToolStripMenuItem.Text = "&Quit";
            this.quitToolStripMenuItem.Click += new System.EventHandler(this.quitToolStripMenuItem_Click);
            // 
            // projectToolStripMenuItem
            // 
            this.projectToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.connectToolStripMenuItem,
            this.redraw3DToolStripMenuItem});
            this.projectToolStripMenuItem.Name = "projectToolStripMenuItem";
            this.projectToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.projectToolStripMenuItem.Text = "&Project";
            // 
            // connectToolStripMenuItem
            // 
            this.connectToolStripMenuItem.Name = "connectToolStripMenuItem";
            this.connectToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F9;
            this.connectToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.connectToolStripMenuItem.Text = "&Connect to server";
            this.connectToolStripMenuItem.Click += new System.EventHandler(this.connectToolStripMenuItem_Click);
            // 
            // redraw3DToolStripMenuItem
            // 
            this.redraw3DToolStripMenuItem.Name = "redraw3DToolStripMenuItem";
            this.redraw3DToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F5;
            this.redraw3DToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.redraw3DToolStripMenuItem.Text = "&Redraw 3D";
            this.redraw3DToolStripMenuItem.Click += new System.EventHandler(this.redraw3DToolStripMenuItem_Click);
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.aboutToolStripMenuItem.Text = "&About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.progressbar,
            this.toolStripStatusLabel,
            this.draw_status,
            this.errorlabel});
            this.statusStrip1.Location = new System.Drawing.Point(0, 390);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(750, 26);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // progressbar
            // 
            this.progressbar.Name = "progressbar";
            this.progressbar.Size = new System.Drawing.Size(120, 20);
            this.progressbar.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            // 
            // toolStripStatusLabel
            // 
            this.toolStripStatusLabel.Image = global::client.Properties.Resources.red;
            this.toolStripStatusLabel.Margin = new System.Windows.Forms.Padding(10, 3, 20, 2);
            this.toolStripStatusLabel.Name = "toolStripStatusLabel";
            this.toolStripStatusLabel.Size = new System.Drawing.Size(95, 21);
            this.toolStripStatusLabel.Text = "Disconnected";
            // 
            // draw_status
            // 
            this.draw_status.Name = "draw_status";
            this.draw_status.Size = new System.Drawing.Size(0, 21);
            // 
            // errorlabel
            // 
            this.errorlabel.Name = "errorlabel";
            this.errorlabel.Size = new System.Drawing.Size(0, 21);
            // 
            // toolStrip1
            // 
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.select_toolstrip,
            this.move_toolstrip,
            this.resize_toolstrip,
            this.rotate_toolstrip,
            this.toolStripSeparator1,
            this.zoomin_toolstrip,
            this.zoomout_toolstrip,
            this.toolStripSeparator2,
            this.light_toolstrip,
            this.sphere_toolstrip,
            this.cylinder_toolstrip});
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.toolStrip1.Size = new System.Drawing.Size(750, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "Pointer";
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
            // rotate_toolstrip
            // 
            this.rotate_toolstrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.rotate_toolstrip.Image = global::client.Properties.Resources.rotate_btn;
            this.rotate_toolstrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.rotate_toolstrip.Name = "rotate_toolstrip";
            this.rotate_toolstrip.Size = new System.Drawing.Size(23, 22);
            this.rotate_toolstrip.Text = "toolStripButton2";
            this.rotate_toolstrip.Click += new System.EventHandler(this.rotate_toolstrip_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
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
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // light_toolstrip
            // 
            this.light_toolstrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.light_toolstrip.Image = global::client.Properties.Resources.light_btn;
            this.light_toolstrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.light_toolstrip.Name = "light_toolstrip";
            this.light_toolstrip.Size = new System.Drawing.Size(23, 22);
            this.light_toolstrip.Text = "toolStripButton1";
            this.light_toolstrip.Click += new System.EventHandler(this.light_toolstrip_Click);
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
            // cylinder_toolstrip
            // 
            this.cylinder_toolstrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cylinder_toolstrip.Image = global::client.Properties.Resources.cylinder_btn;
            this.cylinder_toolstrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cylinder_toolstrip.Name = "cylinder_toolstrip";
            this.cylinder_toolstrip.Size = new System.Drawing.Size(23, 22);
            this.cylinder_toolstrip.Text = "toolStripButton2";
            this.cylinder_toolstrip.Click += new System.EventHandler(this.cylinder_toolstrip_Click);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.panel3);
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 49);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(750, 341);
            this.panel1.TabIndex = 3;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.tableLayoutPanel1);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(0, 0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(550, 341);
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
            this.tableLayoutPanel1.Size = new System.Drawing.Size(550, 341);
            this.tableLayoutPanel1.TabIndex = 5;
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.view_x);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel4.Location = new System.Drawing.Point(3, 3);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(269, 164);
            this.panel4.TabIndex = 0;
            // 
            // view_x
            // 
            this.view_x.Dock = System.Windows.Forms.DockStyle.Fill;
            this.view_x.Location = new System.Drawing.Point(0, 0);
            this.view_x.Name = "view_x";
            this.view_x.Size = new System.Drawing.Size(269, 164);
            this.view_x.TabIndex = 0;
            this.view_x.TabStop = false;
            this.view_x.Click += new System.EventHandler(this.view_x_Click);
            this.view_x.MouseDown += new System.Windows.Forms.MouseEventHandler(this.view_x_MouseDown);
            this.view_x.MouseMove += new System.Windows.Forms.MouseEventHandler(this.view_x_MouseMove);
            this.view_x.MouseUp += new System.Windows.Forms.MouseEventHandler(this.view_x_MouseUp);
            // 
            // panel5
            // 
            this.panel5.Controls.Add(this.view_y);
            this.panel5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel5.Location = new System.Drawing.Point(278, 3);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(269, 164);
            this.panel5.TabIndex = 1;
            // 
            // view_y
            // 
            this.view_y.Dock = System.Windows.Forms.DockStyle.Fill;
            this.view_y.Location = new System.Drawing.Point(0, 0);
            this.view_y.Name = "view_y";
            this.view_y.Size = new System.Drawing.Size(269, 164);
            this.view_y.TabIndex = 0;
            this.view_y.TabStop = false;
            this.view_y.Click += new System.EventHandler(this.view_y_Click);
            this.view_y.MouseDown += new System.Windows.Forms.MouseEventHandler(this.view_y_MouseDown);
            this.view_y.MouseMove += new System.Windows.Forms.MouseEventHandler(this.view_y_MouseMove);
            this.view_y.MouseUp += new System.Windows.Forms.MouseEventHandler(this.view_y_MouseUp);
            // 
            // panel6
            // 
            this.panel6.Controls.Add(this.view_3d);
            this.panel6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel6.Location = new System.Drawing.Point(3, 173);
            this.panel6.Name = "panel6";
            this.panel6.Size = new System.Drawing.Size(269, 165);
            this.panel6.TabIndex = 2;
            // 
            // view_3d
            // 
            this.view_3d.Dock = System.Windows.Forms.DockStyle.Fill;
            this.view_3d.Location = new System.Drawing.Point(0, 0);
            this.view_3d.Name = "view_3d";
            this.view_3d.Size = new System.Drawing.Size(269, 165);
            this.view_3d.TabIndex = 0;
            this.view_3d.TabStop = false;
            // 
            // panel7
            // 
            this.panel7.Controls.Add(this.view_z);
            this.panel7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel7.Location = new System.Drawing.Point(278, 173);
            this.panel7.Name = "panel7";
            this.panel7.Size = new System.Drawing.Size(269, 165);
            this.panel7.TabIndex = 3;
            // 
            // view_z
            // 
            this.view_z.Dock = System.Windows.Forms.DockStyle.Fill;
            this.view_z.Location = new System.Drawing.Point(0, 0);
            this.view_z.Name = "view_z";
            this.view_z.Size = new System.Drawing.Size(269, 165);
            this.view_z.TabIndex = 0;
            this.view_z.TabStop = false;
            this.view_z.Click += new System.EventHandler(this.view_z_Click);
            this.view_z.MouseDown += new System.Windows.Forms.MouseEventHandler(this.view_z_MouseDown);
            this.view_z.MouseMove += new System.Windows.Forms.MouseEventHandler(this.view_z_MouseMove);
            this.view_z.MouseUp += new System.Windows.Forms.MouseEventHandler(this.view_z_MouseUp);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.panel9);
            this.panel2.Controls.Add(this.panel8);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel2.Location = new System.Drawing.Point(550, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(200, 341);
            this.panel2.TabIndex = 0;
            // 
            // panel9
            // 
            this.panel9.Controls.Add(this.panel10);
            this.panel9.Controls.Add(this.propertyGrid);
            this.panel9.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel9.Location = new System.Drawing.Point(0, 21);
            this.panel9.Name = "panel9";
            this.panel9.Size = new System.Drawing.Size(200, 320);
            this.panel9.TabIndex = 1;
            // 
            // panel10
            // 
            this.panel10.Controls.Add(this.monitoring1);
            this.panel10.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel10.Location = new System.Drawing.Point(0, 261);
            this.panel10.Name = "panel10";
            this.panel10.Size = new System.Drawing.Size(200, 59);
            this.panel10.TabIndex = 1;
            // 
            // monitoring1
            // 
            this.monitoring1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.monitoring1.Location = new System.Drawing.Point(0, 0);
            this.monitoring1.Name = "monitoring1";
            this.monitoring1.Size = new System.Drawing.Size(200, 59);
            this.monitoring1.TabIndex = 0;
            // 
            // propertyGrid
            // 
            this.propertyGrid.CommandsVisibleIfAvailable = false;
            this.propertyGrid.Dock = System.Windows.Forms.DockStyle.Fill;
            this.propertyGrid.Location = new System.Drawing.Point(0, 0);
            this.propertyGrid.Name = "propertyGrid";
            this.propertyGrid.PropertySort = System.Windows.Forms.PropertySort.NoSort;
            this.propertyGrid.Size = new System.Drawing.Size(200, 320);
            this.propertyGrid.TabIndex = 0;
            this.propertyGrid.ToolbarVisible = false;
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
            // show_server_mapping
            // 
            this.show_server_mapping.AutoSize = true;
            this.show_server_mapping.Location = new System.Drawing.Point(278, 29);
            this.show_server_mapping.Name = "show_server_mapping";
            this.show_server_mapping.Size = new System.Drawing.Size(128, 17);
            this.show_server_mapping.TabIndex = 4;
            this.show_server_mapping.Text = "Show server mapping";
            this.show_server_mapping.UseVisualStyleBackColor = true;
            this.show_server_mapping.CheckedChanged += new System.EventHandler(this.show_server_mapping_CheckedChanged);
            // 
            // calculusWorker
            // 
            this.calculusWorker.Connection = null;
            this.calculusWorker.DestinationImage = null;
            this.calculusWorker.Offline = false;
            this.calculusWorker.WorkerReportsProgress = true;
            this.calculusWorker.WorkerSupportsCancellation = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(750, 416);
            this.Controls.Add(this.show_server_mapping);
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
            ((System.ComponentModel.ISupportInitialize)(this.view_x)).EndInit();
            this.panel5.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.view_y)).EndInit();
            this.panel6.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.view_3d)).EndInit();
            this.panel7.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.view_z)).EndInit();
            this.panel2.ResumeLayout(false);
            this.panel9.ResumeLayout(false);
            this.panel10.ResumeLayout(false);
            this.panel8.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem quitToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripProgressBar progressbar;
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
        private CalculusWorker calculusWorker;
        private System.Windows.Forms.ToolStripButton cylinder_toolstrip;
        public System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel;
        private System.Windows.Forms.ToolStripButton rotate_toolstrip;
        private System.Windows.Forms.PictureBox view_3d;
        public System.Windows.Forms.ToolStripStatusLabel errorlabel;
        private System.Windows.Forms.Panel panel10;
        private Monitoring monitoring1;
        private System.Windows.Forms.CheckBox show_server_mapping;
        private System.Windows.Forms.ToolStripMenuItem projectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem connectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem redraw3DToolStripMenuItem;
        private System.Windows.Forms.ToolStripButton light_toolstrip;
    }
}

