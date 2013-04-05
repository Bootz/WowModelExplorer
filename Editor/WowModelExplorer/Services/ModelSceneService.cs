using System;
using mywowNet;
using WowModelExplorer.Controls;

namespace WowModelExplorer.Services
{
    public delegate void MainM2SceneNode_ChangedHandler(object sender, M2SceneNode node);
    public delegate void MainWMOSceneNode_ChangedHandler(object sender, WMOSceneNode node);

    class ModelSceneService
    {
        private CoordSceneNode coordSceneNode;
        private MeshSceneNode gridSceneNode;
        private M2SceneNode mainM2SceneNode;
        private WMOSceneNode mainWMOSceneNode;
        private FileWDT wdt;
        private FileADT adt;

        public ModelSceneService()
        {
            if (instance == null)
            {
                instance = this;
            }
         }
        private static ModelSceneService instance = null;
        public static ModelSceneService Instance { get { return instance; } }

        public CoordSceneNode CoordSceneNode { get { return coordSceneNode; } }
        public MeshSceneNode GridSceneNode { get { return gridSceneNode; } }
        public M2SceneNode MainM2SceneNode { get { return mainM2SceneNode; } }
        public WMOSceneNode MainWMOSceneNode { get { return mainWMOSceneNode; } }
        public FileWDT CurrentWDT { get { return wdt; } }
        public FileADT CurrentADT { get { return adt; } }

        public event MainM2SceneNode_ChangedHandler MainM2SceneNodeChanged;

        private void RemoveMainSceneNode()
        {
            if (mainM2SceneNode != null)
            {
                Engine.Instance.SceneManager.RemoveSceneNode(mainM2SceneNode);
                mainM2SceneNode = null;
            }

            if (mainWMOSceneNode != null)
            {
                Engine.Instance.SceneManager.RemoveSceneNode(mainWMOSceneNode);
                mainWMOSceneNode = null;
            }
        }

        public M2SceneNode SetMainM2SceneNode(string filename, bool npc)
        {
            RemoveMainSceneNode();

            M2SceneNode node = Engine.Instance.SceneManager.AddM2SceneNode(filename, null, npc);

            if (node != null)
            {
                switch(node.Type)
                {
                    case M2Type.MT_INTERFACE:
                        {
                            node.ResetState();
                            node.PlayAnimation("Stand", 0, true, 0);
                            node.SetCamera(0);
                        }
                        break;
                    default:
                        {
                            matrix4 mat = new matrix4(true);
                            mat.RotationDegrees = new vector3df(0, 90, 0);
                            node.SetRelativeTransformation(ref mat);

                            node.ResetState();
                            node.PlayAnimation("Stand", 0, true, 0);
                        }
                        break;
                }
            }

            Engine.Instance.SceneManager.SetDebugM2SceneNode(node);

            mainM2SceneNode = node;

            RaiseMainM2SceneNodeChanged();

            return node;
        }

        private void RaiseMainM2SceneNodeChanged()
        {
            if (MainM2SceneNodeChanged != null)
            {
                MainM2SceneNodeChanged.Invoke(this, mainM2SceneNode);
            }
        }

        public event MainWMOSceneNode_ChangedHandler MainWMOSceneNodeChanged;

        public WMOSceneNode SetMainWMOSceneNode(string filename)
        {
            RemoveMainSceneNode();

            WMOSceneNode node = Engine.Instance.SceneManager.AddWMOSceneNode(filename, null);

            Engine.Instance.SceneManager.SetDebugWMOSceneNode(node);

            mainWMOSceneNode = node;

            RaiseMainWMOSceneNodeChanged();

            return node;
        }

        private void RaiseMainWMOSceneNodeChanged()
        {
            if (MainWMOSceneNodeChanged != null)
            {
                MainWMOSceneNodeChanged.Invoke(this, mainWMOSceneNode);
            }
        }

        public FileWDT LoadWDT(string mapname, int mapid)
        {
            if (wdt != null)
            {
                wdt.UnloadADT(adt);
                adt = null;
                Engine.Instance.ResourceLoader.UnloadWDT(wdt);
                wdt = null;
            }                
            wdt = Engine.Instance.ResourceLoader.LoadWDT(mapname, mapid, true);
            return wdt;
        }

        public FileADT LoadADT(uint row, uint col, bool simple)
        {
            if (adt != null)
            {
                wdt.UnloadADT(adt);
                adt = null;
            }
            adt = wdt.LoadADT(row, col, simple);
            return adt;
        }

        public void Initialize()
        {
            Camera cam = Engine.Instance.SceneManager.AddCamera(new vector3df(0, 5, -10), new vector3df(0, 0, 0), new vector3df(0, 1, 0), 0.5f, 2400.0f, (float)Math.PI / 4.0f);

            Engine.Instance.ManualMeshServices.AddGridMesh("$grid10", 10, 1, new SColor(128, 128, 128));

            gridSceneNode = Engine.Instance.SceneManager.AddMeshSceneNode("$grid10", null);

            coordSceneNode = Engine.Instance.SceneManager.AddCoordSceneNode();
            coordSceneNode.SetPosition2D(E_POSITION_2D.EP2D_BOTTOMLEFT, 18);
            coordSceneNode.SetAxisText("x", "y", "z");
        }

        public void Shutdown()
        {
            Engine.Instance.SceneManager.RemoveAllSceneNodes();
            Engine.Instance.SceneManager.RemoveAllCameras();

            if (wdt != null)
            {
                wdt.UnloadADT(adt);
                adt = null;
                Engine.Instance.ResourceLoader.UnloadWDT(wdt);
                wdt = null;
            }      
        }

    }
}
