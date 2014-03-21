using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

///
/// This code is from StackOverflow
/// http://stackoverflow.com/questions/3529928/how-do-i-put-text-on-progressbar
///

namespace client
{
    public enum ProgressBarDisplayText
    {
        Percentage,
        CustomText
    }

    public class MyProgressBar : ProgressBar
    {
        [DllImportAttribute("uxtheme.dll")]
        private static extern int SetWindowTheme(IntPtr hWnd, string appname, string idlist);

        protected override void OnHandleCreated(EventArgs e)
        {
            SetWindowTheme(this.Handle, "", "");
            base.OnHandleCreated(e);
        }

        //Property to set to decide whether to print a % or Text
        public ProgressBarDisplayText DisplayStyle { get; set; }

        //Property to hold the custom text
        public String CustomText { get; set; }

        new public Color BackColor { get; set; }
        new public Color ForeColor { get; set; }

        public MyProgressBar()
        {
            // Modify the ControlStyles flags
            //http://msdn.microsoft.com/en-us/library/system.windows.forms.controlstyles.aspx
            SetStyle(ControlStyles.UserPaint | ControlStyles.AllPaintingInWmPaint, true);

            BackColor = Color.CadetBlue;
            ForeColor = Color.DimGray;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Rectangle rect = ClientRectangle;
            Graphics g = e.Graphics;

            ProgressBarRenderer.DrawHorizontalBar(g, rect);
            rect.Inflate(-3, -3);
            if (Value > 0)
            {
                // As we doing this ourselves we need to draw the chunks on the progress bar
                Rectangle clip = new Rectangle(rect.X - 2, rect.Y - 2, (int)Math.Round(((float)Value / Maximum) * rect.Width) + 4, rect.Height + 4);
                g.FillRectangle(new SolidBrush(this.BackColor), clip);
            }

            // Set the Display text (Either a % amount or our custom text
            string text = DisplayStyle == ProgressBarDisplayText.Percentage ? Value.ToString() + '%' : CustomText;


            using (Font f = new Font(FontFamily.GenericSerif, 10, FontStyle.Bold))
            {

                SizeF len = g.MeasureString(text, f);
                // Calculate the location of the text (the middle of progress bar)
                Point location = new Point(Convert.ToInt32((rect.Width / 2) - (len.Width / 2)), Convert.ToInt32((rect.Height / 2) - (len.Height / 2)) + 4);
                // Draw the custom text
                g.DrawString(text, f, new SolidBrush(this.ForeColor), location);
            }
        }
    }
}
