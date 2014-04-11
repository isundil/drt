using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client.Animations
{
    public abstract class AAnimation
    {
        public string Type { get; protected set; }
        public string AppliesOn { get; set; }
        public int StartingFrame { get; set; }
        public int FrameNumber { get; set; }
        int modifier;
        public int Modifier
        {
            get
            {
                return modifier;
            }
            set
            {
                modifier = value;
                modifier_per_frame = (double)modifier / Animatronic.FRAMES_PER_SECOND;
            }
        }
        protected double modifier_per_frame;
        public string UUID { get; set; }

        public AAnimation()
        { }
        public AAnimation(AObjects o)
        {
            this.UUID = o.UUID;
            this.AppliesOn = o.Name;
        }

        public abstract void ApplyOnObject(AObjects o);
    }

    public class TranslateX : AAnimation
    {
        public TranslateX(AObjects o) : base(o) { Type = "Translate X"; }
        override public void ApplyOnObject(AObjects o)
        {
            o.X = (int)(o.X + this.modifier_per_frame);
        }
    }
    public class TranslateY : AAnimation
    {
        public TranslateY(AObjects o) : base(o) { Type = "Translate Y"; }
        override public void ApplyOnObject(AObjects o)
        {
            o.Y = (int)(o.Y + this.modifier_per_frame);
        }
    }
    public class TranslateZ : AAnimation
    {
        public TranslateZ(AObjects o) : base(o) { Type = "Translate Z"; }
        override public void ApplyOnObject(AObjects o)
        {
            o.Z = (int)(o.Z + this.modifier_per_frame);
        }
    }

    public class RotateX : AAnimation
    {
        public RotateX(AObjects o) : base(o) { Type = "Rotate X"; }
        override public void ApplyOnObject(AObjects o)
        {
            o.RotX = (int)(o.RotX + this.modifier_per_frame);
        }
    }
    public class RotateY : AAnimation
    {
        public RotateY(AObjects o) : base(o) { Type = "Rotate Y"; }
        override public void ApplyOnObject(AObjects o)
        {
            o.RotY = (int)(o.RotY + this.modifier_per_frame);
        }
    }
    public class RotateZ : AAnimation
    {
        public RotateZ(AObjects o) : base(o) { Type = "Rotate Z"; }
        override public void ApplyOnObject(AObjects o)
        {
            o.RotZ = (int)(o.RotZ + this.modifier_per_frame);
        }
    }

    static public class BuildAnimation
    {
        public static AAnimation build(string name, AObjects o)
        {
            switch (name)
            {
                case "Translate X":
                    return new TranslateX(o);
                case "Translate Y":
                    return new TranslateY(o);
                case "Translate Z":
                    return new TranslateZ(o);
                case "Rotate X":
                    return new RotateX(o);
                case "Rotate Y":
                    return new RotateY(o);
                case "Rotate Z":
                    return new RotateZ(o);
            }
            return null;
        }
    }
}
