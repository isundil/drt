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
            this.Color = new MyColor(System.Drawing.Color.Silver.ToArgb());

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
            throw new NotImplementedException();
        }

        public override void draw_y(System.Drawing.Image b, Viewport vp, bool selected)
        {
            throw new NotImplementedException();
        }

        public override void draw_z(System.Drawing.Image b, Viewport vp, bool selected)
        {
            throw new NotImplementedException();
        }

        public override bool solve_equation_x(Points p)
        {
            throw new NotImplementedException();
        }

        public override bool solve_equation_y(Points p)
        {
            throw new NotImplementedException();
        }

        public override bool solve_equation_z(Points p)
        {
            throw new NotImplementedException();
        }

        public override int getSubModule()
        {
            throw new NotImplementedException();
        }

        public override byte[] getBytes(bool final_render = false)
        {
            throw new NotImplementedException();
        }
    }
}
