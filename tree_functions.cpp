#include "tree.h"

Tree_Errors TreeInit(binary_tree *tree)
{
    assert(tree != NULL);

    tree->num_of_el = 0;
    tree->root = (node_t *)calloc(1, sizeof(node_t));
    if (tree->root == NULL)
    {
        return ERROR_DURING_THE_CREATION_OF_THE_TREE;
    }

    tree->root->data = POIZON;
    tree->root->left = NULL;
    tree->root->right = NULL;
    tree->root->parent = NULL;

    Tree_Errors err = NO_ERROR;
    if ((err = TreeVerify(tree)))
        return err;

    return err;
}

Tree_Errors TreeVerify(binary_tree *tree)
{
    if (tree == NULL) return NULL_POINTER_ON_TREE;
    else if (tree->num_of_el < 0) return NEGATIVE_NUM_OF_ELEMENTS;
    else if (tree->root == NULL) return NULL_POINTER_ON_ROOT; // не забыть в delete учесть удаление корня
    else if (tree->root->parent != NULL) return ROOT_HAVE_PARENT;    

    return NO_ERROR;
}

void TreeDump(binary_tree *tree, const char *file, int line)
{
    assert(tree != NULL);

    dump_to_console(tree, file, line);

    
}

void dump_to_console(const binary_tree *tree, const char *file, int line)
{
    printf("ListDump called from %s :%d\n", file, line);
    printf("ROOT[%p]\n", tree->root);
    printf("Tree content:\n");
    show_tree(tree->root);
    printf("\n");
}

void show_tree(node_t *node)
{
    if (node == NULL)
        return;
    printf("(");
    show_tree(node->left);
    printf("%d", node->data);
    show_tree(node->right);
    printf(")");
    return;
}

bool open_file_success(FILE *fp, const char * file_name)
{
    if (fp == NULL)
    {
        printf("An error occurred when opening the file %s", file_name);
        return false;
    }

    return true;
}

bool close_files_success(FILE *fp, const char * file_name)
{
    if (fclose(fp))
    {
        printf("An error occurred when closing the file %s", file_name);
        return false;
    }
    
    return true;
}

bool print_error(Tree_Errors err)
{
    switch (err)
    {
        case NO_ERROR:
            return true;

        case NULL_POINTER_ON_TREE:
            printf("The pointer on the TREE is empty\n");
            return true;

        case TREE_IS_EMPTY:
            printf("The TREE is empty\n");
            return true;

        case ELEMENT_NOT_FOUND:
            printf("Еhe item to delete was not found in the tree\n");
            return true;

        case ERROR_DURING_THE_CREATION_OF_THE_TREE:
            printf("An error occurred when was the tree created\n");
            return true;

        case NEGATIVE_NUM_OF_ELEMENTS:
            printf("The number of elements takes a negative value\n");
            return true;

        case NULL_POINTER_ON_ROOT:
            printf("The pointer on the ROOT is empty\n");
            return true;

        case ROOT_HAVE_PARENT:
            printf("The ROOT have a parent\n");
            return true;

        default:
            return false;
    }

    return false;
}