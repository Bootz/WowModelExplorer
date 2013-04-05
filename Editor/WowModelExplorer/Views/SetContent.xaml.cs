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
using WowModelExplorer.Controls;
using WowModelExplorer.Data;
using WowModelExplorer.Services;
using mywowNet;

namespace WowModelExplorer.Views
{
    /// <summary>
    /// Interaction logic for SetsContent.xaml
    /// </summary>
    public partial class SetContent : DockableContent
    {
        public SetContent()
        {
            InitializeComponent();

            _setSelect.Set_Selected += new Set_SelectedEventHandler(_setSelect_Set_Selected);
        }

        void _setSelect_Set_Selected(object sender, Set set)
        {
            M2SceneNode node = ModelSceneService.Instance.MainM2SceneNode;
            if (node != null && node.Type == M2Type.MT_CHARACTER && !node.IsNpc)
            {
                node.LoadSet(set.Id);
                
                ModelEditorService.Instance.ShowModelPart(node);
                ModelEditorService.Instance.ShowEditPart(node);
                ModelEditorService.Instance.SetWireFrame(node);

                node.UpdateCharacter();

                //update property
                ShellService.Instance.PropertyContent.UpdateCharacterNode(node);
                ShellService.Instance.EquipmentsWindow.Update();
            }
        }

        public void Initialize()
        {
            _setSelect.FillData();
        }
    }
}
