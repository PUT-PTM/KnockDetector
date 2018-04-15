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
    public class Product
    {
        private string Name;

        private string Image;

        public string Image1 { get => Image; set => Image = value; }
        public string Name1 { get => Name; set => Name = value; }
    }
}