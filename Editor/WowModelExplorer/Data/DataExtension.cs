using System;
using System.Linq;
using mywowNet;
using System.Windows;

namespace WowModelExplorer.Data
{
    public static class DataExtension
    {
        public static void GetAllianceRaceInfos(this RaceInfoCollection raceInfos, Languages language)
        {
            raceInfos.Clear();

            switch(language)
            {
                case Languages.Chinese:
                    {
                        raceInfos.Add(CreateRaceInfo("人类", "human"));
                        raceInfos.Add(CreateRaceInfo("暗夜精灵", "nightelf"));
                        raceInfos.Add(CreateRaceInfo("矮人", "dwarf"));
                        raceInfos.Add(CreateRaceInfo("侏儒", "gnome"));
                        raceInfos.Add(CreateRaceInfo("德莱尼", "draenei"));
                        raceInfos.Add(CreateRaceInfo("狼人", "worgen"));
                        raceInfos.Add(CreateRaceInfo("熊猫人", "pandaren"));
                    }
                    break;
                default:        //english
                    {
                        raceInfos.Add(CreateRaceInfo("Human", "human"));
                        raceInfos.Add(CreateRaceInfo("NightElf", "nightelf"));
                        raceInfos.Add(CreateRaceInfo("Dwarf", "dwarf"));
                        raceInfos.Add(CreateRaceInfo("Gnome", "gnome"));
                        raceInfos.Add(CreateRaceInfo("Draenei", "draenei"));
                        raceInfos.Add(CreateRaceInfo("Worgen", "worgen"));
                        raceInfos.Add(CreateRaceInfo("Pandaren", "pandaren"));
                    }
                    break;
            }
        }

        public static void GetHordeRaceInfos(this RaceInfoCollection raceInfos, Languages language)
        {
            raceInfos.Clear();

            switch (language)
            {
                case Languages.Chinese:
                    {
                        raceInfos.Add(CreateRaceInfo("兽人", "orc"));
                        raceInfos.Add(CreateRaceInfo("牛头人", "tauren"));
                        raceInfos.Add(CreateRaceInfo("亡灵", "scourge"));
                        raceInfos.Add(CreateRaceInfo("巨魔", "troll"));
                        raceInfos.Add(CreateRaceInfo("血精灵", "bloodelf"));
                        raceInfos.Add(CreateRaceInfo("地精", "goblin"));
                        raceInfos.Add(CreateRaceInfo("熊猫人", "pandaren"));
                    }
                    break;
                default:
                    {
                        raceInfos.Add(CreateRaceInfo("Orc", "orc"));
                        raceInfos.Add(CreateRaceInfo("Tauren", "tauren"));
                        raceInfos.Add(CreateRaceInfo("Scourge", "scourge"));
                        raceInfos.Add(CreateRaceInfo("Troll", "troll"));
                        raceInfos.Add(CreateRaceInfo("BloodElf", "bloodelf"));
                        raceInfos.Add(CreateRaceInfo("Goblin", "goblin"));
                        raceInfos.Add(CreateRaceInfo("Pandaren", "pandaren"));
                    }
                    break;
            }
        }

        private static RaceInfo CreateRaceInfo(string name, string shortname)
        {
            uint id = Engine.Instance.WowDatabase.GetRaceId(shortname).Value;
            return new RaceInfo() { Name = name, ShortName = shortname, RaceId = id };
        }

        public static void GetStartOutfitClasses(this StartOutfitClassCollection startOutfits, uint raceId, bool female)
        {
            startOutfits.Clear();
            uint count = Engine.Instance.WowDatabase.GetStartOutfitCount(raceId, female);
            for (uint i = 0; i < count; ++i)
            {
                SEntry? entry = Engine.Instance.WowDatabase.GetStartOutfit(raceId, female, i);
                if (entry.HasValue)
                {
                    startOutfits.Add(new StartOutfitClass() { Name=entry.Value.name, Id=entry.Value.id });
                }
            }
        }

