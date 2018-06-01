using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Support.V7.App;
using Android.Views;
using Android.Widget;
using BluetoothAPP.Adapters;
using BluetoothAPP.Fragments;
using BluetoothAPP.Model;

namespace BluetoothAPP.Activities
{
    [Activity(Label = "KnockDetector", Theme = "@style/Theme.AppCompat.NoActionBar")]
    public class UsersActivity : AppCompatActivity
    {
        BluetoothManage bluetoothMan = new BluetoothManage();
        List<User> users = new List<User>();
        ListView usersList;
        TextView actualUsername;
        ImageButton microphoneBtn;
        ImageButton editBtn;
        ImageButton deleteBtn;

        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
            SetContentView(Resource.Layout.UsersActivity);
            usersList = FindViewById<ListView>(Resource.Id.myListView);
            
            uploadingDatabase();

            UsersViewAdapter adapter = new UsersViewAdapter(this, users);
            usersList.Adapter = adapter;

            usersList.ItemClick += UsersList_ItemClick;

        }

        private void UsersList_ItemClick(object sender, AdapterView.ItemClickEventArgs e)
        {
            LayoutInflater layoutInflater = LayoutInflater.From(this);
            var view = layoutInflater.Inflate(Resource.Layout.Dialog, null);
            actualUsername = view.FindViewById<TextView>(Resource.Id.actualUserName);
            editBtn = view.FindViewById<ImageButton>(Resource.Id.editButton);
            microphoneBtn = view.FindViewById<ImageButton>(Resource.Id.microphoneButton);
            deleteBtn = view.FindViewById<ImageButton>(Resource.Id.deleteButton);


            Android.Support.V7.App.AlertDialog.Builder alertDialogBuilder = new Android.Support.V7.App.AlertDialog.Builder(this);
            alertDialogBuilder.SetView(view);

            Android.Support.V7.App.AlertDialog alertDialogAndroid = alertDialogBuilder.Create();
            alertDialogAndroid.Show();

            actualUsername.Text = users[e.Position].nameToString();


            editBtn.Click += EditBtn_Click;
            deleteBtn.Click += DeleteBtn_Click;
            microphoneBtn.Click += (s, p) =>
            {
                alertDialogAndroid.Dismiss();
                FragmentTransaction transaction = FragmentManager.BeginTransaction();
                MicrophoneFragment microphoneFragment = new MicrophoneFragment();
                transaction.Add(Resource.Id.container, microphoneFragment, "MICROPHONE FRAGMENT");
                transaction.Commit();
                return;
            };

        }

        private void MicrophoneBtn_Click(object sender, EventArgs e)
        {
            FragmentTransaction transaction = FragmentManager.BeginTransaction();
            MicrophoneFragment microphoneFragment = new MicrophoneFragment();
            transaction.Add(Resource.Id.container, microphoneFragment, "MICROPHONE FRAGMENT");
            transaction.Commit();
        }

        private void DeleteBtn_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        private void EditBtn_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
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
            if(DatabaseHolder.howManyUsers() == 0)
                return false;

            for (int i = 0; i < DatabaseHolder.howManyUsers(); i++)
            {
                creatingUser(i);
            }
            return true;
        }
    }
}