using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;
using BluetoothAPP.Activities;
using BluetoothAPP.Adapters;
using BluetoothAPP.Model;
using Java.Lang;
using Java.Util;

namespace BluetoothAPP.Fragments
{
    public class UsersFragment : Fragment
    {
        List<User> users = new List<User>();
        ListView usersList;
        TextView actualUsername;
        ImageButton microphoneBtn;
        ImageButton editBtn;
        ImageButton deleteBtn;
        Android.Support.V7.App.AlertDialog alertDialogAndroid;
        Android.Support.V7.App.AlertDialog.Builder alertDialogBuilder;

        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            var view = inflater.Inflate(Resource.Layout.UsersFragment, container, false);
            usersList = view.FindViewById<ListView>(Resource.Id.myListView);

            uploadingDatabase();

            UsersViewAdapter adapter = new UsersViewAdapter(this.Activity, users);
            usersList.Adapter = adapter;

            usersList.ItemClick += UsersList_ItemClick;
            return view;
        }

        private void UsersList_ItemClick(object sender, AdapterView.ItemClickEventArgs e)
        {
            LayoutInflater layoutInflater = LayoutInflater.From(this.Activity);
            var view = layoutInflater.Inflate(Resource.Layout.Dialog, null);
            actualUsername = view.FindViewById<TextView>(Resource.Id.actualUserName);
            editBtn = view.FindViewById<ImageButton>(Resource.Id.editButton);
            microphoneBtn = view.FindViewById<ImageButton>(Resource.Id.microphoneButton);
            deleteBtn = view.FindViewById<ImageButton>(Resource.Id.deleteButton);


            alertDialogBuilder = new Android.Support.V7.App.AlertDialog.Builder(this.Activity);
            alertDialogBuilder.SetView(view);

            alertDialogAndroid = alertDialogBuilder.Create();
            alertDialogAndroid.Show();

            actualUsername.Text = users[e.Position].nameToString();


            editBtn.Click += EditBtn_Click;
            deleteBtn.Click += DeleteBtn_Click;
            microphoneBtn.Click += MicrophoneBtn_Click;

        }

        private void MicrophoneBtn_Click(object sender, EventArgs e)
        {
            alertDialogAndroid.Dismiss();
            FragmentTransaction transaction = FragmentManager.BeginTransaction();
            MicrophoneFragment microphoneFragment = new MicrophoneFragment();
            transaction.Replace(Resource.Id.container, microphoneFragment, "MICROPHONE_FRAGMENT");
            transaction.AddToBackStack("MICROPHONE_FRAGMENT");
            transaction.Commit();
        }

        private void DeleteBtn_Click(object sender, EventArgs e)
        {
            alertDialogAndroid.Dismiss();
            FragmentTransaction transaction = FragmentManager.BeginTransaction();
            DeleteFragment deleteFragment = new DeleteFragment();
            transaction.Replace(Resource.Id.container, deleteFragment, "DELETE_FRAGMENT");
            transaction.AddToBackStack("DELETE_FRAGMENT");
            transaction.Commit();
        }

        private void EditBtn_Click(object sender, EventArgs e)
        {
            alertDialogAndroid.Dismiss();
            FragmentTransaction transaction = FragmentManager.BeginTransaction();
            EditFragment editFragment = new EditFragment();
            transaction.Replace(Resource.Id.container, editFragment, "EDIT_FRAGMENT");
            transaction.AddToBackStack("EDIT_FRAGMENT");
            transaction.Commit();
        }

        void creatingUser(int i)
        {
            User user = new User
            {
                Id = DatabaseHolder.parsingId(42 * i, (42 * i) + 1),
                Name = DatabaseHolder.parsingChars((42 * i) + 2, (42 * i) + 22),
                Creation_date = DatabaseHolder.parsingChars((42 * i) + 22, (42 * i) + 42)
            };

            string name = user.nameToString();
            string creation_date = user.creationDateToString();
            users.Add(user);
        }



        bool uploadingDatabase()
        {
            if (DatabaseHolder.howManyUsers() == 0)
                return false;

            for (int i = 0; i < DatabaseHolder.howManyUsers(); i++)
            {
                creatingUser(i);
            }

            DatabaseHolder.holdingString[0] = '\0';
            return true;
        }
    }
}