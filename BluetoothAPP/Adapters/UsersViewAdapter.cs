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
using BluetoothAPP.Model;

namespace BluetoothAPP.Adapters
{
    class UsersViewAdapter : BaseAdapter<User>
    {
        private List<User> users;
        private Context context;

        public UsersViewAdapter(Context mContext, List<User> mUsers)
        {
            users = mUsers;
            context = mContext;
        }

        public override User this[int position] => users[position];

        public override int Count => users.Count;

        public override long GetItemId(int position) => position;

        public override View GetView(int position, View convertView, ViewGroup parent)
        {
            View row = convertView;
            if(row == null)
            {
                row = LayoutInflater.From(context).Inflate(Resource.Layout.UsersList, null, false);
            }

            TextView idText = row.FindViewById<TextView>(Resource.Id.id);
            idText.Text = users[position].Id.ToString();

            TextView nameText = row.FindViewById<TextView>(Resource.Id.name);
            nameText.Text = users[position].NameToString();

            TextView creationText = row.FindViewById<TextView>(Resource.Id.creationDate);
            creationText.Text = users[position].CreationDateToString();

            TextView codeText = row.FindViewById<TextView>(Resource.Id.hasCode);
            if (users[position].Secret_code[0] == 0)
                codeText.Text = "No code";
            else codeText.Text = "Code recorded";

            return row;
        }
    }
}