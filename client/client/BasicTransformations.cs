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
            Points tmp = (Points)p.Clone();

            p.X = (int)(tmp.X * values[0] + tmp.Y * values[1] + tmp.Z * values[2]);
            p.Y = (int)(tmp.X * values[3] + tmp.Y * values[4] + tmp.Z * values[5]);
            p.Z = (int)(tmp.X * values[6] + tmp.Y * values[7] + tmp.Z * values[8]);
        }
    }

    public class MatrixX : Matrix
    {
        public MatrixX(double angle)
        {
            values = new double[9];

            values[0] = 1;
            values[4] = Math.Cos(angle);
            values[5] = - Math.Sin(angle);
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
            values[6] = - Math.Sin(angle);
            values[8] = Math.Cos(angle);
        }
    }

    public class MatrixZ : Matrix
    {
        public MatrixZ(double angle)
        {
            values = new double[9];

            values[0] = Math.Cos(angle);
            values[1] = - Math.Sin(angle);
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

            l.AddRange(BitConverter.GetBytes((double)i.refObject.X));
            l.AddRange(BitConverter.GetBytes((double)i.refObject.Y));
            l.AddRange(BitConverter.GetBytes((double)i.refObject.Z));

            return l.ToArray();
        }

        public static byte[] getRotation(SceneItem i)
        {
            List<byte> l = new List<byte>();

            l.AddRange(BitConverter.GetBytes((double)i.refObject.dRotX));
            l.AddRange(BitConverter.GetBytes((double)i.refObject.dRotY));
            l.AddRange(BitConverter.GetBytes((double)i.refObject.dRotZ));

            return l.ToArray();
        }

        public static byte[] getTransparency(SceneItem i)
        {
            List<byte> l = new List<byte>();

            l.AddRange(BitConverter.GetBytes((double)i.refObject.Transparency));

            return l.ToArray();
        }

        public static byte[] getReflection(SceneItem i)
        {
            List<byte> l = new List<byte>();

            l.AddRange(BitConverter.GetBytes((double)i.refObject.Reflection));

            return l.ToArray();
        }
    }
}
