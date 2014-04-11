using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media.Imaging;

namespace client.Animations
{
    public class Animatronic
    {
        static public readonly int FRAMES_PER_SECOND = 24;
     
        public Animatronic()
        {
            animations = new BindingList<AAnimation>();
            frames = new List<System.Drawing.Bitmap>();
        }

        private BitmapSource toBitmapConvert(Bitmap bitmap)
        {
            BitmapSource i = Imaging.CreateBitmapSourceFromHBitmap(
                           bitmap.GetHbitmap(),
                           IntPtr.Zero,
                           Int32Rect.Empty,
                           BitmapSizeOptions.FromEmptyOptions());
            return i;
        }

        public void Animate(FinalRender renderer)
        {
            MemoryStream stream = new MemoryStream();
            FileStream teststream = new FileStream(@"C:\Users\Kim\Desktop\TEST.GIF", FileMode.Create);
            var encoder = new System.Windows.Media.Imaging.GifBitmapEncoder();
            var testencoder = new System.Windows.Media.Imaging.GifBitmapEncoder();
            foreach (var f in frames)
            {
                encoder.Frames.Add(BitmapFrame.Create(toBitmapConvert(f)));
                testencoder.Frames.Add(BitmapFrame.Create(toBitmapConvert(f)));
            }
            encoder.Save(stream);
            testencoder.Save(teststream);

            renderer.Picture.Image = Image.FromStream(stream);
        }

        public BindingList<AAnimation> animations { get; set; }

        List<System.Drawing.Bitmap> frames;

        public int CurrentFrame { get { return index; } private set { } }
        public int FramesNumber { get { return frames.Count; } private set { } }

        public void AddAnimation(AAnimation anim)
        {
            animations.Add(anim);
        }

        private int index = 0;
        public void prepareFrames(System.Drawing.Size screensize)
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
