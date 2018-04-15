using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using BluetoothAPP.Model;

namespace BluetoothAPP.Adapters
{
    public class ProductsListAdapter : BaseAdapter<Product>
    {
        private IList<Product> _productsList;
        private Activity _context;

        public ProductsListAdapter(Activity context, IList<Product> productsList)
        {
            _context = context;
            _productsList = productsList;
        }
        public override Product this[int position]
        {
            get
            {
                return _productsList[position];
            }
        }
        public override int Count
        {
            get
            {
                return _productsList.Count;
            }
        }
        public override long GetItemId(int position)
        {
            return position;
        }

        public override View GetView(int position, View convertView, ViewGroup parent)
        {
            ProductViewHolder holder;
            var product = _productsList[position];


            if (convertView == null)
            {
                convertView = _context.LayoutInflater.Inflate(Resource.Layout.ProductRow, null);
                holder = new ProductViewHolder(convertView.FindViewById<TextView>(Resource.Id.ProductNameTextView), convertView.FindViewById<ImageView>(Resource.Id.ProductPictureImageView));
                convertView.Tag = holder;
            }
            else holder = (ProductViewHolder)convertView.Tag;

            holder.ProductNameTextView.Text = product.Name1;
            int imageResourceId = _context.Resources.GetIdentifier(product.Image1, "drawable", _context.PackageName);
            holder.ProductPictureImageView.SetImageResource(imageResourceId);

            return convertView;
        }
    }

    public class ProductViewHolder : Java.Lang.Object
    {
        public TextView ProductNameTextView;
        public ImageView ProductPictureImageView;

        public ProductViewHolder(TextView text, ImageView img)
        {
            ProductNameTextView = text;
            ProductPictureImageView = img;
        }
    }
}