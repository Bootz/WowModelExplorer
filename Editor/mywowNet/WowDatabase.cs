using System;
using System.Text;
using System.Runtime.InteropServices;

namespace mywowNet
{
    public partial class WowDatabase : INative
    {
        public WowDatabase(IntPtr raw) : base(raw) { }

        public uint ItemCount
        {
            get { return WowDatabase_getItemCount(); }
        }

        public uint NpcCount
        {
            get { return WowDatabase_getNpcCount(); }
        }

        public uint SetCount
        {
            get { return WowDatabase_getSetCount(); }
        }

        public uint MapCount
        {
            get { return WowDatabase_getMapCount(); }
        }

        public uint SpellVisualEffectCount
        {
            get { return WowDatabase_getSpellVisualEffectCount(); }
        }

        public uint GetStartOutfitCount(uint raceid, bool female)
        {
            return WowDatabase_getStartOutfitCount(raceid, female);
        }

        public SItem? GetItem(uint index)
        {
            SItem v = new SItem();
            if (WowDatabase_getItem(index, out v))
                return v;
            return null;
        }

        public SItem? GetItemById(int id)
        {
            SItem v = new SItem();
            if (WowDatabase_getItemById(id, out v))
                return v;
            return null;
        }

        public SNpc? GetNpc(uint index)
        {
            SNpc v = new SNpc();
            if(WowDatabase_getNpc(index, out v))
                return v;
            return null;
        }

        public SEntry? GetStartOutfit(uint raceid, bool female, uint index)
        {
            SEntry v = new SEntry();
            if (WowDatabase_getStartOutfit(raceid, female, index, out v))
                return v;
            return null;
        }

        public SEntry? GetSet(uint index)
        {
            SEntry v = new SEntry();
            if (WowDatabase_getSet(index, out v))
                return v;
            return null;
        }

        public SMap? GetMap(uint index)
        {
            SMap v = new SMap();
            if (WowDatabase_getMap(index, out v))
                return v;
            return null;
        }

        public int? GetSpellVisualEffectId(uint index)
        {
            int v;
            if (WowDatabase_getSpellVisualEffectId(index, out v))
                return v;
            return null;
        }

        public SCharFeature GetMaxCharFeature(uint raceid, bool female)
        {
            SCharFeature v = new SCharFeature();
            WowDatabase_getMaxCharFeature(raceid, female, out v);
            return v;
        }

        public uint? GetRaceId(string racename)
        {
            uint id;
            if (WowDatabase_getRaceId(racename, out id))
                return id;
            return null;
        }

        public void BuildItems()
        {
            WowDatabase_buildItems();
        }

        public bool BuildNpcs(string filename)
        {
            return WowDatabase_buildNpcs(filename);
        }

        public void BuildStartOutfit()
        {
            WowDatabase_buildStartOutfitClass();
        }

        public void BuildMaps()
        {
            WowDatabase_buildMaps();
        }

        public string GetCharacterPath(string race, bool female)
        {
            StringBuilder path = new StringBuilder(256);
            bool success = WowDatabase_getCharacterPath(race, female, path, (uint)path.Capacity);
            if (success)
            {
                return path.ToString(0, path.Length);
            }
            else
            {
                return "";
            }
        }

        public string GetNpcPath(int npcid)
        {
            StringBuilder path = new StringBuilder(256);
            bool success = WowDatabase_getNpcPath(npcid, path, (uint)path.Capacity);
            if (success)
            {
                return path.ToString(0, path.Length);
            }
            else
            {
                return "";
            }
        }

        public string GetItemVisualPath(int visualId)
        {
            StringBuilder path = new StringBuilder(256);
            bool success = WowDatabase_getItemVisualPath(visualId, path, (uint)path.Capacity);
            if (success)
            {
                return path.ToString(0, path.Length);
            }
            else
            {
                return "";
            }
        }

        public string GetSpellVisualEffectName(int visualId)
        {
            StringBuilder path = new StringBuilder(128);
            bool success = WowDatabase_getSpellVisualEffectName(visualId, path, (uint)path.Capacity);
            if (success)
            {
                return path.ToString(0, path.Length);
            }
            else
            {
                return "";
            }
        }

        public string GetSpellVisualEffectPath(int visualId)
        {
            StringBuilder path = new StringBuilder(256);
            bool success = WowDatabase_getSpellVisualEffectPath(visualId, path, (uint)path.Capacity);
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
