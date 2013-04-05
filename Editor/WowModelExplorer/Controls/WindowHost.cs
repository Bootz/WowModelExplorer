using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Runtime.InteropServices;
using WowModelExplorer.Utility;

namespace WowModelExplorer.Controls
{
    public enum MouseMessage
    {
        MouseNone,          //invalid
        MouseLButtonDown,
        MouseLButtonUp,
        MouseRButtonDown,
        MouseRButtonUp,
        MouseMove
    }

    public delegate void MouseMessageHandler(object sender, MouseMessage message, int x, int y);
    public delegate void ResizeEventHandler(object sender, uint w, uint h);

    public class WindowHost : HwndHost
    {
        private IntPtr oldParent;
        private int oldStyle;
        private IntPtr hwnd;

        public WindowHost(IntPtr hwnd)
        {
            this.hwnd = hwnd;
        }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            oldParent = NativeMethods.GetParent(HWnd);
            oldStyle = NativeMethods.GetWindowLongA(HWnd, NativeConstants.GWL_STYLE);

            NativeMethods.SetParent(HWnd, hwndParent.Handle);
            NativeMethods.SetWindowLongA(HWnd, NativeConstants.GWL_STYLE, NativeConstants.WS_CHILD | NativeConstants.WS_VISIBLE);
            return new HandleRef(this, HWnd);
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            NativeMethods.DestroyWindow(hwnd.Handle);
        }

        public event MouseMessageHandler WmMouse;
        public event ResizeEventHandler WmResize;

        protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            if (hwnd == HWnd)
            {
                if (msg == NativeConstants.WM_SIZE)
                {
                    int param = lParam.ToInt32();
                    uint w = (uint)(param & 0x0000ffff);
                    uint h = (uint)((param & 0xffff0000) >> 16);

                    if (WmResize != null)
                        WmResize.Invoke(this, w, h);
                }
                else
                    if (msg == NativeConstants.WM_LBUTTONDOWN ||
                        msg == NativeConstants.WM_RBUTTONDOWN ||
                         msg == NativeConstants.WM_LBUTTONUP ||
                         msg == NativeConstants.WM_RBUTTONUP ||
                         msg == NativeConstants.WM_MOUSEMOVE)
                    {
                        int param = lParam.ToInt32();
                        int x = (param & 0x0000ffff);
                        int y = (int)((param & 0xffff0000) >> 16);

                        if (WmMouse != null)
                        {
                            WmMouse.Invoke(this, getMouseMessageType(msg), x, y);
                        }
                    }
            }

            return base.WndProc(hwnd, msg, wParam, lParam, ref handled);
        }

        MouseMessage getMouseMessageType(int msg)
        {
            switch (msg)
            {
                case NativeConstants.WM_LBUTTONDOWN:
                    return MouseMessage.MouseLButtonDown;
                case NativeConstants.WM_RBUTTONDOWN:
                    return MouseMessage.MouseRButtonDown;
                case NativeConstants.WM_LBUTTONUP:
                    return MouseMessage.MouseLButtonUp;
                case NativeConstants.WM_RBUTTONUP:
                    return MouseMessage.MouseRButtonUp;
                case NativeConstants.WM_MOUSEMOVE:
                    return MouseMessage.MouseMove;
                default:
                    return MouseMessage.MouseNone;
            }
        }

        public IntPtr HWnd { get { return hwnd; } }

    }
}
