using System;
using System.Runtime.InteropServices;

namespace mywowNet
{
    public partial class SceneEnvironment
    {
        const string DllName = @"mywow_dll.dll";

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneEnvironment_getSpecularStrength")]
        public static extern float SceneEnvironment_getSpecularStrength();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "SceneEnvironment_setSpecularStrength")]
        public static extern void SceneEnvironment_setSpecularStrength(float specularStrength);
    }
}
