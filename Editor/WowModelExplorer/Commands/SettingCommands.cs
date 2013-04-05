using System;
using System.Collections.Generic;
using System.Windows.Input;
using AvalonDock;
using mywowNet;
using WowModelExplorer;
using WowModelExplorer.Services;
using WowModelExplorer.Controls.Settings;

namespace WowModelExplorer.Commands
{
    public class SettingCommands
    {
        private static RoutedUICommand engineSettingCommand = new RoutedUICommand();
        private static RoutedUICommand cameraPositionCommand = new RoutedUICommand();
        private static RoutedUICommand cameraSpeedCommand = new RoutedUICommand();
        private static RoutedUICommand cameraModeCommand = new RoutedUICommand();

        public static RoutedUICommand EngineSetting { get { return engineSettingCommand; } }
        public static RoutedUICommand CameraPosition { get { return cameraPositionCommand; } }
        public static RoutedUICommand CameraSpeed { get { return cameraSpeedCommand; } }
        public static RoutedUICommand CameraMode { get { return cameraModeCommand; } }

        private readonly CommandBindingCollection commandBindings = new CommandBindingCollection();

        public CommandBindingCollection CommandBindings { get { return commandBindings; } }

        public SettingCommands()
        {
            commandBindings.Add(new CommandBinding(engineSettingCommand, settingExecuted));
            commandBindings.Add(new CommandBinding(cameraPositionCommand, cameraPositionExecuted));
            commandBindings.Add(new CommandBinding(cameraSpeedCommand, cameraSpeedExecuted));
            commandBindings.Add(new CommandBinding(cameraModeCommand, cameraModeExecuted));
        }

        private void settingExecuted(object sender, ExecutedRoutedEventArgs e)
        {
            EngineSettings dialog = new EngineSettings();
            dialog.FillData();
            dialog.ShowDialog();
            dialog.Owner = ShellService.Instance.MainWindow;
        }

        private void cameraPositionExecuted(object sender, ExecutedRoutedEventArgs e)
        {
            EditorSetOptions? option = e.Parameter as EditorSetOptions?;
            if (!option.HasValue)
                return;

            switch(option.Value)
            {
                case EditorSetOptions.Default:
                    {
                        Camera cam = Engine.Instance.SceneManager.ActiveCamera;
                        if (cam != null)
                        {
                            cam.Position = new vector3df(0, 5, -10);
                            cam.Dir = new vector3df(0, -5, 10);
                            cam.Up = new vector3df(0, 1, 0);
                            cam.RecalculateAll();
                        }
                    }
                    
                    break;
                case EditorSetOptions.Set:
                    break;
            }
        }

        private void cameraSpeedExecuted(object sender, ExecutedRoutedEventArgs e)
        {
            NumSetOptions? option = e.Parameter as NumSetOptions?;
            if (!option.HasValue)
                return;

            switch(option.Value)
            {
                case NumSetOptions.Medium:
                    EngineService.Instance.KeySpeed = 0.3f;
                    break;
                case NumSetOptions.Low:
                    EngineService.Instance.KeySpeed = 0.1f;
                    break;
                case NumSetOptions.Lowest:
                    EngineService.Instance.KeySpeed = 0.05f;
                    break;
                case NumSetOptions.High:
                    EngineService.Instance.KeySpeed = 0.8f;
                    break;
                case NumSetOptions.Highest:
                    EngineService.Instance.KeySpeed = 2.0f;
                    break;
            }
            
        }

        private void cameraModeExecuted(object sender, ExecutedRoutedEventArgs e)
        {
            CameraModes? mode = e.Parameter as CameraModes?;
            if (!mode.HasValue)
                return;

            EngineService.Instance.CameraMode = mode.Value;
        }

    }
}