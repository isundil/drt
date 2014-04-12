using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class Scene
    {
        public Scene()
        {
            Items = new List<SceneItem>();
            RequestedModules = new List<Modules.eModules>();
        }

        public List<SceneItem> Items;
        public List<Modules.eModules> RequestedModules;
    }

    public class SceneItem
    {
        public AObjects refObject;

        public SceneItem(AObjects o)
        {
            Items = new List<SceneItem>();
            Header = new List<byte>();
            this.refObject = o;
        }

        public void addItem(SceneItem i)
        {
            this.NbSubItems++;
            Items.Add(i);
        }
        public List<SceneItem> Items { get; private set; }

        public void addByte(byte b)
        {
            Header.Add(b);
            HeaderSize = (ushort)Header.Count;
        }
        public void addRange(byte[] b)
        {
            Header.AddRange(b);
            HeaderSize = (ushort)Header.Count;
        }

        public byte Module { get; set; }
        public byte SubModule { get; set; }
        public UInt16 HeaderSize { get; protected set; }
        public UInt32 NbSubItems { get; protected set; }
        private List<Byte> Header;
        public byte[] getBytes()
        {
            List<byte> b = new List<byte>();
            b.Add(Module);
            b.Add(SubModule);
            b.AddRange(BitConverter.GetBytes(HeaderSize));
            b.AddRange(BitConverter.GetBytes(NbSubItems));
            b.AddRange(Header);
            return b.ToArray();
        }
    }

    public static class SceneTransform
    {
        public static Scene TransformPreview(AObjects[] ol)
        {
            Scene s = new Scene();

            List<Modules.eModules> authModules = new List<Modules.eModules>()
            {
                Modules.eModules.BASIC_SHAPE,
                Modules.eModules.BASIC_TRANSFORM,
                Modules.eModules.BASIC_LIGHT
            };

            s.RequestedModules.Add(Modules.eModules.BASIC_SHAPE);
            s.RequestedModules.Add(Modules.eModules.BASIC_TRANSFORM);

            foreach (var o in ol)
            {
                if (!authModules.Contains(o.getModule()))
                    continue;
                if (!s.RequestedModules.Contains(o.getModule()))
                    s.RequestedModules.Add(o.getModule());
                s.Items.Add(o.getSceneItem());
            }

            return s;
        }

        public static Scene TransformRender(AObjects[] ol)
        {
            Scene s = new Scene();

            s.RequestedModules.Add(Modules.eModules.BASIC_SHAPE);
            s.RequestedModules.Add(Modules.eModules.BASIC_TRANSFORM);

            foreach (var o in ol)
            {
                if (!s.RequestedModules.Contains(o.getModule()))
                    s.RequestedModules.Add(o.getModule());
                s.Items.Add(o.getSceneItem());
            }

            return s;
        }
    }
}
