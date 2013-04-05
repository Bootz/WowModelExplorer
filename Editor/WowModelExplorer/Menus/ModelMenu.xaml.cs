using System;
using System.Windows;
using System.Windows.Controls;
using WowModelExplorer.Services;
using AvalonDock;
using mywowNet;

namespace WowModelExplorer.Menus
{
    /// <summary>
    /// Interaction logic for ModelMenu.xaml
    /// </summary>
    public partial class ModelMenu : UserControl
    {
        public ModelMenu()
        {
            InitializeComponent();

            this.Loaded += new RoutedEventHandler(ModelMenu_Loaded);
        }

        void ModelMenu_Loaded(object sender, RoutedEventArgs e)
        {
            m2SliderScale.ValueChanged += new RoutedPropertyChangedEventHandler<double>(M2SliderScale_ValueChanged);
            m2SliderOpacity.ValueChanged += new RoutedPropertyChangedEventHandler<double>(M2SliderOpacity_ValueChanged);
            wmoSliderScale.ValueChanged += new RoutedPropertyChangedEventHandler<double>(wmoSliderScale_ValueChanged);
            wmoSliderSpecularStrength.ValueChanged += new RoutedPropertyChangedEventHandler<double>(wmoSliderSpecularStrength_ValueChanged);
         }

        private void menuView_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            menuViewCharacter.IsChecked = ShellService.Instance.CharacterContent.State != DockableContentState.Hidden;
            menuViewNpc.IsChecked = ShellService.Instance.NpcContent.State != DockableContentState.Hidden;
            menuViewSpellVisualEffect.IsChecked = ShellService.Instance.SpellVisualEffectContent.State != DockableContentState.Hidden;
            menuViewMapModel.IsChecked = ShellService.Instance.MapModelContent.State != DockableContentState.Hidden;
            menuViewClothes.IsChecked = ShellService.Instance.ClothesContent.State != DockableContentState.Hidden;
            menuViewWeapon.IsChecked = ShellService.Instance.WeaponContent.State != DockableContentState.Hidden;
            menuViewSet.IsChecked = ShellService.Instance.SetContent.State != DockableContentState.Hidden;
            menuViewMapModelName.IsChecked = ShellService.Instance.MapModelNameContent.State != DockableContentState.Hidden;
            menuViewProperty.IsChecked = ShellService.Instance.PropertyContent.State != DockableContentState.Hidden;
            menuViewAnimation.IsChecked = ShellService.Instance.AnimationContent.State != DockableContentState.Hidden;
            menuViewM2State.IsChecked = ShellService.Instance.M2StateContent.State != DockableContentState.Hidden;
        }

