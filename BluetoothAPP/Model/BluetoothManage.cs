using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Android.App;
using Android.Bluetooth;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Java.IO;
using Java.Util;

namespace BluetoothAPP.Model
{
    public class BluetoothManage
    {
        Activity activ = null;
        BluetoothDevice device;
        BluetoothAdapter adapter;
        BluetoothSocket socket;
        Boolean continuous;
        private string receiver;


        public Boolean getContinuous()
        {
            return continuous;
        }
        public string getReceiver()
        {
            return receiver;
        }

        public BluetoothManage()
        {
            this.receiver = "";
            this.continuous = false;
        }

        public void EnableOrDisableAllMainFunctions(bool isEnabled, Button record)
        {
            record.Enabled = isEnabled;
        }

        public async void BtnConnect_Click()
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
                //txtStatus.Text = "STM Connected";
                //EnableOrDisableAllMainFunctions(true, record);
                //btnConnect.Enabled = false;
            }
            catch (Exception ex)
            {
                //txtStatus.Text = ex.Message;
                Toast.MakeText(activ, ex.Message, ToastLength.Short);
            }
            
        }


        public void writingSignal()
        {
            //Sending 1 through bluetooth by Record Button
            Write("2");
        }


        public void readData()
        {
            Read();
        }


        public async void Write(string strDirection)
        {
            try
            {
                while (socket.IsConnected == false) { }
                if (socket.IsConnected)
                {
                    //Procedure that sends byte through socket
                    byte[] buffer = Encoding.ASCII.GetBytes(strDirection);
                    await socket.OutputStream.WriteAsync(buffer, 0, buffer.Length);
                }
            }
            catch (Exception ex)
            {
                Toast.MakeText(activ, ex.Message, ToastLength.Short);
            }
        }


        public async void Read()
        {
            byte[] buffer = new byte[256];
            try
            {
                //while (socket.IsConnected == false) { }

                //if (socket.IsConnected)
                //{
                    while (socket.InputStream.IsDataAvailable())
                    {
                        //Procedure that reads bytes through socket
                        await socket.InputStream.ReadAsync(buffer, 0, 256);
                        DatabaseHolder.holdingString = System.Text.Encoding.ASCII.GetString(buffer).ToCharArray();
                    }
                //}
            } 
            catch (Exception ex)
            {
                Toast.MakeText(activ, ex.Message, ToastLength.Short);
            }
        }
    }
}