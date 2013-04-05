using System;
using System.Collections;
using System.Collections.Generic;

namespace mywowNet
{
    public partial class SceneEnvironment : INative
    {
        public SceneEnvironment(IntPtr raw) : base(raw) { }

        public float SpecularStrength
        {
            get 
            { 
                return SceneEnvironment_getSpecularStrength();
            }
            set
            {
                SceneEnvironment_setSpecularStrength(value);
            }
        }
    }
}
