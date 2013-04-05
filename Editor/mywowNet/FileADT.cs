using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;

namespace mywowNet
{
    public partial class FileADT : INative
    {
        public FileADT(IntPtr raw) : base(raw) { }

        public uint M2Count
        {
            get { return FileADT_getM2Count(pointer); }
        }

        public uint WMOCount
        {
            get { return FileADT_getWMOCount(pointer); }
        }

        public string GetM2FileName(uint index, bool shortname)
        {
            StringBuilder path = new StringBuilder(256);
            bool success = FileADT_getM2FileName(pointer, index, path, (uint)path.Capacity, shortname);
            if (success)
            {
                return path.ToString(0, path.Length);
            }
            else
            {
                return "";
            }
        }

        public string GetWMOFileName(uint index, bool shortname)
        {
            StringBuilder path = new StringBuilder(256);
            bool success = FileADT_getWMOFileName(pointer, index, path, (uint)path.Capacity, shortname);
            if (success)
            {
                return path.ToString(0, path.Length);
            }
            else
            {
                return "";
            }
        }
    }
}