        public static void FromSCharFeature(this CharFeature feature, SCharFeature schar)
        {
            feature.SkinColor = schar.skinColor;
            feature.FaceType = schar.faceType;
            feature.FacialHair = schar.facialHair;
            feature.HairColor = schar.hairColor;
            feature.HairStyle = schar.hairStyle;
        }

        public static void GetMaxCharFeature(this CharFeature feature, uint raceId, bool female)
        {
            SCharFeature schar = Engine.Instance.WowDatabase.GetMaxCharFeature(raceId, female);

            feature.FromSCharFeature(schar);
        }

        public static void GetAllNpcs(this NpcCollection npcs)
        {
            WowDatabase _wowDatabase = Engine.Instance.WowDatabase;

            uint npcCount = _wowDatabase.NpcCount;
            npcs.Clear();

            for (uint i = 0; i < npcCount; ++i)
            {
                SNpc? r = _wowDatabase.GetNpc(i);
                if (r != null && r.Value.modelId != -1)
                {
                    npcs.Add(new Npc() { Name = r.Value.name, Type = r.Value.type, ModelDisplayId = r.Value.modelDisplayId, ModelId = r.Value.modelId });
                }
            }
        }

        public static void GetItemsByType(this ItemCollection items, E_ITEM_TYPE type)
        {
            WowDatabase _wowDatabase = Engine.Instance.WowDatabase;
            uint itemCount = _wowDatabase.ItemCount;

            items.Clear();

            for (uint i = 0; i < itemCount; ++i)
            {
                SItem? r = _wowDatabase.GetItem(i);
                if (r != null)
                {
                    if (r.Value.type == (int)type)
                    {
                        if (r.Value.name.IndexOf("deprecated", StringComparison.CurrentCultureIgnoreCase) == -1)
                            items.Add(new Item() { Name = r.Value.name, Type = (E_ITEM_TYPE)r.Value.type, Id = r.Value.id, ModelId = r.Value.modelId, SubClassName = r.Value.subclassname });
                    }
                }
            }
        }

        public static void GetItemsBySlot(this ItemCollection items, E_CHAR_SLOTS slot)
        {
            WowDatabase _wowDatabase = Engine.Instance.WowDatabase;
            uint itemCount = _wowDatabase.ItemCount;

            items.Clear();

            for (uint i = 0; i < itemCount; ++i)
            {
                SItem? r = _wowDatabase.GetItem(i);
                if (r != null)
                {
                    if (r.Value.IsMatchSlot(slot) && (r.Value.name.IndexOf("deprecated", StringComparison.CurrentCultureIgnoreCase) == -1))
                        items.Add(new Item() { Name = r.Value.name, Type = (E_ITEM_TYPE)r.Value.type, Id = r.Value.id, ModelId = r.Value.modelId,  SubClassName = r.Value.subclassname });
                }
            }
        }

        public static void GetAllSets(this SetCollection sets)
        {
            WowDatabase wowDatabase = Engine.Instance.WowDatabase;

            uint setCount = wowDatabase.SetCount;
            sets.Clear();

            for (uint i = 0; i < setCount; ++i)
            {
                SEntry? r = wowDatabase.GetSet(i);
                if (r != null)
                    sets.Add(new Set() { Name = r.Value.name, Id = r.Value.id });
            }
        }

        public static void GetAllSpellVisualEffects(this SpellVisualEffectCollection spellVisualEffects)
        {
            WowDatabase wowDatabase = Engine.Instance.WowDatabase;

            uint visualCount = wowDatabase.SpellVisualEffectCount;
            spellVisualEffects.Clear();

            for (uint i = 0; i < visualCount; ++i)
            {
                int? id = wowDatabase.GetSpellVisualEffectId(i);
                if (id != null)
                {
                    string name = Engine.Instance.WowDatabase.GetSpellVisualEffectName(id.Value);
                    if (!name.Contains("zzOLD_"))
                        spellVisualEffects.Add(new SpellVisualEffect() { Id = id.Value, Name = name });
                }
            }
        }

