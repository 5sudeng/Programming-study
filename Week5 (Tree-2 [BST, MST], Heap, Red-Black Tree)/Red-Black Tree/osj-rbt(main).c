/*
int main() {
    // Create a new red-black tree
    rbtree *tree = new_rbtree();

    // Insert some values into the tree
    rbtree_insert(tree, 10);
    rbtree_insert(tree, 20);
    rbtree_insert(tree, 30);
    rbtree_insert(tree, 40);
    rbtree_insert(tree, 50);
    rbtree_insert(tree, 60);
    
    // Find and print the minimum value in the tree
    node_t *min = rbtree_min(tree);
    if (min != tree->nil) {
        printf("Minimum value: %d\n", min->key);
    } else {
        printf("The tree is empty.\n");
    }

    // Find and print the maximum value in the tree
    node_t *max = rbtree_max(tree);
    if (max != tree->nil) {
        printf("Maximum value: %d\n", max->key);
    } else {
        printf("The tree is empty.\n");
    }

    // Find a specific value
    int key_to_find = 30;
    node_t *found = rbtree_find(tree, key_to_find);
    if (found != tree->nil) {
        printf("Found value: %d\n", found->key);
    } else {
        printf("Value %d not found in the tree.\n", key_to_find);
    }

    // Convert the tree to an array and print it
    size_t n = 6; // Number of elements inserted
    key_t *arr = (key_t *)malloc(n * sizeof(key_t));
    rbtree_to_array(tree, arr, n);

    printf("Tree elements in order: ");
    for (size_t i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free the allocated array
    free(arr);

    // Delete a node from the tree
    node_t *node_to_delete = rbtree_find(tree, 40);
    if (node_to_delete != tree->nil) {
        rbtree_erase(tree, node_to_delete);
    }

    // Delete the entire tree
    delete_rbtree(tree);

    return 0;
}
*/