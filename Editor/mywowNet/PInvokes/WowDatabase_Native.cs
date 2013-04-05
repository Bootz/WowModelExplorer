using System;
using System.Text;
using System.Runtime.InteropServices;

namespace mywowNet
{
    public partial class WowDatabase
    {
        const string DllName = @"mywow_dll.dll";

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getItemCount")]
        public static extern uint WowDatabase_getItemCount();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getItem")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getItem(
            uint index,
            out SItem item);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getItemById")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getItemById(
            int id,
            out SItem item);


        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_itemIsCorrectType")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_itemIsCorrectType(
            int type,
            int slot);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getNpcCount")]
        public static extern uint WowDatabase_getNpcCount();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getNpc")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getNpc(
            uint index,
            out SNpc npc);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getRaceId")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getRaceId(
            [MarshalAs(UnmanagedType.LPStr)]string race,
            out uint id);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getStartOutfitCount")]
        public static extern uint WowDatabase_getStartOutfitCount(
            uint race,
            [MarshalAsAttribute(UnmanagedType.I1)]bool female);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getStartOutfit")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getStartOutfit(
            uint race,
            [MarshalAsAttribute(UnmanagedType.I1)]bool female,
            uint index,
            out SEntry entry);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getSetCount")]
        public static extern uint WowDatabase_getSetCount();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getSet")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getSet(
            uint index,
            out SEntry entry);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getMapCount")]
        public static extern uint WowDatabase_getMapCount();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getMap")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getMap(
            uint index,
            out SMap map);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getSpellVisualEffectCount")]
        public static extern uint WowDatabase_getSpellVisualEffectCount();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getSpellVisualEffectId")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getSpellVisualEffectId(
            uint index,
            out int visualId);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_buildItems")]
        public static extern void WowDatabase_buildItems();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_buildNpcs")]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_buildNpcs(
            [MarshalAs(UnmanagedType.LPStr)]string filename);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_buildStartOutfitClass")]
        public static extern void WowDatabase_buildStartOutfitClass();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_buildMaps")]
        public static extern void WowDatabase_buildMaps();

        [DllImport(DllName, EntryPoint = "WowDatabase_getCharacterPath", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getCharacterPath(
            [MarshalAs(UnmanagedType.LPStr)]string race,
            [MarshalAsAttribute(UnmanagedType.I1)]bool female,
            StringBuilder path,
            uint size);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "WowDatabase_getMaxCharFeature")]
        public static extern void WowDatabase_getMaxCharFeature(
             uint raceid,
             [MarshalAsAttribute(UnmanagedType.I1)]bool female,
             out SCharFeature feature);

        [DllImport(DllName, EntryPoint = "WowDatabase_getNpcPath", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getNpcPath(
             int npcid,
             StringBuilder path,
             uint size);

        [DllImport(DllName, EntryPoint = "WowDatabase_getItemVisualPath", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getItemVisualPath(
             int visualId,
             StringBuilder path,
             uint size);

        [DllImport(DllName, EntryPoint = "WowDatabase_getSpellVisualEffectName", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getSpellVisualEffectName(
             int visualId,
             StringBuilder path,
             uint size);

        [DllImport(DllName, EntryPoint = "WowDatabase_getSpellVisualEffectPath", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool WowDatabase_getSpellVisualEffectPath(
             int visualId,
             StringBuilder path,
             uint size);

    }
}