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
        }

        public int GridLevel { get; set; }

        public Points ox { get; set; }
        public Points oy { get; set; }
        public Points oz { get; set; }
    }
}
