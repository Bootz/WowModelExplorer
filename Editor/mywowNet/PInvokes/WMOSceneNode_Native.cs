using System;
using System.Runtime.InteropServices;
using System.ComponentModel;
using System.Text;

namespace mywowNet
{
    public partial class WMOSceneNode
    {
        const string DllName = @"mywow_dll.dll";

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WMOSceneNode_showEditPart")]
        public static extern void WMOSceneNode_showEditPart(
            IntPtr node,
            E_WMO_EDIT_PART editpart,
            [MarshalAsAttribute(UnmanagedType.I1)]bool show);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WMOSceneNode_setWireframe")]
        public static extern void WMOSceneNode_setWireframe(
            IntPtr node,
            E_OVERRIDE_WIREFRAME wireframe);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WMOSceneNode_getFileWMO")]
        public static extern void WMOSceneNode_getFileWMO(
            IntPtr node,
            out SFileWMO filewmo);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WMOSceneNode_getGroup")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WMOSceneNode_getGroup(
            IntPtr node,
            uint index,
            out SWMOGroup group);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WMOSceneNode_showGroup")]
        public static extern void WMOSceneNode_showGroup(
            IntPtr node,
            uint index,
            [MarshalAsAttribute(UnmanagedType.I1)]bool show);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WMOSceneNode_isGroupShow")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WMOSceneNode_isGroupShow(
            IntPtr node,
            uint index);
    }
}
