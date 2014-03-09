using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace client
{
    public partial class MainForm : Form
    {
        Viewport vp = new Viewport();
        ObjectsList ol = new ObjectsList();

        public MainForm()
        {
            InitializeComponent();

            this.Cursor = new Cursor(Properties.Resources.pointer_ptr.GetHicon());
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

        private void draw_grid(System.Drawing.Bitmap bm)
        {
            empty_bitmap(bm);

            using (var g = System.Drawing.Graphics.FromImage(bm))
            {
                using (var p = new Pen(Color.FromArgb(25, 25, 25)))
                {
                    var dw = bm.Width / 2;
                    var dh = bm.Height / 2;

                    for (int x = 0; x < dw; x += vp.GridLevel) g.DrawLine(p, new Point(x + dw, 0), new Point(x + dw, bm.Height - 1));
                    for (int x = 0; x > -dw; x -= vp.GridLevel) g.DrawLine(p, new Point(x + dw, 0), new Point(x + dw, bm.Height - 1));
                    
                    for (int y = 0; y < dh; y += vp.GridLevel) g.DrawLine(p, new Point(0, y + dh), new Point(bm.Width - 1, y + dh));
                    for (int y = 0; y > -dh; y -= vp.GridLevel) g.DrawLine(p, new Point(0, y + dh), new Point(bm.Width - 1, y + dh));
                }

                using (var p = new Pen(Color.FromArgb(35, 35, 35)))
                {
                    g.DrawLine(p, new Point(0, bm.Height / 2), new Point(bm.Width, bm.Height / 2));
                    g.DrawLine(p, new Point(bm.Width / 2, 0), new Point(bm.Width / 2, bm.Height));
                }
            }
        }

        private void redraw()
        {
            var bm_x = new System.Drawing.Bitmap(view_x.InitialImage, new Size(view_x.Width, view_x.Height));
            draw_grid(bm_x);

            var bm_y = new System.Drawing.Bitmap(view_x.InitialImage, new Size(view_y.Width, view_y.Height));
            draw_grid(bm_y);

            var bm_z = new System.Drawing.Bitmap(view_x.InitialImage, new Size(view_z.Width, view_z.Height));
            draw_grid(bm_z);

            foreach (var o in ol)
            {
                o.draw_x(bm_x, Color.SteelBlue);
                o.draw_y(bm_y, Color.SteelBlue);
                o.draw_z(bm_z, Color.SteelBlue);
            }

            view_x.Image = bm_x;
            view_y.Image = bm_y;
            view_z.Image = bm_z;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            vp.GridLevel = 5;
            vp.X = 0;
            vp.Y = 0;
            vp.Z = 0;

            redraw();
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            redraw();
        }

        enum eDrawMode
        {
            SPHERE,
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

        Points p1 = new Points(), p2 = new Points();

        private void save_views()
        {
            this.view_x_cp = this.view_x.Image;
            this.view_y_cp = this.view_y.Image;
            this.view_z_cp = this.view_z.Image;
        }

        private void view_x_MouseDown(object sender, MouseEventArgs e)
        {
            if (this.drawMode == eDrawMode.NONE) return;

            p1.Y = e.X;
            p1.Z = e.Y;

            save_views();
        }
        private void view_y_MouseDown(object sender, MouseEventArgs e)
        {
            if (this.drawMode == eDrawMode.NONE) return;

            p1.X = e.X;
            p1.Z = e.Y;

            save_views();
        }
        private void view_z_MouseDown(object sender, MouseEventArgs e)
        {
            if (this.drawMode == eDrawMode.NONE) return;

            p1.X = e.X;
            p1.Y = e.Y;

            save_views();
        }

        private void view_x_MouseUp(object sender, MouseEventArgs e)
        {
            if (this.drawMode == eDrawMode.NONE) return;

            p2.Y = e.X;
            p2.Z = e.Y;

            switch (this.drawMode)
            {
                case eDrawMode.SPHERE:
                    var s = Sphere.create_x((Points)p1.Clone(), (Points)p2.Clone());
                    ol.Add(s);
                    break;
            }

            redraw();
        }
        private void view_y_MouseUp(object sender, MouseEventArgs e)
        {
            if (this.drawMode == eDrawMode.NONE) return;

            p2.X = e.X;
            p2.Z = e.Y;

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

            p2.X = e.X;
            p2.Y = e.Y;

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

        private void drawTmpObject(MouseEventArgs e, Points p3, eView v)
        {
            draw_status.Text = "Coords { X : " + p3.X + ", Y : " + p3.Y + ", Z : " + p3.Z + " }";

            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode != eDrawMode.NONE)
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

                        draw_status.Text += ", Sphere { Cy : " + s.centerPoint.Y + ", Cz : " + s.centerPoint.Z + ", R : " + ((Sphere)s).rayon + " }";

                        s.draw_x(vx, Color.White);
                        s.draw_y(vy, Color.White);
                        s.draw_z(vz, Color.White);
                        break;
                }
                view_x.Image = vx;
                view_y.Image = vy;
                view_z.Image = vz;
            }
        }

        private void view_x_MouseMove(object sender, MouseEventArgs e)
        {
            Points p3 = new Points() { Y = e.X, Z = e.Y };

            drawTmpObject(e, p3, eView.x);
        }
        private void view_y_MouseMove(object sender, MouseEventArgs e)
        {
            Points p3 = new Points() { X = e.X, Z = e.Y };

            drawTmpObject(e, p3, eView.y);
        }
        private void view_z_MouseMove(object sender, MouseEventArgs e)
        {
            Points p3 = new Points() { X = e.X, Y = e.Y };

            drawTmpObject(e, p3, eView.z);
        }

        private Image view_x_cp { get; set; }
        private Image view_y_cp { get; set; }
        private Image view_z_cp { get; set; }
    }
}
