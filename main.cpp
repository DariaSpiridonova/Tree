#include "tree.h"

int main()
{
    binary_tree tree;

    TreeInit(&tree);
    tree_insert(&tree, 10);
    tree_insert(&tree, 5);
    tree_insert(&tree, 20);
    tree_insert(&tree, 3);
    tree_insert(&tree, 7);
    tree_insert(&tree, 15);
    tree_insert(&tree, 6);
    tree_insert(&tree, 13);
    tree_insert(&tree, 16);
    TREE_DUMP(&tree);

    node_delete(&tree, tree.root, tree.root);
    return 0;
}