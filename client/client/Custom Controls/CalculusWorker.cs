﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class CalculusWorker : BackgroundWorker
    {
        private AObjects[] ol;
        private Animations.Animatronic animatronic;
        private MainForm form;

        public System.Drawing.Image DestinationImage { get; set; }
        public ConClient Connection { get; set; }

        public bool Offline { get; set; }

        private void doScenePreviewCalculus(object o, DoWorkEventArgs e)
        {
            if (Mode != MODE.PREVIEW) return;
            var s = SceneTransform.TransformPreview(ol);
            
            if (! this.Offline) Connection.NEWJOB(s, DestinationImage.Size);
        }

        private void doFinalRenderCalculus(object o, DoWorkEventArgs e)
        {
            if (Mode != MODE.RENDER) return;

            render.Render.Invoke(render.Render.MyClose);
            var s = SceneTransform.TransformRender(ol, form.finalrender.Checked);
            if (!this.Offline) Connection.NEWJOB(s, DestinationImage.Size);
        }

        private AObjects getFromUUID(string uuid)
        {
            foreach (var o in ol)
            {
                if (o.UUID == uuid) return o;
            }
            return null;
        }

        private void apply_transformations()
        {
            foreach (var a in animatronic.animations)
            {
                if (animatronic.CurrentFrame >= a.StartingFrame && animatronic.CurrentFrame < a.StartingFrame + a.FrameNumber)
                {
                    var o = getFromUUID(a.UUID);
                    if (o == null) continue;
                    a.ApplyOnObject(o);
                }
            }
        }

        private void doFinalRenderWithAnimationsCalculus(object o, DoWorkEventArgs e)
        {
            if (Mode != MODE.ANIM) return;


            var s = SceneTransform.TransformRender(ol, form.finalrender.Checked);
            var frame = animatronic.getNextFrame();
            if (frame == null)
            {
                render.Render.Invoke(render.Render.MyClose);
                animatronic.Animate(render);
                return;
            }

            apply_transformations();

            form.pdestination = null;
            form.destination = frame;
            this.DestinationImage = frame;

            render.Render.Invoke(render.Render.PlusOne);
            if (!this.Offline) Connection.NEWJOB(s, frame.Size);
        }

        public CalculusWorker()
        {
            this.DoWork += new DoWorkEventHandler(doScenePreviewCalculus);
            this.DoWork += new DoWorkEventHandler(doFinalRenderCalculus);
            this.DoWork += new DoWorkEventHandler(doFinalRenderWithAnimationsCalculus);
        }

        public enum MODE {
            PREVIEW,
            RENDER,
            ANIM
        };
        public MODE Mode;

        public void DoScenePreviewCalculus(ObjectsList ol)
        {
            this.ol = ol.Items;
            Mode = MODE.PREVIEW;
            this.RunWorkerAsync();
        }

        FinalRender render;
        public void DoFinalRenderCalculus(ObjectsList ol, MainForm f, FinalRender r)
        {
            this.ol = ol.Items;

            this.animatronic = ol.Animatronic;
            this.form = f;
            this.render = r;

            if (animatronic.FramesNumber == 0 || form.skipanimations.Checked)
                Mode = MODE.RENDER;
            else
            {
                render.Render.Invoke(render.Render.SetMaximum, new object[] { animatronic.FramesNumber });
                Mode = MODE.ANIM;
            }

            this.RunWorkerAsync();
        }
    }
}
