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
    [Activity(Label = "UsersActivity")]
    public class UsersActivity : AppCompatActivity
    {
        BluetoothManage bluetoothMan = new BluetoothManage();
        List<User> users = new List<User>();
        ListView usersList;

        protected override void OnStart()
        {
            base.OnStart();
        }


        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
            SetContentView(Resource.Layout.UsersActivity);
            usersList = FindViewById<ListView>(Resource.Id.myListView);
            
            uploadingDatabase();

            UsersViewAdapter adapter = new UsersViewAdapter(this, users);
            usersList.Adapter = adapter;
            

            /*
            FragmentTransaction fragmentTransaction = FragmentManager.BeginTransaction();
            UsersFragment usersFragment = new UsersFragment();
            fragmentTransaction.Add(Resource.Id.fragment_container, usersFragment, "USERS_FRAGMENT");
            fragmentTransaction.Commit();


            FragmentManager.BackStackChanged += (s, e) =>
            {
                if (FragmentManager.BackStackEntryCount > 0)
                    SupportActionBar.SetDisplayHomeAsUpEnabled(true);
                else SupportActionBar.SetDisplayHomeAsUpEnabled(false);
            };
            */
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