using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class ConClient
    {
        TcpClient con = null;

        public enum eInstruction
        {
            CAUTH       = 1,
            WELCOME     = 2,
            IDCH        = 3,
            NEWJOB      = 8,
            RESULT      = 13,
            COMPILFAIL  = 14
        }

        public void Disconnect()
        {
            if (con != null)
            con.Close();
        }

        int READ(NetworkStream n, byte[] buf, int size)
        {
            int read = 0;
            while (read < size)
            {
                read += n.Read(buf, read, size - read);
            }
            return read;
        }

        private void write_header(Scene s, System.Drawing.Size size, List<byte> buf)
        {
            var n = con.GetStream();

            byte nbr = (byte)s.RequestedModules.Count;

            buf.Add(nbr);
            foreach (var m in s.RequestedModules)
                buf.AddRange(SceneTransform.Modules[m]);

            buf.AddRange(BitConverter.GetBytes((UInt16)size.Width));
            buf.AddRange(BitConverter.GetBytes((UInt16)size.Height));
            buf.AddRange(s.Items[0].refObject.getBytes());
            s.Items.RemoveAt(0);
        }

        private void write_items(Scene s, List<byte> buf)
        {
            buf.AddRange(BitConverter.GetBytes((UInt32)s.Items.Count));
            foreach (var i in s.Items)
            {
                buf.Add((byte) s.RequestedModules.IndexOf(i.Module));
                buf.Add((byte) i.SubModule);

                // header size
                var h = i.refObject.getBytes();
                buf.AddRange(BitConverter.GetBytes((UInt16) h.Length));

                // nb sub items
                buf.AddRange(BitConverter.GetBytes((UInt32)0));

                // header
                buf.AddRange(h);
            }
        }

        public void NEWJOB(Scene s, System.Drawing.Size size)
        {
            var n = con.GetStream();
            var src = clientId;

            n.WriteByte((byte)eInstruction.NEWJOB); 
            n.Write(BitConverter.GetBytes((UInt16)src), 0, 2);

            List<byte> buf = new List<byte>();
            write_header(s, size, buf);
            write_items(s, buf);

            n.Write(BitConverter.GetBytes((UInt64)buf.Count), 0, 8);
            n.Write(buf.ToArray(), 0, buf.Count);
        }

        public void CAUTH()
        {
            var n = con.GetStream();
            n.WriteByte((byte) eInstruction.CAUTH);
            var msg = -1;
            n.Write(BitConverter.GetBytes((UInt16)msg), 0, 2);
        }

        public bool WELCOME()
        {
            var n = con.GetStream();
            var buf = new byte[2];
            READ(n, buf, 2);

            this.clientId = BitConverter.ToInt16(buf, 0);
            if (clientId != -1) return true;
            return false;
        }

        public bool IDCH()
        {
            var n = con.GetStream();
            var buf = new byte[4];
            READ(n, buf, 4);

            this.clientId = BitConverter.ToInt16(buf, 2);
            if (this.clientId != -1) return true;
            return false;
        }

        public void NewConnection(string ip, int port)
        {
            try
            {
                clientId = -1;
                con = new TcpClient(ip, port);

                CAUTH();
            }
            catch (System.Net.Sockets.SocketException e) {
                System.Windows.Forms.MessageBox.Show(e.Message);
            }
            catch (Exception) { throw; }
        }

        public byte ReadSync()
        {
            var n = con.GetStream();

            if (!n.CanRead) throw new Exception("Can't read dude");

            var i = n.ReadByte();

            if (i == -1) throw new Exception("End of stream");
            return (byte)i;
        }

        public void RESULT(MainForm f)
        {
            var n = con.GetStream();
            var buf = new byte[10];
            READ(n, buf, 10);

            UInt16 Id = BitConverter.ToUInt16(buf, 0);
            UInt16 X = BitConverter.ToUInt16(buf, 2);
            UInt16 Y = BitConverter.ToUInt16(buf, 4);
            UInt32 color = BitConverter.ToUInt32(buf, 6);

            f.Invoke(f.DrawPixel, new object[] { X, Y, System.Drawing.Color.FromArgb((int) color) });
        }

        public short clientId { get; set; }
    }
}
