#include <iostream>
#include <string.h>

using namespace std;

// Implement definition of all classes and the member functions in this file.

class Container{
public:
    float size;
    float capacity;
    string container_type;
    string capacity_code;
    string* container_code = new string;

    Container(float size) : size(size) {}
    ~Container() { delete container_code; }
    
    float get_size() const { return size; }
    virtual void set_capacity() = 0;
    float get_capacity() const { return capacity; }

    void set_container_code() {
    
        if (capacity < 100) {capacity_code = "1"; }
        else if (capacity < 200) { capacity_code = "2"; }
        else { capacity_code = "3"; }

        *container_code = container_type + capacity_code;
    }
    string* get_container_code() { return container_code; }

};

class Box: public Container{
public:
    Box(float size) : Container(size) { }
    ~Box() {}

    void set_capacity() override {
        capacity = size * 1;
    }
};

class PaperBox: public Box{
public:
    PaperBox(float size) : Box(size) {
        container_type = "PaB";
    }
    ~PaperBox() {}

    void set_capacity() override {
        capacity = size * 1.3;
    }

};

class PlasticBox: public Box{
public:
    PlasticBox(float size) : Box(size) {
        container_type = "PlB";
    }
    ~PlasticBox() {}

    void set_capacity() override {
        capacity = size * 1.1;
    }
};

class Bag: public Container{
public:
    Bag(float size) : Container(size) {
        container_type = "B";
    }
    ~Bag() {}

    void set_capacity() override {
        capacity = size * 3;
    }
};

class Carrier: public Container{
public:
    Box* aux1 = nullptr;
    Box* aux2 = nullptr;

    Carrier(float size) : Container(size) {
        container_type = "C";
    }
    ~Carrier() { delete aux1; delete aux2; }

    void set_capacity() override {
        capacity = size * 5;
    }

    void add_aux(Box* aux) {
        if (!aux1) {
            aux1 = aux;
            capacity += aux->get_capacity() * 1.1;
        } else if (!aux2) {
            aux2 = aux;
            capacity += aux->get_capacity() * 1.1;
        } else {
            return;
        }
    }

    Box* get_aux(int n) {
        if (n==1 && aux1) { return aux1; }
        else if (n==2 && aux2) { return aux2; }
        else { return nullptr; }
    }
};