using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;
using BluetoothAPP.Activities;
using BluetoothAPP.Adapters;
using BluetoothAPP.Model;
using Java.Lang;
using Java.Util;

namespace BluetoothAPP.Fragments
{
    public class UsersFragment : Fragment
    {
        List<User> users = new List<User>();
        ListView usersList;
        TextView actualUsername;
        ImageButton microphoneBtn;
        ImageButton editBtn;
        ImageButton deleteBtn;
        ImageView addUser;
        EditText newUserName;
        Button acceptBtn;
        Button OKBtn;
        static int counterForItemClick = 0;
        static bool flagIsFirstUpload = true;

        Android.Support.V7.App.AlertDialog alertDialogAndroid;
        Android.Support.V7.App.AlertDialog.Builder alertDialogBuilder;

        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {
            var view = inflater.Inflate(Resource.Layout.UsersFragment, container, false);
            usersList = view.FindViewById<ListView>(Resource.Id.myListView);
            addUser = view.FindViewById<ImageView>(Resource.Id.addUser);

            addUser.Click += AddUser_Click;

            if (flagIsFirstUpload)
            {
                if (DatabaseHolder.CODE() == "OK")
                {
                    if (uploadingDatabase())
                    {
                        UsersViewAdapter adapter = new UsersViewAdapter(this.Activity, users);
                        usersList.Adapter = adapter;

                        counterForItemClick++;
                        usersList.ItemClick += UsersList_ItemClick;
                    }
                }
                else if (DatabaseHolder.CODE() == "ER")
                    Toast.MakeText(this.Activity, "ERROR WHILE UPLOADING A DATABASE!", ToastLength.Long).Show();
                flagIsFirstUpload = false;
            }
            else
            {
                UsersViewAdapter adapter = new UsersViewAdapter(this.Activity, users);
                usersList.Adapter = adapter;

                counterForItemClick++;
                usersList.ItemClick += UsersList_ItemClick;
            }
            
            return view;
        }

        private void AddUser_Click(object sender, EventArgs e)
        {
            LayoutInflater layoutInflater = LayoutInflater.From(this.Activity);
            var view = layoutInflater.Inflate(Resource.Layout.AddDialog, null);
            newUserName = view.FindViewById<EditText>(Resource.Id.userNew);
            acceptBtn = view.FindViewById<Button>(Resource.Id.acceptButton);

            alertDialogBuilder = new Android.Support.V7.App.AlertDialog.Builder(this.Activity);
            alertDialogBuilder.SetView(view);

            alertDialogAndroid = alertDialogBuilder.Create();
            alertDialogAndroid.Show();
            
            acceptBtn.Click += (s, p) =>
            {

                if (newUserName.Text == "")
                {
                    Toast.MakeText(this.Activity, "You have to type a name first!", ToastLength.Long).Show();
                }
                else
                {
                    User user = new User();
                    string name = newUserName.Text;
                    string date = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss");


                    //string str = DatabaseHolder.ADDUS + DatabaseHolder.parsingChars() + toStringFromCharArr(user.Creation_date) + '\a';
                    string str = "ADDUS\a";
                    BluetoothHolder.bluetoothManage.Write("GETDB\a");
                    alertDialogAndroid.Dismiss();


                    LayoutInflater layoutInflaterr = LayoutInflater.From(this.Activity);
                    var vieww = layoutInflaterr.Inflate(Resource.Layout.OKDialog, null);
                    OKBtn = vieww.FindViewById<Button>(Resource.Id.OKButton);

                    alertDialogBuilder = new Android.Support.V7.App.AlertDialog.Builder(this.Activity);
                    alertDialogBuilder.SetView(vieww);

                    alertDialogAndroid = alertDialogBuilder.Create();
                    alertDialogAndroid.Show();


                    OKBtn.Click += (x, y) =>
                    {
                        BluetoothHolder.bluetoothManage.Read();
                        Toast.MakeText(this.Activity, "Received: " + DatabaseHolder.receiver, ToastLength.Long).Show();

                        if (DatabaseHolder.CODE() == "OK")
                        {
                            //Toast.MakeText(this.Activity, "Received: " + DatabaseHolder.receiver, ToastLength.Long).Show();
                            uploadingDatabase();

                            UsersViewAdapter adapter = new UsersViewAdapter(this.Activity, users);
                            usersList.Adapter = adapter;

                            
                            if (counterForItemClick == 0)
                            {
                                usersList.ItemClick += UsersList_ItemClick;
                            }
                            counterForItemClick++;
                        }
                        else if (DatabaseHolder.CODE() == "ER")
                            Toast.MakeText(this.Activity, "There was an error while uploading a database!", ToastLength.Long).Show();
                        else Toast.MakeText(this.Activity, "UNKNOWN ERROR - RECEIVED MSG:'" + DatabaseHolder.receiver + "'", ToastLength.Long).Show();
                        
                    };


                }
            };

        }
        

