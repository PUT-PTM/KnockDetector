using Android.App;
using Android.Widget;
using Android.OS;
using Android.Support.V7.App;
using BluetoothAPP.Fragments;
using Android.Content;
using BluetoothAPP.Activities;
using System;
using Android.Views.InputMethods;
using BluetoothAPP.Model;

namespace BluetoothAPP
{
    [Activity(Label = "BluetoothAPP", MainLauncher = true, Icon = "@drawable/Lock")]
    public class MainActivity : AppCompatActivity
    {
        
        Button login;
        EditText username;
        EditText password;
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
             
            SetContentView(Resource.Layout.MainActivity);

            var layout = FindViewById<LinearLayout>(Resource.Id.loginLayout);
            var toolbar = FindViewById<Android.Support.V7.Widget.Toolbar>(Resource.Id.toolbar);
            login = FindViewById<Button>(Resource.Id.Login);
            username = FindViewById<EditText>(Resource.Id.NazwaUzytkownika);
            password = FindViewById<EditText>(Resource.Id.Haslo);
            username.Hint = "Username";
            password.Hint = "Password";


            toolbar.Title = "Knock Detector";
            SetSupportActionBar(toolbar);
            SupportActionBar.SetDisplayHomeAsUpEnabled(false);
            toolbar.NavigationClick += (s, e) =>
            {
               OnBackPressed();
            };
            
            BluetoothHolder.bluetoothManage.BtnConnect_Click();
            BluetoothHolder.bluetoothManage.Write(DatabaseHolder.GETDB);


            login.Click += (s, e) =>
            {
                btnLoginClick(s, e, username, password);
            };

            layout.Click += mRelativeLayout_Click;

        }

        void mRelativeLayout_Click(object sender, EventArgs e)
        {
            InputMethodManager inputManager = (InputMethodManager)this.GetSystemService(Activity.InputMethodService);
            inputManager.HideSoftInputFromWindow(this.CurrentFocus.WindowToken, HideSoftInputFlags.None);
        }

        public void btnLoginClick(object sender, EventArgs e, EditText username, EditText password)
        {
            
            if (username.Text == "admin" && password.Text == "admin")
            {
                BluetoothHolder.bluetoothManage.Read();
                var nextActivity = new Intent(this, typeof(UsersActivity));
                StartActivity(nextActivity);
                
            }
        }
    }
}

