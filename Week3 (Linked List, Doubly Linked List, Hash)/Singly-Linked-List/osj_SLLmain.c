#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SinglyLinkedList.h"

void getStr(char* str) {
  memset(str, ' ', 4 * sizeof(char));
  scanf("%s", str);
  rewind(stdin);
}

int main(void) {
  int action = 0;
  char str[4] = "";
  char pre[4] = "";
  linkedList_h* L;
  listNode* p;
  L = createLinkedList_h();

  while (1) {
    printf("Choose action: \n");
    printf("1: push_front, 2: push_back, 3: insert, 4: pop_front, 5: pop_back\n");
    printf("6: erase, 7: find, 8: reverse, 9: free, 10: end\n");
    scanf("%d", &action);
    rewind(stdin);

    switch (action) {
      case 1:
        printf("String to push: ");
        getStr(str);
        push_front(L, str);
        print(L);
        break;
      case 2:
        printf("String to push: ");
        getStr(str);
        push_back(L, str);
        print(L);
        break;
      case 3:
        printf("String of the previous node: ");
        getStr(pre);
        printf("String to push: ");
        getStr(str);
        insert(L, find(L, pre), str);
        print(L);
        break;
      case 4:
        pop_front(L);
        print(L);
        break;
      case 5:
        pop_back(L);
        print(L);
        break;
      case 6:
        printf("String of node to delete: ");
        getStr(str);
        erase(L, find(L, str));
        print(L);
        break;
      case 7:
        printf("String of node to find: ");
        getStr(str);
        p = find(L, str);
        printf("data: %s, link: %x\n", p->data, p->link);
        break;
      case 8:
        reverse(L);
        print(L);
        break;
      case 9:
        freeLinkedList(L);
        print(L);
        break;
      case 10:
        printf("End the program\n");
        exit(0);
        break;
      default:
        printf("Wrong option: %d\n", action);
    }
  }
  return 0;
}