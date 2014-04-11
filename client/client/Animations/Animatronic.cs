using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;

namespace client.Animations
{
    public class Animatronic
    {
        public readonly int FRAMES_PER_SECOND = 24;
     
        public Animatronic()
        {
            animations = new BindingList<AAnimation>();
            frames = new List<System.Drawing.Bitmap>();
        }

        public BindingList<AAnimation> animations { get; set; }

        List<System.Drawing.Bitmap> frames;

        public int FramesNumber { get { return frames.Count; } private set { } }

        public void AddAnimation(AAnimation anim)
        {
            animations.Add(anim);
        }

        private int index = 0;
        public void prepareFrames(Size screensize)
        {
            index = 0;
            foreach (var a in animations)
            {
                while (a.StartingFrame + a.FrameNumber > FramesNumber)
                {
                    frames.Add(new System.Drawing.Bitmap(screensize.Width, screensize.Height));
                }
            }
        }

        public Bitmap getNextFrame()
        {
            if (index >= frames.Count) return null;
            return frames[index++];
        }
    }
}
