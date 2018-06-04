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

        public BluetoothSocket getSocket()
        {
            return socket;
        }
        

        public async void BtnConnect_Click()
        {

            try
            {
                if (socket == null)
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
                }
            }
            catch (Exception ex)
            {
                Toast.MakeText(activ, ex.Message, ToastLength.Short);
            }
            
        }
        

        public void closingSocket()
        {
            if (socket != null)
            {
                try
                {
                    socket.Close();
                }
                catch (System.IO.IOException e)
                {
                }
                socket = null;
            }
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


        public void Read()
        {
            byte[] buffer = new byte[256];
            try
            {
                while (socket.InputStream.IsDataAvailable())
                {
                    lock (this)
                    {
                        //Procedure that reads bytes through socket
                        socket.InputStream.Read(buffer, 0, 256);
                        DatabaseHolder.receiver = System.Text.Encoding.ASCII.GetString(buffer);
                        socket.InputStream.Flush();
                        //DatabaseHolder.holdingString = DatabaseHolder.receiver;
                    }
                }
            } 
            catch (Exception ex)
            {
                Toast.MakeText(activ, ex.Message, ToastLength.Short);
            }
        }
    }
}