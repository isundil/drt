using client.Animations;
using client.Objects;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace client
{
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
            animatronic = new Animatronic();
        }

        public AObjects GetById(int id)
        {
            foreach (var o in Collection)
            {
                if (o.Id == id) return o;
            }
            return null;
        }

        public Animatronic animatronic;

        // For XML serialization only !
        public AObjects[] Items
        {
            get {
                var a = new AObjects[collection.Count];
                int i = 0;
                foreach (var o in collection)
                {
                    a[i] = o.Clone() as AObjects;
                    i++;
                }
                return a;
            }
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
    abstract public class AObjects : ICloneable
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
                UUID = Guid.NewGuid().ToString();

                total++;
                Id = total;
            }
        }

        protected AObjects(AObjects o)
        {
            Color = new MyColor(0, 0, 0);
            matrixX = new MatrixX(0);
            matrixY = new MatrixY(0);
            matrixZ = new MatrixZ(0);

            this.centerPoint = new Points();
            this.Color = o.Color;
            this.Id = o.Id;
            this.Name = o.Name;
            this.Radius = o.Radius;
            this.RotX = o.RotX;
            this.RotY = o.RotY;
            this.RotZ = o.RotZ;
            this.UUID = o.UUID;
            this.X = o.X;
            this.Y = o.Y;
            this.Z = o.Z;
        }

        abstract public object Clone();

        [Browsable(false)]
        public string UUID { get; set; }

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

        virtual public Modules.eModules getModule() { return Modules.eModules.BASIC_SHAPE; }
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

        public SceneItem getSceneItem()
        {
            var sc = new SceneItem(this);

            sc.Module = (byte)getModule();
            sc.SubModule = (byte)getSubModule();
            sc.addRange(this.getBytes());

            var translation = new SceneItem(this);
            translation.Module = (byte)Modules.eModules.BASIC_TRANSFORM;
            translation.SubModule = (byte)Modules.Submodules[Modules.eModules.BASIC_TRANSFORM]["TRANSLATION"];
            translation.addRange(BasicTransformations.getTranslation(translation));
            sc.addItem(translation);

            var rotate = new SceneItem(this);
            rotate.Module = (byte)Modules.eModules.BASIC_TRANSFORM;
            rotate.SubModule = (byte)Modules.Submodules[Modules.eModules.BASIC_TRANSFORM]["ROTATION"];
            rotate.addRange(BasicTransformations.getRotation(rotate));
            sc.addItem(rotate);

            return sc;
        }
    }
}
