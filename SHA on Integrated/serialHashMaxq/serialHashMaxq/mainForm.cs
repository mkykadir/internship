using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Security.Cryptography;
using System.Diagnostics;
using System.IO;

namespace serialHashMaxq
{
    public partial class mainForm : Form
    {
        public delegate void AddDataDelegate(String myString);
        public AddDataDelegate myDelegate;

        TextWriter tw;
        bool writtenBefore = false;

        public mainForm()
        {
            InitializeComponent();
            getCOMPorts();
        }

        private void getCOMPorts()
        {
            String[] availableCOMPorts = SerialPort.GetPortNames();
            cbCOMPorts.Items.AddRange(availableCOMPorts);
        }

        public void AddDataMethod(String myString)
        {
            tbResultHash.AppendText(myString);
        }

        private void mainForm_Load(object sender, EventArgs e)
        {
            this.myDelegate = new AddDataDelegate(AddDataMethod);
            
            if(fbdLogFile.ShowDialog() == DialogResult.OK)
            {
                tw = new StreamWriter(fbdLogFile.SelectedPath + "\\logFile.txt");
            }else
            {
                Application.Exit();
            }
            if (!spMain.IsOpen)
            {
                lStatus.Text = "No Connection";
                lStatus.ForeColor = Color.Red;
            }
        }

        private void bConnect_Click(object sender, EventArgs e)
        {
            if(bConnect.Text == "Disconnect")
            {
                if (spMain.IsOpen)
                {
                    try
                    {
                        spMain.Close();
                        bConnect.Text = "Connect";
                        pReadWrite.Enabled = false;
                        lStatus.Text = "No Connection";
                    }
                    catch (Exception)
                    {
                        MessageBox.Show("Error occured while closing COM port.");
                    }
                    
                }
                return;
            }

            if(cbCOMPorts.Text == "" || cbBaudRate.Text == "")
            {
                MessageBox.Show("Select one of the COM ports and BaudRate", "Error", MessageBoxButtons.OKCancel, MessageBoxIcon.Error);
                return;          
            }

            spMain.PortName = cbCOMPorts.Text;
            spMain.BaudRate = Convert.ToInt32(cbBaudRate.Text);
            try
            {
                spMain.Open();
            }
            catch (Exception)
            {
                MessageBox.Show("Error occured while connecting to the COM port.");
            }

            if (spMain.IsOpen)
            {
                pReadWrite.Enabled = true;
                lStatus.Text = "Connection established";
                lStatus.ForeColor = Color.Green;
                bConnect.Text = "Disconnect";
            }
        }

        private void mainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (spMain.IsOpen)
            {
                try
                {
                    spMain.Close();
                }
                catch (Exception)
                {
                    MessageBox.Show("Error occured while closing COM port.");
                }
            }

            try
            {
                if (!writtenBefore)
                {
                    tw.WriteLine(tbResultHash.Text);
                }
                tw.Close();
            }
            catch (Exception)
            {
                MessageBox.Show("Error occured while closing file");
            }
        }

        private byte[] patternToByte(string input)
        {
            int arraySize = input.Length / 8;
            if(!(input.Length < 8))
            {
                if (input.Length % 8 != 0)
                {
                    input = input.Insert(0, new string('0', 8-(input.Length % 8)));
                    arraySize++;
                }
                tbPattern.Text = input;
            }
            
            byte[] res = new byte[arraySize];
            for(int i = arraySize-1; i >= 0; i--)
            {
                res[i] = Convert.ToByte(input.Substring(i*8, 8), 2);
            }

            
            return res;
        }

        private bool checkAscii(string input)
        {
            const int maxascii = 255;
            //return true if input contains non-ascii characters
            return input.Any(c => c > maxascii);
        }

        private void bSend_Click(object sender, EventArgs e)
        {
            if(tbStringToHash.Text == String.Empty || tbPattern.Text == String.Empty)
            {
                MessageBox.Show("One of the following text boxes are empty, please check:\n - String to Hash\n - Pattern", "Empty Text Boxes", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (checkAscii(tbStringToHash.Text))
            {
                MessageBox.Show("String to Hash, text box contains non-ASCII characters.", "Non-ASCII", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            

            try
            {
                spMain.DiscardOutBuffer();
                byte[] getData = Encoding.ASCII.GetBytes(tbStringToHash.Text);
                byte[] patternByte = patternToByte(tbPattern.Text);
                byte[] arrayToSend = new byte[tbStringToHash.TextLength + (tbPattern.Text.Length /8) + 5];
                arrayToSend[0] = 0x02;
                if (cbHardwareAccel.Checked)
                {
                    arrayToSend[2] = 0x01;
                }else
                {
                    arrayToSend[2] = 0x02;
                }
                arrayToSend[3] = Convert.ToByte(tbPattern.Text.Length / 8);
                patternByte.CopyTo(arrayToSend, 4);
                getData.CopyTo(arrayToSend, 4 + tbPattern.Text.Length / 8);
                arrayToSend[arrayToSend.Length-1] = 0x03;
                arrayToSend[1] = Convert.ToByte(arrayToSend.Length);
                spMain.Write(arrayToSend, 0, arrayToSend.Length);
            }
            catch (Exception err)
            {
                MessageBox.Show("Error occured while writing to the serial port. Error details:\n" + err.ToString());
            }
        }

        private void spMain_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                string s = spMain.ReadExisting();
                tbResultHash.Invoke(this.myDelegate, new Object[] { s });
                spMain.DiscardInBuffer();         
            }
            catch (Exception)
            {
                MessageBox.Show("Error occured while reading");
            }
        }

        private void tbResultHash_TextChanged(object sender, EventArgs e)
        {
            if(tbResultHash.Text.Length > 120000)
            {
                writtenBefore = true;
                try
                {
                    tw.WriteLineAsync(tbResultHash.Text);
                    tbResultHash.Clear();
                }catch(Exception)
                {
                    MessageBox.Show("Error occured while writing text!");
                }
            }else
            {
                writtenBefore = false;
            }
        }
    }
}
