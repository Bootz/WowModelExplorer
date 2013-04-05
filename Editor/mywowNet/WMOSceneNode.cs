using System;
using System.Runtime.InteropServices;

namespace mywowNet
{
    public partial class WMOSceneNode : SceneNode
    {
        public WMOSceneNode(IntPtr raw) : base(raw) {}

        public void SetWireFrame(E_OVERRIDE_WIREFRAME wireframe)
        {
            WMOSceneNode_setWireframe(pointer, wireframe);
        }

        public SFileWMO FileWMO
        {
            get
            {
                SFileWMO wmo = new SFileWMO();
                WMOSceneNode_getFileWMO(pointer, out wmo);
                return wmo;
            }
        }

        SWMOGroup[] _groups;
        public SWMOGroup[] Groups
        {
            get
            {
                uint num = FileWMO.numGroups;
                _groups = new SWMOGroup[num];
                for (uint i = 0; i < num; ++i)
                {
                    WMOSceneNode_getGroup(pointer, i, out _groups[i]);
                }
                return _groups;
            }
        }

        public void ShowGroup(int index, bool show)
        {
            WMOSceneNode_showGroup(pointer, (uint)index, show);
        }

        public bool IsGroupShow(int index)
        {
            return WMOSceneNode_isGroupShow(pointer, (uint)index);
        }

        public void ShowEditPart(E_WMO_EDIT_PART editpart, bool show)
        {
            WMOSceneNode_showEditPart(pointer, editpart, show);
        }

    }
}