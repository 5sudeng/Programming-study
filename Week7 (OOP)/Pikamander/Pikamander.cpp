/*
class inheritance에 대한 모든 것.
Computing 1 기준 : class11, 12s
*/



#include <iostream>
#include <string>
using namespace std;



/*Base Class
1. protected members : 외부에서 다룰 수 없고, 수정도 불가능하지만, 내부 method 및 상속 (derived) class는 접근 가능.
2. enum : user defined type
    - enum [typename] {admissible type name} [변수명]
    - 컴파일 내부에서는 각 value가 0,1,2~ 로 인식된다.*/



class Pokemon{
    protected:
        std::string name; // 24byte
        int hp; //4byte
        enum mytype {Electric, fire} type; // 4byte

    public: // 지금은 out of definition 구현이 아님.
        //constructor
        Pokemon(std::string name, int hp, mytype type) : name(name), hp(hp), type(type){

        } 
        //destructor : virtual
        virtual ~Pokemon(){
            cout<< "delete Pokemon" <<endl;
        }
        
        int getHP(){
            return hp;
        }
        std::string getName(){
            return name;
        }
        mytype getType(){
            return type;
        }

        void decreaseHp(int amount){
            hp -=amount;
        }

        //virtual을 붙이면 override을 쓴다는 의미가 됨.
        virtual void attack(Pokemon& opponent){ // call by reference oponent
            std::cout <<"[Base]" << name <<" attacks " <<opponent.getName()<<std::endl; //<<opponent.name 이것도 가능 protected이지만, 클래스 내부이므로
        }


};


/* Derived Classed
1. inherits from
2. is derived from
3. extends
4. is a subclass of
*/

class Pikachu : public Pokemon
{ // Pokemon 상속 

    //inheritnace type
    // public : base의 level을 그대로 다 가져감. private은 private으로 등등
    // protected : public member들을 protected로
    // private : base의 모든 것들을 private로, 한번 상속하면, 다른 상속되는 클래스도 건들지 못하게 됨.
    // default로 private임.
    int electricLevel;  // default private attribute // 4byte

    public: // 외부에서 사용가능하도록.
    //constructor
        Pikachu() : Pokemon("Pikachu", 100, Electric), electricLevel(10){ // initializer list 내부에 base class constructor recalled, (안넣으면 default constructor recall 구현되어 있다면.)
            
        }
    //destructor : 먼저 불리고 그다음 base destructor호출
        ~Pikachu() override {
            cout<< "delete Pikachu" <<endl;

        }

    //methods
        void attack(Pokemon& opponent) override { // override to base class function

            Pokemon::attack(opponent); // 이런식으로 parent의 method calling
            if (opponent.getType() == fire)
                opponent.decreaseHp(electricLevel - 2);
            else
            opponent.decreaseHp(electricLevel);

            cout<< "(Attacker) " << name << " HP : " << hp<< endl;
            cout<<"(Opponent) " <<opponent.getName()<<" HP : " <<opponent.getHP() <<endl;
        }

        void cry(){
            std::cout<< "Pika pika!" << std::endl;
        }

};



/* derived class 2*/
class Charmander : public Pokemon
{
    int flameLevel; // private

    public : 
        Charmander() : Pokemon("Charmander", 200, fire), flameLevel(5){

        }
        ~Charmander()  {
            cout<< "delete charmander" <<endl;
        }
        void attack(Pokemon& opponent) {
            // Pokemon::attack(opponent);
            if (opponent.getType() == Electric){
                opponent.decreaseHp(flameLevel +2);

            }
            else opponent.decreaseHp(flameLevel);

            cout<< "(Attacker) " << name << " HP : " << hp<< endl;
            cout<<"(Opponent) " <<opponent.getName()<<" HP : " <<opponent.getHP() <<endl;
        }

};




/*
inheritance에서 다 상속되는데 예외적인 것은 딱 4가지
constructor, destructor, copy assignment operator, move assignment operator : 리소스 관리이기 때문
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* class substiution
OOP의 개념 중 하나로, 상속 클래스를 base 클래스로 인식하게 해주는 방법임
base class pointer가 상속 클래스 pointer로 역할을 하는 셈임. : base attribute 을 사용하게 됨.

*/
Pokemon* createPokemon(string name){ // create pointer (type of Pokemon) 
    if (name == "Pikachu"){
        return new Pikachu(); // new로 heap에 Pickachu관련 메모리 할당하고 메모리 주소 할당
    }
    else if (name=="Charmander"){
        return new Charmander();
    }
    else return nullptr;
}



