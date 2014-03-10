using System;
using System.Drawing;
using System.Windows.Forms;

namespace client
{
    public partial class MainForm : Form
    {
        Viewport vp = new Viewport();
        ObjectsList ol;

        public MainForm()
        {
            InitializeComponent();

            this.Cursor = new Cursor(Properties.Resources.pointer_ptr.GetHicon());
            ol = new ObjectsList(this);
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

                    for (int x = dw + vp.ox.Y; x < bm.Width; x += vp.GridLevel) g.DrawLine(p, new Point(x, 0), new Point(x, bm.Height - 1));
                    for (int x = dw + vp.ox.Y; x > 0; x -= vp.GridLevel) g.DrawLine(p, new Point(x, 0), new Point(x, bm.Height - 1));
                    for (int y = dh + vp.ox.Z; y < bm.Height; y += vp.GridLevel) g.DrawLine(p, new Point(0, y), new Point(bm.Width - 1, y));
                    for (int y = dh + vp.ox.Z; y > 0; y -= vp.GridLevel) g.DrawLine(p, new Point(0, y), new Point(bm.Width - 1, y));
                }

                using (var p = new Pen(Color.FromArgb(35, 35, 35)))
                {
                    g.DrawLine(p, new Point(bm.Width / 2 + vp.ox.Y, 0), new Point(bm.Width / 2 + vp.ox.Y, bm.Height));
                    g.DrawLine(p, new Point(0, bm.Height / 2 + vp.ox.Z), new Point(bm.Width, bm.Height / 2 + vp.ox.Z));
                }
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

                    for (int x = dw + vp.oy.X; x < bm.Width; x += vp.GridLevel) g.DrawLine(p, new Point(x, 0), new Point(x, bm.Height - 1));
                    for (int x = dw + vp.oy.X; x > 0; x -= vp.GridLevel) g.DrawLine(p, new Point(x, 0), new Point(x, bm.Height - 1));
                    for (int y = dh + vp.oy.Z; y < bm.Height; y += vp.GridLevel) g.DrawLine(p, new Point(0, y), new Point(bm.Width - 1, y));
                    for (int y = dh + vp.oy.Z; y > 0 ; y -= vp.GridLevel) g.DrawLine(p, new Point(0, y), new Point(bm.Width - 1, y));
                }

                using (var p = new Pen(Color.FromArgb(35, 35, 35)))
                {
                    g.DrawLine(p, new Point(bm.Width / 2 + vp.oy.X, 0), new Point(bm.Width / 2 + vp.oy.X, bm.Height));
                    g.DrawLine(p, new Point(0, bm.Height / 2 + vp.oy.Z), new Point(bm.Width, bm.Height / 2 + vp.oy.Z));
                }
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

