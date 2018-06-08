using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;
using BluetoothAPP.Model;
using Java.Lang;

namespace BluetoothAPP.Fragments
{
    public class DeleteFragment : Fragment
    {
        ListView usersToDelete;
        IList<string> namesOfUsers;
        IList<Integer> idsOfUsers;
        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            BluetoothHolder.activity = this.Activity;
            var view = inflater.Inflate(Resource.Layout.DeleteLayout, container, false);
            usersToDelete = view.FindViewById<ListView>(Resource.Id.usersToDelete);

            Bundle bundle = this.Arguments;
            namesOfUsers = bundle.GetStringArrayList("STRINGLIST");
            idsOfUsers = bundle.GetIntegerArrayList("INTLIST");
            
            ArrayAdapter<string> arrayAdapter = new ArrayAdapter<string>(Activity, Android.Resource.Layout.SimpleListItem1, namesOfUsers);
            usersToDelete.Adapter = arrayAdapter;

            usersToDelete.ItemClick += UsersToDelete_ItemClick;

            return view;
        }

        private void UsersToDelete_ItemClick(object sender, AdapterView.ItemClickEventArgs e)
        {
            
        }
        
    }
}