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
        public static string receiver;
        public static string GETDB = "GETDB\a";
        public static string ADDUS = "ADDUS";
        public static string CHNCD = "CHNCD";
        public static string CHNUS = "CHNUS";
        public static string RECCD = "RECCD";
        public static string DELUS = "DELUS";


        public static string holdingStringToString()
        {
            string str = "";
            int i = 0;
            while(holdingString[i] != '\0')
            {
                str += holdingString[i];
                i++;
            }
            return str;
        }

        public static void receiverToHoldingString()
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

        public static char[] stringToCharArray()
        {
            char[] charArray = new char[863];
            for(int i =0; i < receiver.Length; i++)
            {
                charArray[i] = receiver[i];
            }
            return charArray;
        }

        public static string CODE()
        {
            return "" + receiver[0] + receiver[1];
        }

        public static int charsToInt(char ch0, char ch1)
        {
            int ret = 0;
            ret |= ch1 << 8;
            ret |= ch0;
            return ret;
        }
        

        public static char[] parsingChars(int start)
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

        public static int parsingId(int start, int end)
        {
            return charsToInt(holdingString[start], holdingString[end]);
        }

        public static void flushHolder()
        {
            for(int i =0; i < 863; i++)
            {
                holdingString[i] = '\0';
            }
        }

        public static int howManyUsers()
        {
            if (receiver[2] == '\a')
                return 0;
            else if (receiver[45] == '\a')
                return 1;
            else if (receiver[91] == '\a')
                return 2;
            else if (receiver[137] == '\a')
                return 3;
            else if (receiver[183] == '\a')
                return 4;
            else if (receiver[229] == '\a')
                return 5;
            else if (receiver[275] == '\a')
                return 6;
            else if (receiver[321] == '\a')
                return 7;
            else if (receiver[367] == '\a')
                return 8;
            else if (receiver[413] == '\a')
                return 9;
            else if (receiver[459] == '\a')
                return 10;
            else if (receiver[505] == '\a')
                return 11;
            else if (receiver[551] == '\a')
                return 12;
            else if (receiver[597] == '\a')
                return 13;
            else if (receiver[643] == '\a')
                return 14;
            else if (receiver[689] == '\a')
                return 15;
            else if (receiver[735] == '\a')
                return 16;
            else if (receiver[781] == '\a')
                return 17;
            else if (receiver[827] == '\a')
                return 18;
            else if (receiver[919] == '\a')
                return 19;
            return 20;
        }
        /*
        public static string responseToString()
        {
            string str = "";
            for(int i =0; i < 5; i++)
            {
                str += RESPONSE[i];
            }
            return str;
        }
        */

        /*
        public static int howManyUsers()
        {
            if (holdingString[2] == '\0')
                return 0;
            if (holdingString[44] == '\0')
                return 1;
            if (holdingString[86] == '\0')
                return 2;
            if (holdingString[128] == '\0')
                return 3;
            if (holdingString[170] == '\0')
                return 4;
            if (holdingString[212] == '\0')
                return 5;
            if (holdingString[254] == '\0')
                return 6;
            if (holdingString[296] == '\0')
                return 7;
            if (holdingString[338] == '\0')
                return 8;
            if (holdingString[380] == '\0')
                return 9;
            if (holdingString[422] == '\0')
                return 10;
            if (holdingString[464] == '\0')
                return 11;
            if (holdingString[506] == '\0')
                return 12;
            if (holdingString[548] == '\0')
                return 13;
            if (holdingString[590] == '\0')
                return 14;
            if (holdingString[632] == '\0')
                return 15;
            if (holdingString[674] == '\0')
                return 16;
            if (holdingString[716] == '\0')
                return 17;
            if (holdingString[758] == '\0')
                return 18;
            if (holdingString[800] == '\0')
                return 19;
            return 20;
        } 
        */
    }
}