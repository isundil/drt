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

        List<string> LOADING = new List<string>() {
            "I'M SPARRRTACUS !",
            "Preparing a Nutty Moka...",
            "Landing on the moon...",
            "Testing midichlorians rate...",
            "I see skies of green, red roses too...",
            "Climbing the yellow lemon tree...",
            "Washing the dishes...",
            "Conquering the world...",
            "Converting coffee into code...",
            "Launching the pokeball...",
            "Conjuring a unicorn...",
            "NYANYANYANYANYANYANYANYANYA NYAN NYAN NYANYA NYANYANYAN...",
            "Switching on the light...",
            "Switching off the light...",
            "Playing David Guetta sound...",
            "Making studid loading sentences...",
            "NAK NAK NAKNAAAAK !",
            "Forging one ring to rule them all...",
            "Making the awesome sonic RAINBOOOOM !"
        };

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
            changeLoadingSentence();
        }

        Random rand = new Random(Guid.NewGuid().GetHashCode());
        string pickOne()
        {
            var i = rand.Next(0, LOADING.Count);
            var s = LOADING[i];
            LOADING.RemoveAt(i);
            return s;
        }

        void changeLoadingSentence()
        {
            this.loadsentence.Text = pickOne();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            changeLoadingSentence();
        }
    }
}
