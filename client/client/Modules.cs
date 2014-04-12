using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public static class Modules
    {
        static private byte[] to20Bytes(string s)
        {
            byte[] r = new byte[20];
            for (var i = 0; i < s.Length; ++i) r[i] = (byte)s[i];
            return r;
        }

        public enum eModules
        {
            BASIC_SHAPE,
            BASIC_TRANSFORM,
            BASIC_LIGHT,
            ADVANCED_LIGHT
        }
        public static Dictionary<eModules, byte[]> ModuleNames = new Dictionary<eModules, byte[]>()
        {
            { eModules.BASIC_SHAPE, to20Bytes("basic_shape") },
            { eModules.BASIC_TRANSFORM, to20Bytes("basic_transform") },
            { eModules.BASIC_LIGHT, to20Bytes("basic_light") },
            { eModules.ADVANCED_LIGHT, to20Bytes("advanced_light") }
        };
        public static Dictionary<eModules, Dictionary<string, int>> Submodules = new Dictionary<eModules, Dictionary<string, int>>()
        {
            { eModules.BASIC_SHAPE, new Dictionary<string, int>() {
                { "SPHERE",      1 },
                { "CYLINDER",    2 },
                { "CONE",        3 }
            } },
            { eModules.BASIC_TRANSFORM, new Dictionary<string, int>() {
                { "TRANSLATION", 1 },
                { "ROTATION",    2 }
            } },
            { eModules.BASIC_LIGHT, new Dictionary<string, int>() {
                { "LIGHT",       1 }
            } },
            { eModules.ADVANCED_LIGHT, new Dictionary<string, int>() {
                { "LIGHT",       1 },
                { "TRANSPARENCY",2 },
                { "REFLECTION",  3 }
            } }
        };
    }
}
