using System;
using System.Collections.Generic;
using Android.App;
using Android.OS;
using Android.Views;
using Android.Widget;
using BluetoothAPP.Adapters;
using BluetoothAPP.Model;
using Java.Lang;

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
        Button AccBtn;
        Button uploadBtn;
        Button uploadBtnOK;

        Android.Support.V7.App.AlertDialog alertDialogAndroid;
        Android.Support.V7.App.AlertDialog.Builder alertDialogBuilder;

        public override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
        }

        public override View OnCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
        {

            var view = inflater.Inflate(Resource.Layout.UsersFragment, container, false);
            OnCreateViewConfig(view);
            return view;
        }

        private void AddUser_Click(object sender, EventArgs e)
        {
            LayoutInflater layoutInflater = LayoutInflater.From(this.Activity);
            var view = layoutInflater.Inflate(Resource.Layout.AddDialog, null);
            AddUser_ClickConfig(view);
            acceptBtn.Click += AcceptBtn_Click;
        }

        private void AcceptBtn_Click(object sender, EventArgs p)
        {
            DatabaseHolder.receiver = "";
            WrittenNameCheck();
        }

        private void AccBtn_Click(object sender, EventArgs p)
        {
            BluetoothHolder.bluetoothManage.Read();
            OKBtn.Enabled = true;
            AccBtn.Enabled = false;

            if (DatabaseHolder.CODE() == "OK")
            {
                Toast.MakeText(this.Activity, "Received: " + DatabaseHolder.receiver, ToastLength.Long).Show();
            }
            else if (DatabaseHolder.CODE() == "ER")
                Toast.MakeText(this.Activity, "There was an error while uploading a database!", ToastLength.Long).Show();
            else Toast.MakeText(this.Activity, "UNKNOWN ERROR - RECEIVED MSG:'" + DatabaseHolder.receiver + "'", ToastLength.Long).Show();
            alertDialogAndroid.Dismiss();
        }

        private void OKBtn_Click(object sender, EventArgs e)
        {
            BluetoothHolder.bluetoothManage.Read();
            if (DatabaseHolder.CODE() == "OK")
            {
                Toast.MakeText(this.Activity, "Received: " + DatabaseHolder.receiver, ToastLength.Long).Show();

                UploadingDatabase();

                UsersViewAdapter adapter = new UsersViewAdapter(this.Activity, users);
                usersList.Adapter = adapter;
            }
            alertDialogAndroid.Dismiss();
        }

        private void UsersList_ItemClick(object sender, AdapterView.ItemClickEventArgs e)
        {
            LayoutInflater layoutInflater = LayoutInflater.From(this.Activity);
            var view = layoutInflater.Inflate(Resource.Layout.Dialog, null);
            UsersList_ItemClickConfig(view); 
            
            actualUsername.Text = users[e.Position].NameToString();

            editBtn.Click += EditBtn_Click;
            deleteBtn.Click += (s, p) =>
            {
                DeleteBtn_Click(s, p, e);
            };
            microphoneBtn.Click += (s, p) =>
            {
                MicrophoneBtn_Click(s, p, e);
            };
        }
        

        private void MicrophoneBtn_Click(object sender, EventArgs p, AdapterView.ItemClickEventArgs e)
        {
            alertDialogAndroid.Dismiss();
            LayoutInflater layoutInflater = LayoutInflater.From(this.Activity);
            var view = layoutInflater.Inflate(Resource.Layout.OKDialog, null);
            Delete_ClickConfig(view, "Record your code now!");
            
            OKBtn.Enabled = false;
            BluetoothHolder.bluetoothManage.Write(DatabaseHolder.RECCD);
            DatabaseHolder.receiver = "";
            AccBtn.Click += (s, c) =>
            {
                AccBtn_Click2(s, c, e);
            };
            OKBtn.Click += OKBtn_Click1;
        }

        private void DeleteBtn_Click(object sender, EventArgs p, AdapterView.ItemClickEventArgs e)
        {
            alertDialogAndroid.Dismiss();
            LayoutInflater layoutInflater = LayoutInflater.From(this.Activity);
            var view = layoutInflater.Inflate(Resource.Layout.OKDialog, null);
            Delete_ClickConfig(view, "User has been deleted!");

            char[] ar = new char[2];
            ar = DatabaseHolder.IntToCharArr(users[e.Position].Id);
            OKBtn.Enabled = false;
            BluetoothHolder.bluetoothManage.Write(DatabaseHolder.DELUS + ar[0] + ar[1] + '\a');
            DatabaseHolder.receiver = "";
            AccBtn.Click += AccBtn_Click1;
        }

        private void OKBtn_Click1(object sender, EventArgs e)
        {
            BluetoothHolder.bluetoothManage.Read();
            if (DatabaseHolder.CODE() == "OK")
            {
                Toast.MakeText(this.Activity, "Received: " + DatabaseHolder.receiver, ToastLength.Long).Show();
                DatabaseHolder.receiver = "";
            }
            else Toast.MakeText(this.Activity, "Received: " + DatabaseHolder.receiver, ToastLength.Long).Show();
            alertDialogAndroid.Dismiss();
        }

        private void AccBtn_Click2(object sender, EventArgs e, AdapterView.ItemClickEventArgs p)
        {
            BluetoothHolder.bluetoothManage.Read();
            OKBtn.Enabled = true;
            AccBtn.Enabled = false;

            if (DatabaseHolder.CODE() == "OK")
            {
                Toast.MakeText(this.Activity, "Received: " + DatabaseHolder.receiver, ToastLength.Long).Show();

                char[] ar = new char[2];
                ar = DatabaseHolder.IntToCharArr(users[p.Position].Id);
                DatabaseHolder.receiver = "";
                BluetoothHolder.bluetoothManage.Write(DatabaseHolder.CHNCD + ar[0] + ar[1] + '\a');

                //while (DatabaseHolder.receiver.Length < 3)
                    //BluetoothHolder.bluetoothManage.Read();
                //Toast.MakeText(this.Activity, "Received: " + DatabaseHolder.receiver, ToastLength.Long).Show();
                //DatabaseHolder.receiver = "";
                //BluetoothHolder.bluetoothManage.Write(DatabaseHolder.GETDB);
                
            }
            else if (DatabaseHolder.CODE() == "ER")
                Toast.MakeText(this.Activity, "There was an error while uploading a database!", ToastLength.Long).Show();
            else Toast.MakeText(this.Activity, "UNKNOWN ERROR - RECEIVED MSG:'" + DatabaseHolder.receiver + "'", ToastLength.Long).Show();
        }

        private void AccBtn_Click1(object sender, EventArgs e)
        {
            BluetoothHolder.bluetoothManage.Read();
            OKBtn.Enabled = true;
            AccBtn.Enabled = false;

            if (DatabaseHolder.CODE() == "OK")
            {
                Toast.MakeText(this.Activity, "Received: " + DatabaseHolder.receiver, ToastLength.Long).Show();

                DatabaseHolder.receiver = "";
                //BluetoothHolder.bluetoothManage.Write(DatabaseHolder.GETDB);
            }
            else if (DatabaseHolder.CODE() == "ER")
                Toast.MakeText(this.Activity, "There was an error while uploading a database!", ToastLength.Long).Show();
            else Toast.MakeText(this.Activity, "UNKNOWN ERROR - RECEIVED MSG:'" + DatabaseHolder.receiver + "'", ToastLength.Long).Show();
            alertDialogAndroid.Dismiss();
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

        private void CreatingUser(int i)
        {
            int offset = 2;
            User user = new User
            {
                Id = DatabaseHolder.ParsingId(offset + (43 * i), offset + (43 * i) + 1),
                Name = DatabaseHolder.ParsingChars(offset + (43 * i)+2),
                Creation_date = DatabaseHolder.ParsingChars(offset + (43 * i) + 22),
            };
            user.Secret_code[0] = DatabaseHolder.receiver[offset + (43 * i) + 42];
            users.Add(user);
        }



        private bool UploadingDatabase()
        {
            users.Clear();
            if (DatabaseHolder.HowManyUsers() == 0)
                return false;

            //DatabaseHolder.ReceiverToHoldingString();
            for (int i = 0; i < DatabaseHolder.HowManyUsers(); i++)
            {
                CreatingUser(i);
            }
            return true;
        }

        private void UploadingUsersList()
        {
            BluetoothHolder.bluetoothManage.Read();
            if (DatabaseHolder.CODE() == null)
            {
                Toast.MakeText(this.Activity, "ERROR, RECEIVED MESSAGE HAS WRONG FORMAT", ToastLength.Long).Show();
            }
            else if (DatabaseHolder.CODE() == "OK")
            {
                if (UploadingDatabase())
                {
                    UsersViewAdapter adapter = new UsersViewAdapter(this.Activity, users);
                    usersList.Adapter = adapter;
                }
            }
            else if (DatabaseHolder.CODE() == "ER")
                Toast.MakeText(this.Activity, "ERROR WHILE UPLOADING A DATABASE!", ToastLength.Long).Show();
        }


        private void WrittenNameCheck()
        {
            if (newUserName.Text == "")
            {
                Toast.MakeText(this.Activity, "You have to type a name first!", ToastLength.Long).Show();
            }
            else
            {
                string msgToSend = "";
                if (newUserName.Text.Length <= 20)
                {
                    msgToSend = StringToSend();
                    BluetoothHolder.bluetoothManage.Write(msgToSend);
                    alertDialogAndroid.Dismiss();

                    LayoutInflater layoutInflaterr = LayoutInflater.From(this.Activity);
                    var vieww = layoutInflaterr.Inflate(Resource.Layout.OKDialog, null);

                    AccBtn_ClickConfig(vieww);
                    AccBtn.Click += AccBtn_Click;
                    //OKBtn.Click += OKBtn_Click;
                }
                else if (newUserName.Text.Length > 20)
                {
                    Toast.MakeText(this.Activity, "User name too long! (MAX 20 CHARACTERS)", ToastLength.Long).Show();
                }
            }
        }

        private List<string> GetAllNames()
        {
            List<string> list = new List<string>();
            for (int i = 0; i < DatabaseHolder.HowManyUsers(); i++)
            {
                list.Add(users[i].NameToString());
            }
            return list;
        }

        private string StringTo20ElementString(string str)
        {
            string arr = "";
            for(int i =0; i < str.Length; i++)
            {
                arr += str[i];
            }
            for (int i = str.Length; i < 20; i++)
            {
                arr += '#';
            }
            return arr;
        }

        private string StringToSend()
        {
            string name = StringTo20ElementString(newUserName.Text);
            string date = StringTo20ElementString(DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss"));
            return DatabaseHolder.ADDUS + name + date + '\a';
        }

        private IList<Integer> PutIdsList()
        {
            IList<Integer> list = new List<Integer>();
            for(int i =0; i < users.Count; i++)
            {
                list.Add((Integer)users[i].Id);
            }
            return list;
        }

        private void OnCreateViewConfig(View view)
        {
            BluetoothHolder.activity = this.Activity;
            usersList = view.FindViewById<ListView>(Resource.Id.myListView);
            addUser = view.FindViewById<ImageView>(Resource.Id.addUser);
            uploadBtn = view.FindViewById<Button>(Resource.Id.uploadButton);

            if (!addUser.HasOnClickListeners)
            {
                addUser.Click += AddUser_Click;
            }

            if (!usersList.HasOnClickListeners)
            {
                usersList.ItemClick += UsersList_ItemClick;
            }

            if (!uploadBtn.HasOnClickListeners)
            {
                uploadBtn.Click += UploadBtn_Click;
            }

        }

        private void UploadBtn_Click(object sender, EventArgs e)
        {
            DatabaseHolder.receiver = "";
            BluetoothHolder.bluetoothManage.Write(DatabaseHolder.GETDB);

            LayoutInflater layoutInflaterr = LayoutInflater.From(this.Activity);
            var vieww = layoutInflaterr.Inflate(Resource.Layout.UploadDialog, null);
            uploadBtnOK = vieww.FindViewById<Button>(Resource.Id.UploadButtonOK);

            alertDialogBuilder = new Android.Support.V7.App.AlertDialog.Builder(this.Activity);
            alertDialogBuilder.SetView(vieww);

            alertDialogAndroid = alertDialogBuilder.Create();
            alertDialogAndroid.Show();

            uploadBtnOK.Click += UploadBtnOK_Click;

        }

        private void UploadBtnOK_Click(object sender, EventArgs e)
        {
            UploadingUsersList();
            alertDialogAndroid.Dismiss();
        }

        private void Delete_ClickConfig(View view, string txt)
        {
            newUserName = view.FindViewById<EditText>(Resource.Id.userNew);
            AccBtn = view.FindViewById<Button>(Resource.Id.AccButton);
            OKBtn = view.FindViewById<Button>(Resource.Id.OkButton);
            TextView text = view.FindViewById<TextView>(Resource.Id.justTextAdd1);

            text.Text = txt;

            alertDialogBuilder = new Android.Support.V7.App.AlertDialog.Builder(this.Activity);
            alertDialogBuilder.SetView(view);

            alertDialogAndroid = alertDialogBuilder.Create();
            alertDialogAndroid.Show();
        }

        private void AddUser_ClickConfig(View view)
        {
            newUserName = view.FindViewById<EditText>(Resource.Id.userNew);
            acceptBtn = view.FindViewById<Button>(Resource.Id.acceptButton);

            alertDialogBuilder = new Android.Support.V7.App.AlertDialog.Builder(this.Activity);
            alertDialogBuilder.SetView(view);

            alertDialogAndroid = alertDialogBuilder.Create();
            alertDialogAndroid.Show();
        }

        private void AccBtn_ClickConfig(View vieww)
        {
            AccBtn = vieww.FindViewById<Button>(Resource.Id.AccButton);
            OKBtn = vieww.FindViewById<Button>(Resource.Id.OkButton);

            alertDialogBuilder = new Android.Support.V7.App.AlertDialog.Builder(this.Activity);
            alertDialogBuilder.SetView(vieww);

            alertDialogAndroid = alertDialogBuilder.Create();
            alertDialogAndroid.Show();
            OKBtn.Enabled = false;
        }

        private void UsersList_ItemClickConfig(View view)
        {
            actualUsername = view.FindViewById<TextView>(Resource.Id.actualUserName);
            editBtn = view.FindViewById<ImageButton>(Resource.Id.editButton);
            microphoneBtn = view.FindViewById<ImageButton>(Resource.Id.microphoneButton);
            deleteBtn = view.FindViewById<ImageButton>(Resource.Id.deleteButton);

            alertDialogBuilder = new Android.Support.V7.App.AlertDialog.Builder(this.Activity);
            alertDialogBuilder.SetView(view);

            alertDialogAndroid = alertDialogBuilder.Create();
            alertDialogAndroid.Show();
        }
    }
}