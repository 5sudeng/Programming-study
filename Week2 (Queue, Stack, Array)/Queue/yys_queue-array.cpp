#include<iostream>
using namespace std;


const int maxSize = 5;

class MyQueue{
    public:
        int isEmpty();
        int isFull();
        void Enqueue(int t);
        int Dequeue();
        void Resize();


    private:
        int front = 0; 
        int rear = 0; // circular queue이기 때문에, 같은 값으로 시작
        int queue[maxSize]; // 배열로 구현, maxSize가 정해져있음. 

};


//out of class definition
int MyQueue::isEmpty(){
    if (front == rear){
        return true;
    }
    return false;
}

int MyQueue::isFull(){
    if ((rear +1)% maxSize == front){
        return true;
    }
    return false;
}

void MyQueue::Resize(){

}

void MyQueue::Enqueue(int t){
  
    if(isFull()){
        cout<<"queue is full"<<endl;
        Resize();
    }
    
    // enqueue at rear++
    rear = (rear+1) % maxSize; // 역시 circular이기 때문에 modular 계산
    queue[rear] = t;
}

int MyQueue::Dequeue(){

    if (!isEmpty()){
        // dequeue at ++front
        return queue[++front % maxSize]; // maxSize modular 계산을 하는 이유 : 순환이기에.
    }


    return -1;
}