/* virtual function(overriden) : class substituion과 같이 쓰는 개념임.
class substituion으로 base 클래스로 인식하게 하면서 base 속성들을 썼는데, 더 나아가 원래의 상속 클래스의 method을 사용하려면?

virtual function = 같은 이름의 상속 클래스에 의해 overriden되는 base 클래스내 함수.

보통은 같은 이름의 function(destructor포함)을 상속 클래스에서 구현할 때, base에서 virtual로 해놓는게 안정적임.


override  = 하위 클래스가 상위클래스의 함수를 결국 재정의하는 것임.
*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Episode1(){
    Pikachu pikachu;
    Charmander charmander; // stack 메모리 할당 , destructor 알아서 할당.


    std::cout << "Size of Pikachu: " << sizeof(Pikachu) << " bytes" << std::endl; // 48byte = Pokemon(32byte) + eletriclevel(4byte) + vtable(8byte) + 메모리 정렬(4byte)
    std::cout << "Size of Charmander: " << sizeof(Charmander) << " bytes" << std::endl; // 48byte


    std::cout << "Address of pikachu: " << &pikachu << std::endl; // 이게 더 높은 주소
    std::cout << "Address of charmander: " << &charmander << std::endl;

    cout<<"Pikachu's hp " <<pikachu.getHP() <<endl; // 100
    cout<<"Charmander's hp " <<charmander.getHP() <<endl; // 200

    pikachu.attack(charmander); 
    /* 
    method overriden : child의  method가 불림.
    //[Base]Pikachu attacks Charmander
    (Attacker) Pikachu HP : 100
    (Opponent) Charmander HP : 192
    */


    cout<<"Charmander's hp " <<charmander.getHP() <<endl; // 192

    charmander.attack(pikachu); 
    /* 
    //Pokemon::attack(opponent)가 없어서 출력 하지 않음.
    (Attacker) Charmander HP : 192
    (Opponent) Pikachu HP : 93
    */
    cout<<"Pikachu's hp " <<pikachu.getHP() <<endl; // 93

    

    //class subsitution
    Pokemon *pokemon1, *pokemon2; // Pokemon pointer ::: 마찬가지로 heap에 저장되는 메모리라 별도로 delete를 해야 함.
    std::string pokemonName1, pokemonName2; // name of new pokemon

    cout <<"Enter name for Pokemon 1(Pikachu or Charmander) : ";
    cin >> pokemonName1;
    pokemon1 = createPokemon(pokemonName1);//move assignment operator

    

    cout <<"Enter name for Pokemon 2(Pikachu or Charmander) : ";
    cin >> pokemonName2;
    pokemon2 = createPokemon(pokemonName2);

    if ((pokemon1 == nullptr) || (pokemon2 == nullptr)) return;

    cout<< "Pokemon1 : " << pokemon1 -> getName()<<endl;  // Pikachu
    cout<<"Pokemon2 : " << (*pokemon2).getName() <<endl; // Charmander

    cout<<"attack of pokemon2 to pokemon2"  <<endl;
    


    (*pokemon2).attack(*pokemon1); 
    /*
    (Attacker) Charmander HP : 200
    (Opponent) Pikachu HP : 93
    */
    (*pokemon1).attack(*pokemon2); 
    (*pokemon1).attack(*pokemon2); 
    /* 
    [Base]Pikachu attacks Charmander
    (Attacker) Pikachu HP : 93
    (Opponent) Charmander HP : 184
    */

    delete pokemon1;
    delete pokemon2;
    
    

    //destructor 활용
    Pokemon* pokemon = new Pikachu(); 
    delete pokemon;
    /* 
    delete Pikachu
    delete Pokemon  
    */


    Pokemon* pokemon3 = new Charmander(); 
    delete pokemon3;
    /* 
    delete charmander
    delete Pokemon  
    */

    Charmander* charmander2 = new Charmander(); 
    // new : 동적할당:: 별도로 삭제하지 않으면 (혹은 unique_ptr, shared_ptr가 아니라면) 사라지지 않고, 남아 있는다.
    delete charmander2;
    
    cout<<"end" <<endl; // end




}

    // 이후, 앞에서 stack에 정의된 것들 차례로 destructor 자동 호출
    /* 
    1. charmander destructor (가장 최근에 정의된 것부터)
    2. Pikachu destructor

    * 가장 최근 것부터 지우는 이유: stack이기 때문 (LIFO)
    ** 마지막에 추가된 데이터가 먼저 제거된다.
    *** 스택 메모리 상, 변수 선언된 순서대로 낮은 주소부터 높은 주소로 할당되는 것은 맞으나,
    **** 스택이 자라는 방향은 높은 주소에서 낮은 주소로 향한다. 즉 나중에 선언된 변수가 더 낮은 주소를 가지게 된다.
    Pikachu가 charmander보다 높은 주소를 가진다.


    */




int main(){
    Episode1();
}