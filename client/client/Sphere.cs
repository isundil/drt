﻿using System;
using System.Collections.Generic;
using System.Drawing;

namespace client
{
    public class Sphere : AObjects
    {
        new static public AObjects create_x(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            var d = (int)Math.Sqrt(Math.Pow(p2.Y - p1.Y, 2) + Math.Pow(p2.Z - p1.Z, 2));
            return new Sphere(p1, d, tmp);
        }
        new static public AObjects create_y(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Z - p2.Z, 2) + Math.Pow(p1.X - p2.X, 2));

            return new Sphere(p1, d, tmp);
        }
        new static public AObjects create_z(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Y - p2.Y, 2) + Math.Pow(p1.X - p2.X, 2));

            return new Sphere(p1, d, tmp);
        }

        override public void draw_x(Image b, Viewport vp, bool selected)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            p.Y -= this.Radius;
            p.Z += this.Radius;
            Util.convertToGe(p, vp, b, Util.eView.x);

            g.DrawEllipse(new Pen((selected ? System.Drawing.Color.White : Color.toColor())), new Rectangle(
                    new Point(p.Y, p.Z),
                    new Size((int)(this.Radius * 2 * vp.fx), (int)(this.Radius * 2 * vp.fx))
                ));
        }
        override public void draw_y(Image b, Viewport vp, bool selected)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            p.X -= this.Radius;
            p.Z += this.Radius;
            Util.convertToGe(p, vp, b, Util.eView.y);

            g.DrawEllipse(new Pen((selected ? System.Drawing.Color.White : Color.toColor())), new Rectangle(
                    new Point(p.X, p.Z),
                    new Size((int)(this.Radius * 2 * vp.fy), (int)(this.Radius * 2 * vp.fy))
                ));
        }
        override public void draw_z(Image b, Viewport vp, bool selected)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            p.X -= this.Radius;
            p.Y += this.Radius;
            Util.convertToGe(p, vp, b, Util.eView.z);

            g.DrawEllipse(new Pen((selected ? System.Drawing.Color.White : Color.toColor())), new Rectangle(
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

        static protected int count = 0;
        Sphere()
        {
            this.centerPoint = new Points();
            base.AddOneToCount(typeof(Sphere));
        }

        private Sphere(Points c, int d, bool tmp)
            : base(tmp)
        {
            this.centerPoint = c;
            this.Radius = d;
            this.Color = new MyColor(System.Drawing.Color.SteelBlue.ToArgb());

            if (!tmp)
            {
                this.Name = "Sphere" + base.AddOneToCount(typeof(Sphere));
            }
        }

        override public int getSubModule()
        {
            return (int)eSubModules.SPHERE;
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
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            p.Y -= this.Radius;
            p.Z += this.Radius;
            Util.convertToGe(p, vp, b, Util.eView.x);

            g.DrawEllipse(new Pen((selected ? System.Drawing.Color.White : Color.toColor())), new Rectangle(
                    new Point(p.Y, p.Z),
                    new Size((int)(this.Radius * 2 * vp.fx), (int)(this.Radius * 2 * vp.fx))
                ));
        }
        override public void draw_y(Image b, Viewport vp, bool selected)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            p.X -= this.Radius;
            p.Z += this.Radius;
            Util.convertToGe(p, vp, b, Util.eView.y);

            g.DrawEllipse(new Pen((selected ? System.Drawing.Color.White : Color.toColor())), new Rectangle(
                    new Point(p.X, p.Z),
                    new Size((int)(this.Radius * 2 * vp.fy), (int)(this.Radius * 2 * vp.fy))
                ));
        }
        override public void draw_z(Image b, Viewport vp, bool selected)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            p.X -= this.Radius;
            p.Y += this.Radius;
            Util.convertToGe(p, vp, b, Util.eView.z);

            g.DrawEllipse(new Pen((selected ? System.Drawing.Color.White : Color.toColor())), new Rectangle(
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

        static protected int count = 0;
        Cylinder()
        {
            this.centerPoint = new Points();
            base.AddOneToCount(typeof(Cylinder));
        }

        private Cylinder(Points c, int d, bool tmp)
            : base(tmp)
        {
            this.centerPoint = c;
            this.Radius = d;
            this.Color = new MyColor(System.Drawing.Color.Red.ToArgb());

            if (!tmp)
            {
                this.Name = "Cylinder" + base.AddOneToCount(typeof(Cylinder));
            }
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
