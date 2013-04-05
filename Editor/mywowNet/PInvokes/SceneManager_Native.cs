using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace mywowNet
{
    public partial class SceneManager
    {
        const string DllName = @"mywow_dll.dll";

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_drawAll")]
        public static extern void SceneManager_drawAll();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_setBackgroundColor")]
        public static extern void SceneManager_setBackgroundColor(
            SColor color);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_getBackgroundColor")]
        public static extern void SceneManager_getBackgroundColor(
            out SColor color);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_showDebug")]
        public static extern void SceneManager_showDebug(
         E_SCENE_DEBUG_PART part, 
         [MarshalAsAttribute(UnmanagedType.I1)]bool show);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_removeSceneNode")]
        public static extern void SceneManager_removeSceneNode(
            IntPtr sceneNode);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_removeAllCameras")]
        public static extern void SceneManager_removeAllCameras();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_removeAllSceneNodes")]
        public static extern void SceneManager_removeAllSceneNodes();


        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_setDebugM2Node")]
        public static extern void SceneManager_setDebugM2Node(
            IntPtr sceneNode);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_setDebugWMONode")]
        public static extern void SceneManager_setDebugWMONode(
            IntPtr sceneNode);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_setActiveCamera")]
        public static extern void SceneManager_setActiveCamera(
            IntPtr cam);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_getActiveCamera")]
        public static extern IntPtr SceneManager_getActiveCamera();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_addCamera")]
        public static extern IntPtr SceneManager_addCamera(
            vector3df position,
            vector3df lookat,
            vector3df up,
            float near,
            float far,
            float fov);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_addCoordSceneNode")]
        public static extern IntPtr SceneManager_addCoordSceneNode( );

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_addMeshSceneNode")]
        public static extern IntPtr SceneManager_addMeshSceneNode(
            [MarshalAs(UnmanagedType.LPStr, SizeConst = 64)]string name,
            IntPtr parent);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_addM2SceneNode")]
        public static extern IntPtr SceneManager_addM2SceneNode(
            [MarshalAs(UnmanagedType.LPStr, SizeConst = 256)]string meshfilename,
            IntPtr parent,
            [MarshalAsAttribute(UnmanagedType.I1)]bool npc);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneManager_addWMOSceneNode")]
        public static extern IntPtr SceneManager_addWMOSceneNode(
            [MarshalAs(UnmanagedType.LPStr, SizeConst = 256)]string wmofilename,
            IntPtr parent);

    }
}