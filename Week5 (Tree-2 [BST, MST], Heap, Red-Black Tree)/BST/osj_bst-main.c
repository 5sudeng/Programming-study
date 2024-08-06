//
//  main.c
//  BST
//
//  Created by Sujeong Oh on 2022/12/21.
//

#include <stdio.h>
#include "bst.h"

void menu(void);

int main(void) {
  treeNode* root = NULL;
  treeNode* foundedNode = NULL;
  int action = 0, key = 0;

  root = insert(root, 8);
  insert(root, 3);
  insert(root, 10);
  insert(root, 2);
  insert(root, 5);
  insert(root, 14);
  insert(root, 11);
  insert(root, 16);

  while (1) {
    printf("Choose action: \n");
    printf("1: insert, 2: erase, 3: find, 4: print, 5: exit\n");
    scanf("%d", &action);
    rewind(stdin);

    switch (action) {
      case 1:
        printf("Value to insert : ");
        scanf("%d", &key);
        rewind(stdin);
        insert(root, key);
        inorder(root);
        printf("\n");
        break;
      case 2:
        printf("Value to erase : ");
        scanf("%d", &key);
        rewind(stdin);
        erases(root, key);
        inorder(root);
        printf("\n");
        break;
      case 3:
        printf("Value to find : ");
        scanf("%d", &key);
        rewind(stdin);
        foundedNode = find(root, key);
        if (foundedNode != NULL)
          printf("Found %d!\n", key);
        else
          printf("Unable to find %d!\n", key);
        inorder(root);
        printf("\n");
        break;
      case 4:
        inorder(root);
        printf("\n");
        break;
      case 5:
        printf("End the program\n");
        return 0;
      default:
        printf("Invalid option. Choose again. \n");
        break;
    }
  }
}

