using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Gypard
{
    public partial class MainWin : Form
    {
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
    }
}
