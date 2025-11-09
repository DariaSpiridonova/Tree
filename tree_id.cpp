#include "tree.h"

Tree_Errors tree_insert(binary_tree *tree, used_type value)
{
    assert(tree != NULL);

    Tree_Errors err = NO_ERROR;
    if ((err = TreeVerify(tree)))
        return err;

    if (tree->root->data == POIZON) tree->root->data = value;
    else
    {
        node_t *ptr = tree->root;
        while (true)
        {
            if (value <= ptr->data)
            {
                if (ptr->left == NULL)
                {
                    printf("ptr.data = %d, ptr->left = NULL\n", ptr->data);
                    NodeInit(tree, &ptr->left, ptr, value);
                    printf("ptr->left->data = %d\n", ptr->left->data);
                    tree->num_of_el++;

                    break;
                }
                else 
                {
                    ptr = ptr->left;
                    continue;
                }
            }
            else
            {
                if (ptr->right == NULL)
                {
                    printf("ptr.data = %d, ptr->left = NULL\n", ptr->data);
                    NodeInit(tree, &ptr->right, ptr, value);
                    printf("ptr->right->data = %d\n", ptr->right->data);
                    tree->num_of_el++;

                    break;
                }
                else 
                {
                    ptr = ptr->right;
                    continue;
                }
            }
        }
    }

    if ((err = TreeVerify(tree)))
        return err;

    return err;
}

Tree_Errors NodeDestroy(binary_tree *tree, used_type value)
{
    assert(tree != NULL);

    Tree_Errors err = NO_ERROR;
    if ((err = TreeVerify(tree)))
        return err;

    if (tree->root->data == POIZON) return TREE_IS_EMPTY;
    node_t *ptr = tree->root;
    if (value == ptr->data)
    {
        node_delete(tree, ptr, ptr);
        TreeInit(tree, tree->file_name);
    }
    
    while (true)
    {
        if (value <= ptr->data)
            {
                if (value == ptr->data)
                {
                    node_delete(tree, ptr, ptr);
                }

                if (ptr->left == NULL)
                {
                    return ELEMENT_NOT_FOUND;
                }

                if (value != ptr->left->data)
                {
                    ptr = ptr->left;
                }

                if (value == ptr->left->data)
                {
                    node_delete(tree, ptr->left, ptr->left);
                }
            }

        if (value > ptr->data)
            {
                if (ptr->right == NULL)
                {
                    return ELEMENT_NOT_FOUND;
                }

                if (value != ptr->right->data)
                {
                    ptr = ptr->right;
                }

                if (value == ptr->right->data)
                {
                    node_delete(tree, ptr->right, ptr->right);
                }
            }
    }

    if ((err = TreeVerify(tree)))
        return err;

    return err;
}

Tree_Errors NodeInit(binary_tree *tree, node_t **node, node_t *parent, used_type value)
{
    assert(tree != NULL);
    assert(parent != NULL);

    Tree_Errors err = NO_ERROR;
    if ((err = TreeVerify(tree)))
        return err;

    *node = (node_t *)calloc(1, sizeof(node_t));
    (*node)->parent = parent;
    (*node)->data = value;
    (*node)->left = NULL;
    (*node)->right = NULL;

    if ((err = TreeVerify(tree)))
        return err;

    return err;
}

Tree_Errors node_delete(binary_tree *tree, node_t *node, node_t *ptr)
{
    assert(tree != NULL);
    assert(ptr != NULL);

    Tree_Errors err = NO_ERROR;
    if ((err = TreeVerify(tree)))
        return err;

    if (node == NULL)
    {
        printf("node = NULL");
        return NO_ERROR;
    }
    node_delete(tree, node->left, ptr);
    node_delete(tree, node->right, ptr);

    printf("%d\n", node->data);
    free(node);
    tree->num_of_el--;
    printf("Free\n");
    node = NULL;

    return err;
}