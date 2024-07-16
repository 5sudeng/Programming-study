#include<iostream>
using namespace std;


// const int maxSize = 5;

class MyQueue{

    private:
        int front = 0; 
        int rear = 0; // circular queue이기 때문에, 같은 값으로 시작
        // int queue[maxSize]; // 배열로 구현, maxSize가 정해져있음. 
        int *queue; // 동적 할당으로 변경 : for resize
        int maxSize;

    public:

        MyQueue(int max){
            maxSize = max;
            queue = new int[maxSize];
        }

        ~MyQueue(){ // destructor
            delete[] queue;
        }

        int isEmpty();
        int isFull();
        void Enqueue(int t);
        int Dequeue();
        void Resize();
        


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
    
    maxSize *=2; // 두배로 키우기
    int *new_queue;
    new_queue = new int[maxSize];

    //copy original to new one
    //std::copy(queue, queue + (maxSize / 2), new_queue);
    for (int i=0; i<maxSize/2; ++i){
        new_queue[i] = queue[i];
    }
    delete[] queue;
    queue = new_queue;

    cout<<"Successfully resize"<<endl;

}

void MyQueue::Enqueue(int t){
  
    if(isFull()){
        cout<<"queue is full"<<endl;
        Resize();
    }
    
    // enqueue at rear++
    rear = (rear+1) % maxSize; // 역시 circular이기 때문에 modular 계산
    queue[rear] = t;
    cout<<"enqueue : " <<t<<endl;
}

int MyQueue::Dequeue(){

    if (!isEmpty()){
        // dequeue at ++front
        return queue[++front % maxSize]; // maxSize modular 계산을 하는 이유 : 순환이기에.
    }


    return -1;
}



int main() {
    MyQueue q(5);

    // Test Enqueue and Dequeue
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    q.Enqueue(40);
    q.Enqueue(50); // Queue should resize here
    q.Enqueue(60);

    cout << "Dequeue: " << q.Dequeue() << endl; // Expected: 10
    cout << "Dequeue: " << q.Dequeue() << endl; // Expected: 20
    cout << "Dequeue: " << q.Dequeue() << endl; // Expected: 30

    // Test Enqueue after Dequeue
    q.Enqueue(70);
    q.Enqueue(80);

    cout << "Dequeue: " << q.Dequeue() << endl; // Expected: 40
    cout << "Dequeue: " << q.Dequeue() << endl; // Expected: 50
    cout << "Dequeue: " << q.Dequeue() << endl; // Expected: 60
    cout << "Dequeue: " << q.Dequeue() << endl; // Expected: 70
    cout << "Dequeue: " << q.Dequeue() << endl; // Expected: 80

    // Test Dequeue on empty queue
    cout << "Dequeue: " << q.Dequeue() << endl; // Expected: -1 (queue is empty)

    return 0;
}