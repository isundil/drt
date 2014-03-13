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
        private MainForm _form;

        public ListenerWorker(ConClient con, MainForm form)
        {
            this.Connection = con;
            _form = form;
            this.DoWork += new DoWorkEventHandler(doListen);
        }

        private void Connect()
        {
            _form.toolStripStatusLabel.Text = "Connected with id : " + Connection.clientId;
            _form.toolStripStatusLabel.Image = Properties.Resources.green;
        }

        private void Disconnect()
        {
            Connection.clientId = -1;

            this.Connection.Disconnect();
            _form.toolStripStatusLabel.Text = "Disconnected";
            _form.toolStripStatusLabel.Image = Properties.Resources.red;

            try
            {
                _form.Invoke(_form.Connect);
            }
            catch (Exception)
            { }
        }

        private void doListen(object o, DoWorkEventArgs e)
        {
            if (Connection == null) return;

            while (true)
            {
                try
                {
                    byte b = Connection.ReadSync();

                    switch ((client.ConClient.eInstruction)b)
                    {
                        case ConClient.eInstruction.WELCOME:
                            if (Connection.WELCOME()) Connect();
                            else Disconnect();
                            break;
                        case ConClient.eInstruction.IDCH:
                            if (Connection.IDCH()) Connect();
                            else Disconnect();
                            break;
                        case ConClient.eInstruction.RESULT:
                        case ConClient.eInstruction.COMPILFAIL:
                            throw new NotImplementedException();
                            break;
                        default:
                            Disconnect();
                            break;
                    }
                }
                catch (Exception)
                {
                    Disconnect();
                }
            }
        }
    }
}
