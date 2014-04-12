using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client.Objects
{
    public class Plan : AObjects
    {
        Plan(Plan o)
            : base(o)
        { }

        override public object Clone()
        {
            return new Plan(this);
        }

        public override void Refresh()
        {
            generate_points();
        }

        static protected int count = 0;
        Plan()
        {
            this.centerPoint = new Points();
            base.AddOneToCount(typeof(Plan));
        }

        private Plan(Points c, bool tmp)
            : base(tmp)
        {
            this.centerPoint = c;
            this.Color = new MyColor(System.Drawing.Color.BlueViolet.ToArgb());

            generate_points();

            if (!tmp)
            {
                this.Name = "Plane" + base.AddOneToCount(typeof(Plan));
            }
        }

        private List<Points> points = new List<Points>();
        public void generate_points()
        {
            points.Clear();

            points.Add(
                   new Points()
                   {
                       X = -150,
                       Y = 150,
                       Z = 0
                   });
            points.Add(
                   new Points()
                   {
                       X = 150,
                       Y = 150,
                       Z = 0
                   });
            points.Add(
                   new Points()
                   {
                       X = 150,
                       Y = -150,
                       Z = 0
                   });
            points.Add(
                   new Points()
                   {
                       X = -150,
                       Y = -150,
                       Z = 0
                   });

            matrixX.ApplyOnPoint(points[0]);
            matrixY.ApplyOnPoint(points[0]);
            matrixZ.ApplyOnPoint(points[0]);
            matrixX.ApplyOnPoint(points[1]);
            matrixY.ApplyOnPoint(points[1]);
            matrixZ.ApplyOnPoint(points[1]);
            matrixX.ApplyOnPoint(points[2]);
            matrixY.ApplyOnPoint(points[2]);
            matrixZ.ApplyOnPoint(points[2]);
            matrixX.ApplyOnPoint(points[3]);
            matrixY.ApplyOnPoint(points[3]);
            matrixZ.ApplyOnPoint(points[3]);
        }

        new static public AObjects create_x(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            return new Plan(p1, tmp);
        }
        new static public AObjects create_y(Points p1, Points p2, Viewport vp, bool tmp = false)
        {

            return new Plan(p1, tmp);
        }
        new static public AObjects create_z(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            return new Plan(p1, tmp);
        }

        private void draw_points(Image b, Viewport vp, bool selected, Util.eView view)
        {
            var points_f = new Point[points.Count];
            var g = System.Drawing.Graphics.FromImage(b);

            for (var i = 0; i < points_f.Length; i++)
            {
                Points t = (Points)points[i].Clone();
                t.X += centerPoint.X;
                t.Y += centerPoint.Y;
                t.Z += centerPoint.Z;
                Util.convertToGe(t, vp, b, view);
                if (view == Util.eView.x) points_f[i] = new Point(t.Y, t.Z);
                if (view == Util.eView.y) points_f[i] = new Point(t.X, t.Z);
                if (view == Util.eView.z) points_f[i] = new Point(t.X, t.Y);
            }

            using (var pen = new Pen((selected ? System.Drawing.Color.White : Color.toColor())))
            {
                for (var id = 0; id < points_f.Length; id++)
                {
                    g.DrawLine(pen, points_f[id], points_f[(id + 1 >= points_f.Length ? 0 : id + 1)]);
                }
            }
        }

        public override void draw_x(System.Drawing.Image b, Viewport vp, bool selected)
        {
            draw_points(b, vp, selected, Util.eView.x);
        }

        public override void draw_y(System.Drawing.Image b, Viewport vp, bool selected)
        {
            draw_points(b, vp, selected, Util.eView.y);
        }

        public override void draw_z(System.Drawing.Image b, Viewport vp, bool selected)
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
                return _isInSegment(delta, p.Y, p.Z, p0.Y, p0.Z, p1.Y, p1.Z);
            }
            if (view == Util.eView.y)
            {
                return _isInSegment(delta, p.X, p.Z, p0.X, p0.Z, p1.X, p1.Z);
            }
            if (view == Util.eView.z)
            {
                return _isInSegment(delta, p.X, p.Y, p0.X, p0.Y, p1.X, p1.Y);
            }
            return false;
        }

        bool isInWireframe(Points p, Util.eView view)
        {
            if (   isInSegment(p, points[0], points[1], view)
                || isInSegment(p, points[1], points[2], view)
                || isInSegment(p, points[2], points[3], view)
                || isInSegment(p, points[3], points[0], view))
                return true;
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

        public override int getSubModule()
        {
            return Modules.Submodules[getModule()]["PLAN"];
        }

        public override byte[] getBytes(bool final_render = false)
        {
            List<byte> b = new List<byte>();

            b.AddRange(BitConverter.GetBytes((UInt32)Color.GetARGB()));

            AddLimits(b);

            return b.ToArray();
        }
    }
}
