#include <iostream>
using namespace std;

class BasePizza {
    public:
        virtual int cost(){
            return 0;
        }
};

class Margherita : public BasePizza {
    public:
        int cost(){
            return 100;
        }
};

class FarmHouse : public BasePizza {
    public:
        int cost(){
            return 100;
        }
};

class toppingDecorator : public BasePizza{
      
};

class ExtraCheese : public toppingDecorator{
    public:
        BasePizza *pizza;
        ExtraCheese(BasePizza *pizza){
            this->pizza = pizza;
        }
        
        int cost(){
            return 20 + pizza->cost();
        }
};

class Mushroom : public toppingDecorator{
    public:
        BasePizza *pizza;
        Mushroom(BasePizza *pizza){
            this->pizza = pizza;
        }
        
        int cost(){
            return 30 + pizza->cost();
        }
};

int main()
{
    Margherita *margherita = new Margherita();
    
    BasePizza *margheritaExtraCheese = new ExtraCheese(margherita);
    cout<<"Margherita with extra cheese :"<<margheritaExtraCheese->cost()<<endl;
    
    BasePizza *margheritaExtraCheeseAndMushroom = new Mushroom(margheritaExtraCheese);
    cout<<"Margherita with extra cheese :"<<margheritaExtraCheeseAndMushroom->cost()<<endl;

    return 0;
}
