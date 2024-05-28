using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApp2
{
    internal class Strimes
    {
        private int x = 160;
        private int y = 40;

        private bool orient = false;


        public Strimes() 
        {
            
            Random random = new Random(2);
            this.orient = Convert.ToBoolean(random.Next());

        }


    }
}
