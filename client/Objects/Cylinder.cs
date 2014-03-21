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
        public int Height { get; set; }

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
            var points_f1 = new Point[points_top.Count];
            var points_f2 = new Point[points_top.Count];
            var g = System.Drawing.Graphics.FromImage(b);
            
            var i = 0;
            double c = 100;
            foreach (var p in points_top)
            {
                Points t = (Points)p.Clone();
                Util.convertToGe(t, vp, b, Util.eView.x);
                points_f1[i] = new Point(t.Y, t.Z);
                i++;
            }
            i = 0;
            foreach (var p in points_bottom)
            {
                Points t = (Points)p.Clone();
                Util.convertToGe(t, vp, b, Util.eView.x);
                points_f2[i] = new Point(t.Y, t.Z);
                i++;
            }

            using (var pen = new Pen((selected ? System.Drawing.Color.White : Color.toColor())))
            {
                g.DrawClosedCurve(pen, points_f1);
                g.DrawClosedCurve(pen, points_f2);

                for (var id = 0; id < points_f1.Length; id++ )
                {
                    g.DrawLine(pen, points_f1[id], points_f2[id]);
                }
            }
        }
        override public void draw_y(Image b, Viewport vp, bool selected)
        {
            var points_f1 = new Point[points_top.Count];
            var points_f2 = new Point[points_top.Count];
            var g = System.Drawing.Graphics.FromImage(b);

            var i = 0;
            foreach (var p in points_top)
            {
                Points t = (Points)p.Clone();
                Util.convertToGe(t, vp, b, Util.eView.y);
                points_f1[i] = new Point(t.X, t.Z);
                i++;
            }
            i = 0;
            foreach (var p in points_bottom)
            {
                Points t = (Points)p.Clone();
                Util.convertToGe(t, vp, b, Util.eView.y);
                points_f2[i] = new Point(t.X, t.Z);
                i++;
            }

            using (var pen = new Pen((selected ? System.Drawing.Color.White : Color.toColor())))
            {
                g.DrawClosedCurve(pen, points_f1);
                g.DrawClosedCurve(pen, points_f2);

                for (var id = 0; id < points_f1.Length; id++)
                {
                    g.DrawLine(pen, points_f1[id], points_f2[id]);
                }
            }
        }
        override public void draw_z(Image b, Viewport vp, bool selected)
        {
            var points_f1 = new Point[points_top.Count];
            var points_f2 = new Point[points_top.Count];
            var g = System.Drawing.Graphics.FromImage(b);

            var i = 0;
            foreach (var p in points_top)
            {
                Points t = (Points)p.Clone();
                Util.convertToGe(t, vp, b, Util.eView.z);
                points_f1[i] = new Point(t.X, t.Y);
                i++;
            }
            i = 0;
            foreach (var p in points_bottom)
            {
                Points t = (Points)p.Clone();
                Util.convertToGe(t, vp, b, Util.eView.z);
                points_f2[i] = new Point(t.X, t.Y);
                i++;
            }

            using (var pen = new Pen((selected ? System.Drawing.Color.White : Color.toColor())))
            {
                g.DrawClosedCurve(pen, points_f1);
                g.DrawClosedCurve(pen, points_f2);

                for (var id = 0; id < points_f1.Length; id++)
                {
                    g.DrawLine(pen, points_f1[id], points_f2[id]);
                }
            }
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

        private List<Points> points_top = new List<Points>();
        private List<Points> points_bottom = new List<Points>();
        public void generate_points()
        {
            double angle = 0;
            double delta = Math.PI / 8;
            points_top.Clear();
            points_bottom.Clear();

            while (angle < 2 * Math.PI)
            {
                var p1 = new Points()
                    {
                        X = (int)(this.Radius * Math.Cos(angle)) + centerPoint.X,
                        Y = (int)(this.Radius * Math.Sin(angle)) + centerPoint.Y,
                        Z = Height / 2 + centerPoint.Z
                    };
                var p2 = new Points()
                    {
                        X = (int)(this.Radius * Math.Cos(angle)) + centerPoint.X,
                        Y = (int)(this.Radius * Math.Sin(angle)) + centerPoint.Y,
                        Z = -Height / 2 + centerPoint.Z
                    };

                this.matrixX.ApplyOnPoint(p1);
                this.matrixX.ApplyOnPoint(p2);
                this.matrixY.ApplyOnPoint(p1);
                this.matrixY.ApplyOnPoint(p2);
                this.matrixZ.ApplyOnPoint(p1);
                this.matrixZ.ApplyOnPoint(p2);

                points_top.Add(p1);
                points_bottom.Add(p2);
                angle += delta;
            }
        }

        Cylinder()
        {
            this.centerPoint = new Points();
            base.AddOneToCount(typeof(Cylinder));
            //generate_points();
        }

        private Cylinder(Points c, int d, bool tmp)
            : base(tmp)
        {
            this.centerPoint = c;
            this.Radius = d;
            this.Height = 100;
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

            b.AddRange(BitConverter.GetBytes((UInt32)Color.GetARGB()));
            b.AddRange(BitConverter.GetBytes((UInt16)Radius));

            return b.ToArray();
        }
    }
}
