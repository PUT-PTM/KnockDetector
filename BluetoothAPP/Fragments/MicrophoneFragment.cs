using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;
using BluetoothAPP.Model;

namespace BluetoothAPP.Fragments
{
    public class MicrophoneFragment : Fragment
    {

        Button record;
        Activity activity;
        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Create your fragment here
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            var view = inflater.Inflate(Resource.Layout.MicrophoneLayout, container, false);
            record = view.FindViewById<Button>(Resource.Id.recordButton);

            
            record.Click += Record_Click;

            return view;
        }


        private void Record_Click(object sender, EventArgs e)
        {
            BluetoothHolder.bluetoothManage.Write("1");
        }
    }
}