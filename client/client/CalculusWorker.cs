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

        private void doScenePreviewCalculus(object o, DoWorkEventArgs e)
        {
            var s = SceneTransform.TransformPreview(ol);

            
        }

        public void DoScenePreviewCalculus(ObjectsList ol)
        {
            this.ol = ol;
            this.DoWork += new DoWorkEventHandler(doScenePreviewCalculus);
        }
    }
}
