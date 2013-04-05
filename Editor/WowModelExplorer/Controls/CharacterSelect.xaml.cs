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
using WowModelExplorer.Data;
using mywowNet;
using WowModelExplorer.Services;
using System.ComponentModel;

namespace WowModelExplorer.Controls
{
    public delegate void StartOutfitUpdatedHandler(object sender, M2SceneNode node);

    /// <summary>
    /// Interaction logic for CharacterSelect.xaml
    /// </summary>
    public partial class CharacterSelect : UserControl
    {
        private RaceInfo raceInfo;
        private bool female = false;
        private string startOutfitName;
        private int startOutfitId;

        private SelectionChangedEventHandler lbClassSelectionChanged;
        public event StartOutfitUpdatedHandler StartOutfitUpdated;

        public CharacterSelect()
        {
            InitializeComponent();

            lbClassSelectionChanged = new SelectionChangedEventHandler(_lbClasses_SelectionChanged);
            SubscribeEvents();
        }

        private void CharacterSelect_Loaded(object sender, RoutedEventArgs e)
        {
            if (_rbMale.IsChecked.Value == false && _rbFemale.IsChecked.Value == false)
                _rbMale.IsChecked = true;
        }

        private void SubscribeEvents()
        {
            Loaded += new RoutedEventHandler(CharacterSelect_Loaded);

            _lbAlliance.AddHandler(ListBoxItem.MouseDoubleClickEvent, new MouseButtonEventHandler(_lbAlliance_Selected));
            _lbAlliance.SelectionChanged += (sender, e) => 
                { 
                    if (_lbAlliance.SelectedIndex != -1)
                        _lbHorde.SelectedIndex = -1;
                };
            _lbAlliance.PreviewKeyDown += (sender, e) => { e.Handled = true; };
            _lbAlliance.PreviewKeyUp += (sender, e) => { e.Handled = true; };

            _lbHorde.AddHandler(ListBoxItem.MouseDoubleClickEvent, new MouseButtonEventHandler(_lbHorde_Selected));
            _lbHorde.SelectionChanged += (sender, e) =>
                {
                    if (_lbHorde.SelectedIndex != -1)
                        _lbAlliance.SelectedIndex = -1;
                };
            _lbHorde.PreviewKeyDown += (sender, e) => { e.Handled = true; };
            _lbHorde.PreviewKeyUp += (sender, e) => { e.Handled = true; };

            _rbFemale.Checked += new RoutedEventHandler(_rbFemale_Checked);
            _rbFemale.Unchecked += new RoutedEventHandler(_rbFemale_Unchecked);
        }

        void _lbClasses_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            StartOutfitClass outfit = _lbClasses.SelectedItem as StartOutfitClass;
            if (outfit != null)
            {
                startOutfitName = outfit.Name;
                startOutfitId = outfit.Id;

                UseStartOutfit();
            }
        }

        void _rbFemale_Checked(object sender, RoutedEventArgs e)
        {
            female = true;

            ChangeCharacter();
        }

        void _rbFemale_Unchecked(object sender, RoutedEventArgs e)
        {
            female = false;

            ChangeCharacter();
        }

        private void _lbAlliance_Selected(object sender, MouseButtonEventArgs e)
        {
            if (_lbAlliance.SelectedIndex != -1)
            {
                raceInfo = _lbAlliance.SelectedItem as RaceInfo;

                ChangeCharacter();
            }
        }

        private void _lbHorde_Selected(object sender, MouseButtonEventArgs e)
        {
            if (_lbHorde.SelectedIndex != -1)
            {
                raceInfo = _lbHorde.SelectedItem as RaceInfo;

                ChangeCharacter();
            }
        }

        private void ChangeCharacter()
        {
            if (raceInfo == null)
                return;

            WowDatabase _wowDatabase = Engine.Instance.WowDatabase;
            string path = _wowDatabase.GetCharacterPath(raceInfo.ShortName, female);
            M2SceneNode node = ModelSceneService.Instance.SetMainM2SceneNode(path, false);

             UpdateStartOutfitClasses();
             UpdateMaxCharFeature();
             UpdateCurrentCharFeature();
        }

