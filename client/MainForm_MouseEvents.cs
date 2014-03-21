using client.Objects;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace client
{
    public partial class MainForm : Form
    {
        enum eDrawMode
        {
            SPHERE,
            CYLINDER,
            LIGHT,
            NONE,
            GRAB,
            RESIZE,
            ZOOMIN,
            ZOOMOUT,
            ROTATE
        };
        eDrawMode drawMode = eDrawMode.NONE;

        Points p1, p2;

        private void save_views()
        {
            this.view_x_cp = this.view_x.Image;
            this.view_y_cp = this.view_y.Image;
            this.view_z_cp = this.view_z.Image;
        }

        private void view_x_Click(object sender, EventArgs e)
        {
            if (this.drawMode == eDrawMode.ZOOMIN)
            {
                if (vp.fx < 8) vp.fx *= 2;

                redraw();
            }
            if (this.drawMode == eDrawMode.ZOOMOUT)
            {
                if (vp.fx > 0.25F) vp.fx /= 2;

                redraw();
            }
        }
        private void view_y_Click(object sender, EventArgs e)
        {
            if (this.drawMode == eDrawMode.ZOOMIN)
            {
                if (vp.fy < 8) vp.fy *= 2;

                redraw();
            }
            if (this.drawMode == eDrawMode.ZOOMOUT)
            {
                if (vp.fy > 0.25F) vp.fy /= 2;

                redraw();
            }
        }
        private void view_z_Click(object sender, EventArgs e)
        {
            if (this.drawMode == eDrawMode.ZOOMIN)
            {
                if (vp.fz < 8) vp.fz *= 2;

                redraw();
            }
            if (this.drawMode == eDrawMode.ZOOMOUT)
            {
                if (vp.fz > 0.25F) vp.fz /= 2;

                redraw();
            }
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
                        redraw();
                    }
                }

                return;
            }
            if (this.drawMode > eDrawMode.NONE) return;

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
                        redraw();
                    }
                }

                return;
            }
            if (this.drawMode > eDrawMode.NONE) return;

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
                        redraw();
                    }
                }

                return;
            }
            if (this.drawMode > eDrawMode.NONE) return;

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
                case eDrawMode.LIGHT:
                    s = Light.create_x((Points)p1.Clone(), (Points)p2.Clone(), vp);
                    break;
            }
            if (s != null)
            {
                ol.Add(s);
                ol.Selected = s;
            }

            redraw();
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
                case eDrawMode.LIGHT:
                    s = Light.create_y((Points)p1.Clone(), (Points)p2.Clone(), vp);
                    break;
            }
            if (s != null)
            {
                ol.Add(s);
                ol.Selected = s;
            }

            redraw();
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
                case eDrawMode.LIGHT:
                    s = Light.create_z((Points)p1.Clone(), (Points)p2.Clone(), vp);
                    break;
            }
            if (s != null)
            {
                ol.Add(s);
                ol.Selected = s;
            }

            redraw();
            propertyGrid.Refresh();
        }

        AObjects _tmpObject = null;

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
                var angle = Math.Acos(((double)Math.Abs(p3.Y - ol.Selected.Y) / d));

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
    }
}
