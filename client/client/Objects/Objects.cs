using client.Objects;
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
    public enum eSubModules
    {
        CAMERA      = 0,
        SPHERE      = 1,
        CYLINDER    = 2,
        CONE        = 3
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

    [XmlRoot("Scene")]
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
            set
            {
                foreach (var o in value)
                {
                    o.Refresh();
                    collection.Add(o);
                }
            }
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

        public override string ToString()
        {
            return "{ X = " + X + ", Y = " + Y + ", Z = " + Z + " }"; 
        }
    }

    [XmlInclude(typeof(Camera))]
    [XmlInclude(typeof(Light))]
    [XmlInclude(typeof(Sphere))]
    [XmlInclude(typeof(Cylinder))]
    [XmlInclude(typeof(Cone))]
    abstract public class AObjects
    {
        protected AObjects()
        {
            Color = new MyColor(0, 0, 0);
            matrixX = new MatrixX(0);
            matrixY = new MatrixY(0);
            matrixZ = new MatrixZ(0);

            ++total;
            Id = total;
        }

        protected AObjects(bool tmp) {
            Color = new MyColor(0, 0, 0);
            matrixX = new MatrixX(0);
            matrixY = new MatrixY(0);
            matrixZ = new MatrixZ(0);

            if (!tmp)
            {
                total++;
                Id = total;
            }
        }

        public abstract void Refresh();

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

        internal MatrixX matrixX;
        internal MatrixY matrixY;
        internal MatrixZ matrixZ;

        protected double _rotX;
        protected double _rotY;
        protected double _rotZ;
        public int RotX
        {
            get
            {
                return (int)((_rotX * 180) / Math.PI);
            }
            set
            {
                _rotX = (value * Math.PI) / 180;
                matrixX = new MatrixX(_rotX);
            }
        }
        public int RotY
        {
            get
            {
                return (int)((_rotY * 180) / Math.PI);
            }
            set
            {
                _rotY = (value * Math.PI) / 180;
                matrixY = new MatrixY(_rotY);
            }
        }
        public int RotZ
        {
            get
            {
                return (int)((_rotZ * 180) / Math.PI);
            }
            set
            {
                _rotZ = (value * Math.PI) / 180;
                matrixZ = new MatrixZ(_rotZ);
            }
        }

        internal double dRotX
        {
            get
            {
                return _rotX;
            }
            set
            {
                _rotX = value;
                matrixX = new MatrixX(value);
            }
        }
        internal double dRotY
        {
            get
            {
                return _rotY;
            }
            set
            {
                _rotY = value;
                matrixY = new MatrixY(value);
            }
        }
        internal double dRotZ
        {
            get
            {
                return _rotZ;
            }
            set
            {
                _rotZ = value;
                matrixZ = new MatrixZ(value);
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
}
