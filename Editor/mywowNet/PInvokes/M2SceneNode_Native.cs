using System;
using System.Runtime.InteropServices;
using System.ComponentModel;
using System.Text;

namespace mywowNet
{
    public partial class M2SceneNode
    {
        const string DllName = @"mywow_dll.dll";

        #region base

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getFileM2")]
        public static extern void M2SceneNode_getFileM2(
            IntPtr node,
            out SFileM2 filem2);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getType")]
        public static extern M2Type M2SceneNode_getType(
            IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_isNpc")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_isNpc(
            IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_buildVisibleGeosets")]
        public static extern void M2SceneNode_buildVisibleGeosets(
            IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_updateCharacter")]
        public static extern void M2SceneNode_updateCharacter(
           IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_updateNpc")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_updateNpc(
            IntPtr node,
            int npcid);

#endregion

        #region camera

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_setModelCamera")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_setModelCamera(
            IntPtr node,
            int cameraid);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getModelCamera")]
        public static extern int M2SceneNode_getModelCamera(
            IntPtr node);

        #endregion

        #region animations

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_playAnimationByName")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_playAnimationByName(
            IntPtr node,
            [MarshalAs(UnmanagedType.LPStr, SizeConst = 64)]string name,
            uint subIdx,
            [MarshalAsAttribute(UnmanagedType.I1)]bool loop,
            int timeblend);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_playAnimationByIndex")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_playAnimationByIndex(
            IntPtr node,
            uint anim,
            [MarshalAsAttribute(UnmanagedType.I1)]bool loop,
            int timeblend);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getAnimationCount")]
        public static extern uint M2SceneNode_getAnimationCount(
            IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getAnimation")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_getAnimation(
            IntPtr node,
            uint index,
            out SAnimation anim);

#endregion


        #region charfeature

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_setCharFeature")]
        public static extern void M2SceneNode_setCharFeature(
            IntPtr node,
            SCharFeature feature);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getCharFeature")]
        public static extern void M2SceneNode_getCharFeature(
            IntPtr node,
            out SCharFeature feature);

#endregion

      
        #region  item

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_takeItem")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_takeItem(
            IntPtr node,
            int itemid,
            out int slot);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_resetSlot")]
        public static extern void M2SceneNode_resetSlot(
            IntPtr node,
            int slot);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getSlotItemId")]
        public static extern int M2SceneNode_getSlotItemId(
            IntPtr node,
            int slot);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_slotHasModel")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_slotHasModel(
            IntPtr node,
            int slot);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_loadStartOutfit")]
        public static extern void M2SceneNode_loadStartOutfit(
            IntPtr node,
            int startId,
            [MarshalAsAttribute(UnmanagedType.I1)]bool deathknight);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_loadSet")]
        public static extern void M2SceneNode_loadSet(
            IntPtr node,
            int setid);

#endregion

       
        #region animation player

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_pause")]
        public static extern void M2SceneNode_pause(
             IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_resume")]
        public static extern void M2SceneNode_resume(
             IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_stop")]
        public static extern void M2SceneNode_stop(
             IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_step")]
        public static extern void M2SceneNode_step(
             IntPtr node,
            float frame);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_isPlaying")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_isPlaying(
             IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getCurrentFrame")]
        public static extern float M2SceneNode_getCurrentFrame(
             IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_setCurrentFrame")]
        public static extern void M2SceneNode_setCurrentFrame(
             IntPtr node,
            float frame);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getCurrentAnimationIndex")]
        public static extern int M2SceneNode_getCurrentAnimationIndex(
             IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_setLoop")]
        public static extern void M2SceneNode_setLoop(
            IntPtr node,
            [MarshalAsAttribute(UnmanagedType.I1)]bool loop);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_isLoop")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_isLoop(
             IntPtr node);

#endregion

     
        #region show/hide

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_showModelPart")]
        public static extern void M2SceneNode_showModelPart(
            IntPtr node,
            E_MODEL_PART modepart,
            [MarshalAsAttribute(UnmanagedType.I1)]bool show);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_showEditPart")]
        public static extern void M2SceneNode_showEditPart(
            IntPtr node,
            E_MODEL_EDIT_PART editpart,
            [MarshalAsAttribute(UnmanagedType.I1)]bool show);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_setWireframe")]
        public static extern void M2SceneNode_setWireframe(
            IntPtr node,
            E_OVERRIDE_WIREFRAME wireframe);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_showGeoset")]
        public static extern void M2SceneNode_showGeoset(
            IntPtr node,
            uint index,
            [MarshalAsAttribute(UnmanagedType.I1)]bool show);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_isGeosetShow")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_isGeosetShow(
            IntPtr node,
            uint index);

#endregion


        #region Child SceneNode
         [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getChildSceneNodes")]
         [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_getChildSceneNodes(
            IntPtr node,
            out SM2ChildSceneNodes sceneNodes);

#endregion

        #region file property

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getRenderFlag")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_getRenderFlag(
            IntPtr node,
            out SRenderFlag renderflag,
            uint index);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getGeoset")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_getGeoset(
            IntPtr node,
            uint index,
            out SGeoset geoset);

        [DllImport(DllName, EntryPoint = "M2SceneNode_getReplaceTextureFileName", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
         public static extern void M2SceneNode_getReplaceTextureFileName(
              IntPtr node,
              E_MODEL_REPLACE_TEXTURE texture, 
              StringBuilder path,
              uint size);

        [DllImport(DllName, EntryPoint = "M2SceneNode_getTextureFileName", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void M2SceneNode_getTextureFileName(
              IntPtr node,
              uint index, 
              StringBuilder path,
              uint size);

        [DllImport(DllName, EntryPoint = "M2SceneNode_getRegionTextureFileName", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void M2SceneNode_getRegionTextureFileName(
             IntPtr node,
             ECharRegions region,
             StringBuilder path,
             uint size);

        #endregion

        #region property
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_setModelAlpha")]
        public static extern void M2SceneNode_setModelAlpha(
            IntPtr node,
            float alpha);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getModelAlpha")]
        public static extern float M2SceneNode_getModelAlpha(
            IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_setModelColor")]
        public static extern void M2SceneNode_setModelColor(
            IntPtr node,
            SColor color);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_getModelColor")]
        public static extern void M2SceneNode_getModelColor(
            IntPtr node,
            out SColor color);
#endregion

        #region logic

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_resetState")]
        public static extern void M2SceneNode_resetState(
            IntPtr node);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_isStateValid")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_isStateValid(
            IntPtr node,
            E_M2_STATES state);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "M2SceneNode_changeState")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool M2SceneNode_changeState(
            IntPtr node,
            E_M2_STATES state);

        #endregion
    }
}