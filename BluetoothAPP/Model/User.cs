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
    public class User
    {
        public char[] Name { get; set; }
        public int Id { get; set; }
        public char[] Creation_date { get; set; }
        public bool Secret_code { get; set; }

        public User()
        {
            Name = new char[20];
            Creation_date = new char[20];
        }
        


        public string nameToString()
        {
            string str = "";
            for (int i = 0; i < 20; i++)
            {
                str += Name[i];
            }
            return str;
        }

        public string creationDateToString()
        {
            string str = "";
            for (int i = 0; i < 20; i++)
            {
                str += Creation_date[i];
            }
            return str;
        }
    }
}