        private void ShowOtherModel_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            menuShowHelm.IsChecked = ModelEditorService.Instance.IsShow(E_MODEL_PART.EMP_HEAD);
            menuShowCape.IsChecked = ModelEditorService.Instance.IsShow(E_MODEL_PART.EMP_CAPE);
            menuShowShoulder.IsChecked = ModelEditorService.Instance.IsShow(E_MODEL_PART.EMP_SHOULDER);
            menuShowLeftHand.IsChecked = ModelEditorService.Instance.IsShow(E_MODEL_PART.EMP_LEFTHAND);
            menuShowRightHand.IsChecked = ModelEditorService.Instance.IsShow(E_MODEL_PART.EMP_RIGHTHAND);
        }

        private void menuEditView_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            menuShowModel.IsChecked = ModelEditorService.Instance.IsShow(E_MODEL_EDIT_PART.EEP_MODEL);
            menuShowParticles.IsChecked = ModelEditorService.Instance.IsShow(E_MODEL_EDIT_PART.EEP_PARTICLES);
            menuShowBoundingBox.IsChecked = ModelEditorService.Instance.IsShow(E_MODEL_EDIT_PART.EEP_BOUNDINGBOX);
            menuShowBones.IsChecked = ModelEditorService.Instance.IsShow(E_MODEL_EDIT_PART.EEP_BONES);
            menuShowAttachmentPoints.IsChecked = ModelEditorService.Instance.IsShow(E_MODEL_EDIT_PART.EEP_ATTACHMENTPOINTS);
            menuModelStateMode.IsChecked = ModelEditorService.Instance.StateMode;
        }

        private void menuWmoView_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            menuWmoShowWMO.IsChecked = ModelEditorService.Instance.IsShow(E_WMO_EDIT_PART.EEP_WMO);
            menuWmoShowBoundingBox.IsChecked = ModelEditorService.Instance.IsShow(E_WMO_EDIT_PART.EEP_BOUNDINGBOX);
        }

        private void menuOption_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            menuOptionShowBaseInfo.IsChecked = ModelEditorService.Instance.IsShow(EditorShowOptions.DebugText);
            menuOptionShowGeosets.IsChecked = ModelEditorService.Instance.IsShow(EditorShowOptions.DebugGeosets);
            menuOptionShowPlane.IsChecked = ModelEditorService.Instance.IsShow(EditorShowOptions.Plane);
            menuOptionShowCoord.IsChecked = ModelEditorService.Instance.IsShow(EditorShowOptions.Coord);
        }

        private void menuModelWireframe_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            menuModelWireFrameNone.IsChecked = ModelEditorService.Instance.M2WireFrame == E_OVERRIDE_WIREFRAME.EOW_NONE;
            menuModelWireFrameOnly.IsChecked = ModelEditorService.Instance.M2WireFrame == E_OVERRIDE_WIREFRAME.EOW_WIREFRAME;
            menuModelWireFrameSolid.IsChecked = ModelEditorService.Instance.M2WireFrame == E_OVERRIDE_WIREFRAME.EOW_WIREFRAME_SOLID;
            menuModelWireFrameOneColor.IsChecked = ModelEditorService.Instance.M2WireFrame == E_OVERRIDE_WIREFRAME.EOW_WIREFRAME_ONECOLOR;
        }

        private void menuWmoWireframe_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            menuWmoWireFrameNone.IsChecked = ModelEditorService.Instance.WmoWireFrame == E_OVERRIDE_WIREFRAME.EOW_NONE;
            menuWmoWireFrameOnly.IsChecked = ModelEditorService.Instance.WmoWireFrame == E_OVERRIDE_WIREFRAME.EOW_WIREFRAME;
            menuWmoWireFrameSolid.IsChecked = ModelEditorService.Instance.WmoWireFrame == E_OVERRIDE_WIREFRAME.EOW_WIREFRAME_SOLID;
            menuWmoWireFrameOneColor.IsChecked = ModelEditorService.Instance.WmoWireFrame == E_OVERRIDE_WIREFRAME.EOW_WIREFRAME_ONECOLOR;
        }

        private void menuOptionBackMusic_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            menuOptionBackMusicNone.IsChecked = ModelEditorService.Instance.BackMusic == BackMusicFiles.None;
        }

        private void menuThemeMusic_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            menuOptionBackMusicMainTiltle.IsChecked = ModelEditorService.Instance.BackMusic == BackMusicFiles.MainTitle;
            menuOptionBackMusicWotLK.IsChecked = ModelEditorService.Instance.BackMusic == BackMusicFiles.WotLK;
            menuOptionBackMusicCataclysm.IsChecked = ModelEditorService.Instance.BackMusic == BackMusicFiles.Cataclysm;
            menuOptionBackMusicPandaria.IsChecked = ModelEditorService.Instance.BackMusic == BackMusicFiles.Pandaria;
            menuOptionBackMusicHighBorne.IsChecked = ModelEditorService.Instance.BackMusic == BackMusicFiles.HighBorne;
        }

        private void menuCityMusic_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            menuOptionBackMusicStormwind.IsChecked = ModelEditorService.Instance.BackMusic == BackMusicFiles.Stormwind;
            menuOptionBackMusicDarnassus.IsChecked = ModelEditorService.Instance.BackMusic == BackMusicFiles.Darnassus;
            menuOptionBackMusicIronforge.IsChecked = ModelEditorService.Instance.BackMusic == BackMusicFiles.Ironforge;
            menuOptionBackMusicOrgrimmar.IsChecked = ModelEditorService.Instance.BackMusic == BackMusicFiles.Orgrimmar;
            menuOptionBackMusicUndercity.IsChecked = ModelEditorService.Instance.BackMusic == BackMusicFiles.Undercity;
            menuOptionBackMusicThunderbluff.IsChecked = ModelEditorService.Instance.BackMusic == BackMusicFiles.Thunderbluff;
        }

        private void menuSettingCameraSpeed_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            menuSettingCameraSpeedLowest.IsChecked = EngineService.Instance.KeySpeed == 0.05f;
            menuSettingCameraSpeedLow.IsChecked = EngineService.Instance.KeySpeed == 0.1f;
            menuSettingCameraSpeedMedium.IsChecked = EngineService.Instance.KeySpeed == 0.3f;
            menuSettingCameraSpeedHigh.IsChecked = EngineService.Instance.KeySpeed == 0.8f;
            menuSettingCameraSpeedHighest.IsChecked = EngineService.Instance.KeySpeed == 2.0f;
        }

        private void menuSettingCameraModes_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            menuSettingCameraModesFPS.IsChecked = EngineService.Instance.CameraMode == CameraModes.FPS;
            menuSettingCameraModesMaya.IsChecked = EngineService.Instance.CameraMode == CameraModes.Maya;
        }

        private void menuLanguages_SubmenuOpend(object sender, RoutedEventArgs e)
        {
            App app = Application.Current as App;
            menuLanguagesChinese.IsChecked = app.Language == Languages.Chinese;
            menuLanguagesEnglish.IsChecked = app.Language == Languages.English;
        }

        private void menuModelScale_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            M2SceneNode node = ModelSceneService.Instance.MainM2SceneNode;
            if (node != null)
            {
                matrix4 mat = new matrix4(true);
                node.GetRelativeTransformation(out mat);
                m2SliderScale.Value = mat.Scale.X;
            }
        }

        private void menuModelOpacity_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            M2SceneNode node = ModelSceneService.Instance.MainM2SceneNode;
            if (node != null)
            {
                m2SliderOpacity.Value = node.ModelAlpha;
            }
        }

        private void M2SliderScale_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            M2SceneNode node = ModelSceneService.Instance.MainM2SceneNode;
            if (node != null)
            {
                float scale = (float)e.NewValue;
                matrix4 mat = new matrix4(true);
                node.GetRelativeTransformation(out mat);

                matrix4 newMat = new matrix4(true);
                newMat.RotationRadians = mat.RotationRadians;
                newMat.Scale = new vector3df(scale, scale, scale);
                newMat.Translation = mat.Translation;
                node.SetRelativeTransformation(ref newMat);
                node.Update(true);
            }
        }

        private void M2SliderOpacity_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            M2SceneNode node = ModelSceneService.Instance.MainM2SceneNode;
            if (node != null)
            {
                node.ModelAlpha = (float)e.NewValue;
            }
        }

        private void M2ScaleDefault_Click(object sender, RoutedEventArgs e)
        {
            M2SceneNode node = ModelSceneService.Instance.MainM2SceneNode;
            if (node != null)
            {
                float scale = 1.0f;
                matrix4 mat = new matrix4(true);
                node.GetRelativeTransformation(out mat);

                matrix4 newMat = new matrix4(true);
                newMat.RotationRadians = mat.RotationRadians;
                newMat.Scale = new vector3df(scale, scale, scale);
                newMat.Translation = mat.Translation;
                node.SetRelativeTransformation(ref newMat);
                node.Update(true);
            }
        }

        private void M2OpacityDefault_Click(object sender, RoutedEventArgs e)
        {
            M2SceneNode node = ModelSceneService.Instance.MainM2SceneNode;
            if (node != null)
            {
                node.ModelAlpha = 1.0f;
            }
        }

        private void menuWmoScale_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            WMOSceneNode node = ModelSceneService.Instance.MainWMOSceneNode;
            if (node != null)
            {
                matrix4 mat = new matrix4(true);
                node.GetRelativeTransformation(out mat);
                wmoSliderScale.Value = mat.Scale.X;
            }
        }

        void wmoSliderScale_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            WMOSceneNode node = ModelSceneService.Instance.MainWMOSceneNode;
            if (node != null)
            {
                float scale = (float)e.NewValue;
                matrix4 mat = new matrix4(true);
                node.GetRelativeTransformation(out mat);

                matrix4 newMat = new matrix4(true);
                newMat.RotationRadians = mat.RotationRadians;
                newMat.Scale = new vector3df(scale, scale, scale);
                newMat.Translation = mat.Translation;
                node.SetRelativeTransformation(ref newMat);
                node.Update(true);
            }
        }

        private void WmoScaleDefault_Click(object sender, RoutedEventArgs e)
        {
            WMOSceneNode node = ModelSceneService.Instance.MainWMOSceneNode;
            if (node != null)
            {
                float scale = 3.0f;
                matrix4 mat = new matrix4(true);
                node.GetRelativeTransformation(out mat);

                matrix4 newMat = new matrix4(true);
                newMat.RotationRadians = mat.RotationRadians;
                newMat.Scale = new vector3df(scale, scale, scale);
                newMat.Translation = mat.Translation;
                node.SetRelativeTransformation(ref newMat);
                node.Update(true);
            }
        }

        void wmoSliderSpecularStrength_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            Engine.Instance.SceneEnvironment.SpecularStrength = (float)e.NewValue;
        }

        private void menuWmoSpecularStrength_SubmenuOpened(object sender, RoutedEventArgs e)
        {
            wmoSliderSpecularStrength.Value = Engine.Instance.SceneEnvironment.SpecularStrength;
        }

        private void WmoSpecularStrengthDefault_Click(object sender, RoutedEventArgs e)
        {
            Engine.Instance.SceneEnvironment.SpecularStrength = 0.5f;
        }



    }
}
