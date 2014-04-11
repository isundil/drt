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
        private AObjects applieson;
        public string AppliesOn
        {
            get
            {
                return applieson.Name;
            }
            private set { }
        }
        public int StartingFrame { get; set; }
        public int FrameNumber { get; set; }
        public int Modifier { get; set; }

        public AAnimation()
        { }
        public AAnimation(AObjects o)
        {
            applieson = o;
        }
    }

    public class TranslateX : AAnimation
    {
        public TranslateX(AObjects o) : base(o) { Type = "Translate X"; }
    }
    public class TranslateY : AAnimation
    {
        public TranslateY(AObjects o) : base(o) { Type = "Translate Y"; }
    }
    public class TranslateZ : AAnimation
    {
        public TranslateZ(AObjects o) : base(o) { Type = "Translate Z"; }
    }

    public class RotateX : AAnimation
    {
        public RotateX(AObjects o) : base(o) { Type = "Rotate X"; }
    }
    public class RotateY : AAnimation
    {
        public RotateY(AObjects o) : base(o) { Type = "Rotate Y"; }
    }
    public class RotateZ : AAnimation
    {
        public RotateZ(AObjects o) : base(o) { Type = "Rotate Z"; }
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
