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
    public partial class Monitoring : UserControl
    {
        public Monitoring()
        {
            InitializeComponent();

            this.cpu_usage.BackColor = Color.CadetBlue;
            this.cpu_usage.ForeColor = Color.Gray;
            this.ram_usage.BackColor = Color.SpringGreen;
            this.ram_usage.ForeColor = Color.Gray;

            this.cpu_usage.DisplayStyle = ProgressBarDisplayText.Percentage;
            this.ram_usage.DisplayStyle = ProgressBarDisplayText.CustomText;

            this.cpu_usage.Value = 0;
            this.cpu_usage.Maximum = 100;
            this.ram_usage.CustomText = "? / ?";
        }

        public void UpdateMonitor(byte cpu, UInt32 ramuse, UInt32 rammax)
        {
            if (ramuse > rammax) return;

            string u = "MB";
            if (rammax > 1024 * 1024)
            {
                rammax = (UInt32)Math.Floor((double)rammax / 1024);
                ramuse = (UInt32)Math.Floor((double)ramuse / 1024);
                u = "GB";
            }

            this.cpu_usage.Value = (cpu * 100) / 255;
            this.ram_usage.Maximum = (int) rammax;
            this.ram_usage.CustomText = ramuse.ToString() + " / " + rammax.ToString() + " " + u;
            this.ram_usage.Value = (int)ramuse;
        }
    }
}
