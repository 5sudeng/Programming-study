#include <stdio.h>
#include <stdlib.h>

#include "cQueue.h"

void getElement(element *data) {
  scanf("%d", data);
  rewind(stdin);
}

int main(void) {
  int action = 0;
  QueueType* cQ = createCQueue();
  element data;

  while (1) {
    printf("Choose action: \n");
    printf("1: push, 2: pop, 3: front, 4: back, 5: empty, 6: full, 7: end\n");
    scanf("%d", &action);
    rewind(stdin);

    switch (action) {
      case 1:
        printf("Digit to push: ");
        getElement(&data);
        push(cQ, data);
        print(cQ);
        break;
      case 2:
        printf("pop(): %d\n", pop(cQ));
        print(cQ);
        break;
      case 3:
        printf("front(): %d\n", front(cQ));
        print(cQ);
        break;
      case 4:
        printf("back(): %d\n", back(cQ));
        print(cQ);
        break;
      case 5:
        printf("isEmpty(): %d\n", isEmpty(cQ));
        print(cQ);
        break;
      case 6:
        printf("isFull(): %d\n", isFull(cQ));
        print(cQ);
        break;
      case 7:
        printf("End the program\n");
        exit(0);
        break;
      default:
        printf("Wrong option: %d\n", action);
    }
  }
  return 0;
}
