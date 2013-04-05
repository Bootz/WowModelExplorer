using System;
using System.Runtime.InteropServices;

namespace mywowNet
{
    [StructLayout(LayoutKind.Sequential)]
    public struct SColor
    {
        public SColor(uint a, uint r, uint g, uint b)
        {
            color = ((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
        }

        public SColor(uint r, uint g, uint b)
        {
            color = ((uint)(0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
        }

        /// unsigned int
        public uint color;

        public byte A
        {
            get { return (byte)((color >> 24) & 0xff); }
        }

        public byte R
        {
            get { return (byte)((color >> 16) & 0xff); }
        }

        public byte G
        {
            get { return (byte)((color >> 8) & 0xff); }
        }

        public byte B
        {
            get { return (byte)((color) & 0xff); }
        }

    }

    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct SVideoSetting
    {
        /// unsigned int
        public uint antialias;

        /// boolean
        [MarshalAs(UnmanagedType.I1)]
        public bool vsync;
        /// boolean
        [MarshalAs(UnmanagedType.I1)]
        public bool fullscreen;

        /// boolean
        [MarshalAs(UnmanagedType.I1)]
        public bool materialProjection;
        /// int
        public E_LEVEL materialResolution;

        /// int
        public E_TEXTURE_FILTER textureFilter;

      
        // int
        public E_LEVEL viewDistance;
        public E_LEVEL envDetail;
        public E_LEVEL groundScene;

        public E_LEVEL shadowQuality;
        public E_LEVEL liquidDetail;
        public E_LEVEL sunLightEffect;
        public E_LEVEL particleDensity;
        public E_LEVEL SSAO;
    }

    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct SAdvancedSetting
    {
         /// boolean
        [MarshalAs(UnmanagedType.I1)]
        public bool tripleBuffers;
        /// boolean
        [MarshalAs(UnmanagedType.I1)]
        public bool reduceInputDelay;
        /// boolean
        [MarshalAs(UnmanagedType.I1)]
        public bool useHardwarePointer;

        /// int
        public int maxForegroundFPS;

        /// int
        public int maxBackgroundFPS;
    }

    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct SItem
    {
        /// wchar_t[64]
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string name;

        /// int
        public int id;

        /// int
        public int type;

        ///int
        public int modelId;

        /// wchar_t[64]
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string subclassname;
    }

    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct SCharFeature
    {   
        /// unsigned int
        public uint skinColor;

        /// unsigned int
        public uint faceType;

        /// unsigned int
        public uint hairColor;

        /// unsigned int
        public uint hairStyle;

        /// unsigned int
        public uint facialHair;
    }

    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct SNpc
    {
        /// wchar_t[64]
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string name;

        /// int
        public int modelDisplayId;

        /// int
        public int modelId;

        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string type;
    }

    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct SEntry
    {
        /// wchar_t[64]
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string name;

        /// int
        public int id;
    }

    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SAnimation
    {

        /// char[64]
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string name;

        /// unsigned int
        public uint subIndex;

        /// unsigned int
        public uint length;

        /// unsigned int
        public uint animIndex;

        /// int
        public int next;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct SMap
    {
        /// int
        public int id;

        /// wchar_t[64]
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string internalname;

        /// wchar_t[64]
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string name;

        /// int
        public int type;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SFileM2
    {

        /// char[64]
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string name;

        /// char[256]
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string longname;

        /// unsigned int
        public uint numVertices;

        /// unsigned int
        public uint numBoundingVerts;

        /// unsigned int
        public uint numBoundingTriangles;

        /// unsigned int
        public uint numTextures;

        /// unsigned int
        public uint numTexLookup;

        /// unsigned int
        public uint numAttachLookup;

        /// unsigned int
        public uint numGlobalSequences;

        /// unsigned int
        public uint numColors;

        /// unsigned int
        public uint numTransparencies;

        /// unsigned int
        public uint numTransparencyLookup;

        /// unsigned int
        public uint numTexAnim;

        /// unsigned int
        public uint numAnimations;

        /// unsigned int
        public uint numBones;

        /// unsigned int
        public uint numRenderFlags;

        /// unsigned int
        public uint numParticleSystems;

        /// unsigned int
        public uint numRibbonEmitters;

        /// unsigned int
        public uint numGeosets;

        /// unsigned int
        public uint numTexUnits;
    }


    [StructLayout(LayoutKind.Sequential)]
    public struct SRenderFlag
    {

        /// unsigned short
        public ushort flags;

        /// unsigned short
        public ushort blend;

        /// boolean
        [MarshalAs(UnmanagedType.I1)]
        public bool lighting;

        /// boolean
        [MarshalAs(UnmanagedType.I1)]
        public bool zwrite;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct SGeoset
    {

        /// unsigned int
        public uint vcount;

        /// unsigned int
        public uint icount;

        /// unsigned int
        public uint geoID;

        /// short
        public short texID;

        /// unsigned short
        public ushort rfIndex;

        /// short
        public short colorIndex;

        /// short
        public short transIndex;

        /// short
        public short texAnimIndex;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct SM2ChildSceneNodes
    {
        /// IM2SceneNode*
        public IntPtr head;

        /// IM2SceneNode*
        public IntPtr leftShoulder;

        /// IM2SceneNode*
        public IntPtr rightShoulder;

        /// IM2SceneNode*
        public IntPtr leftHand;

        /// IM2SceneNode*
        public IntPtr rightHand;
    }


    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SFileWMO
    {

        /// char[64]
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string name;

        /// char[256]
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string longname;

        /// unsigned int
        public uint numMaterials;

        /// unsigned int
        public uint numGroups;

        /// unsigned int
        public uint numPortals;

        /// unsigned int
        public uint numLights;

        /// unsigned int
        public uint numModels;

        /// unsigned int
        public uint numDoodads;

        /// unsigned int
        public uint numDoodadSets;

        /// unsigned int
        public uint wmoID;
    }

    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct SWMOGroup
    {
        /// char[64]
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string name;

        /// unsigned int
        public uint numBatches;

        /// unsigned int
        public uint numLights;

        /// unsigned int
        public uint numDoodads;

        /// unsigned int
        public uint ICount;

        /// unsigned int
        public uint VCount;
    }
}
