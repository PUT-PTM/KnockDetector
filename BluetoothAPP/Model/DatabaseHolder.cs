using System;
using System.Collections;
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
    public class DatabaseHolder
    {
        public static string receiver = "";
        public static string GETDB = "GETDB\a";
        public static string ADDUS = "ADDUS";
        public static string CHNCD = "CHNCD";
        public static string CHNUS = "CHNUS";
        public static string RECCD = "RECCD\a";
        public static string DELUS = "DELUS";
        
        public static string CODE()
        {
            if (receiver.Length < 2)
                return null;
            return "" + receiver[0] + receiver[1];
        }

        public static int CharsToInt(char ch0, char ch1)
        {
            int ret = 0;
            ret |= ch1 << 8;
            ret |= ch0;
            return ret;
        }

        public static char[] IntToCharArr(int x)
        {
            char[] arr = new char[2];
            arr[0] = (arr[1] = (char)0);
            arr[0] |= (char)x;
            arr[1] |= (char)(x >> 8);
            return arr;
        }

        public static char[] ParsingChars(int start)
        {
            char[] arr = new char[20];
            int i = 0;
            int j = start;
            while(!receiver[j].Equals('#'))
            {
                arr[i] = receiver[j];
                j++;
                i++;
            }
            return arr;
        }

        public static int ParsingId(int start, int end)
        {
            return CharsToInt(receiver[start], receiver[end]);
        }
        

        public static int HowManyUsers()
        {
            for(int i =0; i < 20; i++)
            {
                if (receiver[i * 43 + 2].Equals('\0'))
                    return i;
            }
            return 0;
        }
    }
}