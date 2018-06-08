using Android.App;
using Android.Widget;
using Android.OS;
using Android.Support.V7.App;
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
        LinearLayout layout;
        Button login;
        EditText username;
        EditText password;
        Android.Support.V7.Widget.Toolbar toolbar;

        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
            SetContentView(Resource.Layout.MainActivity);
            OnCreateConfig();
            
            BluetoothHolder.bluetoothManage.BtnConnect_Click();
            BluetoothHolder.bluetoothManage.Write(DatabaseHolder.GETDB);
            
            toolbar.NavigationClick += (s, e) =>
            {
                OnBackPressed();
            };
            login.Click += (s, e) =>
            {
                btnLoginClick(s, e, username, password);
            };
            layout.Click += mRelativeLayout_Click;

        }

        private void OnCreateConfig()
        {
            BluetoothHolder.activity = this;

            layout = FindViewById<LinearLayout>(Resource.Id.loginLayout);
            toolbar = FindViewById<Android.Support.V7.Widget.Toolbar>(Resource.Id.toolbar);
            login = FindViewById<Button>(Resource.Id.Login);
            username = FindViewById<EditText>(Resource.Id.NazwaUzytkownika);
            password = FindViewById<EditText>(Resource.Id.Haslo);
            username.Hint = "Username";
            password.Hint = "Password";

            toolbar.Title = "Knock Detector";
            SetSupportActionBar(toolbar);
            SupportActionBar.SetDisplayHomeAsUpEnabled(false);
        }

        void mRelativeLayout_Click(object sender, EventArgs e)
        {
            InputMethodManager inputManager = (InputMethodManager)this.GetSystemService(Activity.InputMethodService);
            inputManager.HideSoftInputFromWindow(this.CurrentFocus.WindowToken, HideSoftInputFlags.None);
        }

        public void btnLoginClick(object sender, EventArgs e, EditText username, EditText password)
        {
            BluetoothHolder.bluetoothManage.Read();
            if (username.Text == "admin" && password.Text == "admin")
            {
                var nextActivity = new Intent(this, typeof(UsersActivity));
                StartActivity(nextActivity);
            }
        }
    }
}

