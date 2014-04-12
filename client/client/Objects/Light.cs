using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client.Objects
{
    public class Light : AObjects
    {
        Light(Light o)
            : base(o)
        { }

        override public object Clone()
        {
            return new Light(this);
        }

        public override void Refresh()
        { }

        new static public AObjects create_x(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            return new Light(p1, tmp);
        }
        new static public AObjects create_y(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            return new Light(p1, tmp);
        }
        new static public AObjects create_z(Points p1, Points p2, Viewport vp, bool tmp = false)
        {
            return new Light(p1, tmp);
        }

        override public void draw_x(Image b, Viewport vp, bool selected)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            Util.convertToGe(p, vp, b, Util.eView.x);

            using (TextureBrush brush = new TextureBrush(
                (selected ? Properties.Resources.light : Properties.Resources.ulight), WrapMode.Clamp))
            {
                brush.TranslateTransform(p.Y - Properties.Resources.light.Width / 2, p.Z - Properties.Resources.light.Height / 2);
                g.FillRectangle(brush,
                                p.Y - Properties.Resources.light.Width / 2, p.Z - Properties.Resources.light.Height / 2,
                                Properties.Resources.light.Width, Properties.Resources.light.Height);
            }
        }
        override public void draw_y(Image b, Viewport vp, bool selected)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            Util.convertToGe(p, vp, b, Util.eView.y);

            using (TextureBrush brush = new TextureBrush(
                (selected ? Properties.Resources.light : Properties.Resources.ulight), WrapMode.Clamp))
            {
                brush.TranslateTransform(p.X - Properties.Resources.light.Width / 2, p.Z - Properties.Resources.light.Height / 2);
                g.FillRectangle(brush,
                                p.X - Properties.Resources.light.Width / 2, p.Z - Properties.Resources.light.Height / 2,
                                Properties.Resources.light.Width, Properties.Resources.light.Height);
            }
        }
        override public void draw_z(Image b, Viewport vp, bool selected)
        {
            var g = System.Drawing.Graphics.FromImage(b);

            var p = this.centerPoint.Clone() as Points;
            Util.convertToGe(p, vp, b, Util.eView.z);

            using (TextureBrush brush = new TextureBrush(
                (selected ? Properties.Resources.light : Properties.Resources.ulight), WrapMode.Clamp))
            {
                brush.TranslateTransform(p.X - Properties.Resources.light.Width / 2, p.Y - Properties.Resources.light.Height / 2);
                g.FillRectangle(brush,
                                p.X - Properties.Resources.light.Width / 2, p.Y - Properties.Resources.light.Height / 2,
                                Properties.Resources.light.Width, Properties.Resources.light.Height);
            }
        }

        public override bool solve_equation_x(Points p)
        {
            return false;
        }
        public override bool solve_equation_y(Points p)
        {
            return false;
        }
        public override bool solve_equation_z(Points p)
        {
            return false;
        }

        static protected int count = 0;
        Light()
        {
            this.centerPoint = new Points();
            base.AddOneToCount(typeof(Light));
        }

        private Light(Points c, bool tmp)
            : base(tmp)
        {
            this.centerPoint = c;
            this.Color = new MyColor(System.Drawing.Color.Black.ToArgb());

            if (!tmp)
            {
                this.Name = "Light" + base.AddOneToCount(typeof(Light));
            }
        }

        override public Modules.eModules getModule(bool final_render = false)
        {
            return (final_render ? Modules.eModules.ADVANCED_LIGHT : Modules.eModules.BASIC_LIGHT);
        }
        override public int getSubModule()
        {
            return Modules.Submodules[Modules.eModules.BASIC_LIGHT]["LIGHT"];
        }

        override public byte[] getBytes()
        {
            return new byte[] { };
        }

        override public SceneItem getSceneItem(bool final_render = false)
        {
            var sc = new SceneItem(this);

            sc.Module = (byte)getModule(final_render);
            sc.SubModule = (byte)getSubModule();

            var translation = new SceneItem(this);
            translation.Module = (byte)Modules.eModules.BASIC_TRANSFORM;
            translation.SubModule = (byte)Modules.Submodules[Modules.eModules.BASIC_TRANSFORM]["TRANSLATION"];
            translation.addRange(BasicTransformations.getTranslation(translation)); 
            sc.addItem(translation);

            return sc;
        }
    }
}
