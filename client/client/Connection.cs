using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace client
{
    public partial class Connection : Form
    {
        public Connection()
        {
            InitializeComponent();
        }

        private void cancel_btn_Click(object sender, EventArgs e)
        {
            this.Owner.Close();
        }

        private void ok_btn_Click(object sender, EventArgs e)
        {
            Properties.Settings.Default.default_ip = ip.Text;
            Properties.Settings.Default.default_port = port.Text;

            (this.Owner as MainForm).client.NewConnection(ip.Text, (int)UInt32.Parse(port.Text));
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ip.Text = "192.168.1.172";
            port.Text = "8042";
            ok_btn_Click(sender, e);
        }

        public short Id { get; set; }

        private void port_Validating(object sender, CancelEventArgs e)
        {
            uint r;

            if (!UInt32.TryParse(port.Text, out r))
                e.Cancel = true;
        }

        private void ip_Validating(object sender, CancelEventArgs e)
        {
            string[] s = ip.Text.Split(new char[] { '.' });
            if (s.Length != 4) e.Cancel = true;
            foreach (var a in s) {
                int r;

                if (! Int32.TryParse(a, out r))
                {
                    e.Cancel = true;
                    break;
                }
                if (r < 0 || r > 255)
                {
                    e.Cancel = true;
                    break;
                }
            }
        }
    }
}
