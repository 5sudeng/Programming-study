#include <stdio.h>
#include <stdlib.h>
#define MAX_POLYS 100
struct term{
    int coef;
    int expo;
    struct term *next;
};

typedef struct term Term;

typedef struct polynomial {
    char name;
    Term *first;
    int size = 0;
} Polynomial;

Polynomial *polys[MAX_POLYS]; //polys는 다항식들에 대한 포인터의 배열
int n=0; //저장된 다항식의 개수


//create instance
Term *create_term_instance() {
    Term *t = (Term*)malloc(sizeof(Term));
    t -> coef = 0;
    t -> expo = 0;
    return t;
}

Polynomial *create_polynomial_instance(char name) {      //polynomial 객체 생성 시 다항식의 이름 지정
    Polynomial *ptr_poly = (Polynomial *)malloc(sizeof(Polynomial));
    ptr_poly -> name = name;
    ptr_poly -> size = 0;
    ptr_poly -> first = NULL;
    return ptr_poly;
}


//poly가 가리키는 다항식에 새로운 하나의 항(c,e) 추가
//c - coefficient(계수). e- exponential(차수)
//e.g. 5x^3-4x^2+12에 3x^2 추가하기
void add_term(int c, int e, Polynomial *poly) {
    if (c == 0) return;
    Term *p = poly->first, *q = NULL;
    while (p != NULL && p->expo > e) {
        q = p;
        p = p->next;
    }

    //동일 차수의 항이 존재하는 경우
    if (p != NULL && p->expo == e) { 
        p->coef += c;
        if (p->coef == 0) { //더했더니 계수가 0이 되는 경우
            if (q == NULL) {   //q가 null이면 첫 번째 노드 삭제
                poly->first = p->next;
            }
            else {
                q->next = p->next;   //q의 다음 노드 삭제.
            }
        poly -> size --;
        free(p); //불필요해진 노드 p free시키기
        }
        return;
    }

    //동일 차수의 항이 존재하지 않는 경우 새 instance만들어서 다항식 사이에 집어넣기!
    Term *term = create_term_instnace();
    term -> coef = c;
    term -> expo = e;

    if (q == NULL) { //맨 앞에 삽입하는 경우
        term -> next = poly->first;
        poly->first = term;
    }
    else { //q의 뒤, p의 앞에 삽입(p는 null일 수 있음)
        term -> next = p;
        q -> next = term;
    }
    poly -> size ++;

}



//다항식의 값을 계산하는 함수
int eval(Polynomial *poly, int x) {
    int result = 0;
    Term *t = poly -> first;
    while (t!=NULL) {
        result += eval(t, x);  //각각의 항의 값을 계산하여 더한다
        t = t->next;
    }
    return result;
}


//하나의 항의 값을 계산하는 함수
int eval(Term *term, int x) {
    int result = term -> coef;
    for (int i = 0; i < term -> expo; i++) {
        result *= x;
    }
    return result;
}


//다항식 출력
void print_poly(Polynomial *p) {
    printf("%c=", p->name);
    Term *t = p-> first;
    while (t != NULL) {
        print_term(t);
        printf("+");
        t = t->next;
    }
}

//출력하기
void print_term(Term *pTerm) {
    printf("%dx^%d", pTerm -> coef, pTerm -> expo);
}


//명령어 처리
void process_command() {
    char command_line[BUFFER_LENGTH];
    char copied[BUFFER_LENGTH];
    char *command, *arg1, *arg2;

    while (1) {
        printf("$ ");
        if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0) continue;
        strcpy(copied, command_line);          //command_line을 copied로 복사해 둔다
        command = strtok(command_line, " ");   //tokenizing
        if (strcmp(command, "print") == 0) {
            arg1 = strtok(NULL, " ");
            if (arg1 = NULL) {
                printf("Invalid arguments. \n");
                continue;
            }
            handle_print(arg1[0]);
        }

        else if (strcmp(command, "calc") == 0) {
            arg1 = strtok(NULL, " ");
            if (arg1 == NULL) {
                printf("Invalid arguments. \n");
                continue;
            }

            arg2 = strtok(NULL, " ");
            if (arg2 == NULL) {
                printf("Invalid arguments. \n");
                continue;
            }
            handle_calc(arg1[0], arg2);
        }

        else if (strcmp(command, "exit") == 0) break;

        else {
            handle_definition(copied);  //다항식 입력받아 정의
        }
    }
}


