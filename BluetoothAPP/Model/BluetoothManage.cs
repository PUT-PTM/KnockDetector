using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Android.App;
using Android.Bluetooth;
using Android.Widget;
using Java.Util;

namespace BluetoothAPP.Model
{
    public class BluetoothManage
    {
        Activity activ;
        BluetoothDevice device;
        BluetoothAdapter adapter;
        BluetoothSocket socket;

        public BluetoothManage(Activity activity)
        {
            this.activ = activity;
        }

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
                        Toast.MakeText(activ, "No Bluetooth adaapter found!", ToastLength.Long).Show();

                    if (!adapter.IsEnabled)
                        Toast.MakeText(activ, "Bluetooth adapter is not enabled!", ToastLength.Long).Show();

                    //Looking for HC-05 bluetooth adapter
                    device = (from bd in adapter.BondedDevices
                              where bd.Name == "HC-05"
                              select bd).FirstOrDefault();

                    if (device == null)
                        Toast.MakeText(activ, "Device STM32 not found!", ToastLength.Long).Show();

                    socket = device.CreateRfcommSocketToServiceRecord(UUID.FromString("00001101-0000-1000-8000-00805f9b34fb"));
                    await socket.ConnectAsync();
                    //beginListenForData();
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
            byte[] buffer = new byte[920];
            try
            {
                while (socket.InputStream.IsDataAvailable())
                {
                    lock (this)
                    {
                        //Procedure that reads bytes through socket
                        socket.InputStream.Read(buffer, 0, 920);
                        DatabaseHolder.receiver = System.Text.Encoding.ASCII.GetString(buffer);

                        if (DatabaseHolder.receiver != null)
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

        public void Read1()
        {
            byte[] buffer = new byte[920];
            try
            {
                if (socket.InputStream.IsDataAvailable())
                {

                    //Procedure that reads bytes through socket
                    socket.InputStream.Read(buffer, 0, 920);
                    DatabaseHolder.receiver = System.Text.Encoding.ASCII.GetString(buffer);

                    if (DatabaseHolder.receiver != null)
                        socket.InputStream.Flush();
                    //DatabaseHolder.holdingString = DatabaseHolder.receiver;

                }
            }
            catch (Exception ex)
            {
                Toast.MakeText(activ, ex.Message, ToastLength.Short);
            }
        }
        public void beginListenForData()
        {
            Task.Factory.StartNew(() => {

                byte[] buffer = new byte[1024];

                int bytes;
                while (true)
                {
                    try
                    {
                        //DatabaseHolder.receiver = System.Text.Encoding.ASCII.GetString(buffer);
                        bytes = socket.InputStream.Read(buffer, 0, buffer.Length);
                       
                        if (bytes > 0)
                        {
                            //DatabaseHolder.receiver = System.Text.Encoding.ASCII.GetString(buffer);
                            activ.RunOnUiThread(() => Receiving(buffer));
                        }
                    }
                    catch (Java.IO.IOException)
                    {
                        activ.RunOnUiThread(() => {
                            
                        });
                        break;
                    }
                }
            });
        }
        void Receiving(byte[] buffer)
        { 
            DatabaseHolder.receiver = System.Text.Encoding.ASCII.GetString(buffer);
        }
    }
}