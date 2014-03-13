using System;
using System.ComponentModel;
using System.Drawing;

namespace client
{
    public class MyColorEditor : System.Drawing.Design.UITypeEditor
    {
        private System.Windows.Forms.Design.IWindowsFormsEditorService service;

        public override System.Drawing.Design.UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context)
        {
            return System.Drawing.Design.UITypeEditorEditStyle.Modal;
        }
        public override object EditValue(ITypeDescriptorContext context, IServiceProvider provider, object value)
        {
            if (provider != null) service = (System.Windows.Forms.Design.IWindowsFormsEditorService)provider.GetService(typeof(System.Windows.Forms.Design.IWindowsFormsEditorService));
            if (provider != null)
            {
                MyColor c = (MyColor)value;
                System.Windows.Forms.ColorDialog cd = new System.Windows.Forms.ColorDialog();
                cd.Color = Color.FromArgb(c.GetARGB());
                cd.ShowDialog();
                value = new MyColor(cd.Color.ToArgb());
            }
            return value;
        }
    }
    public class MyColorConverter : TypeConverter
    {
        public override object ConvertFrom(ITypeDescriptorContext context, System.Globalization.CultureInfo culture, object value)
        {
            if (value.GetType() == typeof(string))
                return new MyColor((string)value);
            return base.ConvertFrom(context, culture, value);
        }

        public override object ConvertTo(ITypeDescriptorContext context, System.Globalization.CultureInfo culture, object value, Type destinationType)
        {
            if (destinationType == typeof(string) && value is MyColor)
            {
                MyColor color = (MyColor)value;
                return color.ToString();
            }
            return base.ConvertTo(context, culture, value, destinationType);
        }
    }
    [TypeConverter(typeof(MyColorConverter))]
    public class MyColor
    {
        public byte R { get; set; }
        public byte G { get; set; }
        public byte B { get; set; }

        public MyColor() { R = G = B = 0; }
        public MyColor(byte r, byte g, byte b) { R = r; G = g; B = b; }
        public MyColor(byte[] rgb) { R = rgb[0]; G = rgb[1]; B = rgb[2]; }
        public MyColor(int argb)
        {
            byte[] b = BitConverter.GetBytes(argb);
            R = b[2];
            G = b[1];
            B = b[0];
        }
        public MyColor(string c)
        {
            string[] rgb = c.Split(' ');
            R = Convert.ToByte(rgb[0]);
            G = Convert.ToByte(rgb[1]);
            B = Convert.ToByte(rgb[2]);
        }

        public new string ToString() { return R + " " + G + " " + B; }
        public byte[] GetRGB() { return new byte[] { R, G, B }; }
        public int GetARGB() { return BitConverter.ToInt32(new byte[] { B, G, R, 255 }, 0); }
        public Color toColor() { return Color.FromArgb(R, G, B); }
    }
}
