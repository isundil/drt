using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace client
{
    public class Camera : AObjects
    {
        Camera(Camera o)
            : base(o)
        {
            this.Distance = o.Distance;
        }

        override public object Clone()
        {
            return new Camera(this);
        }

        public Camera()
        {
            this.centerPoint = new Points();
            this.Name = "Camera";
            this.Distance = 1000;

            UUID = "I'M SPARTACUS !";
        }
        public ushort Distance { get; set; }

        public override void Refresh() { }
        public override bool solve_equation_x(Points p) { return false; }
        public override bool solve_equation_y(Points p) { return false; }
        public override bool solve_equation_z(Points p) { return false; }
        public override void draw_x(System.Drawing.Image b, Viewport vp, bool selected) { }
        public override void draw_y(System.Drawing.Image b, Viewport vp, bool selected) { }
        public override void draw_z(System.Drawing.Image b, Viewport vp, bool selected) { }
        public override int getSubModule() { return 0; }
        override public byte[] getBytes()
        {
            List<byte> b = new List<byte>();

            b.AddRange(BitConverter.GetBytes((Int16)this.X));
            b.AddRange(BitConverter.GetBytes((Int16)this.Y));
            b.AddRange(BitConverter.GetBytes((Int16)this.Z));

            b.AddRange(BitConverter.GetBytes((double)this.dRotX));
            b.AddRange(BitConverter.GetBytes((double)this.dRotY));
            b.AddRange(BitConverter.GetBytes((double)this.dRotZ));

            b.AddRange(BitConverter.GetBytes((UInt16)this.Distance));
            return b.ToArray();
        }
    }
}
