using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class ObjectsList : List<AObjects>
    {
        MainForm f;

        public ObjectsList(MainForm f) : base()
        {
            this.f = f;
        }

        private AObjects selected;
        public AObjects Selected
        {
            get
            {
                return selected;
            }
            set
            {
                selected = value;

                f.propertyGrid.SelectedObject = selected;

                if (value != null)
                {
                    f.move_toolstrip.Enabled = true;
                    f.resize_toolstrip.Enabled = true;
                }
                else
                {
                    f.move_toolstrip.Enabled = false;
                    f.resize_toolstrip.Enabled = false;
                }
            }
        }
    }

    public class Points : ICloneable {
        public int X { get; set; }
        public int Y { get; set; }
        public int Z { get; set; }

        public object Clone()
        {
            return new Points() { X = this.X, Y = this.Y, Z = this.Z };
        }
    }

    abstract public class AObjects
    {


        public int Radius { get; set; }
        public int X
        {
            get
            {
                return centerPoint.X;
            }
            set
            {
                centerPoint.X = value;
            }
        }
        public int Y
        {
            get
            {
                return centerPoint.Y;
            }
            set
            {
                centerPoint.Y = value;
            }
        }
        public int Z
        {
            get
            {
                return centerPoint.Z;
            }
            set
            {
                centerPoint.Z = value;
            }
        }
        internal Points centerPoint { get; set; }

        static public AObjects create_x(Points p1, Points p2, Viewport vp) { return null; }
        static public AObjects create_y(Points p1, Points p2, Viewport vp) { return null; }
        static public AObjects create_z(Points p1, Points p2, Viewport vp) { return null; }

        abstract public void draw_x(Image b, Viewport vp, Color c);
        abstract public void draw_y(Image b, Viewport vp, Color c);
        abstract public void draw_z(Image b, Viewport vp, Color c);

        abstract public bool solve_equation_x(Points p);
        abstract public bool solve_equation_y(Points p);
        abstract public bool solve_equation_z(Points p);
    }

    public class Sphere : AObjects
    {
        new static public AObjects create_x(Points p1, Points p2, Viewport vp)
        {
            var d = (int)Math.Sqrt(Math.Pow(p2.Y - p1.Y, 2) + Math.Pow(p2.Z - p1.Z, 2));
            return new Sphere(p1, d);
        }
        new static public AObjects create_y(Points p1, Points p2, Viewport vp)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Z - p2.Z, 2) + Math.Pow(p1.X - p2.X, 2));

            return new Sphere(p1, d);
        }
        new static public AObjects create_z(Points p1, Points p2, Viewport vp)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Y - p2.Y, 2) + Math.Pow(p1.X - p2.X, 2));

            return new Sphere(p1, d);
        }

        override public void draw_x(Image b, Viewport vp, Color c)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            p.Y -= this.Radius;
            p.Z += this.Radius;
            Util.convertToGe(p, vp, b, Util.eView.x);

            g.DrawEllipse(new Pen(c), new Rectangle(
                    new Point(p.Y, p.Z),
                    new Size((int)(this.Radius * 2 * vp.fx), (int)(this.Radius * 2 * vp.fx))
                ));
        }
        override public void draw_y(Image b, Viewport vp, Color c)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            p.X -= this.Radius;
            p.Z += this.Radius;
            Util.convertToGe(p, vp, b, Util.eView.y);

            g.DrawEllipse(new Pen(c), new Rectangle(
                    new Point(p.X, p.Z),
                    new Size((int)(this.Radius * 2 * vp.fy), (int)(this.Radius * 2 * vp.fy))
                ));
        }
        override public void draw_z(Image b, Viewport vp, Color c)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            p.X -= this.Radius;
            p.Y += this.Radius;
            Util.convertToGe(p, vp, b, Util.eView.z);

            g.DrawEllipse(new Pen(c), new Rectangle(
                    new Point(p.X, p.Y),
                    new Size((int)(this.Radius * 2 * vp.fz), (int)(this.Radius * 2 * vp.fz))
                ));
        }

        public override bool solve_equation_x(Points p)
        {
            var _rsq = Math.Pow(this.centerPoint.Y - p.Y, 2) + Math.Pow(this.centerPoint.Z - p.Z, 2);
            if (_rsq >= Math.Pow(this.Radius - 5, 2) && _rsq <= Math.Pow(this.Radius + 5, 2)) return true;
            return false;
        }
        public override bool solve_equation_y(Points p)
        {
            var _rsq = Math.Pow(this.centerPoint.X - p.X, 2) + Math.Pow(this.centerPoint.Z - p.Z, 2);
            var rsq = Math.Pow(this.Radius, 2);

            if (_rsq >= Math.Pow(this.Radius - 5, 2) && _rsq <= Math.Pow(this.Radius + 5, 2)) return true;
            return false;
        }
        public override bool solve_equation_z(Points p)
        {
            var _rsq = Math.Pow(this.centerPoint.X - p.X, 2) + Math.Pow(this.centerPoint.Y - p.Y, 2);
            var rsq = Math.Pow(this.Radius, 2);

            if (_rsq >= Math.Pow(this.Radius - 5, 2) && _rsq <= Math.Pow(this.Radius + 5, 2)) return true;
            return false;
        }

        private Sphere() { }
        private Sphere(Points c, int d)
        {
            this.centerPoint = c;
            this.Radius = d;
        }
    }
}
