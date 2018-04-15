using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;
using BluetoothAPP.Adapters;
using BluetoothAPP.Model;

namespace BluetoothAPP.Fragments
{
    public class MainFragment : Fragment
    {
        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Create your fragment here
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            var mainView = inflater.Inflate(Resource.Layout.MainFragment, container, false);
            var productsListView = mainView.FindViewById<ListView>(Resource.Id.ProductsListView);

            var products = CreateProductsList();

            ProductsListAdapter adapter = new ProductsListAdapter(Activity, products);
            productsListView.Adapter = adapter;
            productsListView.ItemClick += (s, e) =>
            {
                var selectedProduct = products[e.Position];
                FragmentTransaction fragmentTransaction = FragmentManager.BeginTransaction();
                DetailsFragment detailsFragment = new DetailsFragment();
                detailsFragment.SelectedProduct = selectedProduct;

                fragmentTransaction.Replace(Resource.Id.fragment_container, detailsFragment, "DETAILS_FRAGMENT");
                fragmentTransaction.AddToBackStack("DETAILS_FRAGMENT");
                fragmentTransaction.Commit();

            };
            return mainView;
        }

        private IList<Product> CreateProductsList()
        {
            return new List<Product>()
            {
                new Product()
                {
                    Name1 = "Nowy produkt 1",
                    Image1 = "xamarin"
                },
                new Product()
                {
                    Name1 = "Nowy produkt 2",
                    Image1 = "xamarin"
                },
                new Product()
                {
                    Name1 = "Nowy produkt 3",
                    Image1 = "xamarin"
                }
            };
        }

    }
}