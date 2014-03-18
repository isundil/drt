﻿using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace client
{
    public partial class MainForm : Form
    {
        Viewport vp = new Viewport();
        ObjectsList ol;
        public ConClient client;

        public MainForm()
        {
            InitializeComponent();

            this.Icon = Properties.Resources.icon;
            this.Cursor = new Cursor(Properties.Resources.pointer_ptr.GetHicon());

            ol = new ObjectsList(this);

            comboBox1.DataSource = ol.Collection;
            comboBox1.DisplayMember = "Name";
            comboBox1.ValueMember = "Id";
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void empty_bitmap(System.Drawing.Bitmap bm)
        {
            using (var g = System.Drawing.Graphics.FromImage(bm))
            {
                g.Clear(Color.Black);
            }
        }

        private void draw_grid_x(System.Drawing.Bitmap bm)
        {
            empty_bitmap(bm);

            using (var g = System.Drawing.Graphics.FromImage(bm))
            {
                using (var p = new Pen(Color.FromArgb(25, 25, 25)))
                {
                    var dw = bm.Width / 2;
                    var dh = bm.Height / 2;

                    for (int x = dw + vp.ox.Y; x < bm.Width; x += (int)(vp.GridLevel * vp.fx)) g.DrawLine(p, new Point(x, 0), new Point(x, bm.Height - 1));
                    for (int x = dw + vp.ox.Y; x > 0; x -= (int)(vp.GridLevel * vp.fx)) g.DrawLine(p, new Point(x, 0), new Point(x, bm.Height - 1));
                    for (int y = dh + vp.ox.Z; y < bm.Height; y += (int)(vp.GridLevel * vp.fx)) g.DrawLine(p, new Point(0, y), new Point(bm.Width - 1, y));
                    for (int y = dh + vp.ox.Z; y > 0; y -= (int)(vp.GridLevel * vp.fx)) g.DrawLine(p, new Point(0, y), new Point(bm.Width - 1, y));
                }

                using (var p = new Pen(Color.FromArgb(35, 35, 35)))
                {
                    g.DrawLine(p, new Point(bm.Width / 2 + vp.ox.Y, 0), new Point(bm.Width / 2 + vp.ox.Y, bm.Height));
                    g.DrawLine(p, new Point(0, bm.Height / 2 + vp.ox.Z), new Point(bm.Width, bm.Height / 2 + vp.ox.Z));
                }

                g.DrawString("x" + vp.fx, new Font(new FontFamily("Arial"), 10, FontStyle.Bold), new SolidBrush(Color.White), 0, bm.Height - 16);
            }
        }
        private void draw_grid_y(System.Drawing.Bitmap bm)
        {
            empty_bitmap(bm);

            using (var g = System.Drawing.Graphics.FromImage(bm))
            {
                using (var p = new Pen(Color.FromArgb(25, 25, 25)))
                {
                    var dw = bm.Width / 2;
                    var dh = bm.Height / 2;

                    for (int x = dw + vp.oy.X; x < bm.Width; x += (int)(vp.GridLevel * vp.fy)) g.DrawLine(p, new Point(x, 0), new Point(x, bm.Height - 1));
                    for (int x = dw + vp.oy.X; x > 0; x -= (int)(vp.GridLevel * vp.fy)) g.DrawLine(p, new Point(x, 0), new Point(x, bm.Height - 1));
                    for (int y = dh + vp.oy.Z; y < bm.Height; y += (int)(vp.GridLevel * vp.fy)) g.DrawLine(p, new Point(0, y), new Point(bm.Width - 1, y));
                    for (int y = dh + vp.oy.Z; y > 0; y -= (int)(vp.GridLevel * vp.fy)) g.DrawLine(p, new Point(0, y), new Point(bm.Width - 1, y));
                }

                using (var p = new Pen(Color.FromArgb(35, 35, 35)))
                {
                    g.DrawLine(p, new Point(bm.Width / 2 + vp.oy.X, 0), new Point(bm.Width / 2 + vp.oy.X, bm.Height));
                    g.DrawLine(p, new Point(0, bm.Height / 2 + vp.oy.Z), new Point(bm.Width, bm.Height / 2 + vp.oy.Z));
                }

                g.DrawString("x" + vp.fy, new Font(new FontFamily("Arial"), 10, FontStyle.Bold), new SolidBrush(Color.White), 0, bm.Height - 16);
            }
        }
        private void draw_grid_z(System.Drawing.Bitmap bm)
        {
            empty_bitmap(bm);

            using (var g = System.Drawing.Graphics.FromImage(bm))
            {
                using (var p = new Pen(Color.FromArgb(25, 25, 25)))
                {
                    var dw = bm.Width / 2;
                    var dh = bm.Height / 2;

                    for (int x = dw + vp.oz.X; x < bm.Width; x += (int)(vp.GridLevel * vp.fz)) g.DrawLine(p, new Point(x, 0), new Point(x, bm.Height - 1));
                    for (int x = dw + vp.oz.X; x > 0; x -= (int)(vp.GridLevel * vp.fz)) g.DrawLine(p, new Point(x, 0), new Point(x, bm.Height - 1));
                    for (int y = dh + vp.oz.Y; y < bm.Height; y += (int)(vp.GridLevel * vp.fz)) g.DrawLine(p, new Point(0, y), new Point(bm.Width - 1, y));
                    for (int y = dh + vp.oz.Y; y > 0; y -= (int)(vp.GridLevel * vp.fz)) g.DrawLine(p, new Point(0, y), new Point(bm.Width - 1, y));
                }

                using (var p = new Pen(Color.FromArgb(35, 35, 35)))
                {
                    g.DrawLine(p, new Point(bm.Width / 2 + vp.oz.X, 0), new Point(bm.Width / 2 + vp.oz.X, bm.Height));
                    g.DrawLine(p, new Point(0, bm.Height / 2 + vp.oz.Y), new Point(bm.Width, bm.Height / 2 + vp.oz.Y));
                }

                g.DrawString("x" + vp.fz, new Font(new FontFamily("Arial"), 10, FontStyle.Bold), new SolidBrush(Color.White), 0, bm.Height - 16);
            }
        }

        Bitmap td_bitmap;
        bool finished_3d_drawing = true;
        bool request_new_drawing = false;
        private void redraw(bool rebuild_3d = false)
        {
            var bm_x = new System.Drawing.Bitmap(view_x.InitialImage, view_x.Size);
            draw_grid_x(bm_x);

            var bm_y = new System.Drawing.Bitmap(view_x.InitialImage, view_y.Size);
            draw_grid_y(bm_y);

            var bm_z = new System.Drawing.Bitmap(view_x.InitialImage, view_z.Size);
            draw_grid_z(bm_z);

            foreach (var o in ol.Collection)
            {
                o.draw_x(bm_x, vp, (o == ol.Selected));
                o.draw_y(bm_y, vp, (o == ol.Selected));
                o.draw_z(bm_z, vp, (o == ol.Selected));
            }

            view_x.Image = bm_x;
            view_y.Image = bm_y;
            view_z.Image = bm_z;
            if (rebuild_3d == true && request_new_drawing == false && finished_3d_drawing == true)
            {
                finished_3d_drawing = false;
                show_server_mapping.Enabled = false;
                show_server_mapping.Checked = false;
                servers_map.Clear();
                progressbar.Value = 0;
                progressbar.Maximum = view_3d.Width * view_3d.Height;
                calculusWorker.DestinationImage = view_3d.Image;
                calculusWorker.DoScenePreviewCalculus(ol);
            }
            else if (rebuild_3d == true && finished_3d_drawing == false)
            {
                request_new_drawing = true;
            }
        }

        private ListenerWorker listenerWorker = null;
        public delegate void ConnectDelegate();
        public ConnectDelegate Connect;
        public delegate void DrawPixelDelegate(ushort src, int x, int y, Color c);
        public DrawPixelDelegate DrawPixel;
        public delegate void MonitorDelegate(byte cpu, UInt32 ramuse, UInt32 rammax);
        public MonitorDelegate Monitor;

        private void ShowConnection()
        {
            var con = new Connection();
            if (con.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                Properties.Settings.Default.Save();
            }
        }

        private void UpdateMonitor(byte cpu, UInt32 ramuse, UInt32 rammax)
        {
            monitoring1.UpdateMonitor(cpu, ramuse, rammax);
        }

        static int DrawPixel3DView_count = 0;

        Dictionary<ushort, int> servers_map = new Dictionary<ushort,int>();

        private void DrawPixel3DView(ushort src, int x, int y, Color c)
        {
            if (x >= td_bitmap.Width || y >= td_bitmap.Height) return;
            td_bitmap.SetPixel(x, y, c);

            if (servers_map.ContainsKey(src))
            {
                servers_map[src]++;
            }
            else
            {
                servers_map[src] = 1;
            }

            DrawPixel3DView_count++;
            progressbar.Value = DrawPixel3DView_count;

            if (DrawPixel3DView_count % 100 == 0 || DrawPixel3DView_count == progressbar.Maximum)
            {
                view_3d.Refresh();
            }
            if (DrawPixel3DView_count == progressbar.Maximum)
            {
                DrawPixel3DView_count = 0;
                progressbar.Value = 0;
                show_server_mapping.Enabled = true;

                finished_3d_drawing = true;
                if (request_new_drawing == true)
                {
                    request_new_drawing = false;
                    redraw(ol.Collection.Count > 1 ? true : false);
                }
            }
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            vp.GridLevel = 10;
            this.Connect = new ConnectDelegate(ShowConnection);
            this.DrawPixel = new DrawPixelDelegate(DrawPixel3DView);
            this.Monitor = new MonitorDelegate(UpdateMonitor);

            td_bitmap = new Bitmap(view_3d.Width, view_3d.Height);
            empty_bitmap(td_bitmap);
            view_3d.Image = td_bitmap;

            this.client = new ConClient();
            this.listenerWorker = new ListenerWorker(client, this);
            this.listenerWorker.WorkerSupportsCancellation = true;
            this.listenerWorker.RunWorkerAsync();
            
            calculusWorker.Connection = client;
            calculusWorker.DestinationImage = view_3d.Image;

            ol.Add(new Camera());
            ol.Selected = ol.Collection[0];
            redraw(false);

            show_server_mapping.Enabled = false;
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            td_bitmap = new Bitmap(view_3d.Width, view_3d.Height);
            empty_bitmap(td_bitmap);
            view_3d.Image = td_bitmap;

            redraw(ol.Collection.Count > 1 ? true : false);
        }

        enum eDrawMode
        {
            SPHERE,
            CYLINDER,
            NONE,
            GRAB,
            RESIZE,
            ZOOMIN,
            ZOOMOUT,
            ROTATE
        };
        eDrawMode drawMode = eDrawMode.NONE;

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.SPHERE;

            this.Cursor = new Cursor(Properties.Resources.circle_ptr.GetHicon());
        }

        private void cylinder_toolstrip_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.CYLINDER;

            this.Cursor = new Cursor(Properties.Resources.cylinder_ptr.GetHicon());
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.NONE;

            this.Cursor = new Cursor(Properties.Resources.pointer_ptr.GetHicon());
        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.GRAB;

            this.Cursor = new Cursor(Properties.Resources.drag_ptr.GetHicon());
        }

        private void toolStripButton4_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.RESIZE;

            this.Cursor = new Cursor(Properties.Resources.resize_ptr.GetHicon());
        }

        private void rotate_toolstrip_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.ROTATE;

            this.Cursor = new Cursor(Properties.Resources.rotate_ptr.GetHicon());
        }

        private void zoomin_toolstrip_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.ZOOMIN;

            this.Cursor = new Cursor(Properties.Resources.zoomin_ptr.GetHicon());
        }

        private void zoomout_toolstrip_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.ZOOMOUT;

            this.Cursor = new Cursor(Properties.Resources.zoomout_ptr.GetHicon());
        }

        Points p1, p2;

        private void save_views()
        {
            this.view_x_cp = this.view_x.Image;
            this.view_y_cp = this.view_y.Image;
            this.view_z_cp = this.view_z.Image;
        }

        private void view_x_MouseDown(object sender, MouseEventArgs e)
        {
            p1 = new Points();

            p1.X = 0;
            p1.Y = e.X;
            p1.Z = e.Y;

            Util.convertToMy(p1, vp, view_x.Image, Util.eView.x);

            if (this.drawMode == eDrawMode.NONE)
            {
                foreach (var o in ol.Collection)
                {
                    if (o.solve_equation_x(p1))
                    {
                        ol.Selected = o;
                        redraw(false);
                    }
                }

                return;
            }
            if (this.drawMode == eDrawMode.GRAB) return;

            save_views();
        }
        private void view_y_MouseDown(object sender, MouseEventArgs e)
        {
            p1 = new Points();

            p1.X = e.X;
            p1.Y = 0;
            p1.Z = e.Y;

            Util.convertToMy(p1, vp, view_y.Image, Util.eView.y);

            if (this.drawMode == eDrawMode.NONE)
            {
                foreach (var o in ol.Collection)
                {
                    if (o.solve_equation_y(p1))
                    {
                        ol.Selected = o;
                        redraw(false);
                    }
                }

                return;
            }
            save_views();
        }
        private void view_z_MouseDown(object sender, MouseEventArgs e)
        {
            p1 = new Points();

            p1.X = e.X;
            p1.Y = e.Y;
            p1.Z = 0;

            Util.convertToMy(p1, vp, view_z.Image, Util.eView.z);

            if (this.drawMode == eDrawMode.NONE)
            {
                foreach (var o in ol.Collection)
                {
                    if (o.solve_equation_z(p1))
                    {
                        ol.Selected = o;
                        redraw(false);
                    }
                }

                return;
            }
            save_views();
        }

        private void view_x_MouseUp(object sender, MouseEventArgs e)
        {
            if (this.drawMode == eDrawMode.NONE || p1 == null) return;
            _tmpObject = null;

            p2 = new Points();

            p2.X = 0;
            p2.Y = e.X;
            p2.Z = e.Y;

            Util.convertToMy(p2, vp, view_x.Image, Util.eView.x);

            AObjects s = null;
            switch (this.drawMode)
            {
                case eDrawMode.SPHERE:
                    s = Sphere.create_x((Points)p1.Clone(), (Points)p2.Clone(), vp);
                    break;
                case eDrawMode.CYLINDER:
                    s = Cylinder.create_x((Points)p1.Clone(), (Points)p2.Clone(), vp);
                    break;
            }
            if (s != null)
            {
                ol.Add(s);
                ol.Selected = s;
            }

            redraw(true);
            propertyGrid.Refresh();
        }
        private void view_y_MouseUp(object sender, MouseEventArgs e)
        {
            if (this.drawMode == eDrawMode.NONE || p1 == null) return;
            _tmpObject = null;

            p2 = new Points();

            p2.X = e.X;
            p2.Y = 0;
            p2.Z = e.Y;

            Util.convertToMy(p2, vp, view_y.Image, Util.eView.y);

            AObjects s = null;
            switch (this.drawMode)
            {
                case eDrawMode.SPHERE:
                    s = Sphere.create_y((Points)p1.Clone(), (Points)p2.Clone(), vp);
                    break;
                case eDrawMode.CYLINDER:
                    s = Cylinder.create_y((Points)p1.Clone(), (Points)p2.Clone(), vp);
                    break;
            }
            if (s != null)
            {
                ol.Add(s);
                ol.Selected = s;
            }

            redraw(true);
            propertyGrid.Refresh();
        }
        private void view_z_MouseUp(object sender, MouseEventArgs e)
        {
            if (this.drawMode == eDrawMode.NONE || p1 == null) return;
            _tmpObject = null;

            p2 = new Points();

            p2.X = e.X;
            p2.Y = e.Y;
            p2.Z = 0;

            Util.convertToMy(p2, vp, view_z.Image, Util.eView.z);

            AObjects s = null;
            switch (this.drawMode)
            {
                case eDrawMode.SPHERE:
                    s = Sphere.create_z((Points)p1.Clone(), (Points)p2.Clone(), vp);
                    break;
                case eDrawMode.CYLINDER:
                    s = Cylinder.create_z((Points)p1.Clone(), (Points)p2.Clone(), vp);
                    break;
            }
            if (s != null)
            {
                ol.Add(s);
                ol.Selected = s;
            }

            redraw(true);
            propertyGrid.Refresh();
        }

        AObjects _tmpObject = null;
        private bool drawTmpObject(MouseEventArgs e, Points p3, Util.eView v)
        {
            draw_status.Text = "Coords { X : " + p3.X + ", Y : " + p3.Y + ", Z : " + p3.Z + " }";

            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode < eDrawMode.NONE)
            {
                var vx = new System.Drawing.Bitmap(view_x_cp, view_x_cp.Size);
                var vy = new System.Drawing.Bitmap(view_y_cp, view_y_cp.Size);
                var vz = new System.Drawing.Bitmap(view_z_cp, view_z_cp.Size);

                switch (this.drawMode)
                {
                    case eDrawMode.SPHERE:
                        if (_tmpObject != null)
                        {
                            _tmpObject.Radius = (int)Math.Sqrt(Math.Pow(p3.Y - _tmpObject.centerPoint.Y, 2) + Math.Pow(p3.Z - _tmpObject.centerPoint.Z, 2));
                        }
                        else
                        {
                            if (v == Util.eView.x) _tmpObject = Sphere.create_x((Points)p1.Clone(), (Points)p3.Clone(), vp, true);
                            if (v == Util.eView.y) _tmpObject = Sphere.create_y((Points)p1.Clone(), (Points)p3.Clone(), vp, true);
                            if (v == Util.eView.z) _tmpObject = Sphere.create_z((Points)p1.Clone(), (Points)p3.Clone(), vp, true);
                        }

                        draw_status.Text += ", Sphere { Cx : " + _tmpObject.centerPoint.X + ", Cy : " + _tmpObject.centerPoint.Y + ", Cz : " + _tmpObject.centerPoint.Z + ", R : " + _tmpObject.Radius + " }";
                        break;
                    case eDrawMode.CYLINDER:
                        if (_tmpObject != null)
                        {
                            _tmpObject.Radius = (int)Math.Sqrt(Math.Pow(p3.Y - _tmpObject.centerPoint.Y, 2) + Math.Pow(p3.Z - _tmpObject.centerPoint.Z, 2));
                        }
                        else
                        {
                            if (v == Util.eView.x) _tmpObject = Cylinder.create_x((Points)p1.Clone(), (Points)p3.Clone(), vp, true);
                            if (v == Util.eView.y) _tmpObject = Cylinder.create_y((Points)p1.Clone(), (Points)p3.Clone(), vp, true);
                            if (v == Util.eView.z) _tmpObject = Cylinder.create_z((Points)p1.Clone(), (Points)p3.Clone(), vp, true);
                        }

                        draw_status.Text += ", Cylinder { Cx : " + _tmpObject.centerPoint.X + ", Cy : " + _tmpObject.centerPoint.Y + ", Cz : " + _tmpObject.centerPoint.Z + ", R : " + _tmpObject.Radius + " }";
                        break;
                }

                _tmpObject.Refresh();

                _tmpObject.draw_x(vx, vp, true);
                _tmpObject.draw_y(vy, vp, true);
                _tmpObject.draw_z(vz, vp, true);
                        
                view_x.Image = vx;
                view_y.Image = vy;
                view_z.Image = vz;

                return true;
            }

            return false;
        }

        private void view_x_MouseMove(object sender, MouseEventArgs e)
        {
            Points p3 = new Points() { Y = e.X, Z = e.Y };

            Util.convertToMy(p3, vp, view_x.Image, Util.eView.x);

            drawTmpObject(e, p3, Util.eView.x);
            if (p1 == null) return;

            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.NONE)
            {
                vp.ox.Y += (int)((p3.Y - p1.Y) * vp.fx);
                vp.ox.Z += -(int)((p3.Z - p1.Z) * vp.fx);

                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.GRAB)
            {
                if (ol.Selected == null) return;

                ol.Selected.centerPoint.Y = p3.Y;
                ol.Selected.centerPoint.Z = p3.Z;

                ol.Selected.Refresh();
                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.RESIZE)
            {
                if (ol.Selected == null) return;

                ol.Selected.Radius = (int)Math.Sqrt(Math.Pow(p3.Y - ol.Selected.centerPoint.Y, 2) + Math.Pow(p3.Z - ol.Selected.centerPoint.Z, 2));

                ol.Selected.Refresh();
                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.ROTATE)
            {
                var d = Math.Sqrt(Math.Pow(p3.Y - ol.Selected.Y, 2) + Math.Pow(p3.Z - ol.Selected.Z, 2));
                if (d == 0) return;
                var angle = Math.Acos((p3.Y - ol.Selected.Y) / d);

                ol.Selected.RotX = angle;

                ol.Selected.Refresh();
                redraw();
            }
        }
        private void view_y_MouseMove(object sender, MouseEventArgs e)
        {
            Points p3 = new Points() { X = e.X, Z = e.Y };

            Util.convertToMy(p3, vp, view_y.Image, Util.eView.y);

            drawTmpObject(e, p3, Util.eView.y);
            if (p1 == null) return;

            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.NONE)
            {
                vp.oy.X += (int)((p3.X - p1.X) * vp.fy);
                vp.oy.Z += -(int)((p3.Z - p1.Z) * vp.fy);

                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.GRAB)
            {
                if (ol.Selected == null) return;

                ol.Selected.centerPoint.X = p3.X;
                ol.Selected.centerPoint.Z = p3.Z;

                ol.Selected.Refresh();
                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.RESIZE)
            {
                if (ol.Selected == null) return;

                ol.Selected.Radius = (int)Math.Sqrt(Math.Pow(p3.X - ol.Selected.centerPoint.X, 2) + Math.Pow(p3.Z - ol.Selected.centerPoint.Z, 2));

                ol.Selected.Refresh();
                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.ROTATE)
            {
                var d = Math.Sqrt(Math.Pow(p3.X - ol.Selected.X, 2) + Math.Pow(p3.Z - ol.Selected.Z, 2));
                if (d == 0) return;
                var angle = Math.Acos((p3.X - ol.Selected.X) / d);

                ol.Selected.RotY = angle;

                ol.Selected.Refresh();
                redraw();
            }
        }
        private void view_z_MouseMove(object sender, MouseEventArgs e)
        {
            Points p3 = new Points() { X = e.X, Y = e.Y };

            Util.convertToMy(p3, vp, view_z.Image, Util.eView.z);

            drawTmpObject(e, p3, Util.eView.z);
            if (p1 == null) return;

            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.NONE)
            {
                vp.oz.X += (int)((p3.X - p1.X) * vp.fz);
                vp.oz.Y += -(int)((p3.Y - p1.Y) * vp.fz);

                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.GRAB)
            {
                if (ol.Selected == null) return;

                ol.Selected.centerPoint.X = p3.X;
                ol.Selected.centerPoint.Y = p3.Y;

                ol.Selected.Refresh();
                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.RESIZE)
            {
                if (ol.Selected == null) return;

                ol.Selected.Radius = (int)Math.Sqrt(Math.Pow(p3.X - ol.Selected.centerPoint.X, 2) + Math.Pow(p3.Y - ol.Selected.centerPoint.Y, 2));

                ol.Selected.Refresh();
                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.ROTATE)
            {
                var d = Math.Sqrt(Math.Pow(p3.X - ol.Selected.X, 2) + Math.Pow(p3.Y - ol.Selected.Y, 2));
                if (d == 0) return;
                var angle = Math.Acos((p3.X - ol.Selected.X) / d);

                ol.Selected.RotZ = angle;

                ol.Selected.Refresh();
                redraw();
            }
        }

        private Image view_x_cp { get; set; }
        private Image view_y_cp { get; set; }
        private Image view_z_cp { get; set; }

        private void MainForm_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                if (ol.Selected != null && ol.Selected != ol.Collection[0])
                {
                    ol.Remove(ol.Selected);
                    ol.Selected = null;
                    redraw(true);
                }
            }
        }

        private void view_x_Click(object sender, EventArgs e)
        {
            if (this.drawMode == eDrawMode.ZOOMIN)
            {
                if (vp.fx < 8) vp.fx *= 2;

                redraw(false);
            }
            if (this.drawMode == eDrawMode.ZOOMOUT)
            {
                if (vp.fx > 0.25F) vp.fx /= 2;

                redraw(false);
            }
        }
        private void view_y_Click(object sender, EventArgs e)
        {
            if (this.drawMode == eDrawMode.ZOOMIN)
            {
                if (vp.fy < 8) vp.fy *= 2;

                redraw(false);
            }
            if (this.drawMode == eDrawMode.ZOOMOUT)
            {
                if (vp.fy > 0.25F) vp.fy /= 2;

                redraw(false);
            }
        }
        private void view_z_Click(object sender, EventArgs e)
        {
            if (this.drawMode == eDrawMode.ZOOMIN)
            {
                if (vp.fz < 8) vp.fz *= 2;

                redraw(false);
            }
            if (this.drawMode == eDrawMode.ZOOMOUT)
            {
                if (vp.fz > 0.25F) vp.fz /= 2;

                redraw(false);
            }
        }

        private void propertyGrid_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            ol.Selected.Refresh();
            redraw(true);
        }

        private void comboBox1_SelectedValueChanged(object sender, EventArgs e)
        {
            var c = sender as ComboBox;
            if (c.SelectedIndex >= 0)
            {
                ol.Selected = ol.Collection[c.SelectedIndex];
                redraw(false);
            }
        }

        class Nfile
        {
            public string Nshort { get; set; }
            public string Nlong { get; set; }
        }
        Nfile currentfile = new Nfile();

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (currentfile.Nlong != null)
            {
                var x = new XmlSerializer(ol.GetType());
                TextWriter tw = new StreamWriter(currentfile.Nlong);
                try { x.Serialize(tw, ol); }
                catch { MessageBox.Show("An error occured saving the file"); }

                saveAsToolStripMenuItem.Enabled = true;
            }
            else
            {
                loadToolStripMenuItem_Click(sender, e);
            }
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var x = new XmlSerializer(ol.GetType());

            var f = new OpenFileDialog();
            f.Filter = "DRT Save file|*.drt";
            f.InitialDirectory = Environment.CurrentDirectory;
            f.CustomPlaces.Add(new FileDialogCustomPlace(Environment.CurrentDirectory));
            if (f.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                TextReader tr = new StreamReader(f.FileName);
                AObjects.Reinit();

                try
                {
                    ol = x.Deserialize(tr) as ObjectsList;

                    currentfile.Nlong = f.FileName;
                    FileInfo ff = new FileInfo(currentfile.Nlong);
                    currentfile.Nshort = ff.Name;
                    this.Text = currentfile.Nshort;

                    saveAsToolStripMenuItem.Enabled = true;

                    ol.Collection.form = this;
                    comboBox1.DataSource = ol.Collection;

                    redraw(true);
                }
                catch (System.InvalidOperationException)
                {
                    MessageBox.Show("Error, the file you specified is invalid");
                }
            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var x = new XmlSerializer(ol.GetType());

            var f = new SaveFileDialog();
            f.AddExtension = true;

            f.Filter = "DRT Save file|*.drt";
            f.InitialDirectory = Environment.CurrentDirectory;
            f.CustomPlaces.Add(new FileDialogCustomPlace(Environment.CurrentDirectory));

            if (f.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                TextWriter tw = new StreamWriter(f.FileName);
                try
                {
                    x.Serialize(tw, ol);

                    currentfile.Nlong = f.FileName;
                    FileInfo ff = new FileInfo(currentfile.Nlong);
                    currentfile.Nshort = ff.Name;
                    this.Text = currentfile.Nshort;
                }
                catch
                {
                    MessageBox.Show("An error occured saving the file");
                }
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new About().Show();
        }

        private void show_server_mapping_CheckedChanged(object sender, EventArgs e)
        {
            if (!show_server_mapping.Checked)
            {
                view_3d.Image = td_bitmap;
                return;
            }

            Bitmap bm = new Bitmap(td_bitmap.Width, td_bitmap.Height);
            Color[] colors = new Color[10] {
                Color.Red, Color.Blue, Color.Green, Color.Gold, Color.Silver,
                Color.Violet, Color.Turquoise, Color.Pink, Color.AliceBlue, Color.Black
            };

            int x = 0;
            int y = 0;

            foreach (var key in servers_map.Keys)
            {
                for (var i = 0; i < servers_map[key]; i++)
                {
                    bm.SetPixel(x, y, colors[key % colors.Length]);

                    y++;
                    if (y >= td_bitmap.Height)
                    {
                        y = 0;
                        x++;
                    }
                }
            }

            view_3d.Image = bm;
        }
    }
}
