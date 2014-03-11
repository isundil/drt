using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class Viewport
    {
        public Viewport()
        {
            ox = new Points();
            oy = new Points();
            oz = new Points();

            fx = 1;
            fy = 1;
            fz = 1;
        }

        public int GridLevel { get; set; }

        public Points ox { get; set; }
        public Points oy { get; set; }
        public Points oz { get; set; }

        public float fx { get; set; }
        public float fy { get; set; }
        public float fz { get; set; }
    }
}
