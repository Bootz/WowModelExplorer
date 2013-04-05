using System;
using mywowNet;
using System.Diagnostics;
using WowModelExplorer.Controls;
using WowModelExplorer.Utility;

namespace WowModelExplorer.Services
{
    public class EngineService
    {
        public EngineService(DriverType driverType)
        {
            this.driverType = driverType;
            if (instance == null)
            {
                instance = this;
            }
        }

        private static EngineService instance = null;
        public static EngineService Instance { get { return instance; } }

        DriverType driverType;
        public DriverType DriverType
        {
            get { return driverType; }
            set { driverType = value; }
        }

        CameraModes cameraMode = CameraModes.Maya;
        public CameraModes CameraMode
        {
            get { return cameraMode; }
            set { cameraMode = value; }
        }
        float keySpeed = 0.3f;
        public float KeySpeed
        {
            get { return keySpeed; }
            set { keySpeed = value;}
        }

        public IntPtr InitilalizeEngine()
        {
            new Engine();

            if (!Engine.Instance.IsAboveVista && DriverType == DriverType.Direct3D11)
            {
                driverType = DriverType.Direct3D9;
            }

            IntPtr handle = Engine.Instance.CreateDefaultWindow();
            Debug.Assert(handle != IntPtr.Zero);

            bool success = Engine.Instance.Init(handle, DriverType, 0, false, false, 1, true);
            Debug.Assert(success);
            if (!success && DriverType == DriverType.Direct3D11)
            {
                driverType = DriverType.Direct3D9;
                success = Engine.Instance.Init(handle, DriverType, 0, false, false, 1, true);
                Debug.Assert(success);
            }

            return handle;
        }

        public void RetrieveWowData()
        {
            Engine.Instance.WowDatabase.BuildItems();
            Engine.Instance.WowDatabase.BuildNpcs("npcs.csv");
            Engine.Instance.WowDatabase.BuildStartOutfit();
        }

        public void Tick()
        {
            Camera cam = Engine.Instance.SceneManager.ActiveCamera;
            if (ShellService.Instance.MainWindow.IsKeyFocus && cam != null)
            {
                Camera.SKeyControl keycontrol = new Camera.SKeyControl()
                {
                    front = NativeMethods.IsKeyPressed('W'),
                    back = NativeMethods.IsKeyPressed('S'),
                    left = NativeMethods.IsKeyPressed('A'),
                    right = NativeMethods.IsKeyPressed('D'),
                    up = NativeMethods.IsKeyPressed(NativeConstants.VK_SPACE),
                    down = false
                };
                cam.OnKeyMove(KeySpeed, keycontrol);
            }

            Engine.Instance.SceneManager.DrawAll();
        }

        public void Shutdown()
        {
            Engine.Instance.Dispose();
        }

        public void OnResize(uint width, uint height)
        {
            Engine.Instance.Driver.SetDisplayMode(width, height);

            Camera cam = Engine.Instance.SceneManager.ActiveCamera;
            if (cam != null)
                cam.RecalculateAll(); 
        }

        float lastX = 0;
        float lastY = 0;
        bool LCapture = false;
        bool RCapture = false;
        public void OnMouseMessage(MouseMessage message, int x, int y)
        {
            Camera cam = Engine.Instance.SceneManager.ActiveCamera;
            if (cam == null)
                return;

            switch (message)
            {
                case MouseMessage.MouseLButtonDown:
                    if (!RCapture)
                    {
                        lastX = x;
                        lastY = y;
                        LCapture = true;
                    }
                    break;
                case MouseMessage.MouseLButtonUp:
                    if (LCapture)
                    {
                        lastX = lastY = 0;
                        LCapture = false;
                    }
                    RCapture = false;
                    break;
                case MouseMessage.MouseRButtonDown:
                    if (!LCapture)
                    {
                        lastX = x;
                        lastY = y;
                        RCapture = true;
                    }
                    break;
                case MouseMessage.MouseRButtonUp:
                    if (RCapture)
                    {
                        lastX = lastY = 0;
                        RCapture = false;
                    }
                    LCapture = false;
                    break;
                case MouseMessage.MouseMove:
                    {
                        const float blend = 0.8f;				//旋转柔和

                        if (LCapture || RCapture)
                        {
                            float deltaX = x - lastX;
                            float deltaY = y - lastY;

                            bool xChange = Math.Abs(deltaX) > 0.5f;
                            bool yChange = Math.Abs(deltaY) > 0.5f;

                            if (xChange || yChange)
                            {
                                float blendDeltaX = xChange ? deltaX * blend : deltaX;
                                float blendDeltaY = yChange ? deltaY * blend : deltaY;

                                switch (CameraMode)
                                {
                                    case CameraModes.Maya:
                                        {
                                            if (LCapture)
                                                cam.PitchYawMaya(blendDeltaY * 0.3f, blendDeltaX * 0.3f);
                                            else
                                                cam.MoveOffsetMaya(blendDeltaX * 0.02f, blendDeltaY * 0.02f);
                                        }
                                        break;
                                    case CameraModes.FPS:
                                        {
                                            cam.PitchYawFPS(blendDeltaY * 0.2f, blendDeltaX * 0.2f);
                                        }
                                        break;
                                }

                                lastX += blendDeltaX;
                                lastY += blendDeltaY;
                            }
                        }
                    }
                    break;
            }
        }

    }
}
