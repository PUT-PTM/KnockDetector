using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;

namespace BluetoothAPP.Model
{
    public class DatabaseStructure
    {
        public Int16 userId;
        public char[] username;
        public char[] creationDate;

        public DatabaseStructure()
        {
            this.username = new char[20];
            this.creationDate = new char[20];
        }
    }
}