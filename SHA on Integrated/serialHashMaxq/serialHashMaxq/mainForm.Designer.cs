namespace serialHashMaxq
{
    partial class mainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.lCOM = new System.Windows.Forms.Label();
            this.cbCOMPorts = new System.Windows.Forms.ComboBox();
            this.lBaudRate = new System.Windows.Forms.Label();
            this.spMain = new System.IO.Ports.SerialPort(this.components);
            this.cbBaudRate = new System.Windows.Forms.ComboBox();
            this.bConnect = new System.Windows.Forms.Button();
            this.pReadWrite = new System.Windows.Forms.Panel();
            this.bSend = new System.Windows.Forms.Button();
            this.cbHardwareAccel = new System.Windows.Forms.CheckBox();
            this.tbResultHash = new System.Windows.Forms.TextBox();
            this.lResult = new System.Windows.Forms.Label();
            this.tbPattern = new System.Windows.Forms.TextBox();
            this.lPattern = new System.Windows.Forms.Label();
            this.tbStringToHash = new System.Windows.Forms.TextBox();
            this.lStringToHash = new System.Windows.Forms.Label();
            this.ssMain = new System.Windows.Forms.StatusStrip();
            this.lStatus = new System.Windows.Forms.ToolStripStatusLabel();
            this.lTime = new System.Windows.Forms.ToolStripStatusLabel();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.fbdLogFile = new System.Windows.Forms.FolderBrowserDialog();
            this.pReadWrite.SuspendLayout();
            this.ssMain.SuspendLayout();
            this.SuspendLayout();
            // 
            // lCOM
            // 
            this.lCOM.AutoSize = true;
            this.lCOM.Location = new System.Drawing.Point(12, 9);
            this.lCOM.Name = "lCOM";
            this.lCOM.Size = new System.Drawing.Size(31, 13);
            this.lCOM.TabIndex = 0;
            this.lCOM.Text = "COM";
            // 
            // cbCOMPorts
            // 
            this.cbCOMPorts.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
            this.cbCOMPorts.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
            this.cbCOMPorts.FormattingEnabled = true;
            this.cbCOMPorts.Location = new System.Drawing.Point(49, 6);
            this.cbCOMPorts.Name = "cbCOMPorts";
            this.cbCOMPorts.Size = new System.Drawing.Size(121, 21);
            this.cbCOMPorts.TabIndex = 1;
            // 
            // lBaudRate
            // 
            this.lBaudRate.AutoSize = true;
            this.lBaudRate.Location = new System.Drawing.Point(187, 9);
            this.lBaudRate.Name = "lBaudRate";
            this.lBaudRate.Size = new System.Drawing.Size(58, 13);
            this.lBaudRate.TabIndex = 2;
            this.lBaudRate.Text = "Baud Rate";
            // 
            // spMain
            // 
            this.spMain.ReceivedBytesThreshold = 300;
            this.spMain.WriteBufferSize = 4096;
            this.spMain.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.spMain_DataReceived);
            // 
            // cbBaudRate
            // 
            this.cbBaudRate.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
            this.cbBaudRate.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
            this.cbBaudRate.FormattingEnabled = true;
            this.cbBaudRate.Items.AddRange(new object[] {
            "75",
            "110",
            "134",
            "150",
            "300",
            "600",
            "1200",
            "1800",
            "2400",
            "4800",
            "7200",
            "9600",
            "14400",
            "19200",
            "38400",
            "57600",
            "115200",
            "128000"});
            this.cbBaudRate.Location = new System.Drawing.Point(251, 6);
            this.cbBaudRate.Name = "cbBaudRate";
            this.cbBaudRate.Size = new System.Drawing.Size(121, 21);
            this.cbBaudRate.TabIndex = 3;
            // 
            // bConnect
            // 
            this.bConnect.Location = new System.Drawing.Point(378, 5);
            this.bConnect.Name = "bConnect";
            this.bConnect.Size = new System.Drawing.Size(107, 23);
            this.bConnect.TabIndex = 4;
            this.bConnect.Text = "Connect";
            this.bConnect.UseVisualStyleBackColor = true;
            this.bConnect.Click += new System.EventHandler(this.bConnect_Click);
            // 
            // pReadWrite
            // 
            this.pReadWrite.Controls.Add(this.bSend);
            this.pReadWrite.Controls.Add(this.cbHardwareAccel);
            this.pReadWrite.Controls.Add(this.tbResultHash);
            this.pReadWrite.Controls.Add(this.lResult);
            this.pReadWrite.Controls.Add(this.tbPattern);
            this.pReadWrite.Controls.Add(this.lPattern);
            this.pReadWrite.Controls.Add(this.tbStringToHash);
            this.pReadWrite.Controls.Add(this.lStringToHash);
            this.pReadWrite.Controls.Add(this.ssMain);
            this.pReadWrite.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.pReadWrite.Enabled = false;
            this.pReadWrite.Location = new System.Drawing.Point(0, 33);
            this.pReadWrite.Name = "pReadWrite";
            this.pReadWrite.Size = new System.Drawing.Size(580, 263);
            this.pReadWrite.TabIndex = 5;
            // 
            // bSend
            // 
            this.bSend.Location = new System.Drawing.Point(493, 215);
            this.bSend.Name = "bSend";
            this.bSend.Size = new System.Drawing.Size(75, 23);
            this.bSend.TabIndex = 8;
            this.bSend.Text = "Send";
            this.bSend.UseVisualStyleBackColor = true;
            this.bSend.Click += new System.EventHandler(this.bSend_Click);
            // 
            // cbHardwareAccel
            // 
            this.cbHardwareAccel.AutoSize = true;
            this.cbHardwareAccel.Checked = true;
            this.cbHardwareAccel.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbHardwareAccel.Location = new System.Drawing.Point(12, 218);
            this.cbHardwareAccel.Name = "cbHardwareAccel";
            this.cbHardwareAccel.Size = new System.Drawing.Size(134, 17);
            this.cbHardwareAccel.TabIndex = 7;
            this.cbHardwareAccel.Text = "Hardware Acceleration";
            this.cbHardwareAccel.UseVisualStyleBackColor = true;
            // 
            // tbResultHash
            // 
            this.tbResultHash.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tbResultHash.Location = new System.Drawing.Point(92, 72);
            this.tbResultHash.Multiline = true;
            this.tbResultHash.Name = "tbResultHash";
            this.tbResultHash.ReadOnly = true;
            this.tbResultHash.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tbResultHash.Size = new System.Drawing.Size(476, 140);
            this.tbResultHash.TabIndex = 6;
            this.tbResultHash.TextChanged += new System.EventHandler(this.tbResultHash_TextChanged);
            // 
            // lResult
            // 
            this.lResult.AutoSize = true;
            this.lResult.Location = new System.Drawing.Point(49, 75);
            this.lResult.Name = "lResult";
            this.lResult.Size = new System.Drawing.Size(37, 13);
            this.lResult.TabIndex = 5;
            this.lResult.Text = "Result";
            // 
            // tbPattern
            // 
            this.tbPattern.Location = new System.Drawing.Point(92, 38);
            this.tbPattern.Name = "tbPattern";
            this.tbPattern.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.tbPattern.Size = new System.Drawing.Size(476, 20);
            this.tbPattern.TabIndex = 4;
            // 
            // lPattern
            // 
            this.lPattern.AutoSize = true;
            this.lPattern.Location = new System.Drawing.Point(45, 41);
            this.lPattern.Name = "lPattern";
            this.lPattern.Size = new System.Drawing.Size(41, 13);
            this.lPattern.TabIndex = 3;
            this.lPattern.Text = "Pattern";
            // 
            // tbStringToHash
            // 
            this.tbStringToHash.Location = new System.Drawing.Point(92, 9);
            this.tbStringToHash.Name = "tbStringToHash";
            this.tbStringToHash.Size = new System.Drawing.Size(476, 20);
            this.tbStringToHash.TabIndex = 2;
            // 
            // lStringToHash
            // 
            this.lStringToHash.AutoSize = true;
            this.lStringToHash.Location = new System.Drawing.Point(12, 12);
            this.lStringToHash.Name = "lStringToHash";
            this.lStringToHash.Size = new System.Drawing.Size(74, 13);
            this.lStringToHash.TabIndex = 1;
            this.lStringToHash.Text = "String to Hash";
            // 
            // ssMain
            // 
            this.ssMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.lStatus,
            this.lTime});
            this.ssMain.Location = new System.Drawing.Point(0, 241);
            this.ssMain.Name = "ssMain";
            this.ssMain.Size = new System.Drawing.Size(580, 22);
            this.ssMain.SizingGrip = false;
            this.ssMain.TabIndex = 0;
            this.ssMain.Text = "statusStrip1";
            // 
            // lStatus
            // 
            this.lStatus.Name = "lStatus";
            this.lStatus.Size = new System.Drawing.Size(0, 17);
            // 
            // lTime
            // 
            this.lTime.Name = "lTime";
            this.lTime.Size = new System.Drawing.Size(0, 17);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(580, 296);
            this.Controls.Add(this.pReadWrite);
            this.Controls.Add(this.bConnect);
            this.Controls.Add(this.cbBaudRate);
            this.Controls.Add(this.lBaudRate);
            this.Controls.Add(this.cbCOMPorts);
            this.Controls.Add(this.lCOM);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "mainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Main Form";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.mainForm_FormClosing);
            this.Load += new System.EventHandler(this.mainForm_Load);
            this.pReadWrite.ResumeLayout(false);
            this.pReadWrite.PerformLayout();
            this.ssMain.ResumeLayout(false);
            this.ssMain.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lCOM;
        private System.Windows.Forms.ComboBox cbCOMPorts;
        private System.Windows.Forms.Label lBaudRate;
        private System.IO.Ports.SerialPort spMain;
        private System.Windows.Forms.ComboBox cbBaudRate;
        private System.Windows.Forms.Button bConnect;
        private System.Windows.Forms.Panel pReadWrite;
        private System.Windows.Forms.StatusStrip ssMain;
        private System.Windows.Forms.ToolStripStatusLabel lStatus;
        private System.Windows.Forms.Button bSend;
        private System.Windows.Forms.CheckBox cbHardwareAccel;
        private System.Windows.Forms.TextBox tbResultHash;
        private System.Windows.Forms.Label lResult;
        private System.Windows.Forms.TextBox tbPattern;
        private System.Windows.Forms.Label lPattern;
        private System.Windows.Forms.TextBox tbStringToHash;
        private System.Windows.Forms.Label lStringToHash;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ToolStripStatusLabel lTime;
        private System.Windows.Forms.FolderBrowserDialog fbdLogFile;
    }
}