        private void UpdateStartOutfitClasses()
        {
            _lbClasses.SelectionChanged -= lbClassSelectionChanged;

            StartOutfitClasses.GetStartOutfitClasses(raceInfo.RaceId, female);

            _lbClasses.SelectionChanged += lbClassSelectionChanged;

            if (!_lbClasses.Items.IsEmpty)
            {
                SelectClass(startOutfitName);
            }
        }

        private StartOutfitClass SelectClass(string name)
        {
            foreach (object item in _lbClasses.Items)
            {
                StartOutfitClass outfit = item as StartOutfitClass;
                if (outfit.Name == name)
                {
                    _lbClasses.SelectedItem = item;
                    return outfit;
                }
            }
            _lbClasses.SelectedIndex = 0;
            return _lbClasses.SelectedItem as StartOutfitClass;
        }

        private void UpdateMaxCharFeature()
        {
            MaxCharFeature.GetMaxCharFeature(raceInfo.RaceId, female);
        }

        private void UpdateCurrentCharFeature()
        {
            CurrentCharFeature.PropertyChanged -= new PropertyChangedEventHandler(CurrentCharFeature_PropertyChanged);

            M2SceneNode node = ModelSceneService.Instance.MainM2SceneNode;
            if (node != null && node.Type == M2Type.MT_CHARACTER && !node.IsNpc)
            {
                CurrentCharFeature.FromSCharFeature(node.CharFeature);
            }

            CurrentCharFeature.PropertyChanged += new PropertyChangedEventHandler(CurrentCharFeature_PropertyChanged);
        }

        private void UseStartOutfit()
        {
            M2SceneNode node = ModelSceneService.Instance.MainM2SceneNode;
            if (node != null && node.Type == M2Type.MT_CHARACTER && !node.IsNpc)
            {
                 node.LoadStartOutfitId(startOutfitId, startOutfitName == "死亡骑士" || startOutfitName == "DeathKnight");
 
                 ModelEditorService.Instance.ShowModelPart(node);
                 ModelEditorService.Instance.ShowEditPart(node);
                 ModelEditorService.Instance.SetWireFrame(node);

                 node.UpdateCharacter();

                if (StartOutfitUpdated != null)
                {
                    StartOutfitUpdated.Invoke(this, node);
                }
            }
        }

        void CurrentCharFeature_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            M2SceneNode node = ModelSceneService.Instance.MainM2SceneNode;
            if (node != null && node.Type == M2Type.MT_CHARACTER && !node.IsNpc)
            {
                SCharFeature schar = new SCharFeature();
                schar.skinColor = CurrentCharFeature.SkinColor;
                schar.faceType = CurrentCharFeature.FaceType;
                schar.hairStyle = CurrentCharFeature.HairStyle;
                schar.hairColor = CurrentCharFeature.HairColor;
                schar.facialHair = CurrentCharFeature.FacialHair;

                node.CharFeature = schar;

                ModelEditorService.Instance.ShowModelPart(node);
                ModelEditorService.Instance.ShowEditPart(node);
                ModelEditorService.Instance.SetWireFrame(node);

                node.UpdateCharacter();
            }
        }

        public RaceInfoCollection AllianceRaceInfos 
        {
            get { return _mainGrid.Resources["_allianceRaces"] as RaceInfoCollection;  }
        }

        public RaceInfoCollection HordeRaceInfos
        {
            get { return _mainGrid.Resources["_hordeRaces"] as RaceInfoCollection; }
        }

        public StartOutfitClassCollection StartOutfitClasses
        {
            get { return _mainGrid.Resources["_startOutfitClasses"] as StartOutfitClassCollection;  }
        }

        public CharFeature MaxCharFeature
        {
            get { return _mainGrid.Resources["_maxCharFeature"] as CharFeature; }
        }

        public CharFeature CurrentCharFeature
        {
            get { return _mainGrid.Resources["_currentCharFeature"] as CharFeature; }
        }

    }
}
