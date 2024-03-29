﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class myTcpClient : TcpClient
    {
        public bool IsDisposed { get; set; }
        protected override void Dispose(bool d)
        {
            IsDisposed = true;
            base.Dispose(d);
        }

        public myTcpClient(string ip, int port)
            : base (ip, port)
        { }
    }

    public class ConClient
    {
        myTcpClient con = null;

        public enum eInstruction
        {
            CAUTH       = 1,
            WELCOME     = 2,
            IDCH        = 3,
            MONITOR     = 16,
            NEWJOB      = 8,
            RESULT      = 13,
            CHUNKRESULT = 17,
            COMPILFAIL  = 14
        };

        Dictionary<eInstruction, uint> MessagesSizes = new Dictionary<eInstruction, uint> {
            { eInstruction.WELCOME,     2  },
            { eInstruction.IDCH,        4  },
            { eInstruction.COMPILFAIL,  4  },
            { eInstruction.MONITOR,     9  },
            { eInstruction.RESULT,      12 },
            { eInstruction.CHUNKRESULT, 10 }
        };

        public void Disconnect()
        {
            if (con != null)
            con.Close();
        }

        private void write_header(Scene s, System.Drawing.Size size, List<byte> buf)
        {
            byte nbr = (byte)s.RequestedModules.Count;

            buf.Add(nbr);
            foreach (var m in s.RequestedModules)
                buf.AddRange(Modules.ModuleNames[m]);

            buf.AddRange(BitConverter.GetBytes((UInt16)size.Width));
            buf.AddRange(BitConverter.GetBytes((UInt16)size.Height));
            buf.AddRange(s.Items[0].refObject.getBytes());
            s.Items.RemoveAt(0);
            buf.AddRange(BitConverter.GetBytes((UInt32)s.Items.Count));
        }

        private void _write_item(Scene s, SceneItem i, List<byte> buf)
        {
            // Convert module ID with its position in the array
            byte nmodule = 0;
            foreach (var m in s.RequestedModules)
            {
                if (m == (Modules.eModules)(i.Module)) break;
                nmodule++;
            }
            i.Module = nmodule;

            buf.AddRange(i.getBytes());
            foreach (var si in i.Items)
            {
                _write_item(s, si, buf);
            }
        }

        private void write_items(Scene s, List<byte> buf)
        {
            foreach (var i in s.Items)
            {
                _write_item(s, i, buf);
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

        public bool HasEnoughBytesToRead(eInstruction i)
        {
            return MessagesSizes[i] <= con.Available;
        }

        public bool WELCOME(out bool wait_for_instruction)
        {
            var buf = Read(MessagesSizes[eInstruction.WELCOME]);
            wait_for_instruction = false;

            this.clientId = BitConverter.ToUInt16(buf, 0);
            if (clientId != 0xffff) return true;
            return false;
        }

        public void COMPILFAIL(out bool wait_for_instruction)
        {
            var buf = Read(MessagesSizes[eInstruction.COMPILFAIL]);
            wait_for_instruction = false;
        }

        public bool IDCH(out bool wait_for_instruction)
        {
            var buf = Read(MessagesSizes[eInstruction.IDCH]);

            wait_for_instruction = false;
            this.clientId = BitConverter.ToUInt16(buf, 2);
            if (this.clientId != 0xffff) return true;
            return false;
        }

        public void NewConnection(string ip, int port)
        {
            try
            {
                clientId = 0xffff;
                con = new myTcpClient(ip, port);

                CAUTH();
            }
            catch (System.Net.Sockets.SocketException e) {
                System.Windows.Forms.MessageBox.Show(e.Message);
            }
            catch (Exception) { throw; }
        }

        public bool GetByte(out byte b)
        {
            if (!con.Connected) throw new Exception("Socket disconnected");
            var n = con.GetStream();
            if (!n.CanRead) throw new Exception("Socket unreadable");
            var ret = n.ReadByte();
            if (ret == -1)
            {
                b = 0;
                return false;
            }
            b = (byte)ret;
            return true;
        }

        public void RESULT(MainForm f, out bool wait_for_instruction)
        {
            var buf = Read(MessagesSizes[eInstruction.RESULT]);

            wait_for_instruction = false;

            UInt16 Src = BitConverter.ToUInt16(buf, 2);
            UInt16 X = BitConverter.ToUInt16(buf, 4);
            UInt16 Y = BitConverter.ToUInt16(buf, 6);
            Int32 color = BitConverter.ToInt32(buf, 8);

            f.Invoke(f.DrawPixel, new object[] { Src, X, Y, System.Drawing.Color.FromArgb(color) });
        }

        public void CHUNKRESULT(MainForm f, out bool wait_for_instruction)
        {
            var bufhead = Read(MessagesSizes[eInstruction.CHUNKRESULT]);

            wait_for_instruction = false;

            UInt16 Src = BitConverter.ToUInt16(bufhead, 2);
            UInt16 MinX = BitConverter.ToUInt16(bufhead, 4);
            UInt16 MinY = BitConverter.ToUInt16(bufhead, 6);
            byte W = bufhead[8];
            byte H = bufhead[9];

            int s = W * H * sizeof(UInt32);

            // dirty
            while (con.Available < s)
            { }

            var bufpels = Read((uint)(s));
            f.Invoke(f.DrawChunk, new object[] { Src, W, H, MinX, MinY, bufpels });
        }

        public void MONITOR(MainForm f, out bool wait_for_instruction)
        {
            var buf = Read(MessagesSizes[eInstruction.MONITOR]);

            wait_for_instruction = false;

            byte cpu = buf[0];
            UInt32 ramuse = BitConverter.ToUInt32(buf, 1);
            UInt32 rammax = BitConverter.ToUInt32(buf, 5);

            f.Invoke(f.Monitor, new object[] { cpu, ramuse, rammax });
        }

        private byte[] Read(uint size)
        {
            byte[] buf = new byte[size];
            if (!con.Connected) throw new Exception("Socket disconnected");
            var n = con.GetStream();
            if (!n.CanRead)     throw new Exception("Socket unreadable");
            var ret = n.Read(buf, 0, (int)size);
            if (ret == -1)      throw new Exception("Unexpected error");
            if (ret != size)
                throw new Exception("Error reading packet");
            return buf;
        }

        public ushort clientId { get; set; }

        public bool isAvailable()
        {
            if (con == null) return false;
            if (con.IsDisposed) return false;
            if (con.Client == null) return false;
            return !((con.Client.Poll(1000, SelectMode.SelectRead) && (con.Available == 0)) || !con.Connected);
        }

        public bool isCreated()
        {
            return con != null;
        }
    }
}
