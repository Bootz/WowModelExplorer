using System;
using System.Runtime.InteropServices;

namespace mywowNet
{
    public partial class Engine : IDisposable
    {
        private static Engine instance = null;

        public Engine()
        {
            if (instance == null)
            {
                instance = this;
                engine_create();
            }
        }

        ~Engine()
        {
            Dispose();
        }

        public static Engine Instance
        {
            get { return instance; }
        }

        bool _disposed = false;
        public void Dispose()
        {
            if (!_disposed)
            {
                engine_destroy();
                _disposed = true;
            }
        }

        public IntPtr CreateDefaultWindow()
        {
            return engine_createWindow();
        }

        public bool Init(IntPtr hwnd, DriverType driverType, uint adapter, bool fullscreen, bool vsync, uint antialias, bool multithread)
        {
            bool sucesss = engine_initDriver(hwnd, driverType, adapter, fullscreen, vsync, antialias, multithread);
            if (!sucesss)
                return false;

            engine_initSceneManager();

            _driver = new Driver(engine_getDriver());
            _sceneManger = new SceneManager(engine_getSceneManager());
            _wowDatabase = new WowDatabase(engine_getWowDatabase());
            _manualMeshServices = new ManualMeshServices(engine_getManualMeshServices());
            _audioPlayer = new AudioPlayer(engine_getAudioPlayer());
            _resourceLoader = new ResourceLoader(engine_getResourceLoader());
            _sceneEnvironment = new SceneEnvironment(engine_getSceneEnvironment());

            return true;
        }

        public SVideoSetting VideoSetting
        {
            set { engine_setVideoSetting(value); }
            get
            {
                SVideoSetting v = new SVideoSetting();
                engine_getVideoSetting(out v);
                return v;
            }
        }

        public SAdvancedSetting AdvancedSetting
        {
            set { engine_setAdvancedSetting(value); }
            get
            {
                SAdvancedSetting v = new SAdvancedSetting();
                engine_getAdvancedSetting(out v);
                return v;
            }
        }

        Driver _driver;
        SceneManager _sceneManger;
        WowDatabase _wowDatabase;
        ManualMeshServices _manualMeshServices;
        AudioPlayer _audioPlayer;
        ResourceLoader _resourceLoader;
        SceneEnvironment _sceneEnvironment;

        public Driver Driver
        {
            get { return _driver;  }
        }

        public SceneManager SceneManager
        {
            get { return _sceneManger;  }
        }

        public WowDatabase WowDatabase
        {
            get { return _wowDatabase;  }
        }

        public ManualMeshServices ManualMeshServices
        {
            get { return _manualMeshServices;  }
        }

        public AudioPlayer AudioPlayer
        {
            get { return _audioPlayer; }
        }

        public ResourceLoader ResourceLoader
        {
            get { return _resourceLoader; }
        }

        public SceneEnvironment SceneEnvironment
        {
            get { return _sceneEnvironment; }
        }

        public bool IsAboveVista
        {
            get { return engine_isAboveVista(); }
        }
    }
}
