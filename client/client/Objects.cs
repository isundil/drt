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
        public AObjects selected { get; set; }
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
        public int radius { get; set; }
        public Points centerPoint { get; set; }

        static public AObjects create_x(Points p1, Points p2) { return null; }
        static public AObjects create_y(Points p1, Points p2) { return null; }
        static public AObjects create_z(Points p1, Points p2) { return null; }

        abstract public void draw_x(Bitmap b, Viewport vp, Color c);
        abstract public void draw_y(Bitmap b, Viewport vp, Color c);
        abstract public void draw_z(Bitmap b, Viewport vp, Color c);

        abstract public bool solve_equation_x(Points p);
        abstract public bool solve_equation_y(Points p);
        abstract public bool solve_equation_z(Points p);
    }

    public class Sphere : AObjects
    {
        new static public AObjects create_x(Points p1, Points p2)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Y - p2.Y, 2) + Math.Pow(p1.Z - p2.Z, 2));

            return new Sphere(p1, d);
        }
        new static public AObjects create_y(Points p1, Points p2)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Z - p2.Z, 2) + Math.Pow(p1.X - p2.X, 2));

            return new Sphere(p1, d);
        }
        new static public AObjects create_z(Points p1, Points p2)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Y - p2.Y, 2) + Math.Pow(p1.X - p2.X, 2));

            return new Sphere(p1, d);
        }

        override public void draw_x(Bitmap b, Viewport vp, Color c)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            g.DrawEllipse(new Pen(c), new Rectangle(
                    new Point(this.centerPoint.Y - this.radius + vp.ox.Y + b.Width / 2, this.centerPoint.Z - this.radius + vp.ox.Z + b.Height / 2),
                    new Size(this.radius * 2, this.radius * 2)
                ));
        }
        override public void draw_y(Bitmap b, Viewport vp, Color c)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            g.DrawEllipse(new Pen(c), new Rectangle(
                    new Point(this.centerPoint.X - this.radius + vp.oy.X + b.Width / 2, this.centerPoint.Z - this.radius + vp.oy.Z + b.Height / 2),
                    new Size(this.radius * 2, this.radius * 2)
                ));
        }
        override public void draw_z(Bitmap b, Viewport vp, Color c)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            g.DrawEllipse(new Pen(c), new Rectangle(
                    new Point(this.centerPoint.X - this.radius + vp.oz.X + b.Width / 2, this.centerPoint.Y - this.radius + vp.oz.Y + b.Height / 2),
                    new Size(this.radius * 2, this.radius * 2)
                ));
        }

        public override bool solve_equation_x(Points p)
        {
            var _rsq = Math.Pow(this.centerPoint.Y - p.Y, 2) + Math.Pow(this.centerPoint.Z - p.Z, 2);
            if (_rsq >= Math.Pow(this.radius - 5, 2) && _rsq <= Math.Pow(this.radius + 5, 2)) return true;
            return false;
        }
        public override bool solve_equation_y(Points p)
        {
            var _rsq = Math.Pow(this.centerPoint.X - p.X, 2) + Math.Pow(this.centerPoint.Z - p.Z, 2);
            var rsq = Math.Pow(this.radius, 2);

            if (_rsq >= Math.Pow(this.radius - 5, 2) && _rsq <= Math.Pow(this.radius + 5, 2)) return true;
            return false;
        }
        public override bool solve_equation_z(Points p)
        {
            var _rsq = Math.Pow(this.centerPoint.X - p.X, 2) + Math.Pow(this.centerPoint.Y - p.Y, 2);
            var rsq = Math.Pow(this.radius, 2);

            if (_rsq >= Math.Pow(this.radius - 5, 2) && _rsq <= Math.Pow(this.radius + 5, 2)) return true;
            return false;
        }

        private Sphere() { }
        private Sphere(Points c, int d)
        {
            this.centerPoint = c;
            this.radius = d;
        }
    }
}