        public static void GetAllMaps(this MapCollection maps, Languages language)
        {       
            WowDatabase _wowDatabase = Engine.Instance.WowDatabase;

            uint mapCount = _wowDatabase.MapCount;
            maps.Clear();

            for (uint i = 0; i < mapCount; ++i)
            {
                SMap? m = _wowDatabase.GetMap(i);
                if (m != null)
                {
                    if (m.Value.internalname.IndexOf("test", StringComparison.CurrentCultureIgnoreCase) != -1 ||
                        m.Value.internalname.IndexOf("transport", StringComparison.CurrentCultureIgnoreCase) != -1 ||
                        m.Value.internalname.IndexOf("QA_DVD", StringComparison.CurrentCultureIgnoreCase) != -1 ||
                        m.Value.internalname.IndexOf("development", StringComparison.CurrentCultureIgnoreCase) != -1)
                        continue;

                    maps.Add(new Map() { Id=m.Value.id, Name=m.Value.name, InternalName=m.Value.internalname, Type=GetMapTypeName(m.Value.type,language) });
                }
            }
        }

        public static string GetMapTypeName(int type, Languages language)
        {
            switch (language)
            {
                case Languages.Chinese:
                    {
                        switch(type)
                        {
                            case 1:
                                return "地下城";
                            case 2:
                                return "团队";
                            case 3:
                                return "PVP区域";
                            case 4:
                                return "竞技场";
                            default:
                                return "普通";
                        }
                    }
                default:
                    {
                        switch (type)
                        {
                            case 1:
                                return "Dungeon";
                            case 2:
                                return "Raid";
                            case 3:
                                return "PVPZone";
                            case 4:
                                return "Arena";
                            default:
                                return "Normal";
                        }
                    }
            }
        }

        public static void GetAllAdts(this AdtCollection adts, FileWDT wdt)
        {
            adts.Clear();
            for ( uint i = 0; i < wdt.TileCount; ++i )
            {
                uint row, col;
                if (!wdt.GetTile(i, out row, out col))
                    continue;
                string name = String.Format("{0},{1}", row, col);

                adts.Add(new Adt() { Name = name, Id = (int)i, Row = row, Col = col });
            }
        }

        public static string GetStateName(this M2State state, Languages language)
        {
            switch (language)
            {
                case Languages.Chinese:
                    {
                        switch(state.State)
                        {
                            case E_M2_STATES.EMS_STAND: return "站立";
                            case E_M2_STATES.EMS_JUMP: return "跳跃";
                            case E_M2_STATES.EMS_ROLL: return "翻滚";
                            case E_M2_STATES.EMS_KNEEL: return "下跪";
                            case E_M2_STATES.EMS_DANCE: return "跳舞";
                            case E_M2_STATES.EMS_FLYINGKICK: return "飞踢";
                            case E_M2_STATES.EMS_EMOTEREAD: return "阅读";
                            case E_M2_STATES.EMS_CRANE: return "鹤立";
                            case E_M2_STATES.EMS_SPINNINGKICK: return "旋风腿";
                            case E_M2_STATES.EMS_TORPEDO: return "龙卷风";
                            case E_M2_STATES.EMS_WALK: return "行走";
                            case E_M2_STATES.EMS_RUN: return "跑步";
                            case E_M2_STATES.EMS_SITGROUND: return "打坐";
                        }
                    }
                    break;
                default:
                    {
                        switch (state.State)
                        {
                            case E_M2_STATES.EMS_STAND: return "Stand";
                            case E_M2_STATES.EMS_JUMP: return "Jump";
                            case E_M2_STATES.EMS_ROLL: return "Roll";
                            case E_M2_STATES.EMS_KNEEL: return "Kneel";
                            case E_M2_STATES.EMS_DANCE: return "Dance";
                            case E_M2_STATES.EMS_FLYINGKICK: return "FlyingKick";
                            case E_M2_STATES.EMS_EMOTEREAD: return "Read";
                            case E_M2_STATES.EMS_CRANE: return "Crane";
                            case E_M2_STATES.EMS_SPINNINGKICK: return "SpinningKick";
                            case E_M2_STATES.EMS_TORPEDO: return "Torpedo";
                            case E_M2_STATES.EMS_WALK: return "Walk";
                            case E_M2_STATES.EMS_RUN: return "Run";
                            case E_M2_STATES.EMS_SITGROUND: return "SitGround";
                        }
                    }
                    break;
            }
            return "Unknown";
        }

