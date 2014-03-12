﻿using System;
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

        public void NEWJOB()
        {
            var n = con.GetStream();
            var src = -1;

            n.WriteByte((byte)eInstruction.NEWJOB); 
            n.Write(BitConverter.GetBytes((UInt16)src), 0, 2);
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
