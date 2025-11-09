#ifndef TREE
#define TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#define TREE_DUMP(tree)\
        TreeDump(tree,__FILE__, __LINE__)

typedef int used_type;

const used_type POIZON = 765418;
const ssize_t SIZE_OF_NAME = 200;
const ssize_t width = 80;
const ssize_t heigth = 12;
const char link_to_graphviz_file[] = "../Graphviz/tree_graph_for_";

struct NODE_T
{
    used_type data;
    struct NODE_T *left;
    struct NODE_T *right;
    struct NODE_T *parent;
};

typedef struct NODE_T node_t;

typedef struct
{
    ssize_t num_of_el;
    node_t *root;
    const char *file_name;
} binary_tree;

enum Tree_Errors
{
    NO_ERROR,
    NULL_POINTER_ON_TREE,
    TREE_IS_EMPTY,
    ELEMENT_NOT_FOUND,
    ERROR_DURING_THE_CREATION_OF_THE_TREE,
    NEGATIVE_NUM_OF_ELEMENTS,
    NULL_POINTER_ON_ROOT,
    ROOT_HAVE_PARENT    
};

Tree_Errors TreeInit(binary_tree *tree, const char *logfile_name);
Tree_Errors TreeVerify(binary_tree *tree);

void TreeDump(binary_tree *tree, const char *file, int line);
void dump_to_console(const binary_tree *tree, const char *file, int line, ssize_t *rank);
void dump_to_logfile(const binary_tree *tree, const char *logfile_name, const char *gvfile_name, ssize_t *rank);
void dump(FILE *fp, const binary_tree *tree, ssize_t *rank);
void show_tree(FILE *fp, node_t *node, ssize_t *rank, ssize_t *cur_rank);
//void create_graph(const binary_tree *tree, const char *gvfile_name, ssize_t rank);

bool open_file_success(FILE *fp, const char * file_name);
bool close_files_success(FILE *fp, const char * file_name);

bool print_error(Tree_Errors err);

Tree_Errors tree_insert(binary_tree *tree, used_type value);
Tree_Errors node_delete(binary_tree *tree, node_t *node, node_t *ptr);
Tree_Errors NodeInit(binary_tree *tree, node_t **node, node_t *parent, used_type value);
Tree_Errors NodeDestroy(binary_tree *tree, used_type value);

#endif