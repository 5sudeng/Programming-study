/* 
simple vector 구현: Computing 1기준  ::class 8 ~ class10
*/


#include <iostream>
#include <initializer_list> // constructor initalizier_list 를 별도로 사용할 경우.
#include<map>

using namespace std;

template <typename T> // 임의의 type template : 어떤 datatype도 가능해짐.
class SimpleVector
{
    private:
        T* array;
        int size;
        int capacity;

    public:
        //constructor1
        SimpleVector(int initialCapacity): size(0), capacity(initialCapacity){
            array = new T[capacity];
        }

        //constructor2
        SimpleVector(std::initializer_list<int>elements): size(0), capacity(elements.size()){
            array = new int[capacity];
            for (auto element : elements){
                //range based
                addElement(element);
            }
        }
        
        //destructors
        ~SimpleVector(){
            delete[] array;
            // out of scope일때 알아서 불림. -> dynamic(on-heap) released via delete
        }
        
        SimpleVector(); // default constructor
        void addElement(T element);
        void resize();
        int getSize() const;
        void printvec();

        T& operator[](int index); // &: 값 자체 반환
        SimpleVector<T> operator+(SimpleVector& rhs); // 더하고 새로운 Simplevector를 반환
        SimpleVector<T>& operator+=(SimpleVector &rhs); //더하고 그 자체를 반환
        SimpleVector<T> operator++(int);
        SimpleVector<T>& operator<<(const T& e); // appends a new element to v : 그 자체 다시 반환, 상수값 그대로 넣기 때문에 const를 사용, 변수를 사용하면 const를 쓰지 않음.
        bool operator==(SimpleVector&rhs);
        bool operator<(SimpleVector&rhs); // size 비교
        operator bool() const; // SimpleVector 자체로 boolean연산이 가능하도록, 일종의 type conversion
        T* begin();
        T* end();
        


        //copy constructor
        SimpleVector(const SimpleVector<T>& other);

        //copy operator
        SimpleVector<T>& operator=(const SimpleVector<T> & other);
        /*
        & : lvalue(local value를 말함. , 위치를 가진 값을 말함. 메모리 주소를 가리킨다., 수정가능한 값.
        */

        //move constructor
        SimpleVector(SimpleVector<T>&& other) noexcept;

        //move operator
        SimpleVector<T>& operator=(SimpleVector<T> && other) noexcept;
        /*
        &&의 의미 : Rvalue(read value) reference, resouce transfer, copying을 굳이 하지 않도록.
        ** rvalue : 단순한 값, 메모리 주소를 가지지 않음.
        noexcept : exception을 반환하지 않도록 하기 위함.
            - providing a compile-time guarantee that the function will not throw exceptions,
                enhancing the saftey and performance of the code(컴파일 최적화)
        */


        //static member : 해당 class를 사용하는 모든 object에 걸쳐서 관리 및 운영이 가능한 variable
        static std::map<T, int> elementCount;
        static void printElementCount();


};  



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//out of class definition
/* 
Out of class definition
1. class내부에는 함수 선언만 -> header files, implementation은 별도로 정의 -> source file
2. header file은 그대로이니, implementation 만 바꾸고, source file만 recompiling 하면 됨.
3. template implementation(template<typename T>를 쓰는 경우를 말함.)은 instantiation할 때, 
compiler에게 보여야 하므로, declaration과 implementation모두 header file에 넣어둔다.
*/

template<typename T>
SimpleVector<T>::SimpleVector(): size(0), capacity(0){
    array = new int;
}

template<typename T>
void SimpleVector<T>::addElement(T element){
    if (size == capacity){
        resize();
    }
    array[size] = element;
    size ++;
    elementCount[element]++; // static memebr
}


template<typename T>
void SimpleVector<T>::resize(){
    capacity = capacity*2;
    T*newArray = new T[capacity];

    //copy all
    for (int i=0; i<size; i++){
        newArray[i] = array[i];
    }

    //delete old one
    delete[] array;
    array = newArray;
}

template<typename T>
int SimpleVector<T>::getSize() const{ 
    /* 
    const : declare to compiler not to modify capacity when call this function
    */
   return size;
}

