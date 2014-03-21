using System;
using System.IO;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace client
{
    public partial class MainForm : Form
    {
        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void connectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ShowConnection();
        }

        private void redraw3DToolStripMenuItem_Click(object sender, EventArgs e)
        {
            redraw(true);
        }

        class Nfile
        {
            public string Nshort { get; set; }
            public string Nlong { get; set; }
        }
        Nfile currentfile = new Nfile();

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (currentfile.Nlong != null)
            {
                var x = new XmlSerializer(ol.GetType());
                TextWriter tw = new StreamWriter(currentfile.Nlong);
                try { x.Serialize(tw, ol); }
                catch { MessageBox.Show("An error occured saving the file"); }

                saveAsToolStripMenuItem.Enabled = true;
            }
            else
            {
                loadToolStripMenuItem_Click(sender, e);
            }
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var x = new XmlSerializer(ol.GetType());

            var f = new OpenFileDialog();
            f.Filter = "DRT Save file|*.drt";
            f.InitialDirectory = Environment.CurrentDirectory;
            f.CustomPlaces.Add(new FileDialogCustomPlace(Environment.CurrentDirectory));
            if (f.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                TextReader tr = new StreamReader(f.FileName);
                AObjects.Reinit();

                try
                {
                    ol = x.Deserialize(tr) as ObjectsList;

                    currentfile.Nlong = f.FileName;
                    FileInfo ff = new FileInfo(currentfile.Nlong);
                    currentfile.Nshort = ff.Name;
                    this.Text = currentfile.Nshort;

                    saveAsToolStripMenuItem.Enabled = true;

                    ol.Collection.form = this;
                    comboBox1.DataSource = ol.Collection;

                    redraw();
                }
                catch (System.InvalidOperationException)
                {
                    MessageBox.Show("Error, the file you specified is invalid");
                }
            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var x = new XmlSerializer(ol.GetType());

            var f = new SaveFileDialog();
            f.AddExtension = true;

            f.Filter = "DRT Save file|*.drt";
            f.InitialDirectory = Environment.CurrentDirectory;
            f.CustomPlaces.Add(new FileDialogCustomPlace(Environment.CurrentDirectory));

            if (f.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                TextWriter tw = new StreamWriter(f.FileName);
                try
                {
                    x.Serialize(tw, ol);

                    currentfile.Nlong = f.FileName;
                    FileInfo ff = new FileInfo(currentfile.Nlong);
                    currentfile.Nshort = ff.Name;
                    this.Text = currentfile.Nshort;
                }
                catch
                {
                    MessageBox.Show("An error occured saving the file");
                }
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new About().Show();
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.SPHERE;

            this.Cursor = new Cursor(Properties.Resources.circle_ptr.GetHicon());
        }

        private void cylinder_toolstrip_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.CYLINDER;

            this.Cursor = new Cursor(Properties.Resources.cylinder_ptr.GetHicon());
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.NONE;

            this.Cursor = new Cursor(Properties.Resources.pointer_ptr.GetHicon());
        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.GRAB;

            this.Cursor = new Cursor(Properties.Resources.drag_ptr.GetHicon());
        }

        private void toolStripButton4_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.RESIZE;

            this.Cursor = new Cursor(Properties.Resources.resize_ptr.GetHicon());
        }

        private void rotate_toolstrip_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.ROTATE;

            this.Cursor = new Cursor(Properties.Resources.rotate_ptr.GetHicon());
        }

        private void zoomin_toolstrip_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.ZOOMIN;

            this.Cursor = new Cursor(Properties.Resources.zoomin_ptr.GetHicon());
        }

        private void zoomout_toolstrip_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.ZOOMOUT;

            this.Cursor = new Cursor(Properties.Resources.zoomout_ptr.GetHicon());
        }

        private void light_toolstrip_Click(object sender, EventArgs e)
        {
            this.drawMode = eDrawMode.LIGHT;

            this.Cursor = new Cursor(Properties.Resources.light_ptr.GetHicon());
        }
    }

}
