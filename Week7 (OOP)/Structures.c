// python 의 class와 비슷하면서 좀 더 원시적인 형태, 단 method는 없음.
//여러가지 데이터 타입을 하나의 그룹으로 묶는 법


#include <stdio.h>
#include <string.h>
// #include <stdlib.h>
#define Namesize 10
#define STUDENT_NUMS 5

struct StudentType{
    char name[Namesize]; 
    // 9개의 글자와 \0 null 문자 하나 저장 가능.
    /*
    C에서 배열을 직접 수정이 불가능하다.
    */

    int ID;
    int midterm;
    int final;
    int total;
};

typedef struct StudentType Student;

//관련 method는 이렇게 밖에서 정의 : 선언만 해주고 정의는 나중에 해도 됌.
void calculateTotal(Student *s); // 단 pointer로 접근한다. 그래야 직접 메모리 접근 가능ㄴ


///여기다가 해도 됨.
void calculateTotal(Student *s){
    s->total = s->midterm + (*s).final;
}


typedef struct Cafetype
{
    char name[Namesize];
    int coffee_cost;
    int employee;
    
}cafe; //typedef <type> <name> : 타입명을 커스텀 화

void Episode1(){
    printf("Episode1\n");
    struct StudentType A; // struct StudentType까지가 type임.
    A.midterm =10;
    // A.name = "yoonseok"; // 식이 수정할 수 있는 lvalue이어야 한다.?
    char name[Namesize] = "yoonseok";
    strcpy(A.name, name); // 이런식으로 복사해야 함.



    // 아님 시작과 함께 이런식으로 초기화도 가능
    struct StudentType B = {"yoonseok", 20};

    //array도 지원 가능
    cafe c[5]; // 0~4모두 all cafe
    c[0].employee = 10;
    
    cafe* cafeptr = &c[1];
    cafeptr->coffee_cost = 100;

 
}


void Episode2(){
    printf("Episode2 \n");

    //define Student array
    Student s[STUDENT_NUMS];


    //receive inputs
    for(int i =0; i < STUDENT_NUMS; i++)
    {
        printf("input for student #%d\n", i+1);

        printf("\t name : ");
        scanf("%9s", s[i].name); // name은 문자배열이고, s[i].name 은 배열중 가장 첫번째의 주소를 가리킨다.

        printf("\t ID : ");
        scanf("%d", &s[i].ID);

        printf("\t midterm : ");
        scanf("%d", &s[i].midterm);

        printf("\t final : ");
        scanf("%d", &s[i].final);


    }

    //calculate total for each student
    for(int i = 0; i<STUDENT_NUMS; i++){
        calculateTotal(&s[i]);
    }

    //print each total score
    for (int i = 0; i<STUDENT_NUMS; i++)
    {
        printf("total score for student #%d(%s) is %d\n", i, s[i].name, s[i].total);
    }

    

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct structPoint;
struct structPoint
{
    float x;
    float y;

};
typedef struct structPoint Point;

struct structRectangle;
struct structRectangle
{
    Point a;
    Point b;
};
typedef struct structRectangle Rectangle;


//////////////////////////

/* declare functions*/
float area(Rectangle rect);
float width(Rectangle rect);
float height(Rectangle rect);
Point centroid(Rectangle rect);



void Episode3() {
    Point a = {10, 40}; // a.x = 10, a.y = 40
    Point b = {55, 10}; // b.x = 55, b.y = 10

    /* Write your code here */

    // declaration Rectalge
    Rectangle rect;
    rect.a = a;
    rect.b = b;
    Point c;
    float w;
    float h;
    float A;


    c = centroid(rect);
    w = width(rect);
    h = height(rect);
    A = area(rect);

    printf("Bounding Box : (%.1f, %.1f, %.1f, %.1f)\n", c.x, c.y, w, h);
    printf("Area : %.1f\n", A);
    //////////////////////////    

}

/* define functions - area, width, height, centroid */
/* Write your code here */
float area(Rectangle rect)
{
    float w;
    float h;
    w = width(rect);
    h = height(rect);

    return w *h;
}

float width(Rectangle rect)
{
    return rect.b.x - rect.a.x;
}
float height(Rectangle rect)
{
    return rect.a.y - rect.b.y;
}
Point centroid(Rectangle rect)
{
    Point result;
    result.x = (rect.a.x + rect.b.x) /2;
    result.y = (rect.a.y + rect.b.y) /2;
    return result;
}







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    Episode1();
    Episode2();
    Episode3();


    return -1;

}


