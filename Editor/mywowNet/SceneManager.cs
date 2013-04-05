using System;
using System.Collections;
using System.Collections.Generic;

namespace mywowNet
{
    public partial class SceneManager : INative
    {
        public SceneManager(IntPtr raw) : base(raw) { }

        public void DrawAll()
        {
            SceneManager_drawAll();
        }

        public static SColor DefaultBackgroundColor = new SColor(64, 64, 64);
        public SColor BackgroundColor
        {
            set { SceneManager_setBackgroundColor(value); }
            get
            {
                SColor c = new SColor();
                SceneManager_getBackgroundColor(out c);
                return c;
            }
        }

        public void ShowDebug(E_SCENE_DEBUG_PART part, bool show)
        {
            SceneManager_showDebug(part, show);
        }

        public void SetDebugM2SceneNode(M2SceneNode node)
        {
            SceneManager_setDebugM2Node(node != null ? node.pointer : IntPtr.Zero);
        }

        public void SetDebugWMOSceneNode(WMOSceneNode node)
        {
            SceneManager_setDebugWMONode(node != null ? node.pointer : IntPtr.Zero);
        }

        Camera _activeCam = new Camera();
        public Camera ActiveCamera
        {
            get
            {
                IntPtr cam = SceneManager_getActiveCamera();
                if (cam == IntPtr.Zero)
                    return null;

                _activeCam.FromRaw(cam);
                return _activeCam;
            }
            set { SceneManager_setActiveCamera(value.pointer);  }
        }

        public void RemoveSceneNode(SceneNode node)
        {
            SceneManager_removeSceneNode(node.pointer);
        }

        public void RemoveAllSceneNodes()
        {
            SceneManager_removeAllSceneNodes();
        }

        public void RemoveAllCameras()
        {
            SceneManager_removeAllCameras();
        }

        public Camera AddCamera(vector3df position, vector3df lookat, vector3df up, float near, float far, float fov)
        {
            IntPtr raw = SceneManager_addCamera(position, lookat, up, near, far, fov);
            return new Camera(raw);
        }

        public CoordSceneNode AddCoordSceneNode()
        {
            IntPtr raw = SceneManager_addCoordSceneNode();
            if (raw == IntPtr.Zero)
                return null;
            return new CoordSceneNode(raw);
        }

        public MeshSceneNode AddMeshSceneNode(string name, SceneNode parent)
        {
            IntPtr raw = SceneManager_addMeshSceneNode(name, parent == null ? IntPtr.Zero : parent.pointer);
            if (raw == IntPtr.Zero)
                return null;
            return new MeshSceneNode(raw);
        }

        public M2SceneNode AddM2SceneNode(string meshfilename, SceneNode parent, bool npc)
        {
            IntPtr raw = SceneManager_addM2SceneNode(meshfilename, parent == null ? IntPtr.Zero : parent.pointer, npc);
            if (raw == IntPtr.Zero)
                return null;
            return new M2SceneNode(raw);
        }

        public WMOSceneNode AddWMOSceneNode(string wmofilename, SceneNode parent)
        {
            IntPtr raw = SceneManager_addWMOSceneNode(wmofilename, parent == null ? IntPtr.Zero : parent.pointer);
            if (raw == IntPtr.Zero)
                return null;
            return new WMOSceneNode(raw);
        }
    }
}
