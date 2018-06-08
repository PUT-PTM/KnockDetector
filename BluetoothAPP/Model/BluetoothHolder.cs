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
    class BluetoothHolder
    {
        public static Activity activity;
        public static BluetoothManage bluetoothManage = new BluetoothManage(activity);
    }
}