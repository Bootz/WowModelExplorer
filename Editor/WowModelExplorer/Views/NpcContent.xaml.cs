using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using AvalonDock;
using WowModelExplorer.Data;
using WowModelExplorer.Controls;
using WowModelExplorer.Services;
using mywowNet;

namespace WowModelExplorer.Views
{
    /// <summary>
    /// Interaction logic for NpcContent.xaml
    /// </summary>
    public partial class NpcContent : DockableContent
    {
        public NpcContent()
        {
            InitializeComponent();

            _npcSelect.Npc_Selected += new Npc_SelectedEventHandler(_npcSelect_Npc_Selected);
        }

        void _npcSelect_Npc_Selected(object sender, Npc npc)
        {
            string path = Engine.Instance.WowDatabase.GetNpcPath(npc.ModelDisplayId);
            M2SceneNode node = ModelSceneService.Instance.SetMainM2SceneNode(path, true);
            if (node != null)
            {
                ModelEditorService.Instance.ShowEditPart(node);
                ModelEditorService.Instance.SetWireFrame(node);

                node.UpdateNpc(npc.ModelDisplayId);

                //update property
                if (node.Type == M2Type.MT_CHARACTER)
                {
                    ShellService.Instance.PropertyContent.UpdateCharacterNode(node);
                    ShellService.Instance.EquipmentsWindow.Update();
                }
                else
                    ShellService.Instance.PropertyContent.UpdateNpcNode(node);
            }
        }

        public void Initialize()
        {
            _npcSelect.FillData();
        }

    }
}
