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
        }

        public List<SceneItem> Items;
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
        public static Dictionary<eModules, string> Modules = new Dictionary<eModules, string>()
        {
            { eModules.BASIC_SHAPE, "basic_shape" },
            { eModules.BASIC_TRANSFORM, "basic_transform" }
        };

        public static Scene TransformPreview(ObjectsList ol)
        {
            Scene s = new Scene();

            List<eModules> auth = new List<eModules>()
            {
                eModules.BASIC_SHAPE,
                eModules.BASIC_TRANSFORM
            };

            foreach (var o in ol.Collection)
            {
                var i = new SceneItem();
                i.Module = o.getModule();
                i.SubModule = o.getSubModule();
                i.refObject = o;

                s.Items.Add(i);
            }

            return s;
        }
    }
}
