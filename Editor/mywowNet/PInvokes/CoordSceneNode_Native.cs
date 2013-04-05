using System;
using System.Runtime.InteropServices;
using System.ComponentModel;
using System.Text;

namespace mywowNet
{
    public partial class CoordSceneNode
    {
        const string DllName = @"mywow_dll.dll";

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "CoordSceneNode_setPosition2D")]
        public static extern void CoordSceneNode_setPosition2D(IntPtr node, E_POSITION_2D position, float distance);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "CoordSceneNode_setAxisColor")]
        public static extern void CoordSceneNode_setAxisColor(IntPtr node, SColor colorX, SColor colorY, SColor colorZ);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "CoordSceneNode_setAxisText")]
        public static extern void CoordSceneNode_setAxisText(IntPtr node, 
            [In] [MarshalAs(UnmanagedType.LPStr)] string textX, 
            [In] [MarshalAs(UnmanagedType.LPStr)] string textY, 
            [In] [MarshalAs(UnmanagedType.LPStr)] string textZ);

    }
}
