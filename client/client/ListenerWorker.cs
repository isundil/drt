using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace client
{
    public class ListenerWorker : BackgroundWorker
    {
        private ConClient Connection { get; set; }

        public ListenerWorker(ConClient con)
        {
            this.Connection = con;
            this.DoWork += new DoWorkEventHandler(doListen);
            this.RunWorkerAsync();
        }

        private void doListen(object o, DoWorkEventArgs e)
        {
            if (Connection == null) return;

        }
    }
}
