﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace client
{
    public class ListenerWorker : BackgroundWorker
    {
        private ConClient Connection { get; set; }
        private MainForm _form;

        private bool offline;
        public bool Offline {
            get
            {
                return offline;
            }
            set
            {
                offline = value;
                if (value == false)
                {
                    if (!this.IsBusy)
                    this.RunWorkerAsync();
                }
                else
                {
                    this.CancelAsync();
                }
            }
        }

        public ListenerWorker(ConClient con, MainForm form)
        {
            this.Connection = con;
            _form = form;
            this.DoWork += new DoWorkEventHandler(doListen);
        }

        private void Connect()
        {
            _form.errorlabel.Text = "";
            _form.toolStripStatusLabel.Text = "Connected with id : " + Connection.clientId;
            _form.toolStripStatusLabel.Image = Properties.Resources.green;
        }

        private void Disconnect()
        {
            this.CancelAsync();
            if (this.Offline == true) return;
            Connection.clientId = 0xffff;

            this.Connection.Disconnect();
            _form.toolStripStatusLabel.Text = "Disconnected";
            _form.toolStripStatusLabel.Image = Properties.Resources.red;

            try
            {
                _form.Invoke(_form.Connect);
            }
            catch (Exception)
            { }
        }

        private void doListen(object o, DoWorkEventArgs e)
        {
            byte b = 0;
            bool wait_for_instruction = false;
            while (!e.Cancel && !this.Offline)
            {
                if (!Connection.isAvailable())
                {
                    Disconnect();
                }

                try
                {
                    if (wait_for_instruction == false)
                    {
                        b = 0;

                        if (Connection.GetByte(out b))
                        {
                            wait_for_instruction = true;
                        }
                    }

                    if (b == 0) continue;
                    if (!Connection.HasEnoughBytesToRead((ConClient.eInstruction)b)) continue;

                    switch ((ConClient.eInstruction)b)
                    {
                        case ConClient.eInstruction.WELCOME:
                            if (Connection.WELCOME(out wait_for_instruction)) Connect();
                            else Disconnect();
                            break;
                        case ConClient.eInstruction.IDCH:
                            if (Connection.IDCH(out wait_for_instruction)) Connect();
                            else Disconnect();
                            break;
                        case ConClient.eInstruction.RESULT:
                            Connection.RESULT(_form, out wait_for_instruction);
                            break;
                        case ConClient.eInstruction.CHUNKRESULT:
                            Connection.CHUNKRESULT(_form, out wait_for_instruction);
                            break;
                        case ConClient.eInstruction.COMPILFAIL:
                            Connection.COMPILFAIL(out wait_for_instruction);
                            throw new CompilFailException("Sorry, no server can handle your request.");
                        case ConClient.eInstruction.MONITOR:
                            Connection.MONITOR(_form, out wait_for_instruction);
                            break;
                        default:
                            _form.errorlabel.Text = "Unknown packet header";
                            Disconnect();
                            break;
                    }
                }
                catch (CompilFailException ex)
                {
                    _form.errorlabel.Text = ex.Message;
                }
                catch (Exception ex)
                {
                    _form.errorlabel.Text = ex.Message;
                    Disconnect();
                }
            }
        }
    }
    public class CompilFailException : Exception
    {
        public CompilFailException(string msg) : base(msg) { }
    }
}
