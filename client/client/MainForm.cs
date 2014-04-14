using client.Animations;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace client
{
    public partial class MainForm : Form
    {
        Viewport vp = new Viewport();
        ObjectsList ol;
        public ConClient client;

        public MainForm()
        {
            InitializeComponent();

            this.Icon = Properties.Resources.icon;
            this.Cursor = new Cursor(Properties.Resources.pointer_ptr.GetHicon());

            ol = new ObjectsList(this);

            comboBox1.DataSource = ol.Collection;
            comboBox1.DisplayMember = "Name";
            comboBox1.ValueMember = "Id";
        }

        private ListenerWorker listenerWorker = null;
        public delegate void ConnectDelegate();
        public ConnectDelegate Connect;
        public delegate void DrawPixelDelegate(ushort src, int x, int y, Color c);
        public DrawPixelDelegate DrawPixel;
        public delegate void DrawChunkDelegate(ushort src, ushort w, ushort h, int minx, int miny, byte[] bufpels);
        public DrawChunkDelegate DrawChunk;
        public delegate void MonitorDelegate(byte cpu, UInt32 ramuse, UInt32 rammax);
        public MonitorDelegate Monitor;

        private void ShowConnection()
        {
            var con = new Connection();
            var res = con.ShowDialog(this);
            if (res == System.Windows.Forms.DialogResult.OK && this.client.isAvailable())
            {
                Properties.Settings.Default.Save();
                listenerWorker.Offline = false;
                calculusWorker.Offline = false;
            }
            else if (res == System.Windows.Forms.DialogResult.Ignore)
            {
                listenerWorker.Offline = true;
                calculusWorker.Offline = true;
            }
            else if (res == System.Windows.Forms.DialogResult.Cancel)
            {
                this.Close();
            }
        }

        private void UpdateMonitor(byte cpu, UInt32 ramuse, UInt32 rammax)
        {
            monitoring1.UpdateMonitor(cpu, ramuse, rammax);
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            vp.GridLevel = 10;
            this.Connect = new ConnectDelegate(ShowConnection);
            this.DrawPixel = new DrawPixelDelegate(DrawPixel3DView);
            this.DrawChunk = new DrawChunkDelegate(DrawChunk3DView);
            this.Monitor = new MonitorDelegate(UpdateMonitor);

            this.antialias.SelectedIndex = 0;

            td_bitmap = new Bitmap(view_3d.Width, view_3d.Height);
            empty_bitmap(td_bitmap);
            view_3d.Image = td_bitmap;

            this.client = new ConClient();
            this.listenerWorker = new ListenerWorker(client, this);
            this.listenerWorker.WorkerSupportsCancellation = true;
            this.listenerWorker.Offline = false;
            this.calculusWorker.Offline = false;

            calculusWorker.Connection = client;
            calculusWorker.DestinationImage = view_3d.Image;

            ol.Add(new Camera());
            ol.Selected = ol.Collection[0];
            redraw();

            show_server_mapping.Enabled = false;
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            td_bitmap = new Bitmap(view_3d.Width, view_3d.Height);
            empty_bitmap(td_bitmap);
            view_3d.Image = td_bitmap;

            redraw();
        }

        AObjects copy = null;
        private void MainForm_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                if (ol.Selected != null && ol.Selected != ol.Collection[0])
                {
                    ol.Remove(ol.Selected);
                    ol.Selected = null;
                    redraw();
                    e.Handled = true;
                }
            }
            if (e.Control && e.KeyCode == Keys.C)
            {
                if (ol.Selected != ol.Items[0])
                copy = ol.Selected.Clone() as AObjects;
                e.Handled = true;
            }
            if (e.Control && e.KeyCode == Keys.V)
            {
                if (copy != null)
                {
                    var cpy = copy.Copy();
                    ol.Add(cpy);
                    ol.Selected = cpy;
                    e.Handled = true;
                }
            }
        }

        private void propertyGrid_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            ol.Selected.Refresh();
            redraw();
        }

        private void comboBox1_SelectedValueChanged(object sender, EventArgs e)
        {
            var c = sender as ComboBox;
            if (c.SelectedIndex >= 0)
            {
                ol.Selected = ol.Collection[c.SelectedIndex];
                redraw();
            }
        }

        private void show_server_mapping_CheckedChanged(object sender, EventArgs e)
        {
            if (!show_server_mapping.Checked)
            {
                view_3d.Image = td_bitmap;
                return;
            }

            Bitmap bm = new Bitmap(td_bitmap.Width, td_bitmap.Height);
            Color[] colors = new Color[10] {
                Color.Red, Color.Blue, Color.Green, Color.Gold, Color.Silver,
                Color.Violet, Color.Turquoise, Color.Pink, Color.AliceBlue, Color.Black
            };

            int x = 0;
            int y = 0;

            var imagepixels = td_bitmap.Width * td_bitmap.Height;
            var maxpixels = 0;
            foreach (var key in servers_map.Keys)
            { maxpixels += servers_map[key]; }

            foreach (var key in servers_map.Keys)
            {
                var nbpixels = ((double)((double)servers_map[key] * imagepixels)) / maxpixels;
                for (var i = 0; i < nbpixels; i++)
                {
                    bm.SetPixel(x, y, colors[key % colors.Length]);

                    y++;
                    if (y >= td_bitmap.Height)
                    {
                        y = 0;
                        x++;
                    }
                }
            }

            view_3d.Image = bm;
        }

        private void antialias_SelectedValueChanged(object sender, EventArgs e)
        {
            if (antialias.SelectedItem != null)
            {
                AAX = Int32.Parse(antialias.SelectedItem.ToString());
            }
        }
    }
}
