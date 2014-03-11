using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public static class Util
    {
        public enum eView { x, y, z };

        public static void convertToMy(Points p, Viewport vp, Image i, eView view)
        {
            if (view == eView.x)
            {
                p.Y = (int)((p.Y - vp.ox.Y - i.Width / 2) / vp.fx);
                p.Z = -(int)((p.Z - vp.ox.Z - i.Height / 2) / vp.fx);
            }
            else if (view == eView.y)
            {
                p.X = (int)((p.X - vp.oy.X - i.Width / 2) / vp.fy);
                p.Z = -(int)((p.Z - vp.oy.Z - i.Height / 2) / vp.fy);
            }
            else
            {
                p.X = (int)((p.X - vp.oz.X - i.Width / 2) / vp.fz);
                p.Y = -(int)((p.Y - vp.oz.Y - i.Height / 2) / vp.fz);
            }
        }

        public static void convertToGe(Points p, Viewport vp, Image i, eView view)
        {
            if (view == eView.x)
            {
                p.Y = (int)(vp.fx * (p.Y) + vp.ox.Y + i.Width / 2);
                p.Z = (int)(vp.fx * (-p.Z) + vp.ox.Z + i.Height / 2);
            }
            else if (view == eView.y)
            {
                p.X = (int)(vp.fy * (p.X) + vp.oy.X + i.Width / 2);
                p.Z = (int)(vp.fy * (-p.Z) + vp.oy.Z + i.Height / 2);
            }
            else
            {
                p.X = (int)(vp.fz * (p.X) + vp.oz.X + i.Width / 2);
                p.Y = (int)(vp.fz * (-p.Y) + vp.oz.Y + i.Height / 2);
            }
        }
    }
}
