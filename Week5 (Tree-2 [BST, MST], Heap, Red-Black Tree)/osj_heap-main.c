//
//  main.c
//  heap
//
//  Created by Sujeong Oh on 2022/12/25.
//

#include <stdio.h>
#include "heap.h"

int main(void) {
  int action = 0, item = 0;
  heapType* heap = createHeap();
  push(heap, 20);
  push(heap, 15);
  push(heap, 19);
  push(heap, 8);
  push(heap, 13);
  push(heap, 10);

  print(heap);

  while (1) {
    printf("Choose action: \n");
    printf("1: push, 2: top, 3: pop, 4: print, 5: size, 6: exit\n");
    scanf("%d", &action);
    rewind(stdin);

    switch (action) {
      case 1:
        printf("Value to push : ");
        scanf("%d", &item);
        rewind(stdin);
        push(heap, item);
        print(heap);
        break;
      case 2:
        printf("top(): %d\n", top(heap));
        print(heap);
        break;
      case 3:
        pop(heap);
        print(heap);
        break;
      case 4:
        print(heap);
        break;
      case 5:
        printf("size(): %d\n", size(heap));
        break;
      case 6:
        printf("End the program\n");
        return 0;
      default:
        printf("Invalid option. Choose again. \n");
        break;
    }
  }
  return 0;
}
