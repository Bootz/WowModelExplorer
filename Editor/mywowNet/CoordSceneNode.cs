using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.ComponentModel;
using System.Text;

namespace mywowNet
{
    public partial class CoordSceneNode : SceneNode
    {
         public CoordSceneNode(IntPtr raw) : base(raw) { }

        public void SetPosition2D(E_POSITION_2D position, float distance)
        {
            CoordSceneNode_setPosition2D(pointer, position, distance);
        }

        public void SetAxisColor(SColor colorX, SColor colorY, SColor colorZ)
        {
            CoordSceneNode_setAxisColor(pointer, colorX, colorY, colorZ);
        }

        public void SetAxisText(string textX, string textY, string textZ)
        {
            CoordSceneNode_setAxisText(pointer, textX, textY, textZ);
        }
    }
}