void handle_definition(char *expression) {
    erase_blanks(expression); //모든 공백 문자들 제거

    char *f_name = strtok(expression, "=");
    if (f_name == NULL || strlen(f_name) != 1) {
        printf("Unsupported command.");
        return;
    }

    char *exp_body = strtok(NULL, "=");
    if (exp_body == NULL || strlen(exp_body) <= 0) {
        printf("Invalid expression format.--");
        return;
    }

    if (exp_body[0] >= 'a' && exp_body[0] < 'z' && exp_body[0] != 'x') {
        char *former = strtok(exp_body, "+");
        if (former == NULL || strlen(former) != 1) {
            printf("Invalid expression format.");
            return;
        }

        char *later = strtok(NULL, "+");
        if (later == NULL || strlen(later != 1)) {
            printf("Invalid expression format.");
            return;
        }
        Polynomial *pol = create_by_add_two_polynomias(f_name[0], former[0], later[0]);

        if (pol == NULL) {
            printf("Invalid expression format.");
            return;
        }
        insert_polynomial(pol);
    }

    else {
        Polynomial *pol = create_by_parse_polynomial(f_name[0], exp_body);
        if (pol == NULL) {
            printf("Invalid expression format.");
            return;
        }
        insert_polynomial(pol);
    }
}


Polynomial *create_by_parse_polynomial(char name, char *body) {
    Polynomial *ptr_poly = create_polynomial_instance(name);

    int i = 0, begin_term = 0;
    while (i < strlen(body)) {
        if (body[i] == '+' || body[i] == '-') i++; //+혹은 -기호 읽음
        while (i < strlen(body) && body[i] != '+' && body[i] != '-') i++;  //하나의 항이 끝날 때까지 전진
        int result = parse_and_add_term(body, begin_term, i, ptr_poly); //body[begin_term, i) 까지가 하나의 항이다. 이 항을 인식해서 다항식에 추가
        if (result == 0) {   //잘못된 항일 경우 0을 반환하고, 그런 경우 만들고 있던 다항식 자체를 destroy
            destroy_polynomial(ptr_poly);
            return NULL;
        }
        begin_term = i; //다음 항의 시작 위치는 i가 된다
    }
    return ptr_poly;
}

void erase_blanks(char *expression) {
    //문자배열 expression에서 모든 공백 문자들을 제거하여 압축
    //문자열의 끝에 '\0'를 추가해준다
}

Term *parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly) {
    int i = begin;
    int sign_coef = 1, coef = 0, expo = 1;
    if (expr[i] == '+') i++;
    else if (expr[i] == '-') {
        sign_coef = -1;
        i++;
    }

    //digit들을 읽어서 계수의 절대값(coef) 계산하기. 하지만 digit들이 하나도 없을 수 있다 (계수가 1 혹은 -1인 경우)
    while (i < end && expr[i] >= '0' && expr[i] <= '9') {
        coef = coef*10 + (int)(expr[i] - '0');
        i++;
    }

    //coef가 0인 경우 계수는 0이 아니라 1 혹은 -1
    if (coef == 0) coef = sign_coef;
    else coef *= sign_coef;

    //더이상 항을 구성하는 문자가 없다면 상수항
    if (i >= end) {   
        add_term(coef, 0, p_poly);
        return 1;
    }

    //계수 다음에 x가 아닌 다른 문자가 등장해서는 안된다
    if (expr[i] != 'x') return 0;
    i++;

    //계수 다음에 x가 나오고 문자열이 끝난다면 1차항이라는 의미
    if (i>=end) {
        add_term(coef, 1, p_poly);
        return 1;
    }

    //x 다음에 ^가 아닌 다른 문자가 등장해서는 안된다
    if (expr[i] != '^') return 0;
    i++;

    //지수 부분을 읽는다
    expo = 0;
    while (i < end && expr[i] >= '0' && expr[i] <= '9'){
        expo = expo*10 + (int)(expr[i] - '0');
        i++;
    }
    add_term(coef, expo, p_poly);
    return 1;
}

void insert_polynomial(Polynomial *ptr_poly) {
    for (int i = 0; i < n; i++) {
        if (polys[i] -> name == ptr_poly -> name) { //기존에 있는 이름일경우
            destroy_polynomial(polys[i]);  //다항식을 덮어쓸 경우에는 기존의 다항식 객체 free시키기
            polys[i] = ptr_poly;
            return;
        }
    }
    polys[n++] = ptr_poly; //배열 마지막 n번째 자리에 넣기
}



void destroy_polynomial(Polynomial *ptr_poly) {
    if (ptr_poly == NULL) return;
    Term *t = ptr_poly -> first, *tmp;

    while (t!=NULL) {
        tmp = t;
        t = t->next;  //다항식에 속한 모든 항들을 free
        free(tmp);
    }
    free(ptr_poly); //ptr_poly가 가리키는 다항식 객체를 free시킨다
}


Polynomial *create_by_add_two_polynomials(char name, char f, char g) {
    /*left as exercise*/
}
