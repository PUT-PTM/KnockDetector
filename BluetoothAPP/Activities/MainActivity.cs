using Android.App;
using Android.Widget;
using Android.OS;
using Android.Support.V7.App;

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
            toolbar.Title = "Hello from Xamarin Android!";
            SetSupportActionBar(toolbar);
            SupportActionBar.SetDisplayHomeAsUpEnabled(true);
            toolbar.NavigationClick += (s, e) =>
            {
                OnBackPressed();
            };

            FragmentTransaction fragmentTransaction = FragmentManager.BeginTransaction();
            MainFragment mainFragment = new MainFragment();
            fragmentTransaction.Add(Resource.Id.fragment_container, mainFragment, "MAIN_FRAGMENT");
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

