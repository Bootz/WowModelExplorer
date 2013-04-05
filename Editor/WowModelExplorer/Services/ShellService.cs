using System;
using WowModelExplorer;
using WowModelExplorer.Views;
using WowModelExplorer.Commands;
using WowModelExplorer.Menus;
using WowModelExplorer.Controls;

namespace WowModelExplorer.Services
{
    public class ShellService
    {
        private readonly MainWindow mainWindow;

        private readonly FileCommands fileCommands = new FileCommands();
        private readonly AnimationCommands animationCommands = new AnimationCommands();
        private readonly ViewCommands viewCommands = new ViewCommands();
        private readonly ModelOperationCommands modelOperationCommands = new ModelOperationCommands();
        private readonly ModelEditViewCommands modelEditViewCommands = new ModelEditViewCommands();
        private readonly WmoOperationCommands wmoOperationCommands = new WmoOperationCommands();
        private readonly WmoEditViewCommands wmoEditViewCommands = new WmoEditViewCommands();
        private readonly OptionCommands optionCommands = new OptionCommands();
        private readonly SettingCommands settingCommands = new SettingCommands();
        private readonly LanguageCommands languageCommands = new LanguageCommands();

        public ShellService(MainWindow window)
        {
            if (instance == null)
            {
                instance = this;

                mainWindow = window;
            }
         }
        private static ShellService instance = null;
        public static ShellService Instance { get { return instance; } }

        public MainWindow MainWindow { get { return mainWindow; } }

        //model mode views
        public ModelMenu ModelMenu { get { return mainWindow._modelMenu; } }
        public CharacterContent CharacterContent { get { return mainWindow._characterContent; } }
        public NpcContent NpcContent { get { return mainWindow._npcContent; } }
        public SpellVisualEffectContent SpellVisualEffectContent { get { return mainWindow._spellVisualEffectContent; } }
        public MapModelContent MapModelContent { get { return mainWindow._mapModelContent; } }

        public AnimationContent AnimationContent { get { return mainWindow._animationContent; } }
        public ClothesContent ClothesContent { get { return mainWindow._clothesContent; } }
        public WeaponContent WeaponContent { get { return mainWindow._weaponContent; } }
        public SetContent SetContent { get { return mainWindow._setContent; } }
        public MapModelNameContent MapModelNameContent { get { return mainWindow._mapModelNameContent; } }
        public PropertyContent PropertyContent { get { return mainWindow._propertyContent; } }
        public M2StateContent M2StateContent { get { return mainWindow._m2StateContent; } }

        //dialogs
        public M2GeosetsWindow GeosetsWindow { get { return mainWindow.GeosetsWindow; } }
        public WMOGroupsWindow GroupsWindow { get { return mainWindow.GroupsWindow; } }
        public M2EquipmentsWindow EquipmentsWindow { get { return mainWindow.EquipmentsWindow; } }

        //Commands
        public FileCommands FileCommands { get { return fileCommands; } }
        public AnimationCommands AnimationCommands { get { return animationCommands; } }
        public ViewCommands ViewCommands { get { return viewCommands; } }
        public ModelOperationCommands ModelOperationCommands { get { return modelOperationCommands; } }
        public ModelEditViewCommands ModelEditViewCommands { get { return modelEditViewCommands; } }
        public WmoOperationCommands WmoOperationCommands { get { return wmoOperationCommands; } }
        public WmoEditViewCommands WmoEditViewCommands { get { return wmoEditViewCommands; } }
        public OptionCommands OptionCommands { get { return optionCommands; } }
        public SettingCommands SettingCommands { get { return settingCommands; } }
        public LanguageCommands LanguageCommands { get { return languageCommands; } }
    }
}
