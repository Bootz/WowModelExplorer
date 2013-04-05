using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Input;
using WowModelExplorer.Controls;
using System.Threading;
using System.Windows.Threading;
using WowModelExplorer.Controls.Splash;
using WowModelExplorer.Services;
using AvalonDock;
using mywowNet;
using WowModelExplorer.Commands;
using WowModelExplorer.Properties;

namespace WowModelExplorer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly DispatcherTimer timer;
        private WindowHost windowhost;
        private bool isKeyFocus = false;
        private M2GeosetsWindow _geosetsWindow = null;
        private WMOGroupsWindow _groupsWindow = null;
        private M2EquipmentsWindow _equipmentsWindow = null;

        public M2GeosetsWindow GeosetsWindow { get { return _geosetsWindow; } }
        public WMOGroupsWindow GroupsWindow { get { return _groupsWindow; } }
        public M2EquipmentsWindow EquipmentsWindow { get { return _equipmentsWindow; } }

        public MainWindow()
        {
            InitializeComponent();

            Loaded += new RoutedEventHandler(MainWindow_Loaded);
            Closing += new CancelEventHandler(MainWindow_Closing);
            StateChanged += new EventHandler(MainWindow_StateChanged);
            LostKeyboardFocus += delegate { isKeyFocus = false; };

            timer = new DispatcherTimer(DispatcherPriority.ApplicationIdle);
            timer.Interval = new System.TimeSpan(0, 0, 0, 0, 1);
            timer.Tick += new EventHandler(timer_Tick);
        }

        public bool IsKeyFocus { get { return isKeyFocus; } }

        public bool IsMaximized
        {
            get { return WindowState == WindowState.Maximized; }
            set
            {
                if (value)
                {
                    WindowState = WindowState.Maximized;
                }
                else if (WindowState == WindowState.Maximized)
                {
                    WindowState = WindowState.Normal;
                }
            }
        }

        private void InitCommandBindings()
        {
            CommandBindings.AddRange(ShellService.Instance.FileCommands.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.AnimationCommands.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.ViewCommands.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.ModelOperationCommands.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.ModelEditViewCommands.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.WmoOperationCommands.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.WmoEditViewCommands.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.OptionCommands.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.SettingCommands.CommandBindings);

            CommandBindings.AddRange(ShellService.Instance.LanguageCommands.CommandBindings);
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            this.Loaded -= MainWindow_Loaded;

            SplashWindow _splash = new SplashWindow();
            _splash.Show();
            this.IsEnabled = false;

            MessageListener.Instance.StartWork(GetStageText(0), new DispatcherOperationCallback(InitStage0));
            Thread.Sleep(1);

            MessageListener.Instance.StartWork(GetStageText(1), new DispatcherOperationCallback(InitStage1));
            Thread.Sleep(1);

            MessageListener.Instance.StartWork(GetStageText(2), new DispatcherOperationCallback(InitStage2));
            Thread.Sleep(1);

            this.IsEnabled = true;
            _splash.Close();
        }

        private string GetStageText(int index)
        {
            switch (index)
            {
                case 0:
                    return Application.Current.FindResource("stage1") as string;
                case 1:
                    return Application.Current.FindResource("stage2") as string;
                case 2:
                    return Application.Current.FindResource("stage3") as string;
            }
           return "";
        }

        private object InitStage0(object frame)
        {
            IntPtr hwnd = EngineService.Instance.InitilalizeEngine();
            windowhost = new WindowHost(hwnd);

            ModelSceneService.Instance.Initialize();

            windowhost.WmResize += new ResizeEventHandler(windowHost_WmResize);
            windowhost.WmMouse += new MouseMessageHandler(windowHost_WmMouse);

            ((DispatcherFrame)frame).Continue = false;
            return null;
        }

        private object InitStage1(object frame)
        {
            EngineService.Instance.RetrieveWowData();

            ((DispatcherFrame)frame).Continue = false;
            return null;
        }

        private object InitStage2(object frame)
        {
            InitCommandBindings();

            _characterContent.Initialize();
            _npcContent.Initialize();
            _spellVisualEffectContent.Initialize();
            _mapModelContent.Initialize();

            _clothesContent.Initialize();
            _weaponContent.Initialize();
            _setContent.Initialize();

            _propertyContent.Initialize();
            _animationContent.Initialize();
            _m2StateContent.Initialize();

            _propertyContent.Hide();

            //model mode
            if (windowhost.HWnd != IntPtr.Zero)
            {
                _controlHostElement.Child = windowhost;
            }

            _leftDockablePane.SetValue(ResizingPanel.ResizeWidthProperty, new GridLength(180));
            _right2DockablePane.SetValue(ResizingPanel.ResizeWidthProperty, new GridLength(180));
            _rightDockablePane.SetValue(ResizingPanel.ResizeWidthProperty, new GridLength(180));
            _bottomPanel.SetValue(ResizingPanel.ResizeHeightProperty, new GridLength(200));
            _bottomDockablePane.SetValue(ResizingPanel.ResizeWidthProperty, new GridLength(1.0f, GridUnitType.Star));
            _bottom2DockablePane.SetValue(ResizingPanel.ResizeWidthProperty, new GridLength(0.2f, GridUnitType.Star));

            //dialogs
            _geosetsWindow = new M2GeosetsWindow();
            _geosetsWindow.Owner = this;
            _groupsWindow = new WMOGroupsWindow();
            _groupsWindow.Owner = this;
            _equipmentsWindow = new M2EquipmentsWindow();
            _equipmentsWindow.Owner = this;

            this.Activate();
            _characterContent.Activate();

            timer.Start();

            ((DispatcherFrame)frame).Continue = false;
            return null;
        }


        private void MainWindow_Closing(object sender, CancelEventArgs e)
        {
            if (!e.Cancel)
            {
                timer.Stop();
            }

            ModelSceneService.Instance.Shutdown();
            EngineService.Instance.Shutdown();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            //update scene
            EngineService.Instance.Tick();

            //update UI
            if (_animationContent.State != DockableContentState.Hidden)
                Dispatcher.CurrentDispatcher.BeginInvoke(DispatcherPriority.Render, new DispatcherOperationCallback(_tick_UI), null);
        }

        private object _tick_UI(object param)
        {
            _animationContent.UpdateAnimationProgress(ModelEditorService.Instance.StateMode);
            return null;
        }

        private void windowHost_WmResize(object sender, uint w, uint h)
        {
            if (w == 0 || h == 0)
                timer.IsEnabled = false;
            else
            {
                timer.IsEnabled = true;

                EngineService.Instance.OnResize(w, h);
            }
        }

        private void windowHost_WmMouse(object sender, MouseMessage msg, int x, int y)
        {
            if (msg == MouseMessage.MouseLButtonDown || 
                msg == MouseMessage.MouseLButtonUp ||
                msg == MouseMessage.MouseRButtonDown ||
                msg == MouseMessage.MouseRButtonUp)
            {
                if (!isKeyFocus)
                {
                    Keyboard.Focus(this);
                    isKeyFocus = true;
                }
            }

            EngineService.Instance.OnMouseMessage(msg, x, y);
        }

        private void MainWindow_StateChanged(object sender, EventArgs e)
        {
            timer.IsEnabled = WindowState != WindowState.Minimized;   
        }
    }
}