                    for (int x = dw + vp.oz.X; x < bm.Width; x += vp.GridLevel) g.DrawLine(p, new Point(x, 0), new Point(x, bm.Height - 1));
                    for (int x = dw + vp.oz.X; x > 0; x -= vp.GridLevel) g.DrawLine(p, new Point(x, 0), new Point(x, bm.Height - 1));
                    for (int y = dh + vp.oz.Y; y < bm.Height; y += vp.GridLevel) g.DrawLine(p, new Point(0, y), new Point(bm.Width - 1, y));
                    for (int y = dh + vp.oz.Y; y > 0; y -= vp.GridLevel) g.DrawLine(p, new Point(0, y), new Point(bm.Width - 1, y));
                }

                using (var p = new Pen(Color.FromArgb(35, 35, 35)))
                {
                    g.DrawLine(p, new Point(bm.Width / 2 + vp.oz.X, 0), new Point(bm.Width / 2 + vp.oz.X, bm.Height));
                    g.DrawLine(p, new Point(0, bm.Height / 2 + vp.oz.Y), new Point(bm.Width, bm.Height / 2 + vp.oz.Y));
                }
            }
        }

        private void redraw()
        {
            var bm_x = new System.Drawing.Bitmap(view_x.InitialImage, view_x.Size);
            draw_grid_x(bm_x);

            var bm_y = new System.Drawing.Bitmap(view_x.InitialImage, view_y.Size);
            draw_grid_y(bm_y);

            var bm_z = new System.Drawing.Bitmap(view_x.InitialImage, view_z.Size);
            draw_grid_z(bm_z);

            foreach (var o in ol)
            {
                o.draw_x(bm_x, vp, (o == ol.Selected ? Color.White : Color.SteelBlue));
                o.draw_y(bm_y, vp, (o == ol.Selected ? Color.White : Color.SteelBlue));
                o.draw_z(bm_z, vp, (o == ol.Selected ? Color.White : Color.SteelBlue));
            }

            view_x.Image = bm_x;
            view_y.Image = bm_y;
            view_z.Image = bm_z;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            vp.GridLevel = 5;

            redraw();
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            redraw();
        }

        enum eDrawMode
        {
            SPHERE,
            GRAB,
            RESIZE,
            NONE
        };
        eDrawMode drawMode = eDrawMode.NONE;

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.SPHERE;

            this.Cursor = new Cursor(Properties.Resources.circle_ptr.GetHicon());
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

        Points p1 = new Points(), p2 = new Points();

        private void save_views()
        {
            this.view_x_cp = this.view_x.Image;
            this.view_y_cp = this.view_y.Image;
            this.view_z_cp = this.view_z.Image;
        }

        private void view_x_MouseDown(object sender, MouseEventArgs e)
        {
            p1.X = 0;
            p1.Y = e.X - vp.ox.Y - view_x.Width / 2;
            p1.Z = -(e.Y - vp.ox.Z - view_x.Height / 2);

            if (this.drawMode == eDrawMode.NONE)
            {
                foreach (var o in ol)
                {
                    if (o.solve_equation_x(p1))
                    {
                        ol.Selected = o;
                        redraw();
                    }
                }

                return;
            }
            if (this.drawMode == eDrawMode.GRAB) return;

            save_views();
        }
        private void view_y_MouseDown(object sender, MouseEventArgs e)
        {
            p1.X = e.X - vp.oy.X - view_y.Width / 2;
            p1.Y = 0;
            p1.Z = -(e.Y - vp.oy.Z - view_y.Height / 2);

            if (this.drawMode == eDrawMode.NONE)
            {
                foreach (var o in ol)
                {
                    if (o.solve_equation_y(p1))
                    {
                        ol.Selected = o;
                        redraw();
                    }
                }

                return;
            }
            save_views();
        }
        private void view_z_MouseDown(object sender, MouseEventArgs e)
        {
            p1.X = e.X - vp.oz.X - view_z.Width / 2;
            p1.Y = -(e.Y - vp.oz.Y - view_z.Height / 2);
            p1.Z = 0;

            if (this.drawMode == eDrawMode.NONE)
            {
                foreach (var o in ol)
                {
                    if (o.solve_equation_z(p1))
                    {
                        ol.Selected = o;
                        redraw();
                    }
                }

                return;
            }
            save_views();
        }

        private void view_x_MouseUp(object sender, MouseEventArgs e)
        {
            if (this.drawMode == eDrawMode.NONE) return;

            p2.X = 0;
            p2.Y = e.X - vp.ox.Y - view_x.Width / 2;
            p2.Z = -(e.Y - vp.ox.Z - view_x.Height / 2);

            switch (this.drawMode)
            {
                case eDrawMode.SPHERE:
                    var s = Sphere.create_x((Points)p1.Clone(), (Points)p2.Clone());
                    ol.Add(s);
                    ol.Selected = s;
                    break;
            }

            redraw();
        }
        private void view_y_MouseUp(object sender, MouseEventArgs e)
        {
            if (this.drawMode == eDrawMode.NONE) return;

            p2.X = e.X - vp.oy.X - view_y.Width / 2;
            p2.Y = 0;
            p2.Z = -(e.Y - vp.oy.Z - view_y.Height / 2);

            switch (this.drawMode)
            {
                case eDrawMode.SPHERE:
                    var s = Sphere.create_y((Points)p1.Clone(), (Points)p2.Clone());
                    ol.Add(s);
                    break;
            }

            redraw();
        }
        private void view_z_MouseUp(object sender, MouseEventArgs e)
        {
            if (this.drawMode == eDrawMode.NONE) return;

            p2.X = e.X - vp.oz.X - view_z.Width / 2;
            p2.Y = -(e.Y - vp.oz.Y - view_z.Height / 2);
            p2.Z = 0;

            switch (this.drawMode)
            {
                case eDrawMode.SPHERE:
                    var s = Sphere.create_z((Points)p1.Clone(), (Points)p2.Clone());
                    ol.Add(s);
                    break;
            }

            redraw();
        }

        enum eView {x, y, z};

        private bool drawTmpObject(MouseEventArgs e, Points p3, eView v)
        {
            draw_status.Text = "Coords { X : " + p3.X + ", Y : " + p3.Y + ", Z : " + p3.Z + " }";

            if (e.Button == System.Windows.Forms.MouseButtons.Left
                && this.drawMode != eDrawMode.NONE
                && this.drawMode != eDrawMode.GRAB
                && this.drawMode != eDrawMode.RESIZE)
            {
                var vx = new System.Drawing.Bitmap(view_x_cp, view_x_cp.Size);
                var vy = new System.Drawing.Bitmap(view_y_cp, view_y_cp.Size);
                var vz = new System.Drawing.Bitmap(view_z_cp, view_z_cp.Size);

                switch (this.drawMode)
                {
                    case eDrawMode.SPHERE:
                        AObjects s = null;
                        if (v == eView.x) s = Sphere.create_x((Points)p1.Clone(), (Points)p3.Clone());
                        if (v == eView.y) s = Sphere.create_y((Points)p1.Clone(), (Points)p3.Clone());
                        if (v == eView.z) s = Sphere.create_z((Points)p1.Clone(), (Points)p3.Clone());

                        draw_status.Text += ", Sphere { Cx : " + s.centerPoint.X + ", Cy : " + s.centerPoint.Y + ", Cz : " + s.centerPoint.Z + ", R : " + ((Sphere)s).radius + " }";

                        s.draw_x(vx, vp, Color.White);
                        s.draw_y(vy, vp, Color.White);
                        s.draw_z(vz, vp, Color.White);
                        break;
                }
                view_x.Image = vx;
                view_y.Image = vy;
                view_z.Image = vz;

                return true;
            }

            return false;
        }

        private void view_x_MouseMove(object sender, MouseEventArgs e)
        {
            Points p3 = new Points() { Y = e.X - vp.ox.Y - view_x.Width / 2, Z = -(e.Y - vp.ox.Z - view_x.Height / 2) };
            Points p4 = new Points() { Y = e.X , Z = -e.Y };

            drawTmpObject(e, p3, eView.x);

            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.NONE)
            {
                vp.ox.Y = p4.Y - p1.Y - view_x.Width / 2;
                vp.ox.Z = -p4.Z + p1.Z - view_x.Height / 2;

                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.GRAB)
            {
                if (ol.Selected == null) return;

                ol.Selected.centerPoint.Y = p3.Y;
                ol.Selected.centerPoint.Z = p3.Z;

                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.RESIZE)
            {
                if (ol.Selected == null) return;

                ol.Selected.radius = (int)Math.Sqrt(Math.Pow(p3.Y - ol.Selected.centerPoint.Y, 2) + Math.Pow(p3.Z - ol.Selected.centerPoint.Z, 2));

                redraw();
            }
        }
        private void view_y_MouseMove(object sender, MouseEventArgs e)
        {
            Points p3 = new Points() { X = e.X - vp.oy.X - view_y.Width / 2, Z = -(e.Y - vp.oy.Z - view_y.Height / 2) };
            Points p4 = new Points() { X = e.X, Z = -e.Y };

            drawTmpObject(e, p3, eView.y);

            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.NONE)
            {
                vp.oy.X = p4.X - p1.X - view_y.Width / 2;
                vp.oy.Z = -p4.Z + p1.Z - view_y.Height / 2;

                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.GRAB)
            {
                if (ol.Selected == null) return;

                ol.Selected.centerPoint.X = p3.X;
                ol.Selected.centerPoint.Z = p3.Z;

                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.RESIZE)
            {
                if (ol.Selected == null) return;

                ol.Selected.radius = (int)Math.Sqrt(Math.Pow(p3.X - ol.Selected.centerPoint.X, 2) + Math.Pow(p3.Z - ol.Selected.centerPoint.Z, 2));

                redraw();
            }
        }
        private void view_z_MouseMove(object sender, MouseEventArgs e)
        {
            Points p3 = new Points() { X = e.X - vp.oz.X - view_z.Width / 2, Y = -(e.Y - vp.oz.Y - view_z.Height / 2) };
            Points p4 = new Points() { X = e.X, Y = -e.Y };

            drawTmpObject(e, p3, eView.z);

            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.NONE)
            {
                vp.oz.X = p4.X - p1.X - view_z.Width / 2;
                vp.oz.Y = -p4.Y + p1.Y - view_z.Height / 2;

                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.GRAB)
            {
                if (ol.Selected == null) return;

                ol.Selected.centerPoint.X = p3.X;
                ol.Selected.centerPoint.Y = p3.Y;

                redraw();
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode == eDrawMode.RESIZE)
            {
                if (ol.Selected == null) return;

                ol.Selected.radius = (int)Math.Sqrt(Math.Pow(p3.X - ol.Selected.centerPoint.X, 2) + Math.Pow(p3.Y - ol.Selected.centerPoint.Y, 2));

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
                if (ol.Selected != null)
                {
                    ol.Remove(ol.Selected);
                    ol.Selected = null;
                    redraw();
                }
            }
        }
    }
}
