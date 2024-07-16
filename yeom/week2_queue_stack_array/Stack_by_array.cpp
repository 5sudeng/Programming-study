// stack implementation by array


#include<iostream>
#include<algorithm> // std::copy
using namespace std;

class Stack_by_array{
    public:
        int *array; // using poitner, dynamic allocation
        int top;
        int maxSize;

        //constructor
        Stack_by_array(int max){
            top = 0;
            maxSize = max;
            array = new int[max];
        }
        
        //destructor
        ~Stack_by_array(){
            delete[] array;
        }

        int size()
        {
            return top;
        }
        int isEmpty(){
            return top == 0;
        }

        int top(){
            if (isEmpty()) return;
            return array[top];
        }

        void push(int item){
            if (size() == maxSize -1){
                cout<<"full size"<<endl;
                
                maxSize = 2*maxSize;
                int *new_array;
                new_array = new int[maxSize];
                // copy all array data to new array_
                std::copy(array, array + (maxSize / 2), new_array);
                delete[] array;
                array = new_array;


                // //loop copy
                // for (int i = 0; i < maxSize/2 ; ++i){
                //     new_array[i] = array[i];
                // }
                // delete[] array;
                // array = new_array;

            }
            else{
                array[top++] = item;
                return;
            }
        }

        int pop(){
            if (isEmpty()) return;
            return array[top--];
        }

        
};