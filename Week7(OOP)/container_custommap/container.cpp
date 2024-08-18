
#include <type_traits>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

// Implement definition of all classes and the member functions in this file.

class Container{
    //pure virtual class
    protected: //only access within class and derived, friend classes
        float size;
        float capacity;
        enum container_type {B, C, PaB, PIB} container_type;
        string* container_code;
        string capacity_code; // 1, 2, 3

    public:
        //constructor
        Container(float size): size(size){

            container_code = new string(""); // dynamic string code
        };
        //destructor
        virtual ~Container(){
            delete container_code; // delete dynamically made string pointer
        };

        float get_size(){return size;}
        
        //pure virtual
        /*
        abstract class를 만들기 위함임.
        abstract class는 객체를 직접 생성할 수 없으며 반드시 파생 클래스에서 pure virtual function을 정의를 내려줘야 함.
        */
        virtual void set_capacity() = 0;

        float get_capacity(){return capacity;} // virtual이 아니기 때문에, 이 함수는 모든 derived class가 사용이 가능함.

        void set_container_code(){
            if (capacity <100){
                capacity_code = "1";
            }
            else if ((capacity >= 100) && (capacity <200)){
                capacity_code = "2";
            }
            else{
                capacity_code = "3";
            }

            //B3, or C3;
            *container_code +=capacity_code; // 숫자를 뒤에 붙이므로.

        


        }
        string* get_container_code(){
            return container_code;
        }
};



/*
    // not virtual inheritance : diamond problem이 생기지 않아서 굳이 쓰지 않음.
    "virtual public"을 쓰는 이유는
    class WoodenBox : public Container
    class FancyBox : public Box, public WoodenBox
    FancyBox에서 Container constructor가 두번 중복해서 불리는 문제가 발생한다. 불필요한 메모리 낭비와 일관성 문제가 발생
    Box가 Container를 virtual하게 상속을 받으면, Container가 각각  Box와 PaperBox에서 독립적으로 생성되지 않고, 하나의 공통 인스턴스가 공유

    즉. 베이스 클래스(Container) 인스턴스가 하나로 통합되어 diamond problem 문제를 방지할 수 있다.

*/


class Box: virtual public Container{ 
    // not virtual inheritance : diamond problem이 생기지 않아서 굳이 쓰지 않아도 되지만, 혹시 모르니 써둔다.

    public :

        Box(float size) : Container(size){}
        ~Box(){}

        void set_capacity() override {
            capacity = size*1;
        }

};

class PaperBox: public Box{
    public:

        PaperBox(float size): Container(size), Box(size){
            *container_code = "PaB";
        } // Container constructor을 쓰는 이유는 Box에서 virtual inheritance를 했기 때문


        ~PaperBox(){}

        void set_capacity() override{
            capacity = size *1.3;
        }
};

class PlasticBox: public Box{

    public:
        PlasticBox(float size) : Container(size), Box(size){
            *container_code = "PlB";
        }
        ~PlasticBox(){}

        void set_capacity() override{
            capacity = size*1.1;
        }
};

class Bag: public Container{
    public:
        Bag(float size) : Container(size){
            *container_code = "B";
        }
        ~Bag(){}

        void set_capacity() override{
            capacity = size *3;
        }

};

class Carrier: public Container{
    public:

        std::vector<Box*> aux_vec; // for auxiliary containers

        Carrier(float size) : Container(size){
            *container_code = "C";
        }
        ~Carrier(){
            //aux_vec에 담기는 것이 동적 할당으로 만들어 진 것일 수도.
            for(auto v: aux_vec){
                delete v;
            }
        }

        void set_capacity() override{
            capacity = size*5;
        }


        /*
         it can attach up to two auxiliary containers of the Box class. 
         The capacity of a Carrier is determined by adding the capacities of attached auxiliary containers to its original capacity, 
         with the capacity of auxiliary containers being 1.1 times their original capacity.
        */

       void add_aux(Box* aux){
            // aux_vec는 최대 두개까지 가능함.
            if (aux_vec.size() == 2){
                //full
                return;
            }

            aux_vec.push_back(aux);
            capacity += 1.1*(aux->get_capacity());
       }

       Box* get_aux(int n){
        if (n > aux_vec.size()){
            return nullptr;
        }
        return aux_vec.at(n-1); // vector indexing
        //return axu_vec[n-1]; // 이것도 가능.
       }


};







void Episode1(){
    cout << "Episode 1:" << endl;
    float alloc_weight = 0;

    Carrier* carrier1 = new Carrier(100);
    carrier1->set_capacity();

    float carrier_size = carrier1->get_size();
    
    Bag* bag1 = new Bag(50);
    bag1->set_capacity();

    Box* box1 = new Box(10);

    PaperBox* pap_box1 = new PaperBox(10);
    pap_box1->set_capacity();
    PaperBox* pap_box2 = new PaperBox(10);
    pap_box2->set_capacity();

    PlasticBox* plas_box1 = new PlasticBox(10);
    plas_box1->set_capacity();
    PlasticBox* plas_box2 = new PlasticBox(10);
    plas_box2->set_capacity();

    carrier1->add_aux(plas_box1);
    carrier1->add_aux(plas_box2);

    Box* aux_box = carrier1->get_aux(1);
    
    alloc_weight+=carrier1->get_capacity();
    alloc_weight+=bag1->get_capacity();
    alloc_weight+=pap_box1->get_capacity();
    alloc_weight+=pap_box2->get_capacity();

    carrier1->set_container_code();
    bag1->set_container_code();
    pap_box1->set_container_code();
    plas_box1->set_container_code();

    string* code = carrier1->get_container_code();

    cout << "Total capacity:" << alloc_weight << endl;
    delete carrier1;
}

void Episode2(){
    cout << "Episode 2:" << endl;
    float alloc_weight = 0;

    Carrier* carrier1 = new Carrier(150);
    carrier1->set_capacity();

    float carrier_size = carrier1->get_size();

    Bag* bag1 = new Bag(30);
    bag1->set_capacity();
    Box* box1 = new Box(10);

    PaperBox* pap_box1 = new PaperBox(20);
    pap_box1->set_capacity();
    PaperBox* pap_box2 = new PaperBox(20);
    pap_box2->set_capacity();
    PlasticBox* plas_box1 = new PlasticBox(10);
    plas_box1->set_capacity();

    carrier1->add_aux(plas_box1);
    
    alloc_weight+=carrier1->get_capacity();
    alloc_weight+=bag1->get_capacity();
    alloc_weight+=pap_box1->get_capacity();
    alloc_weight+=pap_box2->get_capacity();

    carrier1->set_container_code();
    bag1->set_container_code();
    pap_box1->set_container_code();
    plas_box1->set_container_code();

    string* code = carrier1->get_container_code();

    cout << "Total capacity:" << alloc_weight << endl;
    delete carrier1;
}

int main(void){
    Episode1();
    cout << endl;
    Episode2();
}