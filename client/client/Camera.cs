using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    class Camera : AObjects
    {
        public Camera()
        {
            this.centerPoint = new Points();
            this.Name = "Camera";
        }

        public override void Refresh() { }
        public override bool solve_equation_x(Points p) { return false; }
        public override bool solve_equation_y(Points p) { return false; }
        public override bool solve_equation_z(Points p) { return false; }
        public override void draw_x(System.Drawing.Image b, Viewport vp, bool selected) { }
        public override void draw_y(System.Drawing.Image b, Viewport vp, bool selected) { }
        public override void draw_z(System.Drawing.Image b, Viewport vp, bool selected) { }
        public override int getSubModule() { return (int)eSubModules.CAMERA; }
        override public byte[] getBytes()
        {
            List<byte> b = new List<byte>();

            b.AddRange(BitConverter.GetBytes((UInt16)this.X));
            b.AddRange(BitConverter.GetBytes((UInt16)this.Y));
            b.AddRange(BitConverter.GetBytes((UInt16)this.Z));

            b.AddRange(BitConverter.GetBytes((double)this.RotX));
            b.AddRange(BitConverter.GetBytes((double)this.RotY));
            b.AddRange(BitConverter.GetBytes((double)this.RotZ));

            return b.ToArray();
        }
    }
}
