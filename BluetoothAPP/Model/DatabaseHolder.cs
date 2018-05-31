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
        public static char[] holdingString = new char[840];

        public static int charsToInt(char ch0, char ch1)
        {
            int ret = 0;
            ret |= ch1 << 8;
            ret |= ch0;
            return ret;
        }
        

        public static char[] parsingChars(int start, int end)
        {
            char[] x = new char[20];
            int j = 0;
            for (int i = start; i < end; i++)
            {
                x[j] = holdingString[i];
                j++;
            }
            return x;
        }

        public static int parsingId(int start, int end)
        {
            return charsToInt(holdingString[start], holdingString[end]);
        }
        

        public static int howManyUsers()
        {
            if (holdingString[0] == '\0')
                return 0;
            if (holdingString[42] == '\0')
                return 1;
            if (holdingString[84] == '\0')
                return 2;
            if (holdingString[126] == '\0')
                return 3;
            if (holdingString[168] == '\0')
                return 4;
            if (holdingString[210] == '\0')
                return 5;
            if (holdingString[252] == '\0')
                return 6;
            if (holdingString[294] == '\0')
                return 7;
            if (holdingString[336] == '\0')
                return 8;
            if (holdingString[378] == '\0')
                return 9;
            if (holdingString[420] == '\0')
                return 10;
            if (holdingString[462] == '\0')
                return 11;
            if (holdingString[504] == '\0')
                return 12;
            if (holdingString[546] == '\0')
                return 13;
            if (holdingString[588] == '\0')
                return 14;
            if (holdingString[630] == '\0')
                return 15;
            if (holdingString[672] == '\0')
                return 16;
            if (holdingString[714] == '\0')
                return 17;
            if (holdingString[756] == '\0')
                return 18;
            if (holdingString[798] == '\0')
                return 19;
            return 20;
        } 
    }
}