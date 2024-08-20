//multilevel inheritance

/*

BasePokemon -> EletricPokemon -> Pikachu
BasePokemon -> FirePokemon -> Charmander
BasePokeon -> EletricPokemon & FirePokemon -> Pikamander
** dimond problem 발생  : 
    //diamond problem
    //Pikamander 같은 경우, : basepokemon이 두번 불림. : electricpokemon으로 한번 firepokemon으로 한번
    //공통되는 Basepokemon 이 한번만 되도록.
    // solution : virtual inheritance



*/

#include<iostream>
#include<string>
using namespace std;

class BasePokemon{
    protected: // only access within class and derived, friend classes
        string name;
        int hp;
        enum myType{Electric, Fire , Electrofire} type;

    public:
    //constructor
        BasePokemon(std::string name, int hp, myType type): name(name), hp(hp), type(type){ cout<<"base constructor body"<<endl;}

        virtual ~BasePokemon(){cout<<"base pokemon destructor"<<endl;} // virtual: 상속하면서 override하기 위해
        
        int getHP() const{return hp;}
        
        std::string getName() const{return name;}
        
        myType getType(){return type;}
        
        //for abstract class : "pure virtual function"
        virtual void attack(BasePokemon& opponent)= 0; //pure virtual function 
};

class ElectricPokemon  : virtual public BasePokemon 
// virtual 상속이라면 또 부르지 않음. 
/*
multiple inheritance에서 생기던 ambiguity를 해결하는 셈.

*/
//ElectricPokemon내에 있는 BasePokemon constructor은..override되는 셈임.
{
    public :
        int electriclevel;
        //constructor
        ElectricPokemon(std::string name, int hp, int level) : BasePokemon(name, hp, Electric), electriclevel(level)
        {cout<<"ElectricPokemon constructor"<<endl;}   
};


class FirePokemon : virtual public BasePokemon  
// virtual 상속 : diamond problem 해결안.
{
    public:
        int firelevel;
        FirePokemon(std::string name, int hp, int level)  : BasePokemon(name, hp, Fire),firelevel(level){cout <<"FirePokemon constructor"<<endl;}

        //pure virtual function 정의 안해서 이것도 abstract class취급당함.
};



//derived classes
//상속할 때 public안하면 private
class Pikachu :  public ElectricPokemon // 이것만.
{ 
    public:
        std::string cry;
        //결코 이 순서대로 constructor호출이 아님.
        Pikachu() : BasePokemon("Pikachu", 200, Electric), ElectricPokemon("Pikachu", 100,10) , cry("Pika pika!") {cout <<"Pikachu constructor" <<endl;}

        void attack(BasePokemon& opponent) override {cout<<"pikachu's attack"<<endl;} // abstract class를 위함.
};


class Charmander : public FirePokemon
{
    public:
        int height;
        //결코 이 순서대로 constructor호출이 아님.
        Charmander() : BasePokemon("Charmander", 200, Fire),FirePokemon("Charmander", 200, 5) ,height(15) {cout <<"Charmander constructor" <<endl;}
      
};

//// ambiguity 발생 하는 이유
//이름이 같은 여러 parent의 type
// 내부적으로는 둘다 가지고 있으나 어떤걸 불러와야할지 햇갈려함.


class Pikamander : public ElectricPokemon,public FirePokemon
{
    public : 
        Pikamander() : BasePokemon("Pikamander", 300, Electrofire),ElectricPokemon("Pikachu", 100,10), FirePokemon("Charmander", 200, 5) {cout<<"constructor of Pikamander"<<endl;}
        // name과 hp가 모두 다르게 들어가지만, 이부분은 basepokemon을 위한 것이므로 basepokemon constructor으로만 사용된다.
        // 이게 최종이므로 이걸로 override되는 느낌임.

        friend class Pikachu; // 이러면 Pikachu는 Pikamander의 모든 것(private and protected을 접근이 가능해짐. 
        // 얘를 친구로서 인정한다~ 이런 느낌

        friend ostream& operator<<(ostream& os, Pikamander& Pikamander); 
        // member function은 아니지만  pikamander의 모든 것을 접근 가능. : freind functions로서 인정해준다~ 이런 느낌.


        void attack(BasePokemon& opponent) override{cout<<"pikamander's attack"<<endl;}
};

//diamond problem
//Pikamander 같은 경우, : basepokemon이 두번 불림. : electricpokemon으로 한번 firepokemon으로 한번
//공통되는 Basepokemon 이 한번만 되도록.
// solution : virtual inheritance


//for friend function
ostream& operator<<(ostream& os, Pikamander& pikamander){} // no access private and protected members of pikamander}

int main() {
    Pikachu pikachu;
    cout << pikachu.getHP() << endl; // BasePokemon // 200
    cout << pikachu.electriclevel << endl; // ElectricPokemon // 10
    cout << pikachu.cry << endl; // Pikachu
    // Output: 200  10  Pika pika!

    // ElectricPokemon electropokemon; // 사용 불가 abstract class여서(왜? pure virtual function정의 안했거든)

    //pikmander
    Pikamander pikamander;
    cout<<pikamander.getType() <<endl; // 이번엔 함수가 하나이지만, 두번 불린다는 것이 문제임. 2 : Electrofire
    cout<<pikamander.getName() <<endl; // Pikamander
    cout<<pikamander.getHP()<<endl; // 300

    return 0;

}   