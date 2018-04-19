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
using Java.IO;
using Java.Util;

namespace BluetoothAPP.Model
{
    class BluetoothManager
    {
        private const string UuidUniversalProfile = "00001101-0000-1000-8000-00805F9B34FB";
        private BluetoothDevice result;
        private BluetoothSocket mSocket;
        private BufferedReader reader;
        private System.IO.Stream mStream;
        private InputStreamReader mReader;


        public BluetoothManager()
        {
            reader = null;
        }

        public string getDataFromDevice()
        {
            return reader.ReadLine();
        }

        private UUID getUUID()
        {
            return UUID.FromString(UuidUniversalProfile);
        }


        private void close(IDisposable disposable)
        {
            if (disposable == null)
                return;
            try
            {
                disposable.Dispose();
            }
            catch(Exception)
            {
                throw;
            }
            disposable = null;
        }

        private void openDeviceConnection(BluetoothDevice btDevice)
        {
            try
            {
                mSocket = btDevice.CreateRfcommSocketToServiceRecord(getUUID());
                mSocket.Connect();
                mStream = mSocket.InputStream;
                mReader = new InputStreamReader(mStream);
                reader = new BufferedReader(mReader);

            }
            catch(IOException e)
            {
                close(mSocket);
                close(mStream);
                close(mReader);
                throw e;
            }
        }

        public void getAllPairedDevices()
        {
            BluetoothAdapter btAdapter = BluetoothAdapter.DefaultAdapter;
            var devices = btAdapter.BondedDevices;

            if(devices != null && devices.Count > 0)
            {
                foreach(BluetoothDevice mDevice in devices)
                {
                    openDeviceConnection(mDevice);
                }
            }
        }

    }
}