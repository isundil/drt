﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace client.Animations
{
    [XmlInclude(typeof(TranslateX))]
    [XmlInclude(typeof(TranslateY))]
    [XmlInclude(typeof(TranslateZ))]
    [XmlInclude(typeof(RotateX))]
    [XmlInclude(typeof(RotateY))]
    [XmlInclude(typeof(RotateZ))]
    public abstract class AAnimation
    {
        [XmlIgnore]
        public string Type { get; protected set; }
        [XmlIgnore]
        public string AppliesOn { get; set; }
        public int StartingFrame { get; set; }
        public int FrameNumber { get; set; }
        private int _modifier { get; set; }
        public int Modifier
        {
            get
            {
                return _modifier;
            }
            set
            {
                _modifier = value;
                this.modifier_per_frame = (double)Modifier / FrameNumber;
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
        public TranslateX() { Type = "Translate X"; }
        public TranslateX(AObjects o) : base(o) { Type = "Translate X"; }
        override public void ApplyOnObject(AObjects o)
        {
            o.X = (int)(o.X + this.modifier_per_frame);
        }
    }
    public class TranslateY : AAnimation
    {
        public TranslateY() { Type = "Translate Y"; }
        public TranslateY(AObjects o) : base(o) { Type = "Translate Y"; }
        override public void ApplyOnObject(AObjects o)
        {
            o.Y = (int)(o.Y + this.modifier_per_frame);
        }
    }
    public class TranslateZ : AAnimation
    {
        public TranslateZ() { Type = "Translate Z"; }
        public TranslateZ(AObjects o) : base(o) { Type = "Translate Z"; }
        override public void ApplyOnObject(AObjects o)
        {
            o.Z = (int)(o.Z + this.modifier_per_frame);
        }
    }

    public class RotateX : AAnimation
    {
        public RotateX() { Type = "Rotate X"; }
        public RotateX(AObjects o) : base(o) { Type = "Rotate X"; }
        override public void ApplyOnObject(AObjects o)
        {
            o.RotX = (int)(o.RotX + this.modifier_per_frame);
        }
    }
    public class RotateY : AAnimation
    {
        public RotateY() { Type = "Rotate Y"; }
        public RotateY(AObjects o) : base(o) { Type = "Rotate Y"; }
        override public void ApplyOnObject(AObjects o)
        {
            o.RotY = (int)(o.RotY + this.modifier_per_frame);
        }
    }
    public class RotateZ : AAnimation
    {
        public RotateZ() { Type = "Rotate Z"; }
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