        public static void GetAllSlotItems(this SlotItemCollection slotItems, M2SceneNode node)
        {
            slotItems.Clear();

            if (node.Type != M2Type.MT_CHARACTER || node.IsNpc)
                return;

            WowDatabase wowDatabase = Engine.Instance.WowDatabase;

            E_CHAR_SLOTS[] slots = 
            {
                E_CHAR_SLOTS.CS_HEAD,
                E_CHAR_SLOTS.CS_SHOULDER,
                E_CHAR_SLOTS.CS_SHIRT,
                E_CHAR_SLOTS.CS_CHEST,
                E_CHAR_SLOTS.CS_BELT,
                E_CHAR_SLOTS.CS_PANTS,
                E_CHAR_SLOTS.CS_BOOTS,
                E_CHAR_SLOTS.CS_BRACERS,
                E_CHAR_SLOTS.CS_GLOVES,
                E_CHAR_SLOTS.CS_CAPE,
                E_CHAR_SLOTS.CS_TABARD,
                E_CHAR_SLOTS.CS_HAND_LEFT,
                E_CHAR_SLOTS.CS_HAND_RIGHT,
            };

            for ( int i = 0; i < slots.GetLength(0); ++i )
            {
                int id = node.GetSlotItemId(slots[i]);
                SItem? item = wowDatabase.GetItemById(id);
                if (item.HasValue)
                {
                    slotItems.Add(new SlotItem(){ SlotName = slots[i].GetSlotName(), 
                        ItemId = item.Value.id,
                        ItemName = item.Value.name, 
                        ModelId = item.Value.modelId,
                        SubClassName = item.Value.subclassname });
                }
            }
        }

        public static string GetSlotName(this E_CHAR_SLOTS slot)
        {
            switch(slot)
            {
                case E_CHAR_SLOTS.CS_HEAD:
                    return Application.Current.FindResource("clothesHead") as string;
                case E_CHAR_SLOTS.CS_SHOULDER:
                    return Application.Current.FindResource("clothesShoulder") as string;
                case E_CHAR_SLOTS.CS_SHIRT:
                    return Application.Current.FindResource("clothesShirt") as string;
                case E_CHAR_SLOTS.CS_CHEST:
                    return Application.Current.FindResource("clothesChest") as string;
                case E_CHAR_SLOTS.CS_BELT:
                    return Application.Current.FindResource("clothesBelt") as string;
                case E_CHAR_SLOTS.CS_PANTS:
                    return Application.Current.FindResource("clothesPants") as string;
                case E_CHAR_SLOTS.CS_BOOTS:
                    return Application.Current.FindResource("clothesBoots") as string;
                case E_CHAR_SLOTS.CS_BRACERS:
                    return Application.Current.FindResource("clothesBracers") as string;
                case E_CHAR_SLOTS.CS_GLOVES:
                    return Application.Current.FindResource("clothesGloves") as string;
                case E_CHAR_SLOTS.CS_CAPE:
                    return Application.Current.FindResource("clothesCape") as string;
                case E_CHAR_SLOTS.CS_TABARD:
                    return Application.Current.FindResource("clothesTarbard") as string;
                case E_CHAR_SLOTS.CS_HAND_LEFT:
                    return Application.Current.FindResource("weaponLeft") as string;
                case E_CHAR_SLOTS.CS_HAND_RIGHT:
                    return Application.Current.FindResource("weaponRight") as string;
            }
            return "";
        }
    }
}
