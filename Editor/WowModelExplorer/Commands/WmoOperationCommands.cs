using System;
using System.Collections.Generic;
using System.Windows.Input;
using AvalonDock;
using mywowNet;
using System.Windows.Media;
using WowModelExplorer;
using WowModelExplorer.Services;
using WowModelExplorer.Views;
using WowModelExplorer.Utility;
using WowModelExplorer.Controls;

namespace WowModelExplorer.Commands
{
    public class WmoOperationCommands
    {
        private static RoutedUICommand groupsWindowCommand = new RoutedUICommand();

        public static RoutedUICommand GroupsWindow { get { return groupsWindowCommand; } }

        private readonly CommandBindingCollection commandBindings = new CommandBindingCollection();

        public CommandBindingCollection CommandBindings { get { return commandBindings; } }

        public WmoOperationCommands()
        {
            commandBindings.Add(new CommandBinding(groupsWindowCommand, GroupsWindowExecuted));
        }

        private void GroupsWindowExecuted(object sender, ExecutedRoutedEventArgs e)
        {
            WMOGroupsWindow window = ShellService.Instance.GroupsWindow;
            if (window.IsVisible)
                window.Hide();
            else
            {
                window.Show();
                window.Update();
            }
        }

        private void CanWmoExecuted(object sender, CanExecuteRoutedEventArgs e)
        {
            WMOSceneNode node = ModelSceneService.Instance.MainWMOSceneNode;
            e.CanExecute = (node != null);
        }
    }
}
