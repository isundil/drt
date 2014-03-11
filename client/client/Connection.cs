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
            var r = (this.Owner as MainForm).client.NewConnection(ip.Text, (int) port.Value);

            if (r == false)
            {
                MessageBox.Show("Connection refused.");
            }
            else
            {
                this.Id = (this.Owner as MainForm).client.clientId;
                this.Close();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ip.Text = "192.168.175.129";
            port.Value = 8042;
        }

        public short Id { get; set; }
    }
}
