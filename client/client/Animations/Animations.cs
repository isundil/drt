using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace client.Animations
{
    public partial class Animations : Form
    {
        Animatronic _animatronic;
        public Animatronic animatronic
        {
            get
            {
                return _animatronic;
            }
            set
            {
                _animatronic = value;
                this.dataGridView1.DataSource = _animatronic.animations;
            }
        }
        public ObjectsList objectslist { get; set; }

        public Animations()
        {
            InitializeComponent();
            animationtype.SelectedIndex = 0;
        }

        private void displayinfos()
        {
            int frames = 0;
            foreach (var a in _animatronic.animations)
            {
                if (a.StartingFrame + a.FrameNumber > frames)
                    frames = a.StartingFrame + a.FrameNumber;
            }
            decimal seconds = (decimal)frames / Animatronic.FRAMES_PER_SECOND;

            infosanimations.Text = "" +
                _animatronic.animations.Count + " animations" +
                ", for a total of " +
                frames + " frames, or " + seconds.ToString("F") +" seconds.";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var o = objectslist.GetById((int)appliesonobject.SelectedValue);
            var anim = BuildAnimation.build((string)animationtype.SelectedItem, o);
            anim.StartingFrame = (int)startingframe.Value;
            anim.FrameNumber = (int)numberofframes.Value;
            anim.Modifier = (int)modifiervalue.Value;

            _animatronic.AddAnimation(anim);
            displayinfos();
        }

        private void Animations_Load(object sender, EventArgs e)
        {
            appliesonobject.DataSource = objectslist.Collection;
            appliesonobject.DisplayMember = "Name";
            appliesonobject.ValueMember = "Id";
        }

        private void dataGridView1_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            displayinfos();
        }

        private void dataGridView1_UserDeletedRow(object sender, DataGridViewRowEventArgs e)
        {
            displayinfos();
        }
    }
}
