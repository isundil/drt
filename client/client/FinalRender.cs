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
    public partial class FinalRender : Form
    {
        private Animations.Animatronic animatronic;
        public StateReportRender Render = new StateReportRender();

        public FinalRender(Animations.Animatronic a)
        {
            InitializeComponent();
            animatronic = a;
            var bm = new Bitmap(pictureBox1.Size.Width, pictureBox1.Size.Height);
            using (var g = System.Drawing.Graphics.FromImage(bm))
            {
                g.Clear(Color.Black);
            }
            pictureBox1.Image = bm;
        }

        private void FinalRender_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape) this.Close();
        }

        private void FinalRender_Load(object sender, EventArgs e)
        {
            animatronic.prepareFrames(pictureBox1.Size);

            Render.Show();
        }
    }
}
