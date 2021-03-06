﻿using System;
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
        public char[] Secret_code { get; set; }

        public User()
        {
            Name = new char[20];
            Creation_date = new char[20];
            Secret_code = new char[1];
        }
        


        public string NameToString()
        {
            string str = "";
            for (int i = 0; i < 20; i++)
            {
                str += Name[i];
            }
            return str;
        }

        public string CreationDateToString()
        {
            string str = "";
            for (int i = 0; i < 20; i++)
            {
                str += Creation_date[i];
            }
            return str;
        }
        
        public void FlushArrays()
        {
            for(int i =0; i < 20; i++)
            {
                Creation_date[i] = '\0';
                Name[i] = '\0';
            }
        }
    }
}