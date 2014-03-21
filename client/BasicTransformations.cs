using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    abstract public class Matrix
    {
        protected double[] values;

        public Matrix()
        { }

        public void ApplyOnPoint(Points p)
        {
            p.X = (int)(p.X * values[0] + p.Y * values[1] + p.Z * values[2]);
            p.Y = (int)(p.X * values[3] + p.Y * values[4] + p.Z * values[5]);
            p.Z = (int)(p.X * values[6] + p.Y * values[7] + p.Z * values[8]);
        }
    }

    public class MatrixX : Matrix
    {
        public MatrixX(double angle)
        {
            values = new double[9];

            values[0] = 1;
            values[4] = Math.Cos(angle);
            values[5] = -1 * Math.Sin(angle);
            values[7] = Math.Sin(angle);
            values[8] = Math.Cos(angle);
        }
    }

    public class MatrixY : Matrix
    {
        public MatrixY(double angle)
        {
            values = new double[9];

            values[0] = Math.Cos(angle);
            values[2] = Math.Sin(angle);
            values[4] = 1;
            values[6] = -1 * Math.Sin(angle);
            values[8] = Math.Cos(angle);
        }
    }

    public class MatrixZ : Matrix
    {
        public MatrixZ(double angle)
        {
            values = new double[9];

            values[0] = Math.Cos(angle);
            values[1] = -1 * Math.Sin(angle);
            values[3] = Math.Sin(angle);
            values[4] = Math.Cos(angle);
            values[8] = 1;
        }
    }

    static public class BasicTransformations
    {
        public static byte[] getTranslation(SceneItem i)
        {
            List<byte> l = new List<byte>();
            List<byte> h = new List<byte>();

            l.Add((byte)i.Module);
            l.Add((byte)i.SubModule);
            h.AddRange(BitConverter.GetBytes((double)i.refObject.X));
            h.AddRange(BitConverter.GetBytes((double)i.refObject.Y));
            h.AddRange(BitConverter.GetBytes((double)i.refObject.Z));
            l.AddRange(BitConverter.GetBytes((ushort)h.Count));
            l.AddRange(BitConverter.GetBytes((UInt32)0));
            l.AddRange(h);
            return l.ToArray();
        }
    }
}
