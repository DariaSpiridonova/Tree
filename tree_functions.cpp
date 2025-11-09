#include "tree.h"

Tree_Errors TreeInit(binary_tree *tree, const char *logfile_name)
{
    assert(tree != NULL);

    tree->num_of_el = 1;
    tree->file_name = logfile_name;
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

    ssize_t rank = 0;
    dump_to_console(tree, file, line, &rank);

    time_t rawtime;      
    struct tm *timeinfo; 
    char buffer[80];

    // Get the current calendar time
    time(&rawtime);

    // Convert the calendar time to local time
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%Y_%m_%d_%H_%M_%S", timeinfo);

    // Print the formatted time string
    printf("Current time: %s\n", buffer);
    struct timespec tstart={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);

    char gvfile_name[SIZE_OF_NAME] = {0};
    sprintf(gvfile_name, "%s%s%s%ld.gv", link_to_graphviz_file, tree->file_name, buffer, tstart.tv_nsec);
    printf("%s%s%s%ld.gv\n", link_to_graphviz_file, tree->file_name, buffer, tstart.tv_nsec);

    dump_to_logfile(tree, tree->file_name, gvfile_name, &rank);

    //create_graph(tree, gvfile_name, rank);
}

void dump_to_console(const binary_tree *tree, const char *file, int line, ssize_t *rank)
{
    printf("ListDump called from %s :%d\n", file, line);
    dump(stdout, tree, rank);
}

void dump(FILE *fp, const binary_tree *tree, ssize_t *rank)
{
    fprintf(fp, "ROOT[%p]\n", tree->root);
    fprintf(fp, "{\n");
    fprintf(fp, "    num_of_el = %zd\n", tree->num_of_el);
    fprintf(fp, "    Tree content:\n");
    ssize_t cur_rank = 0;
    show_tree(fp, tree->root, rank, &cur_rank);
    fprintf(fp, "    rank = %zd\n", *rank);
    fprintf(fp, "\n}");
    fprintf(fp, "\n");
}

void dump_to_logfile(const binary_tree *tree, const char *logfile_name, const char *gvfile_name, ssize_t *rank)
{
    FILE *fp = fopen(logfile_name, "a");

    if (!open_file_success(fp, logfile_name))
    {
        return;
    }

    fprintf(fp, "<pre>\n");
    dump(fp, tree, rank);

    fprintf(fp, "<img src=\"%*s.png\" alt=\"Graphviz image\" width=\"1800\">", (int)strlen(gvfile_name) - 3, gvfile_name);

    if (!close_files_success(fp, logfile_name))
    {
        return;
    }
}

/*void create_graph(const binary_tree *tree, const char *gvfile_name, ssize_t rank)
{
    FILE *fp = fopen(gvfile_name, "w");

    if (!open_file_success(fp, gvfile_name))
    {
        return;
    }

    double dis = width / (pow(2, rank - 1) - 1);
    ssize_t cur_rank = 1;
    double step = (double) heigth / (rank - 1);

    fprintf(fp, "digraph {\n");
    fprintf(fp, "   rankdir=TB;\n");
    fprintf(fp, "   node[shape=\"record\", style=\"filled\", fillcolor=\"grey\", fontsize=20, pin = true];\n");
    fprintf(fp, "splines = ortho;\n");
    fprintf(fp, "rank = same;\n");
    //fprintf(fp, "bgcolor=\"LightBlue\";\n");
    fprintf(fp, "invis [shape = record, style = \"invis\", height = 6 , pos = \"2.0, 0.0!\"]\n");
    fprintf(fp, "   \"0\" [label = \"head = %ld | tail = %ld | free = %ld\", fillcolor = \"yellow\", pos = \"0.0, 0.0!\"];\n", list->head, list->tail, list->free);
    for (ssize_t i = 1; i < list->capacity + 1; i++)
    {
        printf("next = %zd\n", list->next[i]);
        fprintf(fp, "   \"%zd\" [label = \"data index = %zd | element = %d | {prev = %zd | next = %zd}\", fillcolor = \"aqua\", pos = \"%zd.0, 0.0!\"];\n", i, i, list->data[i], list->prev[i], list->next[i], 4 * i);
    }
    print_pointer_on_significant_el(fp, "head", list->head);
    print_pointer_on_significant_el(fp, "tail", list->tail);
    print_pointer_on_significant_el(fp, "free", list->free);

    fprintf(fp, "   \"0\" -> \"1\"");
    for (ssize_t i = 2; i < list->capacity + 1; i++)
    {
        fprintf(fp, "-> \"%zd\"", i);
    }
    fprintf(fp, "[style = invis];\n");
    fprintf(fp, "   ");

    ssize_t i = list->next[list->head];
    if (i != 0)
    {
        fprintf(fp, "\"%zd\"", list->head);
        for (i = list->next[list->head]; i != 0; i = list->next[i])
        {
            fprintf(fp, " -> \"%zd\"", i);
        }
        fprintf(fp, "[style = \"\", color = \"black\"];\n");
    }

    link_with_el(fp, 'h', list->head);
    link_with_el(fp, 't', list->tail);
    link_with_el(fp, 'f', list->free);
    
    i = list->prev[list->tail];
    if (i != 0)
    {   
        fprintf(fp, "\"%zd\"", list->tail);
        for (i = list->prev[list->tail]; i != 0; i = list->prev[i])
        {
            fprintf(fp, " -> \"%zd\"", i);
        }
        fprintf(fp, "[style = \"\", color = \"red\"];\n");
    }

        for (i = list->free; i != 0; i = list->next[i])
    {
        fprintf(fp, "\"%zd\"[fillcolor = \"violet\"];\n", i);
    }

    if ((i = list->next[list->free]) != 0)
    {
        fprintf(fp, "\"%zd\"", list->free);
        for (i = list->next[list->free]; i != 0; i = list->next[i])
        {
            fprintf(fp, " -> \"%zd\"", i);
        }
        fprintf(fp, "[style = \"\", color = \"brown\"];\n");
    }

    fprintf(fp, "}");
 
    if (!close_files_success(fp, gvfile_name))
    {
        return;
    }

    char command[SIZE_OF_NAME * 2] = {0};
    printf("gvfile_name = %s, gvfile_name = %*s\n", gvfile_name, (int)strlen(gvfile_name) - 3, gvfile_name);
    sprintf(command, "dot -Kfdp %s -Tpng -o %*s.png", gvfile_name, (int)strlen(gvfile_name) - 3, gvfile_name);
    
    int error = system(command);
    if (error)
    {
        printf("%d", error);
        //assert(0);
    }
}*/


void show_tree(FILE *fp, node_t *node, ssize_t *rank, ssize_t *cur_rank)
{
    if (node == NULL)
        return;
    fprintf(fp, "(");
    (*cur_rank)++;
    show_tree(fp, node->left, rank, cur_rank);
    if (*cur_rank > *rank) *rank = *cur_rank;
    fprintf(fp, "\n        node.parent = %p\n        NODE.DATA = %d\n        node.left = %p\n        node.right = %p\n\n", node->parent, node->data, node->left, node->right);
    show_tree(fp, node->right, rank, cur_rank);
    fprintf(fp, ")");
    (*cur_rank)--;
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