        private void UsersList_ItemClick(object sender, AdapterView.ItemClickEventArgs e)
        {
            LayoutInflater layoutInflater = LayoutInflater.From(this.Activity);
            var view = layoutInflater.Inflate(Resource.Layout.Dialog, null);
            actualUsername = view.FindViewById<TextView>(Resource.Id.actualUserName);
            editBtn = view.FindViewById<ImageButton>(Resource.Id.editButton);
            microphoneBtn = view.FindViewById<ImageButton>(Resource.Id.microphoneButton);
            deleteBtn = view.FindViewById<ImageButton>(Resource.Id.deleteButton);


            alertDialogBuilder = new Android.Support.V7.App.AlertDialog.Builder(this.Activity);
            alertDialogBuilder.SetView(view);

            alertDialogAndroid = alertDialogBuilder.Create();
            alertDialogAndroid.Show();

            actualUsername.Text = users[e.Position].nameToString();

            editBtn.Click += EditBtn_Click;
            deleteBtn.Click += (s, p) =>
            {
                alertDialogAndroid.Dismiss();

                FragmentTransaction transaction = FragmentManager.BeginTransaction();
                DeleteFragment deleteFragment = new DeleteFragment();
                transaction.Replace(Resource.Id.container, deleteFragment, "DELETE_FRAGMENT");
                transaction.AddToBackStack("DELETE_FRAGMENT");

                Bundle bundle = new Bundle();
                bundle.PutStringArrayList("LIST", getAllNames());
                deleteFragment.Arguments = bundle;

                transaction.Commit();
            };
            microphoneBtn.Click += (s, p) =>
            {
                alertDialogAndroid.Dismiss();

                FragmentTransaction transaction = FragmentManager.BeginTransaction();
                MicrophoneFragment microphoneFragment = new MicrophoneFragment();
                transaction.Replace(Resource.Id.container, microphoneFragment, "MICROPHONE_FRAGMENT");
                transaction.AddToBackStack("MICROPHONE_FRAGMENT");

                Bundle bundle = new Bundle();
                bundle.PutString("ID", users[e.Position].Id.ToString());
                microphoneFragment.Arguments = bundle;

                transaction.Commit();
            };
        }

        private void MicrophoneBtn_Click(object sender, EventArgs e)
        {
            alertDialogAndroid.Dismiss();
            FragmentTransaction transaction = FragmentManager.BeginTransaction();
            MicrophoneFragment microphoneFragment = new MicrophoneFragment();
            transaction.Replace(Resource.Id.container, microphoneFragment, "MICROPHONE_FRAGMENT");
            transaction.AddToBackStack("MICROPHONE_FRAGMENT");
            transaction.Commit();
        }

        private void DeleteBtn_Click(object sender, EventArgs e)
        {
            alertDialogAndroid.Dismiss();
            FragmentTransaction transaction = FragmentManager.BeginTransaction();
            DeleteFragment deleteFragment = new DeleteFragment();
            transaction.Replace(Resource.Id.container, deleteFragment, "DELETE_FRAGMENT");
            transaction.AddToBackStack("DELETE_FRAGMENT");
            transaction.Commit();
        }

        private void EditBtn_Click(object sender, EventArgs e)
        {
            alertDialogAndroid.Dismiss();
            FragmentTransaction transaction = FragmentManager.BeginTransaction();
            EditFragment editFragment = new EditFragment();
            transaction.Replace(Resource.Id.container, editFragment, "EDIT_FRAGMENT");
            transaction.AddToBackStack("EDIT_FRAGMENT");
            transaction.Commit();
        }

        void creatingUser(int i)
        {
            User user;
            if (i == 0)
            {
                user = new User
                {
                    Id = DatabaseHolder.parsingId(2, 3),
                    Name = DatabaseHolder.parsingChars(4),
                    Creation_date = DatabaseHolder.parsingChars(24),
                    Secret_code = DatabaseHolder.holdingString[44]
                };
            }
            else
            {
                user = new User
                {
                    Id = DatabaseHolder.parsingId((46 * i), (42 * i) + 1),
                    Name = DatabaseHolder.parsingChars((42 * i) + 4),
                    Creation_date = DatabaseHolder.parsingChars((42 * i) + 24),
                    Secret_code = DatabaseHolder.holdingString[(42 * i) + 44]
                };
            }
            //string name = user.nameToString();
            //string creation_date = user.creationDateToString();
            //string secret_code = user.Secret_code.ToString();
            users.Add(user);
        }



        bool uploadingDatabase()
        {
            users.Clear();
            if (DatabaseHolder.howManyUsers() == 0)
                return false;

            DatabaseHolder.receiverToHoldingString();
            for (int i = 0; i < DatabaseHolder.howManyUsers(); i++)
            {
                creatingUser(i);
            }

            //DatabaseHolder.holdingString[0] = '\0';
            //DatabaseHolder.flushHolder();
            return true;
        }

        List<string> getAllNames()
        {
            List<string> list = new List<string>();
            for (int i = 0; i < DatabaseHolder.howManyUsers(); i++)
            {
                list.Add(users[i].nameToString());
            }
            return list;
        }

        private char[] toCharArr(string str)
        {
            char[] arr = new char[20];
            for(int i =0; i < str.Length; i++)
            {
                arr[i] = str[i];
            }
            if (str.Length < 20)
            {
                for (int i = str.Length; i < 20; i++)
                {
                    arr[i] = '\0';
                }
            }
            return arr;
        }

        private string toStringFromCharArr(char[] arr)
        {
            string str = "";
            for(int i =0; i < 20; i++)
            {
                str += arr[i];
            }
            return str;
        }
    }
}