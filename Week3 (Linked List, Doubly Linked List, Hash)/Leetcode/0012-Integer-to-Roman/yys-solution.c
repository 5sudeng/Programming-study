#include <stdio.h>
#include <string.h>


char * intToRoman(int num){ // return character pointer : string이라는 문자열 "배열"을 반환하기 위함


    // 기본적으로 문자열은 string이 아닌 "배열"로서, 문자열의  array이다.
    int values[] = {1000, 900,500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
    char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX","V", "IV","I"}; // 문자열 배열 포인터를 담는 배열

    static char result[20]; // 정적변수, 반환 이후, 즉 함수 블록을 벗어나서라도 해당 메모리는 유지가 되도록.
    result[0] = '\0'; // 문자열 초기화


    /*
    참고 "" 와 '' in C
    "" : '\0' null 로 끝나는 문자 배열
    '': 단일 문자를 의미
    */

   
    
    for(int i = 0; i<13; i++){
        while(num>=values[i]){
            num-= values[i];
            strcat(result, symbols[i]); // 문자열과 문자열의 cat(symbols[i] 자체가 문자열이다.)
            // 단 result는 크기가 충분히 커야 함. cat하고 result 에 저장하기 때문.
        }

    }
    return result;
}

int main(){

    int num = 3749;
    char * answer = intToRoman(num);
    printf("Answer : %s\n", answer);
    return 0;
}