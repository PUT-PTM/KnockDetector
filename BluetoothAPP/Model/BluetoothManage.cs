using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Android.App;
using Android.Bluetooth;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Java.Util;

namespace BluetoothAPP.Model
{
    public class BluetoothManage
    {
        Activity activ = null;
        BluetoothDevice device;
        BluetoothAdapter adapter;
        BluetoothSocket socket;


        public void EnableOrDisableAllMainFunctions(bool isEnabled, Button record)
        {
            record.Enabled = isEnabled;
        }

        public async void BtnConnect_Click(object sender, EventArgs e, Button btnConnect, Button record, TextView txtStatus)
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
                EnableOrDisableAllMainFunctions(true, record);
                btnConnect.Enabled = false;
            }
            catch (Exception ex)
            {
                txtStatus.Text = ex.Message;
                Toast.MakeText(activ, ex.Message, ToastLength.Short);
            }
        }


        public void BtnRecord_Click(object sender, EventArgs e)
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