template<typename T>
void SimpleVector<T>::printvec(){
    for(int i = 0; i<this->getSize(); i++){
        cout<<(*this)[i]<< " ";
    }
    cout<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
operator overloading : 연산자 재정의
*** operator overwrting과 다른 것임.
*/

//[] operator
template <typename T>
T& SimpleVector<T>::operator[](int index) { // 값 자체를 "복사"가 아니라 call by reference
    return array[index];
}


//operator + : element wise sum : return SimpleVector itself
template<typename T>
SimpleVector<T> SimpleVector<T>::operator+(SimpleVector& rhs){
    SimpleVector<T> result(size);

    for (int i = 0; i <size; ++i){
        result.addElement(array[i] + rhs[i]);
    }
    return result;
}


//operator += : adds v to v element wise : return 그 자체 : &
template<typename T> 
SimpleVector<T>& SimpleVector<T>::operator+=(SimpleVector & rhs){
    for (int i = 0; i<size; ++i){
        array[i] +=rhs.array[i];
    }

    return *this; 
    // this : 현재 객체를 가리키는 특수 포인터, 보통 맴버 함수 내에서 사용된다., 해당 함수를 호출한 객체를 가리킨다. * 연산자를 통해서 dereferenced
    //SimpleVector 그 자체를 반환
}


//operator ++  : iterator에서는 it++이 구현이 안되어잇었는데, 여기서는 해본다. : increment for each element of v return copy of it(not using call by reference)
// evaluation then increment
template<typename T> 
SimpleVector<T> SimpleVector<T>::operator++(int){ // int는 의미는 없지만 pre increment와 구별하기 위함.(argument가 다르면 다른 함수 코드로 구별)
    SimpleVector<T> temp(size);// copy용

    for(int i =0 ; i< size; ++i){
        temp.addElement(array[i]); // evaluation
        ++array[i]; //increment
    }

    return temp;
}


//operator << : v <<e : appends a new element to v
template<typename T>
SimpleVector<T>& SimpleVector<T>::operator<<(const T& e){ //변경을 안할 거라는 의미 , 변수로 들어오는 것이 아닌, 특정 되지 않은 value를 넣어줄 것인데, 이 값이 변하지 않을 거라는 것을 컴파일러에게 명시.
    //변하지 않는 데이터 그 자체 literal 을 변하지 않는 상수 변수로 만들어 주기 위함.
    //만약 literal을 넣어주는 것이 아닌 어떤 변수를 넣어준다고 했을 때는 const는 없어도 됨.

    addElement(e);
    return *this;
}


//== operator : check if v and v contain the same element : boolean return
template<typename T>
bool SimpleVector<T>::operator==(SimpleVector & rhs){
    if (size != rhs.getSize()) return false;
    
    for(int i =0 ;i < size; ++i){
        if (array[i] != rhs[i]) return false;
    }

    return true;
}


//< operator : check if v has a smaller size than v;
template<typename T>
bool SimpleVector<T>::operator<(SimpleVector &rhs){
    if (size < rhs.getSize()) return true;
    else return false;
}

//bool operator : vector v 자체로 true false가 가능하게 : type conversino
template<typename T>
SimpleVector<T>::operator bool() const{ // type으로 아무것도 반환을 안하는 모습, 뭐 함수로 반환하는 것이 아닌, 그 자체로 판정이기 때문.
    return size >0;
}


//ranged based for loop이 가능하려면, begin, end가 구현되어야 함.
// begin, end 둘다 모두 pointer이다.
template<typename T>
T* SimpleVector<T>::begin(){
    return array;
}

template<typename T>
T* SimpleVector<T>::end(){
    return array + size; // size 만큼 array 데이터 타입에 해당하는 단위 만큼 더해준다.
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
// operator overloading as non-member functions
//class내부에서 정의하지 않고, 외부에서 정의 : 즉 클래스 종속 operator가 아님.
//따라서 prototype도 적을 필요가 없음.
//종속을 의미하는 ::도 쓸필요가 없음.
*/


/*
장점
1. class를 또 수정할 필요 없이, scope 밖에서 바로 연산자를 정의가 가능하다.
2. lhs의 implicit type conversion이 가능해짐.
즉 lhs의 경우는 이미 type이 정해져 있기에, "Hello"같은 literal이 lhs 로 오지 못함. 사전에  lhs는 변수로 타입이 이미 정해져 있어야 함.
근데, 이렇게 하면(operator==(const string& lhs, const string& rhs)), "Hello" = str, str = "Hello" 모두 처리가 가능함. argument로 알아서 데이터 타입을 처리해주기 때문.

단, member function 과 non-member가 있다면 member function먼저 실행됨.
*/


//operator <<: appending all elements of the rhs to the lhs
template<typename T>
SimpleVector<T>& operator<<(SimpleVector<T>& lhs, SimpleVector<T>& rhs){
    for (int i = 0; i<rhs.getSize(); ++i){
        lhs.addElement(rhs[i]);
    }
    return lhs;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Copy Semantics

1. deep copy : 메모리 주소를 따로 할당한다. 서로 겹치지 않게.
2. with non-temporary object
    - 새롭게 초기화 혹은 arument를 넘길 때 : copy constructor 사용
    - 객체를 update를 할 때 : copy operator




<copy constructor>
: initialize with non-temporary object (원래 있는 것으로 초기화를 새롭게 하기 위해서)

<copy operator>
: update with another existing object(원래 있던 객체로 업데이트)
: 새롭게 만드는 것이 아니라, 원래 있는 객체(vec)을 다른 객체로 대체하기 위함임.
*/


template<typename T>
SimpleVector<T>::SimpleVector(const SimpleVector<T>& other) // &: call by reference로 들고 와서 const로 취급
: size(0), capacity(other.capacity), array(new  T[other.capacity])
{
    //copy
    for (int i = 0; i<other.getSize(); ++i){
        addElement(other.array[i]);
    }
}

template<typename T>
SimpleVector<T>& SimpleVector<T>::operator=(const SimpleVector<T>& other){
    if(this !=&other){// 주소 비교
        //같지 않다면 다시 만든다.
        delete[] array; //원래꺼 지우고
        capacity = other.capacity;
        array = new T[capacity];
        size = 0;
        for(int i = 0; i<other.size; ++i){ // other에서 가져와서 넣어주기
            addElement(other.array[i]);
        }
    }
    

    //이미 같은 것을 의미하면, 그대로 반환
    return *this;
}




/*
Move Semantics : "복사"가 아니라, 어차피 사라질 녀석 (temporary)를 그대로 가져와서 초기화 혹은 update
    - 이렇게 하면 굳이 복사 비용을 쓰지 않아도 되고, 복사할 수 없는 녀석도 처리할 수 있다.

1. deep copy : memory address 를 따로 할당한다. 서로 겹치지 않게.
2. temporary object을 할당해주는데, 이건 어차피 사라질 거잖아. 그러면 그대로 가져다 쓰자!
3. with temporary object
    - initialize or taking temporary object or returned by value from fuction or using move(variable): move constructor
    - update: move assignment operator

*/


//move constructor : resource를 그대로 가져와서 초기화
template<typename T>
SimpleVector<T>::SimpleVector(SimpleVector<T>&& other) noexcept
: array(other.array), size(other.size), capacity(other.capacity)
{
    other.array = nullptr; // transfer한  other은 지우는 것보다는 unspecified state로 남겨둔다.
    other.size = 0;
    other.capacity = 0;
}

void processVector(SimpleVector<int> vec){
    cout << "copy or move constructor" <<endl;
}

//move assignment operator : temporary 녀석(rvalue)를 가지고 원래 있던 객체를 업데이트
template <typename T>
SimpleVector<T>& SimpleVector<T>::operator=(SimpleVector<T>&& other) noexcept {

    if (this != &other) { // 다른거면 새롭게 할당해주는 느낌.
        delete[] array;
        array = other.array; 
        // object 연산이랑 헷갈리지 말것. 
        //단순 data할당이라 생각하자. (copy operator에서는 일일히 다 복사(라기보단 빈거에 추가?)해줬어야 했음.)
        size = other.size;
        capacity = other.capacity;

        other.array = nullptr; // make them unspecified state
        other.size = 0;
        other.capacity = 0;
    }
    
    return *this;
}

/*
Return Value Opimization : 새롭게 만들. 객체에 temporary lvalue를 반환해서 할당하려고 할 때.
*/

SimpleVector<int> createVector(){

    SimpleVector<int>vec{1,2};
    std::cout<<"&vec in createVector(): " << &vec <<endl;
    return vec; // temporary object scope 벗어나면서 delete

    /*
    내부에서 만드는 temporary이지만 lvalue를 반환해서 밖에 원래 존재했던 것을(혹은 새롭게 정의한 것)에 넣어주는 것.
    그래서 move semantic임.

    lvalue이기에 주소는 가진다.
    */
}


/*
//Static Memebers : 클래스 레벨에서 관리되는 것. 
// instance object을 구현하지 않아도, 클래스로 관리할 수 있는 것.
//ex) : 모든 SimpleVector object을 아우르는 모든 종류의 element의 빈도수를 세는 변수를 만들고, 이를 instance가 class 레벨에서 구현하고 관리하고자 함.
// 클래스 선언에서 되어야 하며 with static
*/

//반드시 필요
template<typename T>
std::map<T, int> SimpleVector<T>::elementCount = {}; //  out of definition으로 initialization이 필요함.


template<typename T>
void SimpleVector<T>::printElementCount(){
    for (auto pair : elementCount){
        cout<<pair.first<< ":" <<pair.second<<endl;
    }
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main_Episode1(){
        //initialization
    SimpleVector<int> vec1(10); // constructor 1
    SimpleVector<int> vec2 = {1,2,3}; // constructor2
    SimpleVector<int> vec3{1,2,3}; // constructor 2

    cout<< vec2.getSize()<<endl;


}


void main_Episode2(){
    
    
    SimpleVector<int> *intVecPtr = nullptr;
    intVecPtr = new SimpleVector<int>(10);
    SimpleVector<int> *intVecPtr2 = new SimpleVector<int>({1,2,3});


    //with smart pointer
    /* 
    unique pointer 기능
    1. 다른 것으로 할당 불가. 이것만 가지고 접근 가능함
    2. free가 알아서 됨. 동적할당인데.

    단 make_unique라는 함수는 c++14에서만 사용 가능함.
    auto other_vecptr = std::make_unique<std::vector<int>>();
    */

   std::unique_ptr<SimpleVector<int>> unique_vec_ptr(new SimpleVector<int>(10));
   unique_vec_ptr ->addElement(20);
   cout<<(*unique_vec_ptr).getSize()<<endl;

    
}


void main_Episode3(){
    SimpleVector<int> vec = {1,2,3,4,5};

    //operator []
    for(int i = 0; i< vec.getSize(); i++){
        cout<<vec[i] <<" ";

    }
    vec[2] = 10;
    cout<<""<<endl;

    //operator + 
    SimpleVector<int> vec2 = {2,3,4,5,6};
    SimpleVector<int> vec3 = vec + vec2;
    vec3.printvec();

    //operator +=
    vec += vec2;
    vec.printvec();

    //operator ++
    cout<<(vec++)[0] <<endl; // return되는 것은 ++ 되기 전 상태
    cout<<vec[0] <<endl; // ++ 된 후 상태

    //operator << : append
    vec<<4<<5;
    vec.printvec();



    //begin, end for ranged based iterator
    for(auto v : vec){
        cout<<v<< " ";
    }
}




void main_Episode4(){
    SimpleVector<int>vec1 = {1,2,3};
    SimpleVector<int>vec2 = {4,5};

    vec1 <<vec2; // member function, nonmember function 둘다 있지만, 형식에 맞게 non-member function이 불림.
    /*
    이게 가능한 이유는 vec2 가 int형식이 아니라서, 멤버 함수보다는 비 멤버 함수에 더 걸맞음을 판단한다.
    ::Name Lookup이라고 함.
    
    */
    vec1.printvec();
}





void main_Episode5(){

    //copy constructor
    SimpleVector<int> vec{1,2,3};
    SimpleVector<int>copyvec = vec; //construct by copy constructor
    copyvec.printvec();


    //copy operator
    SimpleVector<int> vec2{2,3,4};
    vec = vec2; // 원래 있었던 vec을 새롭게 정의하는 것이 아닌, 그대로 copy해서 가져와서 업데이트


    //move constructor
    SimpleVector<int> vec1 = SimpleVector<int>{2,3,4}; // simpleVector<int>{2,3,4}라는 녀석이 금방 사라질 녀석(temporary), 이거 가지고 초기화
    SimpleVector<int> vec3{1,2};
    SimpleVector<int>vec4 = std::move(vec3); // move를 사용하면 temporary로 바뀌게 됨.
    processVector(SimpleVector<int>{4,5,6}); // 이것도 move constructor를 사용한 것. rvalue가 들어갔기에., move constructor 형성 후, 임시로 객체를 만든다음 사용 후, 없앤다.
    
    
    //move operator
    SimpleVector<int>ee{1,2};
    ee = SimpleVector<int>{3,4}; // move opeartor
    SimpleVector<int>vvv{1,2};
    ee = std::move(vvv);


    //move semantic 응용
    // Named Return value optimization : function call이 예상되는 곳에 그대로 넣어버림. when constructor
    vvv = createVector(); // 이건 원래  vvv가 있어서, move operator 작동.
    cout << "&vvv in main(): " << &vvv << endl;// 함수 내 vec과 주소가 다름.
    /*이미 vvv라는 것이 존재했기 때문에 주소가 다른 것임.*/


    // Retrun value optimization (선언과 동시에)
    SimpleVector<int> RVO = createVector(); // copy/move constructor발동해야히지만, 여기서만 사용될 것을 알기에, 같은 것으로 construction
    cout<<"&vec in main() : "<< &RVO <<endl; // 함수내 변수와 주소가 같음.
    /* 
    새롭게 생성되면서 RVO에 직접 객체를 "생성"하기에 주소가 같은 것임.
    */
    

    //static member 접근 그냥 가능, 단 :: operator랑 같이 사용.
    SimpleVector<int>::printElementCount();
    cout<<SimpleVector<int>::elementCount.size()<<endl;
    

}


int main(){

    cout<<"episode1"<<endl;
    main_Episode1();
    cout<<"episode2"<<endl;
    main_Episode2();
    cout<<"episode3"<<endl;
    main_Episode3();
    cout<<"episode4"<<endl;
    main_Episode4();
    cout<<"episode5"<<endl;
    main_Episode5();

    


    return 0;
}
// destructor called
    