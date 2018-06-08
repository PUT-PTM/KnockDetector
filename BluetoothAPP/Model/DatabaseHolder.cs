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
        public static char[] holdingString = new char[920];
        public static string receiver = "";
        public static string GETDB = "GETDB\a";
        public static string ADDUS = "ADDUS";
        public static string CHNCD = "CHNCD";
        public static string CHNUS = "CHNUS";
        public static string RECCD = "RECCD";
        public static string DELUS = "DELUS";
        

        public static void ReceiverToHoldingString()
        {
            int i = 0;
            while(true)
            {
                holdingString[i] = receiver[i];
                i++;
                if (receiver[i - 1] == '\a')
                    break;
            }
        }
        

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
        

        public static char[] ParsingChars(int start)
        {
            char[] x = new char[20];
            int i = 0;
            int j = start;
            while(!receiver[j].Equals('#'))
            {
                x[i] = receiver[j];
                j++;
                i++;
            }
            return x;
        }

        public static int ParsingId(int start, int end)
        {
            return CharsToInt(holdingString[start], holdingString[end]);
        }
        

        public static int HowManyUsers()
        {
            for(int i =0; i < 20; i++)
            {
                if (receiver[i * 43 + 2].Equals('\a'))
                    return i;
            }
            return 0;
        }
    }
}