#include<iostream>
#include<conio.h>
#include<fstream>
#include<process.h>
using namespace std;

class Product{
    public:
        int Pd_id;
        string Pd_name;
        float Pd_price;
        float Pd_tax;
        float Pd_discount;
        int Pd_quantity;

        void create_product(){
            cout << "\n Please Enter The Product No. #";
            cin >> Pd_id;
            cout<<" \n Enter Product name : ";
            cin>>Pd_name;
            cout<<"\n Enter the Price: ";
            cin>>Pd_price;
            cout<<"\n Enter the Quantity:";
            cin>>Pd_quantity;
            cout<<"\n Enter the Tax:";
            cin>>Pd_tax;
            cout<<"\n Enter the Discount:";
            cin>>Pd_discount;
        };

        void display_product(){
            cout<<"The Product No."<<Pd_id<<endl;
            cout<<"The Product Name is "<<Pd_name<<endl;
            cout<< "Quantity: "<<Pd_quantity<<endl;
            cout<< "Discount: "<< Pd_discount<<endl;
            cout<<"Amount: "<<Pd_price<<endl;
            cout<<"Tax: "<<Pd_tax<<endl;
        }
        int Pno()
        {
            return Pd_id;
        }
        string getName()
        {
            return Pd_name;
        }
        float getprice()
        {
            return Pd_price;
        }
        float getdisc()
        {
            return Pd_discount;
        }
        float gettax()
        {
            return Pd_tax;
        }

};


fstream mfile;
Product mproduct;

void make_product(){
    mfile.open("Products.txt", ios::out|ios::app);
    mproduct.create_product();
    mfile.write((char*) & mproduct, sizeof(Product));
    mfile.close();
    cout<<"\n \t\t*************** Product has been created***********************\t\t\n";
    getchar();
}

void displayProducts(){
    //clrscr();
    cout<<"\n \t\t ******************* LIST OF PRODUCTS IN SHELVEs*********************\n";
    mfile.open("Products.txt", ios::in);
    while (mfile.read((char*) &mproduct, sizeof(Product)))
    {
        mproduct.display_product();
        cout<<"\n ************************************************************************";
        getch();
    }
    mfile.close();
    getchar();
}

void update_product(){
    //clrscr();
    int i;
    bool found=false;
    cout<<" \n Enter the Product Number: ";
    cin>>i;
    //clrscr();
    mfile.open("Products.txt", ios::in|ios::out);
    while(mfile.read((char*) &mproduct, sizeof(Product))&& found==false)
    {
        if(mproduct.Pno() ==i)
        {
            mproduct.display_product();
            cout<<"\n\n ..........Enter the new Details to Update.........";
            mproduct.create_product();
            int pos= -1*sizeof(mproduct);
            mfile.seekp(pos,ios::cur);
            mfile.write((char*) &mproduct, sizeof(Product));
            cout<<"\n\n ************* You've Successfully Updated ************";
            found= true;
        }
    }
    mfile.close();
    if (found==false)
    {
        cout<<"\n Product Record Does not exist**";
    }
    getch();
}

void delete_product()
{
    //clrscr();
    int no;
    cout<<"\n Enter the product number of the product you want to delete: ";
    cin>> no;
    mfile.open("Products.txt", ios::out|ios::in);
    fstream mfile2;
    mfile2.open("delete.txt", ios::out);
    mfile.seekg(0,ios::beg);
    while(mfile.read((char*) &mproduct, sizeof(Product)))
    {
        if(mproduct.Pno()!=no)
        {
            mfile2.write((char*) &mproduct, sizeof(Product));
        }
    }
    mfile2.close();
    mfile.close();
    remove("Products.txt");
    rename("delete.txt","Products.txt");
    cout<<"\n Product Successfully Deleted";
    getch();
}

void billing(){
int order_arr[50], quan[50], c = 0;
    float amt, discamt, total = 0;
    char ans = 'Y';
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    do
    {
        cout << "\n\nEnter The Product No. Of The Product : ";
        cin >> order_arr[c];
        cout << "\nQuantity in number : ";
        cin >> quan[c];
        c++;
        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    cout << "\n\nThank You For Placing The Order";
    getch();
    //clrscr();
    cout << "\n\n******************************** INVOICE ************************\n";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount \t after discount\ n ";
    for (int x = 0; x <= c; x++)
    {
        mfile.open("Products.txt", ios:: in );
        mfile.read((char * ) & mproduct, sizeof(Product));
        while (!mfile.eof())
        {
            if (mproduct.Pno() == order_arr[x])
            {
                amt = mproduct.getprice() * quan[x];
                discamt = amt - ((amt * mproduct.getdisc() / 100)+mproduct.gettax());
                cout << "\n" << order_arr[x] << "\t" << mproduct.getName() <<"\t"
                << quan[x] << "\t\t" << mproduct.getprice() << "\t" << amt << "\t\t" << discamt;
                total += discamt;
            }
            mfile.read((char * ) & mproduct, sizeof(Product));
        }

        mfile.close();
    }
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
    getch();
}

int main()
{
    //clrscr();
    for(;;)
    {
        int press;
        cout<<"\n";
        cout<<"\t \t Options command to execute"<<endl;
        cout<<"################################################################################"<<endl;
        cout<<"\n                          1. to Create Product"<<endl;
        cout<<"                          2. to Display Products"<<endl;
        cout<<"                          3. to Update Products"<<endl;
        cout<<"                          4. to Delete Product"<<endl;
        cout<<"                          5. for Billing"<<endl;

        cin>>press;
        switch(press)
        {
            case 1:
                make_product();
                break;
            case 2:
                displayProducts();
                break;

            case 3: update_product();
                break;

            case 4: delete_product();
                break;

            case 5: billing();
                break;
            default:
                break;

        }
    }
}
