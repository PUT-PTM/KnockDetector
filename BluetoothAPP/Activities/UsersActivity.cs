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

        public BluetoothManage bluetoothManage = new BluetoothManage();
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
            SetContentView(Resource.Layout.UsersActivity);

            var toolbar = FindViewById<Android.Support.V7.Widget.Toolbar>(Resource.Id.toolbar);
            toolbar.Title = "Knock Detector";
            SetSupportActionBar(toolbar);
            SupportActionBar.SetDisplayHomeAsUpEnabled(true);
            toolbar.NavigationClick += (s, e) =>
            {
                OnBackPressed();
            };

            FragmentTransaction transaction = FragmentManager.BeginTransaction();
            UsersFragment usersFragment = new UsersFragment();
            transaction.Add(Resource.Id.container, usersFragment, "USERS_FRAGMENT");
            transaction.Commit();


            FragmentManager.BackStackChanged += (s, e) =>
            {
                if (FragmentManager.BackStackEntryCount > 0)
                    SupportActionBar.SetDisplayHomeAsUpEnabled(true);
                else SupportActionBar.SetDisplayHomeAsUpEnabled(false);
            };
        }
        
    }
}