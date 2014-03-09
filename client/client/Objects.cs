using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class ObjectsList : List<AObjects> { }

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
        public Points centerPoint { get; set; }

        static public AObjects create_x(Points p1, Points p2) { return null; }
        static public AObjects create_y(Points p1, Points p2) { return null; }
        static public AObjects create_z(Points p1, Points p2) { return null; }

        abstract public void draw_x(Bitmap b, Color c);
        abstract public void draw_y(Bitmap b, Color c);
        abstract public void draw_z(Bitmap b, Color c);
    }

    public class Sphere : AObjects
    {
        public int rayon { get; set; }

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

        override public void draw_x(Bitmap b, Color c)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            g.DrawEllipse(new Pen(c), new Rectangle(
                    new Point(this.centerPoint.Y - this.rayon, this.centerPoint.Z - this.rayon),
                    new Size(this.rayon * 2, this.rayon * 2)
                ));
        }
        override public void draw_y(Bitmap b, Color c)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            g.DrawEllipse(new Pen(c), new Rectangle(
                    new Point(this.centerPoint.X - this.rayon, this.centerPoint.Z - this.rayon),
                    new Size(this.rayon * 2, this.rayon * 2)
                ));
        }
        override public void draw_z(Bitmap b, Color c)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            g.DrawEllipse(new Pen(c), new Rectangle(
                    new Point(this.centerPoint.X - this.rayon, this.centerPoint.Y - this.rayon),
                    new Size(this.rayon * 2, this.rayon * 2)
                ));
        }

        private Sphere() { }
        private Sphere(Points c, int d)
        {
            this.centerPoint = c;
            this.rayon = d;
        }
    }
}
