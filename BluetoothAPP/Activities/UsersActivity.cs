﻿using System;
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
using BluetoothAPP.Fragments;

namespace BluetoothAPP.Activities
{
    [Activity(Label = "UsersActivity")]
    public class UsersActivity : AppCompatActivity
    {
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
            SetContentView(Resource.Layout.UsersActivity);

            var toolbar = FindViewById<Android.Support.V7.Widget.Toolbar>(Resource.Id.userToolbar);
            toolbar.Title = "Knock Detector";
            SetSupportActionBar(toolbar);
            SupportActionBar.SetDisplayHomeAsUpEnabled(true);
            toolbar.NavigationClick += (s, e) =>
            {
                OnBackPressed();
            };

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



        }
    }
}