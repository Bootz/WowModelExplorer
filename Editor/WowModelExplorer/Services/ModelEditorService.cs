using System;
using WowModelExplorer;
using mywowNet;

namespace WowModelExplorer.Services
{
    public class ModelEditorService
    {
        //model part
        private bool isShowHelm = true;
        private bool isShowCape = true;
        private bool isShowShoulder = true;
        private bool isShowLeftHand = true;
        private bool isShowRightHand = true;

        //model editing part
        private bool isShowModel = true;
        private bool isShowParticles = true;
        private bool isShowModelBoundingBox = false;
        private bool isShowBones = false;
        private bool isShowAttachmentPoints = false;

        //wmo editing part
        private bool isShowWmo = true;
        private bool isShowDoodads = true;
        private bool isShowWmoBoundingBox = false;

        //options
        private bool isShowDebugText = true;
        private bool isShowDebugGeosets = false;
        private bool isShowPlane = true;
        private bool isShowCoord = true;

        //override material
        private E_OVERRIDE_WIREFRAME m2Wireframe = E_OVERRIDE_WIREFRAME.EOW_NONE;
        private E_OVERRIDE_WIREFRAME wmoWireframe = E_OVERRIDE_WIREFRAME.EOW_NONE;

        //music
        private BackMusicFiles backmusic = BackMusicFiles.None;
        private int musicIndex = -1;

        //state mode
        private bool stateMode = false;

        public ModelEditorService()
        {
            if (instance == null)
            {
                instance = this;
            }
        }

        private static ModelEditorService instance = null;
        public static ModelEditorService Instance { get { return instance; } }

        public bool IsShow(E_MODEL_PART modelpart)
        {
            switch (modelpart)
            {
                case E_MODEL_PART.EMP_HEAD:
                    return isShowHelm;
                case E_MODEL_PART.EMP_CAPE:
                    return isShowCape;
                case E_MODEL_PART.EMP_SHOULDER:
                    return isShowShoulder;
                case E_MODEL_PART.EMP_LEFTHAND:
                    return isShowLeftHand;
                case E_MODEL_PART.EMP_RIGHTHAND:
                    return isShowRightHand;
            }
            return false;
        }

        public void SetShow(E_MODEL_PART modelpart, bool show)
        {
            switch (modelpart)
            {
                case E_MODEL_PART.EMP_HEAD:
                    isShowHelm = show;
                    break;
                case E_MODEL_PART.EMP_CAPE:
                    isShowCape = show;
                    break;
                case E_MODEL_PART.EMP_SHOULDER:
                    isShowShoulder = show;
                    break;
                case E_MODEL_PART.EMP_LEFTHAND:
                    isShowLeftHand = show;
                    break;
                case E_MODEL_PART.EMP_RIGHTHAND:
                    isShowRightHand = show;
                    break;
            }
        }

        public bool IsShow(E_MODEL_EDIT_PART editpart)
        {
            switch (editpart)
            {
                case E_MODEL_EDIT_PART.EEP_MODEL:
                    return isShowModel;
                case E_MODEL_EDIT_PART.EEP_PARTICLES:
                    return isShowParticles;
                case E_MODEL_EDIT_PART.EEP_BOUNDINGBOX:
                    return isShowModelBoundingBox;
                case E_MODEL_EDIT_PART.EEP_BONES:
                    return isShowBones;
                case E_MODEL_EDIT_PART.EEP_ATTACHMENTPOINTS:
                    return isShowAttachmentPoints;
            }
            return false;
        }

        public void SetShow(E_MODEL_EDIT_PART editpart, bool show)
        {
            switch (editpart)
            {
                case E_MODEL_EDIT_PART.EEP_MODEL:
                    isShowModel = show;
                    break;
                case E_MODEL_EDIT_PART.EEP_PARTICLES:
                    isShowParticles = show;
                    break;
                case E_MODEL_EDIT_PART.EEP_BOUNDINGBOX:
                    isShowModelBoundingBox = show;
                    break;
                case E_MODEL_EDIT_PART.EEP_BONES:
                    isShowBones = show;
                    break;
                case E_MODEL_EDIT_PART.EEP_ATTACHMENTPOINTS:
                    isShowAttachmentPoints = show;
                    break;
            }
        }

