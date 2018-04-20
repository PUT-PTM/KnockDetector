using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using Android.App;
using Android.Bluetooth;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;
using BluetoothAPP.Activities;
using Java.Util;

namespace BluetoothAPP.Fragments
{
    public class UsersFragment : Fragment
    {
        Activity activ = new UsersActivity();
        BluetoothDevice device;
        BluetoothAdapter adapter;
        BluetoothSocket socket;
        Button btnConnect;
        Button record;
        TextView txtStatus;

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
           
            //Event-Click handlers
            record.Click += BtnRecord_Click;
            btnConnect.Click += BtnConnect_Click;

            //Enabling/Disabling button to press
            EnableOrDisableAllMainFunctions(false);

            return mainView;
        }



        private void EnableOrDisableAllMainFunctions(bool isEnabled)
        {
            record.Enabled = isEnabled;
        }

        async void BtnConnect_Click(object sender, EventArgs e)
        {
            try
            {
                //Using default adapter of a phone
                adapter = BluetoothAdapter.DefaultAdapter;
                if (adapter == null)
                    throw new Exception("No Bluetooth adapter found.");

                if (!adapter.IsEnabled)
                    throw new Exception("Bluetooth adapter is not enabled.");

                //Looking for HC-05 bluetooth adapter
                device = (from bd in adapter.BondedDevices
                          where bd.Name == "HC-05"
                          select bd).FirstOrDefault();

                if (device == null)
                    throw new Exception("STM32 device not found.");

                socket = device.CreateRfcommSocketToServiceRecord(UUID.FromString("00001101-0000-1000-8000-00805f9b34fb"));
                await socket.ConnectAsync();
                //Shows text on screen of app when STM connected
                txtStatus.Text = "STM Connected";
                EnableOrDisableAllMainFunctions(true);
                btnConnect.Enabled = false;
            }
            catch (Exception ex)
            {
                txtStatus.Text = ex.Message;
                Toast.MakeText(activ, ex.Message, ToastLength.Short);
            }
        }


        void BtnRecord_Click(object sender, EventArgs e)
        {
            //Sending 1 through bluetooth by Record Button
            RobotMainFunction("1");
        }

        
        private async void RobotMainFunction(string strDirection)
        {
            try
            {
                //Procedure that sends byte through socket
                byte[] buffer = Encoding.ASCII.GetBytes(strDirection);
                await socket.OutputStream.WriteAsync(buffer, 0, buffer.Length);
            }
            catch (Exception ex)
            {
                Toast.MakeText(activ, ex.Message, ToastLength.Short);
            }
        }
    }
}