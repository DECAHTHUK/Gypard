using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace Gypard
{
    public partial class MainWin : Form
    {
        [DllImport("GypardC.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void init_cons();

		public MainWin()
        {
            InitializeComponent();
        }

        private void Profile1_Click(object sender, EventArgs e)
        {

        }

        private void Profile2_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Console.WriteLine(FieldA.Text);
        }

        private void Minus1_Click(object sender, EventArgs e)
        {
            int thing = Int32.Parse(SpeedNum.Text);
            if (thing != 0)
            {
                thing--;
                SpeedNum.Text = thing.ToString();
            }
        }

        private void Plus1_Click(object sender, EventArgs e)
        {
            int thing = Int32.Parse(SpeedNum.Text);
            if (thing != 10)
            {
                thing++;
                SpeedNum.Text = thing.ToString();
            }
        }

        private void Minus2_Click(object sender, EventArgs e)
        {
            int thing = Int32.Parse(AccelerationNum.Text);
            if (thing != 0)
            {
                thing--;
                AccelerationNum.Text = thing.ToString();
            }
        }

        private void Plus2_Click(object sender, EventArgs e)
        {
            int thing = Int32.Parse(AccelerationNum.Text);
            if (thing != 10)
            {
                thing++;
                AccelerationNum.Text = thing.ToString();
            }
        }

        private void BtnRun_Click(object sender, EventArgs e)
        {
			Thread thread1 = new Thread(MainWin.init_cons);
			thread1.Start();
        }

        private void BtnGuide_Click(object sender, EventArgs e)
        {
            Console.WriteLine(FieldA.Text);
        }
    }
}
