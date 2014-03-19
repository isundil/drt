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
            RequestedModules = new List<eModules>();
        }

        public List<SceneItem> Items;
        public List<eModules> RequestedModules;
    }

    public class SceneItem
    {
        public eModules Module;
        public int SubModule;

        public SceneItem()
        {
            Items = new List<SceneItem>();
        }

        public AObjects refObject;
        public List<SceneItem> Items;
    }

    public enum eModules
    {
        BASIC_SHAPE,
        BASIC_TRANSFORM
    }

    public static class SceneTransform
    {
        static private byte[] to20Bytes(string s)
        {
            byte[] r = new byte[20];
            for (var i = 0; i < s.Length; ++i) r[i] = (byte)s[i];
            return r;
        }
        public static Dictionary<eModules, byte[]> Modules = new Dictionary<eModules, byte[]>()
        {
            { eModules.BASIC_SHAPE, to20Bytes("basic_shape") },
            { eModules.BASIC_TRANSFORM, to20Bytes("basic_transform") }
        };

        public static Scene TransformPreview(ObjectsList ol)
        {
            Scene s = new Scene();

            s.RequestedModules.Add(eModules.BASIC_SHAPE);
            s.RequestedModules.Add(eModules.BASIC_TRANSFORM);

            foreach (var o in ol.Collection)
            {
                var i = new SceneItem();

                i.Module = o.getModule();
                i.SubModule = o.getSubModule();
                i.refObject = o;

                var translation = new SceneItem();
                translation.Module = eModules.BASIC_TRANSFORM;
                translation.SubModule = 1;
                translation.refObject = o;

                i.Items.Add(translation);

                s.Items.Add(i);
            }

            return s;
        }
    }
}
