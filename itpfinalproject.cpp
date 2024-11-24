#include <iostream>
#include <fstream>
using namespace std;


class Product {
public:
    string name;
    double price;

    Product(string n,double p):name(n),price(p){}//constructor initializer list used to initialize the name and price

    virtual~Product(){}

    //virtual function to display product information.
    virtual void informations() const{
        cout<<"Description: "<<name<<" - Rs. "<<price<<endl;
    }
    //use of function
    double getPrice() const{    
        return price;
    }
};

class iPhone: public Product{// inheritance from product class
public:
    iPhone():Product("iPhone",150000){}
    void informations() const override{
    cout<<"iPhone - Rs. 150000"<<endl;
    }
};

class Laptop: public Product{
public:
    Laptop(): Product("Laptop",99000){}
    void informations() const override{//Override of the base class function 'informations'
    cout<<"Laptop - Rs. 99000"<<endl;
    }
};


class Motherboard : public Product {
public:
    Motherboard() : Product("Motherboard",120000) {}
    void informations() const override {//Override of the base class function 'informations'
    cout<<"Motherboard - Rs. 120000"<<endl;
    }
};

class GraphicsCard : public Product {
public:
    GraphicsCard() : Product("Graphics Card",95000) {}
    void informations() const override {//Override of the base class function 'informations'
    cout<<"Graphics Card - Rs. 95000"<<endl;
    }
};

class RAM : public Product {
public:
    RAM() : Product("RAM",32000) {}
    void informations() const override {//Override of the base class function 'informations'
    cout<<"RAM - Rs. 32000"<<endl;
    }
};
int main()
 {
    const double VAT=0.13; // VAT of 13%
    string customerName;
    cout<<"********************WELCOME TO ETUSAA STORE********************"<<endl;

    cout<<"Enter your name: ";//customer detail
    cin>>customerName;
    
    //array to store pointers to products
    Product* products[5] ={new iPhone(),new Laptop(),new Motherboard(),new GraphicsCard(),new RAM()}; 

    char moreproducts='Y'; //character to add more products
    double nodiscount=0;

    ofstream recordfile("record.txt",ios::app); //the use of file handling

    if (!recordfile.is_open()){
    cout<<"Unable to open file for sales record";
    return 1;
    }

    while (moreproducts=='Y' || moreproducts=='y'){
        cout<<"The products we currently have are:"<<endl;
        for (size_t i=0; i<5; ++i) {
        cout<<i+1<<". ";//the serial number of respective products
        products[i]->informations();
        }

        int choice;
        cout<<"Enter the number of the product you want to buy: "<<endl;//quantity of products
        cin>>choice;

    
        if(choice<1 || choice>5){
         cout<<"Invalid choice."<<endl;
        continue;
        }
        recordfile;

        int quantity;
        cout<<"Enter the quantity of the product: ";
        cin>>quantity;

        double totalprice=quantity*products[choice - 1]->getPrice();// accessing get price and calculating total price
        nodiscount =nodiscount+totalprice;//total price with no discount
            cout<<"Added "<<quantity<<" "<<products[choice - 1]->name<<"(s) to your cart for Rs. "<<totalprice<<endl;//quantity and amount

        recordfile<<"Product: "<<products[choice - 1]->name<<", Quantity: "<<quantity<<", Total Price: Rs. "<<totalprice<<endl;
         
            cout<<"Do you want to add more products (Y/N)? ";
            cin>>moreproducts;
    }

    double vat=nodiscount*VAT;//adding vat
    double totalprice=nodiscount+vat;//total price after adding vat


     if (totalprice>300000) {//lucky draw
        int luckynum;
        cout<<"You have a chance to win Iphone"<<endl;
        cout<<"Please enter any number between 1 to 20: ";
        cin>>luckynum;

      
    if(luckynum==3 || luckynum==17) {
    cout <<"Congrats!!!! You won an iPhone!"<<endl<<endl<<endl<<endl;

            totalprice=totalprice-150000; 

        }
         else{
        cout<<"Better luck next time! You did not win an iPhone."<<endl<<endl<<endl<<endl;
        }
    }

    cout<<"|-----------------------------------INVOICE-----------------------------------|"<<endl;
    cout<<"|                         Etusaa Store                                        |"<<endl;
    cout<<"|                        Lalitpur, Nepal                                      |"<<endl;
    cout<<"|-----------------------------------------------------------------------------|"<<endl;
    cout<<"| Description                | Quantity | Price per Unit | Total Price        |"<<endl;
    cout<<"|----------------------------|----------|----------------|--------------------|"<<endl;
    cout<<"| 1.iPhone                   |          |                |                    |"<<endl;
    cout<<"| 2.Laptop                   |          |                |                    |"<<endl;
    cout<<"| 3.Motherboard              |          |                |                    |"<<endl;
    cout<<"| 4.Graphics Card            |          |                |                    |"<<endl;
    cout<<"| 5.RAM                      |          |                |                    |"<<endl;
    cout<<"|-----------------------------------------------------------------------------|"<<endl;
    cout<<"| Total Price:                                             Rs."<<nodiscount<<endl;
    cout<<"| VAT (13%):                                               Rs."<<vat<<endl;
    cout<<"| Total Price (including VAT):                             Rs."<<totalprice<<endl;
    cout<<"|-----------------------------------------------------------------------------|" << endl;
  //cleaning allocated memory
    for(size_t i=0;i<5;++i){
        delete products[i];
    }

    recordfile.close();//closing sales record file

 
    return 0;
}