        public bool IsShow(E_WMO_EDIT_PART editpart)
        {
            switch(editpart)
            {
                case E_WMO_EDIT_PART.EEP_WMO:
                    return isShowWmo;
                case E_WMO_EDIT_PART.EEP_DOODADS:
                    return isShowDoodads;
                case E_WMO_EDIT_PART.EEP_BOUNDINGBOX:
                    return isShowWmoBoundingBox;
            }
            return false;
        }

        public void SetShow(E_WMO_EDIT_PART editpart, bool show)
        {
            switch (editpart)
            {
                case E_WMO_EDIT_PART.EEP_WMO:
                    isShowWmo = show;
                    break;
                case E_WMO_EDIT_PART.EEP_DOODADS:
                    isShowDoodads = show;
                    break;
                case E_WMO_EDIT_PART.EEP_BOUNDINGBOX:
                    isShowWmoBoundingBox = show;
                    break;
            }
        }

        public bool IsShow(EditorShowOptions option)
        {
            switch (option)
            {
                case EditorShowOptions.DebugText:
                    return isShowDebugText;
                case EditorShowOptions.DebugGeosets:
                    return isShowDebugGeosets;
                case EditorShowOptions.Plane:
                    return isShowPlane;
                case EditorShowOptions.Coord:
                    return isShowCoord;
            }
            return false;
        }

        public void SetShow(EditorShowOptions option, bool show)
        {
            switch (option)
            {
                case EditorShowOptions.DebugText:
                    isShowDebugText = show;
                    break;
                case EditorShowOptions.DebugGeosets:
                    isShowDebugGeosets = show;
                    break;
                case EditorShowOptions.Plane:
                    isShowPlane = show;
                    break;
                case EditorShowOptions.Coord:
                    isShowCoord = show;
                    break;
            }
        }

        public void ShowModelPart(M2SceneNode node)
        {
            if (node != null && node.Type == M2Type.MT_CHARACTER && !node.IsNpc)
            {
                //apply show option
                node.ShowModelPart(E_MODEL_PART.EMP_HEAD, isShowHelm);
                node.ShowModelPart(E_MODEL_PART.EMP_CAPE, isShowCape);
                node.ShowModelPart(E_MODEL_PART.EMP_SHOULDER, isShowShoulder);
                node.ShowModelPart(E_MODEL_PART.EMP_LEFTHAND, isShowLeftHand);
                node.ShowModelPart(E_MODEL_PART.EMP_RIGHTHAND, isShowRightHand);
            }
        }

        public void ShowEditPart(M2SceneNode node)
        {
            if (node != null)
            {
                node.ShowEditPart(E_MODEL_EDIT_PART.EEP_MODEL, isShowModel);
                node.ShowEditPart(E_MODEL_EDIT_PART.EEP_PARTICLES, isShowParticles);
                node.ShowEditPart(E_MODEL_EDIT_PART.EEP_BOUNDINGBOX, isShowModelBoundingBox);
                node.ShowEditPart(E_MODEL_EDIT_PART.EEP_BONES, isShowBones);
                node.ShowEditPart(E_MODEL_EDIT_PART.EEP_ATTACHMENTPOINTS, isShowAttachmentPoints);
            }
        }

        public void SetWireFrame(M2SceneNode node)
        {
            if (node != null)
                node.SetWireFrame(M2WireFrame);
        }

        public void SetWireFrame(WMOSceneNode node)
        {
            if (node != null)
                node.SetWireFrame(WmoWireFrame);
        }

       public E_OVERRIDE_WIREFRAME M2WireFrame
        {
            get { return m2Wireframe; }
            set { m2Wireframe = value; } 
        }

        public E_OVERRIDE_WIREFRAME WmoWireFrame
        {
            get { return wmoWireframe; }
            set { wmoWireframe = value; } 
        }

        public BackMusicFiles BackMusic
        {
            get { return backmusic; }
            set { backmusic = value; }
        }

        public int MusicIndex
        {
            get { return musicIndex; }
            set { musicIndex = value; }
        }

        public bool StateMode
        {
            get { return stateMode; }
            set { stateMode = value; }
        }
    }
}
