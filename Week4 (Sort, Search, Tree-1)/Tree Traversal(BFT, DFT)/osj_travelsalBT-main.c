//
//  main.c
//  travelsalBT2
//
//  Created by Sujeong Oh on 2022/12/21.
//

#include <stdio.h>
#include "traversalBT.h"

int main(void) {
    // (A*B-C/D)
    treeNode* n7 = makeRootNode('D', NULL, NULL);
    treeNode* n6 = makeRootNode('C', NULL, NULL);
    treeNode* n5 = makeRootNode('B', NULL, NULL);
    treeNode* n4 = makeRootNode('A', NULL, NULL);
    treeNode* n3 = makeRootNode('/', n6, n7);
    treeNode* n2 = makeRootNode('*', n4, n5);
    treeNode* n1 = makeRootNode('-', n2, n3);

    printf("\n preorder : ");
    preorder1(n1);

    printf("\n inorder : ");
    inorder(n1);

    printf("\n postorder : ");
    postorder1(n1);
    
    puts("");

    getchar();  return 0;
}
