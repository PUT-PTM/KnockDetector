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

namespace BluetoothAPP.Fragments
{
    public class DeleteFragment : Fragment
    {
        ListView usersToDelete;
        IList<string> listOfUsers;
        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            var view = inflater.Inflate(Resource.Layout.DeleteLayout, container, false);
            usersToDelete = view.FindViewById<ListView>(Resource.Id.usersToDelete);

            Bundle bundle = this.Arguments;
            listOfUsers = bundle.GetStringArrayList("LIST");
            
            ArrayAdapter<string> arrayAdapter = new ArrayAdapter<string>(Activity, Android.Resource.Layout.SimpleListItem1, listOfUsers);
            usersToDelete.Adapter = arrayAdapter;

            usersToDelete.Click += UsersToDelete_Click;

            return view;
        }

        private void UsersToDelete_Click(object sender, EventArgs e)
        {

        }
    }
}