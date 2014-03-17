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
            _form.errorlabel.Text = "";
            _form.toolStripStatusLabel.Text = "Connected with id : " + Connection.clientId;
            _form.toolStripStatusLabel.Image = Properties.Resources.green;
        }

        private void Disconnect()
        {
            Connection.clientId = 0xffff;

            this.Connection.Disconnect();
            _form.toolStripStatusLabel.Text = "Disconnected";
            _form.toolStripStatusLabel.Image = Properties.Resources.red;

            this.CancelAsync();

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

            bool wait_for_instruction = false;
            while (true)
            {
                try
                {
                    byte b = 0;

                    if (wait_for_instruction == false)
                    {
                        if (Connection.GetByte(out b))
                        {
                            wait_for_instruction = true;
                        }
                    }

                    switch ((ConClient.eInstruction)b)
                    {
                        case ConClient.eInstruction.WELCOME:
                            if (Connection.WELCOME(out wait_for_instruction)) Connect();
                            else Disconnect();
                            break;
                        case ConClient.eInstruction.IDCH:
                            if (Connection.IDCH(out wait_for_instruction)) Connect();
                            else Disconnect();
                            break;
                        case ConClient.eInstruction.RESULT:
                            Connection.RESULT(_form, out wait_for_instruction);
                            break;
                        case ConClient.eInstruction.COMPILFAIL:
                            throw new NotImplementedException();
                            break;
                        default:
                            Disconnect();
                            break;
                    }
                }
                catch (Exception ex)
                {
                    _form.errorlabel.Text = ex.Message;
                    Disconnect();
                }
            }
        }
    }
}
