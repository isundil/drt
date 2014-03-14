using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class CalculusWorker : BackgroundWorker
    {
        private ObjectsList ol;

        public System.Drawing.Image DestinationImage { get; set; }
        public ConClient Connection { get; set; }

        private void doScenePreviewCalculus(object o, DoWorkEventArgs e)
        {
            var s = SceneTransform.TransformPreview(ol);
  
            Connection.NEWJOB(s, DestinationImage.Size);
        }

        public CalculusWorker()
        {
            this.DoWork += new DoWorkEventHandler(doScenePreviewCalculus);
        }

        public void DoScenePreviewCalculus(ObjectsList ol)
        {
            this.ol = ol;
            this.RunWorkerAsync();
        }
    }
}
