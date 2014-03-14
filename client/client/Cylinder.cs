using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class Cylinder : AObjects
    {
        new static public AObjects create_x(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            var d = (int)Math.Sqrt(Math.Pow(p2.Y - p1.Y, 2) + Math.Pow(p2.Z - p1.Z, 2));
            return new Cylinder(p1, d, tmp);
        }
        new static public AObjects create_y(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Z - p2.Z, 2) + Math.Pow(p1.X - p2.X, 2));

            return new Cylinder(p1, d, tmp);
        }
        new static public AObjects create_z(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Y - p2.Y, 2) + Math.Pow(p1.X - p2.X, 2));

            return new Cylinder(p1, d, tmp);
        }

        override public void draw_x(Image b, Viewport vp, bool selected)
        {
            var points = new Point[points_x.Count];
            var g = System.Drawing.Graphics.FromImage(b);
            var i = 0;

            foreach (var p in points_x)
            {
                Points t = (Points)p.Clone();

                this.matrixX.ApplyOnPoint(t);
                this.matrixY.ApplyOnPoint(t);
                this.matrixZ.ApplyOnPoint(t);

                t.X += this.centerPoint.X;
                t.Y += this.centerPoint.Y;
                t.Z += this.centerPoint.Z;

                Util.convertToGe(t, vp, b, Util.eView.x);
                points[i] = new Point(t.Y, t.Z);
                i++;
            }

            g.DrawClosedCurve(new Pen((selected ? System.Drawing.Color.White : Color.toColor())), points);
        }
        override public void draw_y(Image b, Viewport vp, bool selected)
        {
            var points = new Point[points_y.Count];
            var g = System.Drawing.Graphics.FromImage(b);
            var i = 0;

            foreach (var p in points_y)
            {
                Points t = (Points)p.Clone();

                this.matrixX.ApplyOnPoint(t);
                this.matrixY.ApplyOnPoint(t);
                this.matrixZ.ApplyOnPoint(t);

                t.X += this.centerPoint.X;
                t.Y += this.centerPoint.Y;
                t.Z += this.centerPoint.Z;

                Util.convertToGe(t, vp, b, Util.eView.y);
                points[i] = new Point(t.X, t.Z);
                i++;
            }

            g.DrawClosedCurve(new Pen((selected ? System.Drawing.Color.White : Color.toColor())), points);
        }
        override public void draw_z(Image b, Viewport vp, bool selected)
        {
            var points = new Point[points_z.Count];
            var g = System.Drawing.Graphics.FromImage(b);
            var i = 0;

            foreach (var p in points_z)
            {
                Points t = (Points)p.Clone();

                this.matrixX.ApplyOnPoint(t);
                this.matrixY.ApplyOnPoint(t);
                this.matrixZ.ApplyOnPoint(t);

                t.X += this.centerPoint.X;
                t.Y += this.centerPoint.Y;
                t.Z += this.centerPoint.Z;

                Util.convertToGe(t, vp, b, Util.eView.z);
                points[i] = new Point(t.X, t.Y);
                i++;
            }

            g.DrawClosedCurve(new Pen((selected ? System.Drawing.Color.White : Color.toColor())), points);
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

        static protected int count = 0;

        private List<Points> points_x = new List<Points>();
        private List<Points> points_y = new List<Points>();
        private List<Points> points_z = new List<Points>();
        public void generate_points()
        {
            double angle = 0;
            double delta = Math.PI / 8;
            points_x.Clear();
            points_y.Clear();
            points_z.Clear();

            while (angle < 2 * Math.PI)
            {
                points_x.Add(
                    new Points()
                    {
                        Y = (int)(this.Radius * Math.Cos(angle)),
                        Z = (int)(this.Radius * Math.Sin(angle))
                    }
                    );

                points_y.Add(
                    new Points()
                    {
                        X = (int)(this.Radius * Math.Cos(angle)),
                        Z = (int)(this.Radius * Math.Sin(angle))
                    }
                    );

                points_z.Add(
                    new Points()
                    {
                        X = (int)(this.Radius * Math.Cos(angle)),
                        Y = (int)(this.Radius * Math.Sin(angle))
                    }
                    );
                angle += delta;
            }
        }

        Cylinder()
        {
            this.centerPoint = new Points();
            base.AddOneToCount(typeof(Cylinder));
            generate_points();
        }

        private Cylinder(Points c, int d, bool tmp)
            : base(tmp)
        {
            this.centerPoint = c;
            this.Radius = d;
            this.Color = new MyColor(System.Drawing.Color.Red.ToArgb());

            generate_points();

            if (!tmp)
            {
                this.Name = "Cylinder" + base.AddOneToCount(typeof(Cylinder));
            }
        }

        public override void Refresh()
        {
            generate_points();
        }

        override public int getSubModule()
        {
            return (int)eSubModules.CYLINDER;
        }

        override public byte[] getBytes()
        {
            List<byte> b = new List<byte>();

            b.Add(Color.R);
            b.Add(Color.G);
            b.Add(Color.B);
            b.AddRange(BitConverter.GetBytes((UInt16)Radius));

            return b.ToArray();
        }
    }
}
