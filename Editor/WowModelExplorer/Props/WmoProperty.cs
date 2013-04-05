using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using mywowNet;
using System.ComponentModel;

namespace WowModelExplorer.Props
{
    public class WmoProperty : INotifyPropertyChanged
    {

        #region Properties
        #endregion

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string propertyName)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        #endregion
    }
}
