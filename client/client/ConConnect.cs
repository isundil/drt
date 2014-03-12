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

        enum eInstruction
        {
            CAUTH   = 1,
            WELCOME = 2,
            NEWJOB  = 8
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
            var buf = new byte[3];
            n.Read(buf, 0, 3);

            this.clientId = BitConverter.ToInt16(buf, 1);
            if (buf[0] == (byte)eInstruction.WELCOME && clientId != -1) return true;
            return false;
        }

        public bool NewConnection(string ip, int port)
        {
            try
            {
                clientId = -1;
                con = new TcpClient(ip, port);
            }
            catch (System.Net.Sockets.SocketException e) {
                System.Windows.Forms.MessageBox.Show(e.Message);
            }
            catch (Exception) { throw; }

            if (con == null) return false;

            CAUTH();
            return WELCOME();
        }

        public short clientId { get; set; }
    }
}
