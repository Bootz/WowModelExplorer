using System;
using System.ComponentModel;
using System.Collections.ObjectModel;

namespace WowModelExplorer.Data
{
    public class Map : Entry
    {
        private string internalName;
        private string type;

        public string InternalName
        {
            get { return internalName; }
            set
            {
                if (internalName != value)
                {
                    internalName = value;
                    RaisePropertyChanged("InternalName");
                }
            }
        }

        public string Type
        {
            get { return type; }
            set
            {
                if (type != value)
                {
                    type = value;
                    RaisePropertyChanged("Type");
                }
            }
        }
    }

    public class MapCollection : ObservableCollection<Map>
    {

    }
}
