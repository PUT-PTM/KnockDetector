using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;
using BluetoothAPP.Activities;
using BluetoothAPP.Model;
using Java.Lang;
using Java.Util;

namespace BluetoothAPP.Fragments
{
    public class UsersFragment : Fragment
    {
        Activity activ = new UsersActivity();
        BluetoothManage bluetooth = new BluetoothManage();

        Button btnConnect;
        Button record;
        TextView txtStatus;
        TextView received;

        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            //Getting main fragment layout
            var mainView = inflater.Inflate(Resource.Layout.UsersFragment, container, false);
            //Getting buttons and texts from layout
            record = mainView.FindViewById<Button>(Resource.Id.record);
            btnConnect = mainView.FindViewById<Button>(Resource.Id.connectBtn);
            txtStatus = mainView.FindViewById<TextView>(Resource.Id.txtStatus);
            received = mainView.FindViewById<TextView>(Resource.Id.receivedText);
            string data = "";
            received.Text = "Didnt received anything yet!";
         




            //Event-Click handlers
            record.Click += (s, e) =>
            {
                bluetooth.BtnRecord_Click(s, e);
                received.Text = bluetooth.getReceiver();
            };
            btnConnect.Click += (s, e) =>
            {
                bluetooth.BtnConnect_Click(s, e, btnConnect, record, txtStatus);
            };


            
            //Enabling/Disabling button to press
            bluetooth.EnableOrDisableAllMainFunctions(false, record);
            

            return mainView;
        }
    }
}