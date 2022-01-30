
namespace Gypard
{
    partial class MainWin
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWin));
            this.SidePanel = new System.Windows.Forms.Panel();
            this.Profile1 = new System.Windows.Forms.Button();
            this.Profile1Indicator = new System.Windows.Forms.PictureBox();
            this.Profile2Indicator = new System.Windows.Forms.PictureBox();
            this.Profile2 = new System.Windows.Forms.Button();
            this.SidePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Profile1Indicator)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Profile2Indicator)).BeginInit();
            this.SuspendLayout();
            // 
            // SidePanel
            // 
            this.SidePanel.BackColor = System.Drawing.SystemColors.InactiveBorder;
            this.SidePanel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.SidePanel.Controls.Add(this.Profile2Indicator);
            this.SidePanel.Controls.Add(this.Profile2);
            this.SidePanel.Controls.Add(this.Profile1Indicator);
            this.SidePanel.Controls.Add(this.Profile1);
            this.SidePanel.Location = new System.Drawing.Point(12, 12);
            this.SidePanel.Name = "SidePanel";
            this.SidePanel.Size = new System.Drawing.Size(261, 669);
            this.SidePanel.TabIndex = 0;
            // 
            // Profile1
            // 
            this.Profile1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Profile1.FlatAppearance.BorderSize = 0;
            this.Profile1.FlatAppearance.MouseDownBackColor = System.Drawing.Color.DarkGray;
            this.Profile1.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.Profile1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Profile1.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Profile1.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.Profile1.Location = new System.Drawing.Point(3, 15);
            this.Profile1.Name = "Profile1";
            this.Profile1.Size = new System.Drawing.Size(227, 58);
            this.Profile1.TabIndex = 0;
            this.Profile1.Text = "Profile 1";
            this.Profile1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.Profile1.UseVisualStyleBackColor = true;
            this.Profile1.Click += new System.EventHandler(this.Profile1_Click);
            // 
            // Profile1Indicator
            // 
            this.Profile1Indicator.Image = ((System.Drawing.Image)(resources.GetObject("Profile1Indicator.Image")));
            this.Profile1Indicator.Location = new System.Drawing.Point(232, 36);
            this.Profile1Indicator.Name = "Profile1Indicator";
            this.Profile1Indicator.Size = new System.Drawing.Size(22, 25);
            this.Profile1Indicator.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.Profile1Indicator.TabIndex = 1;
            this.Profile1Indicator.TabStop = false;
            // 
            // Profile2Indicator
            // 
            this.Profile2Indicator.Image = ((System.Drawing.Image)(resources.GetObject("Profile2Indicator.Image")));
            this.Profile2Indicator.Location = new System.Drawing.Point(232, 100);
            this.Profile2Indicator.Name = "Profile2Indicator";
            this.Profile2Indicator.Size = new System.Drawing.Size(22, 25);
            this.Profile2Indicator.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.Profile2Indicator.TabIndex = 3;
            this.Profile2Indicator.TabStop = false;
            // 
            // Profile2
            // 
            this.Profile2.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Profile2.FlatAppearance.BorderSize = 0;
            this.Profile2.FlatAppearance.MouseDownBackColor = System.Drawing.Color.DarkGray;
            this.Profile2.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.Profile2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Profile2.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Profile2.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.Profile2.Location = new System.Drawing.Point(3, 79);
            this.Profile2.Name = "Profile2";
            this.Profile2.Size = new System.Drawing.Size(227, 58);
            this.Profile2.TabIndex = 2;
            this.Profile2.Text = "Profile 2";
            this.Profile2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.Profile2.UseVisualStyleBackColor = true;
            this.Profile2.Click += new System.EventHandler(this.Profile2_Click);
            // 
            // MainWin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Silver;
            this.ClientSize = new System.Drawing.Size(878, 693);
            this.Controls.Add(this.SidePanel);
            this.Name = "MainWin";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Gypard";
            this.SidePanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.Profile1Indicator)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Profile2Indicator)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel SidePanel;
        private System.Windows.Forms.Button Profile1;
        private System.Windows.Forms.PictureBox Profile1Indicator;
        private System.Windows.Forms.PictureBox Profile2Indicator;
        private System.Windows.Forms.Button Profile2;
    }
}

