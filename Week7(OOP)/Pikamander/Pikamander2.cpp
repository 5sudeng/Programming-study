// Multiple inheritance : many parents
/* 

BasePokemon & EletricPokemon -> Pikachu
BasePokemon & FirePokemon -> Charmander

BasePokemon & EletrcPokemon & FirePokemon -> Pikamander
=> 세개의 class가 모두 독립이고(not 상속) -> Pikachu, Charmander, Pikamander에서 복수로 상속하려고 해서 생기는 문제
:: ambiguity
*/


//pikachu가 base pokemon and eletric type pokemon inherit same time
#include<iostream>
#include<string>
using namespace std;

class BasePokemon{
    protected: // only access within class and derived, friend classes
        string name;
        int hp;

    public:
    //constructor
        BasePokemon(std::string name, int hp): name(name), hp(hp){ cout<<"base constructor body"<<endl;}

        virtual ~BasePokemon(){cout<<"base pokemon destructor"<<endl;} // virtual: 상속하면서 override하기 위해

        int getHP() const{return hp;}
        std::string getName() const{return name;}

};

//사용자 정의 type
enum myType{Electric, Fire};

//또다른 class
class ElectricPokemon 
{
    public :
        myType type;
        int electriclevel;

        //constructor
        ElectricPokemon(int level) : electriclevel(level), type(Electric){cout<<"Electric Pokemon constructor"<<endl;}
        virtual myType getType(){return type;} // virtual : ambigity를 해결하기 위함.

        ~ElectricPokemon() {cout<<"EletricPokemon destructor"<<endl;}
};


class FirePokemon
{
    public:
     myType type;
     int firelevel;

        FirePokemon(int level) : firelevel(level), type(Fire){cout <<"FirePokemon constructor"<<endl;}
        virtual myType getType(){return type;}
      
        ~FirePokemon() {cout<<"FirePokemon destructor"<<endl;}
};



//derived classes
//상속할 때 public안하면 private
class Pikachu : public BasePokemon, public ElectricPokemon// base class list 이 순서대로 constructor 호출임.
{ 
    public:
        std::string cry;

        //결코 이 순서대로 constructor호출이 아님.
        Pikachu() : ElectricPokemon(10) ,BasePokemon("Pikachu", 100) , cry("Pika pika!") {cout <<"Pikachu constructor" <<endl;}
        
        ~Pikachu(){cout<< "Pikachu detructor"<<endl;}
};


class Charmander : public BasePokemon, public FirePokemon // base class list 이 순서대로 constructor 호출임.
{ 
    public:
        int height;

        //결코 이 순서대로 constructor호출이 아님.
        Charmander() : FirePokemon(5) ,BasePokemon("Charmander", 200) ,height(15) {cout <<"Charmander constructor" <<endl;}
        ~Charmander(){cout<<"Charmander destructor"<<endl;}
};

//// ambiguity 발생 하는 이유
//이름이 같은 여러 parent의 type
// 내부적으로는 둘다 가지고 있으나 어떤걸 불러와야할지 햇갈려함.


class Pikamander : public BasePokemon, public ElectricPokemon, public FirePokemon
{
    public : 
        Pikamander() : BasePokemon("Pikamander", 300), ElectricPokemon(10), FirePokemon(5){cout<<"constructor of Pikamander"<<endl;}

        myType getType()override {return ElectricPokemon::type;}  // override and EletricPokemon::type :  embiguity해결하기 위함.


        ~Pikamander(){cout<<"Pikamander destructor"<<endl;}
};





int main() {
    Pikachu pikachu;
    /* 
    constructor calling
    base constructor body
    Electric Pokemon constructor
    Pikachu constructor
    */


    cout << pikachu.getHP() << endl; // BasePokemon // 100
    cout << pikachu.electriclevel << endl; // ElectricPokemon / 10
    cout << pikachu.cry << endl; // Pikachu
    // Output: 100  10  Pika pika!


    //pikamander
    Pikamander pikamander;
    /*
    base constructor body
    Electric Pokemon constructor
    FirePokemon constructor
    constructor of Pikamander
    
    */
    // cout<<pikamander.getType()<<endl; 
    // 모호하다고 나옴. (같은 함수가 electricpokemon 이랑 firepokemon둘다 구현되어 있어서.)
    
    
    
    
    //solutions : 직접 특정 지어주기.
    cout<<pikamander.ElectricPokemon::getType()<<endl; // 혹은 그냥 type //0으로 찍힘.
    
    cout<<pikamander.getType()<<endl;// 혹은  override로 정의해버리던가. -> 그냥 pikamander꺼로 덮어버린다.


    //그래도 모호하니. 공통된 것은 하나로 합치고, 계층적으로 상속하게 하는 것이 나을 수도.


}   

//out of scope : destructor calling
/*

desturctor도 거꾸로 : Pikamander -> Pikachu

[Pikamander destructor]
Pikamander destructor
FirePokemon destructor
EletricPokemon destructor
base pokemon destructor


[Pikachu destructor]
Pikachu detructor
EletricPokemon destructor
base pokemon destructor
*/

    