using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

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

    public enum eSubModules
    {
        SPHERE = 1
    }

    public class ObjectsListB : BindingList<AObjects>
    {
        public MainForm form { get; set; }

        public ObjectsListB() : base() { }
        public ObjectsListB(MainForm f) : base()
        {
            this.form = f;
        }

        private AObjects selected;

        public AObjects Selected
        {
            get
            {
                return selected;
            }
            set
            {
                selected = value;

                if (value != null)
                {
                    form.propertyGrid.SelectedObject = selected;
                    form.comboBox1.SelectedValue = selected.Id;

                    form.move_toolstrip.Enabled = true;
                    form.resize_toolstrip.Enabled = true;
                }
                else
                {
                    form.move_toolstrip.Enabled = false;
                    form.resize_toolstrip.Enabled = false;
                }
            }
        }
    }

    [XmlRoot]
    public class ObjectsList
    {
        private ObjectsListB collection;

        ObjectsList() { collection = new ObjectsListB(); }
        public ObjectsList(MainForm f)
        {
            collection = new ObjectsListB(f);
        }

        // For XML serialization only !
        public AObjects[] Items
        {
            get { return collection.ToArray(); }
            set { foreach (var o in value) collection.Add(o); }
        }

        [XmlIgnore]
        public ObjectsListB Collection { get { return collection; } private set {} }
        [XmlIgnore]
        public AObjects Selected { get { return collection.Selected; } set { collection.Selected = value; } }

        public void Add(AObjects o) { collection.Add(o); }
        public void Remove(AObjects o) { collection.Remove(o); }
    }

    public class Points : ICloneable {
        public int X { get; set; }
        public int Y { get; set; }
        public int Z { get; set; }

        public object Clone()
        {
            return new Points() { X = this.X, Y = this.Y, Z = this.Z };
        }
    }

    [XmlInclude(typeof(Sphere))]
    abstract public class AObjects
    {
        protected AObjects()
        {
            Color = new MyColor(0, 0, 0);

            ++total;
            Id = total;
        }

        protected AObjects(bool tmp) {
            Color = new MyColor(0, 0, 0);

            if (!tmp)
            {
                total++;
                Id = total;
            }
        }

        static private int total = 0;

        static private Dictionary<Type, int> counts = new Dictionary<Type,int>();

        static public void Reinit()
        {
            total = 0;
            counts.Clear();
        }

        public string Name { get; set; }

        [XmlIgnore]
        public int Id { get; private set; }

        public int Radius { get; set; }
        public int X
        {
            get
            {
                return centerPoint.X;
            }
            set
            {
                centerPoint.X = value;
            }
        }
        public int Y
        {
            get
            {
                return centerPoint.Y;
            }
            set
            {
                centerPoint.Y = value;
            }
        }
        public int Z
        {
            get
            {
                return centerPoint.Z;
            }
            set
            {
                centerPoint.Z = value;
            }
        }

        [EditorAttribute(typeof(MyColorEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public MyColor Color { get; set; }

        internal Points centerPoint { get; set; }

        static public AObjects create_x(Points p1, Points p2, Viewport vp, bool tmp = false) { return null; }
        static public AObjects create_y(Points p1, Points p2, Viewport vp, bool tmp = false) { return null; }
        static public AObjects create_z(Points p1, Points p2, Viewport vp, bool tmp = false) { return null; }

        abstract public void draw_x(Image b, Viewport vp, bool selected);
        abstract public void draw_y(Image b, Viewport vp, bool selected);
        abstract public void draw_z(Image b, Viewport vp, bool selected);

        abstract public bool solve_equation_x(Points p);
        abstract public bool solve_equation_y(Points p);
        abstract public bool solve_equation_z(Points p);

        public eModules getModule() { return eModules.BASIC_SHAPE; }
        public abstract int getSubModule();

        public abstract byte[] getBytes();

        protected int AddOneToCount(Type type)
        {
            if (counts.ContainsKey(type))
                counts[type]++;
            else
                counts[type] = 1;
            return counts[type];
        }
    }

    public class Sphere : AObjects
    {
        new static public AObjects create_x(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            var d = (int)Math.Sqrt(Math.Pow(p2.Y - p1.Y, 2) + Math.Pow(p2.Z - p1.Z, 2));
            return new Sphere(p1, d, tmp);
        }
        new static public AObjects create_y(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Z - p2.Z, 2) + Math.Pow(p1.X - p2.X, 2));

            return new Sphere(p1, d, tmp);
        }
        new static public AObjects create_z(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            var d = (int)Math.Sqrt(Math.Pow(p1.Y - p2.Y, 2) + Math.Pow(p1.X - p2.X, 2));

            return new Sphere(p1, d, tmp);
        }

        override public void draw_x(Image b, Viewport vp, bool selected)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            p.Y -= this.Radius;
            p.Z += this.Radius;
            Util.convertToGe(p, vp, b, Util.eView.x);

            g.DrawEllipse(new Pen((selected ? System.Drawing.Color.White : Color.toColor())), new Rectangle(
                    new Point(p.Y, p.Z),
                    new Size((int)(this.Radius * 2 * vp.fx), (int)(this.Radius * 2 * vp.fx))
                ));
        }
        override public void draw_y(Image b, Viewport vp, bool selected)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            p.X -= this.Radius;
            p.Z += this.Radius;
            Util.convertToGe(p, vp, b, Util.eView.y);

            g.DrawEllipse(new Pen((selected ? System.Drawing.Color.White : Color.toColor())), new Rectangle(
                    new Point(p.X, p.Z),
                    new Size((int)(this.Radius * 2 * vp.fy), (int)(this.Radius * 2 * vp.fy))
                ));
        }
        override public void draw_z(Image b, Viewport vp, bool selected)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            p.X -= this.Radius;
            p.Y += this.Radius;
            Util.convertToGe(p, vp, b, Util.eView.z);

            g.DrawEllipse(new Pen((selected ? System.Drawing.Color.White : Color.toColor())), new Rectangle(
                    new Point(p.X, p.Y),
                    new Size((int)(this.Radius * 2 * vp.fz), (int)(this.Radius * 2 * vp.fz))
                ));
        }

        public override bool solve_equation_x(Points p)
        {
            var _rsq = Math.Pow(this.centerPoint.Y - p.Y, 2) + Math.Pow(this.centerPoint.Z - p.Z, 2);
            if (_rsq >= Math.Pow(this.Radius - 5, 2) && _rsq <= Math.Pow(this.Radius + 5, 2)) return true;
            return false;
        }
        public override bool solve_equation_y(Points p)
        {
            var _rsq = Math.Pow(this.centerPoint.X - p.X, 2) + Math.Pow(this.centerPoint.Z - p.Z, 2);
            var rsq = Math.Pow(this.Radius, 2);

            if (_rsq >= Math.Pow(this.Radius - 5, 2) && _rsq <= Math.Pow(this.Radius + 5, 2)) return true;
            return false;
        }
        public override bool solve_equation_z(Points p)
        {
            var _rsq = Math.Pow(this.centerPoint.X - p.X, 2) + Math.Pow(this.centerPoint.Y - p.Y, 2);
            var rsq = Math.Pow(this.Radius, 2);

            if (_rsq >= Math.Pow(this.Radius - 5, 2) && _rsq <= Math.Pow(this.Radius + 5, 2)) return true;
            return false;
        }

        static protected int count = 0;
        Sphere()
        {
            this.centerPoint = new Points();
            base.AddOneToCount(typeof(Sphere));
        }

        private Sphere(Points c, int d, bool tmp) : base(tmp)
        {
            this.centerPoint = c;
            this.Radius = d;
            this.Color = new MyColor(System.Drawing.Color.SteelBlue.ToArgb());

            if (! tmp)
            {
                this.Name = "Sphere" + base.AddOneToCount(typeof(Sphere));
            }
        }

        override public int getSubModule()
        {
            return (int)eSubModules.SPHERE;
        }

        override public byte[] getBytes()
        {
            List<byte> b = new List<byte>();
            
            b.Add(Color.R);
            b.Add(Color.G);
            b.Add(Color.B);
            b.AddRange(BitConverter.GetBytes((UInt16) Radius));

            return b.ToArray();
        }
    }
}
