#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
using namespace std;

class Bill{
  private:
    string Item;
    int Rate , Quantity;
  public:
     Bill(): Item("") , Rate(0) , Quantity(0){ }

     void setItem(string item){
       Item = item;
     }

     void setRate(int rate){
        Rate = rate;
     }

      void setQuantity(int quant){
        Quantity = quant;
     }

     string getItem(){
        return Item;
     }

     int getRate(){
        return Rate;
     }

     int getQuantity(){
        return Quantity;
     }
};

addItem(Bill b){
  bool close = false;
  while(!close){
    int choice ;

    cout<<"\t1.     Add "<<endl;
    cout<<"\t2.     close "<<endl;
    cout<<"\t->     Enter Choice: ";
    cin>>choice;

    if(choice == 1){
       system("cls");
       string item;
       int rate , quant ;

       cout<<"\t Enter Item Name: ";
       cin>>item;
       b.setItem(item);

       cout<<"\t Enter Rate of Item: ";
       cin>>rate;
       b.setRate(rate);

       cout<<"\t Enter Quantity of Item: ";
       cin>>quant;
       b.setQuantity(quant);

       ofstream out("D:/Bill.txt",ios::app);
       if(!out){
          cout<<"\t\tError file can't open "<<endl;
       }
       else{
          out<<"\t"<<b.getItem()<<" : "<<b.getRate()<<" : "<<b.getQuantity()<<endl<<endl;
       }
       out.close();
       cout<<"\t Item added successfully! "<<endl;
       Sleep(3000);
    }
    else if( choice == 2){
       system("cls");
       close = true;
       cout<<"\tBack To Main Menu: "<<endl;
       Sleep(3000);
    }
  }
}

printBill(Bill b){
   system("cls");
   int count = 0;
   bool closed = false;
   while(!closed){
     int choice ;

     cout<<"\t1.     Add Bill "<<endl;
     cout<<"\t2.     close "<<endl;
     cout<<"\t->     Enter Choice: ";
     cin>>choice;

     if(choice == 1){
        string item;
        int quant;
        cout<<"\tEnter Item: ";
        cin>>item;
        cout<<"\tEnter Quantity: ";
        cin>>quant;

        ifstream in("D:/Bill.txt");
        ofstream out("D:/Bill Temp.txt");

        string line;
        bool found = false;

        while(getline(in, line)){
           stringstream ss;
           ss << line;
           string itemName;
           int itemRate, itemQuantity;
           char delimiter;
           ss>>itemName>>delimiter>>itemRate>>delimiter>>itemQuantity;

           if(item == itemName){
              found = true;
              if(quant <= itemQuantity){
                 int amount = itemRate*quant;
                 cout<<"\t Item | Rate | Quantity | Amount "<<endl;
                 cout<<"\t"<<itemName<<"\t"<<itemRate<<"\t"<<quant<<"\t"<<amount<<endl;
                 int newQuantity = itemQuantity - quant;
                 itemQuantity = newQuantity;
                 count += amount;

                 out<<"\t"<<itemName<<" : "<<itemRate<<" : "<<itemQuantity<<endl<<endl;
              }
              else{
                 cout<<"\tSorry, "<<item<<" Ended! "<<endl;
              }
           }
           else{
              out<<line<<endl;
           }
        }
        if(!found){
          cout<<"\tItem not available "<<endl;
        }
        out.close();
        in.close();
        remove("D:/Bill.txt");
        rename("D:/Bill Temp.txt", "D:/Bill");
     }
     else if(choice == 2){
        closed = true;
        cout<<"\tClosing Total Bil "<<endl;
     }
     Sleep(3000);
    }
    system("cls");
    cout<<endl<<endl;
    cout<<"\t Total Bill ----------:"<<count<<endl<<endl;
    cout<<"\tThanks for shopping "<<endl;
    Sleep(5000);
}
int main(){
   Bill b;

   bool exit = false;

   while(!exit){
     system("cls");
     int val;

     cout<<"\tWelcome To Super Market Billing System"<<endl;
     cout<<"\t*****************************************"<<endl;
     cout<<"\t\t1.  Add Item. "<<endl;
     cout<<"\t\t2.  Print Bill. "<<endl;
     cout<<"\t\t3.  Exit. "<<endl;
     cout<<"\t\t->  Enter Choice: ";
     cin>>val;
     if(val == 1){
        system("cls");
         addItem(b);
         Sleep(3000);
     }
     else if(val == 2){
        system("cls");
        printBill(b);
     }
     else if(val == 3){
        system("cls");
        exit = true;
        cout<<"\tGood Luck! "<<endl;
        Sleep(3000);
     }
   }
}