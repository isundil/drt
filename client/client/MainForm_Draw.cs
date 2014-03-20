using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace client
{
    public partial class MainForm : Form
    {

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
            if (rebuild_3d == true)
            {
                servers_map.Clear();
                progressbar.Value = 0;
                DrawPixel3DView_count = 0;
                progressbar.Maximum = view_3d.Width * view_3d.Height;
                calculusWorker.DestinationImage = view_3d.Image;
                calculusWorker.DoScenePreviewCalculus(ol);
            }
        }

        static int DrawPixel3DView_count = 0;

        Dictionary<ushort, int> servers_map = new Dictionary<ushort, int>();

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
            }
        }

        private bool drawTmpObject(MouseEventArgs e, Points p3, Util.eView v)
        {
            draw_status.Text = "Coords { X : " + p3.X + ", Y : " + p3.Y + ", Z : " + p3.Z + " }";

            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.drawMode < eDrawMode.NONE)
            {
                var vx = new System.Drawing.Bitmap(view_x_cp, view_x_cp.Size);
                var vy = new System.Drawing.Bitmap(view_y_cp, view_y_cp.Size);
                var vz = new System.Drawing.Bitmap(view_z_cp, view_z_cp.Size);

                Type object_type = null;

                switch (this.drawMode)
                {
                    case eDrawMode.SPHERE:
                        object_type = typeof(Sphere);
                        break;
                    case eDrawMode.CYLINDER:
                        object_type = typeof(Cylinder);
                        break;
                }

                if (object_type == null) return false;

                if (_tmpObject != null)
                {
                    if (v == Util.eView.x) _tmpObject.Radius = (int)Math.Sqrt(Math.Pow(p3.Y - _tmpObject.centerPoint.Y, 2) + Math.Pow(p3.Z - _tmpObject.centerPoint.Z, 2));
                    if (v == Util.eView.y) _tmpObject.Radius = (int)Math.Sqrt(Math.Pow(p3.X - _tmpObject.centerPoint.X, 2) + Math.Pow(p3.Z - _tmpObject.centerPoint.Z, 2));
                    if (v == Util.eView.z) _tmpObject.Radius = (int)Math.Sqrt(Math.Pow(p3.X - _tmpObject.centerPoint.X, 2) + Math.Pow(p3.Y - _tmpObject.centerPoint.Y, 2));
                }
                else
                {
                    if (v == Util.eView.x) _tmpObject = object_type.GetMethod("create_x").Invoke(null, new object[] { (Points)p1.Clone(), (Points)p3.Clone(), vp, true }) as AObjects;
                    if (v == Util.eView.y) _tmpObject = object_type.GetMethod("create_y").Invoke(null, new object[] { (Points)p1.Clone(), (Points)p3.Clone(), vp, true }) as AObjects;
                    if (v == Util.eView.z) _tmpObject = object_type.GetMethod("create_z").Invoke(null, new object[] { (Points)p1.Clone(), (Points)p3.Clone(), vp, true }) as AObjects;
                }
                draw_status.Text += ", " + object_type.ToString() + " { Cx : " + _tmpObject.centerPoint.X + ", Cy : " + _tmpObject.centerPoint.Y + ", Cz : " + _tmpObject.centerPoint.Z + ", R : " + _tmpObject.Radius + " }";

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
    }
}
