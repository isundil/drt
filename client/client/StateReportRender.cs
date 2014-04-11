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
    public partial class StateReportRender : Form
    {
        public delegate void PlusOneDelegate();
        public PlusOneDelegate PlusOne;
        public delegate void CloseDelegate();
        public CloseDelegate MyClose;
        public delegate void SetMaximumDelegate(int max);
        public SetMaximumDelegate SetMaximum;

        private void setMaximum(int max)
        {
            this.progressBar1.Maximum = max;
            this.progressBar1.CustomText = 0.ToString() + " / " + max;
        }

        private void myclose()
        {
            this.Close();
        }

        private void plusOne()
        {
            this.progressBar1.Value++;
            this.progressBar1.CustomText = this.progressBar1.Value.ToString() + " / " + this.progressBar1.Maximum;
        }

        public StateReportRender()
        {
            InitializeComponent();
            this.progressBar1.Value = 0;
            progressBar1.DisplayStyle = ProgressBarDisplayText.CustomText;
            PlusOne = plusOne;
            MyClose = myclose;
            SetMaximum = setMaximum;
        }
    }
}
