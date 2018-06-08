using Android.App;
using Android.OS;
using Android.Views;
using BluetoothAPP.Model;

namespace BluetoothAPP.Fragments
{
    public class EditFragment : Fragment
    {
        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            BluetoothHolder.activity = this.Activity;
            var view = inflater.Inflate(Resource.Layout.EditLayout, container, false);
            
            return view;
        }
    }
}