using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class Cone : AObjects
    {
        Cone(Cone o)
            : base(o)
        {
            this.Height = o.Height;
        }

        override public object Clone()
        {
            return new Cone(this);
        }

        new static public AObjects create_x(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            var d = (int)Math.Sqrt(Math.Pow(p2.Y - p1.Y, 2) + Math.Pow(p2.Z - p1.Z, 2));
            return new Cone(p1, d, tmp);
        }
        new static public AObjects create_y(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Z - p2.Z, 2) + Math.Pow(p1.X - p2.X, 2));

            return new Cone(p1, d, tmp);
        }
        new static public AObjects create_z(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Y - p2.Y, 2) + Math.Pow(p1.X - p2.X, 2));

            return new Cone(p1, d, tmp);
        }

        private void draw_points(Image b, Viewport vp, bool selected, Util.eView view)
        {
            var points_f1 = new Point[points_top.Count];
            var points_f2 = new Point[points_bottom.Count];
            Point cp = new Point();
            var g = System.Drawing.Graphics.FromImage(b);

            for (var i = 0; i < points_f1.Length; i++)
            {
                Points t1 = (Points)points_top[i].Clone();
                Points t2 = (Points)points_bottom[i].Clone();
                Points c = (Points)centerPoint.Clone();
                t1.X += centerPoint.X;
                t1.Y += centerPoint.Y;
                t1.Z += centerPoint.Z;
                t2.X += centerPoint.X;
                t2.Y += centerPoint.Y;
                t2.Z += centerPoint.Z;
                Util.convertToGe(t1, vp, b, view);
                Util.convertToGe(t2, vp, b, view);
                Util.convertToGe(c, vp, b, view);
                if (view == Util.eView.x) cp = new Point(c.Y, c.Z);
                if (view == Util.eView.y) cp = new Point(c.X, c.Z);
                if (view == Util.eView.z) cp = new Point(c.X, c.Y);
                if (view == Util.eView.x) points_f1[i] = new Point(t1.Y, t1.Z);
                if (view == Util.eView.y) points_f1[i] = new Point(t1.X, t1.Z);
                if (view == Util.eView.z) points_f1[i] = new Point(t1.X, t1.Y);
                if (view == Util.eView.x) points_f2[i] = new Point(t2.Y, t2.Z);
                if (view == Util.eView.y) points_f2[i] = new Point(t2.X, t2.Z);
                if (view == Util.eView.z) points_f2[i] = new Point(t2.X, t2.Y);
            }

            using (var pen = new Pen((selected ? System.Drawing.Color.White : Color.toColor())))
            {
                for (var id = 0; id < points_f1.Length; id++)
                {
                    g.DrawLine(pen, points_f1[id], cp);
                    g.DrawLine(pen, points_f2[id], cp);
                }
                g.DrawClosedCurve(pen, points_f1);
                g.DrawClosedCurve(pen, points_f2);
            }
        }

        override public void draw_x(Image b, Viewport vp, bool selected)
        {
            draw_points(b, vp, selected, Util.eView.x);
        }

        override public void draw_y(Image b, Viewport vp, bool selected)
        {
            draw_points(b, vp, selected, Util.eView.y);
        }
        override public void draw_z(Image b, Viewport vp, bool selected)
        {
            draw_points(b, vp, selected, Util.eView.z);
        }

        bool is_between (float x, float bound1, float bound2, float delta)
        {
           return (((x >= (bound1 - delta)) && (x <= (bound2 + delta))) || ((x >= (bound2 - delta)) && (x <= (bound1 + delta))));
        }

        private bool _isInSegment(float delta, int pY, int pZ, int p0Y, int p0Z, int p1Y, int p1Z)
        {
            if (is_between(pY, p0Y, p1Y, delta) && is_between(pZ, p0Z, p1Z, delta))
            {
                if (Math.Abs(p1Y - p0Y) <= delta)
                {
                    return (true);
                }

                float M = (float)(p1Z - p0Z) / (p1Y - p0Y);
                float C = -(M * pY) + pZ;

                return (Math.Abs(C) <= delta);
            }
            return false;
        }

        bool isInSegment(Points p, Points p2, Points p3, Util.eView view)
        {
            float delta = 10f;
            Points p0 = (Points)p2.Clone();
            Points p1 = (Points)p3.Clone();
            p0.X += centerPoint.X;
            p1.X += centerPoint.X;
            p0.Y += centerPoint.Y;
            p1.Y += centerPoint.Y;
            p0.Z += centerPoint.Z;
            p1.Z += centerPoint.Z;

            if (view == Util.eView.x)
            {
                return _isInSegment(delta, p.Y, p.Z, centerPoint.Y, centerPoint.Z, p0.Y, p0.Z)
                    || _isInSegment(delta, p.Y, p.Z, p1.Y, p1.Z, centerPoint.Y, centerPoint.Z);
            }
            if (view == Util.eView.y)
            {
                return _isInSegment(delta, p.X, p.Z, p0.X, p0.Z, centerPoint.X, centerPoint.Z)
                    || _isInSegment(delta, p.X, p.Z, centerPoint.X, centerPoint.Z, p1.X, p1.Z);
            }
            if (view == Util.eView.z)
            {
                return _isInSegment(delta, p.X, p.Y, p0.X, p0.Y, centerPoint.X, centerPoint.Y)
                    || _isInSegment(delta, p.X, p.Y, centerPoint.X, centerPoint.Y, p1.X, p1.Y);
            }
            return false;
        }

        bool isInWireframe(Points p, Util.eView view)
        {
            if (isInSegment(p, points_top[0], points_bottom[0], view)) return true;
            for (var i = 1; i < points_top.Count; i++)
            {
                if (isInSegment(p, points_top[i - 1], points_top[i], view)
                    || isInSegment(p, points_bottom[i - 1], points_bottom[i], view)
                    || isInSegment(p, points_bottom[i], points_top[i], view))
                    return true;
            }
            return false;
        }

        public override bool solve_equation_x(Points p)
        {
            return isInWireframe(p, Util.eView.x);
        }
        public override bool solve_equation_y(Points p)
        {
            return isInWireframe(p, Util.eView.y);
        }
        public override bool solve_equation_z(Points p)
        {
            return isInWireframe(p, Util.eView.z);
        }

        static protected int count = 0;

        private List<Points> points_top = new List<Points>();
        private List<Points> points_bottom = new List<Points>();
        public void generate_points()
        {
            double angle = 0;
            double delta = Math.PI / Math.Pow(2, 3);
            points_top.Clear();
            points_bottom.Clear();

            while (angle < 2 * Math.PI)
            {
                points_top.Add(
                    new Points()
                    {
                        X = (int)(this.Radius * Math.Cos(angle)),
                        Y = (int)(this.Radius * Math.Sin(angle)),
                        Z = (int)(Height / 2)
                    }
                    );
                points_bottom.Add(
                    new Points()
                    {
                        X = (int)(this.Radius * Math.Cos(angle)),
                        Y = (int)(this.Radius * Math.Sin(angle)),
                        Z = (int)(-Height / 2)
                    }
                    );

                matrixX.ApplyOnPoint(points_top[points_top.Count - 1]);
                matrixX.ApplyOnPoint(points_bottom[points_bottom.Count - 1]);
                matrixY.ApplyOnPoint(points_top[points_top.Count - 1]);
                matrixY.ApplyOnPoint(points_bottom[points_bottom.Count - 1]);
                matrixZ.ApplyOnPoint(points_top[points_top.Count - 1]);
                matrixZ.ApplyOnPoint(points_bottom[points_bottom.Count - 1]);
                angle += delta;
            }
        }

        public uint Height { get; set; }

        Cone()
        {
            this.centerPoint = new Points();
            base.AddOneToCount(typeof(Cone));
        }

        private Cone(Points c, int d, bool tmp)
            : base(tmp)
        {
            this.centerPoint = c;
            this.Radius = d;
            this.Height = 100;
            this.Color = new MyColor(System.Drawing.Color.Aquamarine.ToArgb());

            generate_points();

            if (!tmp)
            {
                this.Name = "Cone" + base.AddOneToCount(typeof(Cone));
            }
        }

        public override void Refresh()
        {
            generate_points();
        }

        override public int getSubModule()
        {
            return Modules.Submodules[getModule()]["CONE"];
        }

        override public byte[] getBytes(bool final_render = false)
        {
            List<byte> b = new List<byte>();
            double a = Math.Atan2(Radius, (double)Height / 2);

            b.AddRange(BitConverter.GetBytes((UInt32)Color.GetARGB()));
            b.AddRange(BitConverter.GetBytes((double)(a / 2)));

            AddLimits(b);

            return b.ToArray();
        }
    }
}
