using Android.App;
using Android.Widget;
using Android.OS;
using Android.Support.V7.App;
using BluetoothAPP.Fragments;
using Android.Content;
using BluetoothAPP.Activities;

namespace BluetoothAPP
{
    [Activity(Label = "BluetoothAPP", MainLauncher = true, Icon = "@drawable/Lock")]
    public class MainActivity : AppCompatActivity
    {
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Set our view from the "main" layout resource
            SetContentView(Resource.Layout.MainActivity);

            var toolbar = FindViewById<Android.Support.V7.Widget.Toolbar>(Resource.Id.toolbar);
            toolbar.Title = "Knock Detector";
            SetSupportActionBar(toolbar);
            SupportActionBar.SetDisplayHomeAsUpEnabled(false);
            toolbar.NavigationClick += (s, e) =>
            {
               OnBackPressed();
            };

            //FragmentTransaction fragmentTransaction = FragmentManager.BeginTransaction();
            //MainFragment mainFragment = new MainFragment();
            //fragmentTransaction.Add(Resource.Id.fragment_container, mainFragment, "MAIN_FRAGMENT");
            //fragmentTransaction.Commit();

            //FragmentManager.BackStackChanged += (s, e) =>
            //{
             //   if (FragmentManager.BackStackEntryCount > 0)
              //      SupportActionBar.SetDisplayHomeAsUpEnabled(true);
               // else SupportActionBar.SetDisplayHomeAsUpEnabled(false);

            //};

            var username = FindViewById<EditText>(Resource.Id.NazwaUzytkownika);
            var password = FindViewById<EditText>(Resource.Id.Haslo);
            var login = FindViewById<Button>(Resource.Id.Login);
            username.Hint = "Username";
            password.Hint = "Password";

            login.Click += (s, e) =>
            {
                if (username.Text == "admin" && password.Text == "admin")
                {

                    var nextActivity = new Intent(this, typeof(UsersActivity));
                    StartActivity(nextActivity);
                }
            };
            }
    }
}

