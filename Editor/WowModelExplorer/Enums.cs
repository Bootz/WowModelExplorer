using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WowModelExplorer
{
    public enum Languages
    {
        Chinese,
        English,
    }

    public enum OpenTypes
    {
        LoginScreen,
    }

    public enum ModelViewTypes
    {
        Character,
        Npc,
        SpellVisualEffect,
        MapModel,
        Clothes,
        Weapon,
        Set,
        Animation,
        MapModelName,
        Property,
        M2State,
    }

    public enum EditorShowOptions
    {
        DebugText,
        Plane,
        DebugGeosets,
        Coord,
    }

    public enum EditorSetOptions
    {
        Default,
        Set
    }

    public enum BackMusicFiles
    {
        None,
        MainTitle,
        WotLK,
        Cataclysm,
        Pandaria,
        HighBorne,
        Stormwind,
        Darnassus,
        Ironforge,
        Orgrimmar,
        Thunderbluff,
        Undercity
    }

    public enum CameraModes
    {
        FPS,
        Maya
    }

    public enum NumSetOptions
    {
        Medium,
        Low,
        Lowest,
        High,
        Highest
    }
}
