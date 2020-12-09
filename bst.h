#ifndef __BST_H
#define __BST_H

struct bst;
struct bst_iterator;

struct bst_node* newNode(int key, void *val);
struct bst_node* insert_helper(struct bst_node *n, int key, void *val);
int bst_helper(struct bst_node *n);
struct bst_node * inSuccess(struct bst_node* node);
struct bst_node* deleteNode(struct bst_node* root, int key);
void *find_helper(struct bst_node *n, int key);
struct bst* bst_create();
void bst_free(struct bst* bst);
int bst_size(struct bst* bst);
void bst_insert(struct bst* bst, int key, void* value);
void bst_remove(struct bst* bst, int key);
void* bst_get(struct bst* bst, int key);

struct bst_iterator;

struct bst_iterator* bst_iterator_create(struct bst* bst);
void bst_iterator_free(struct bst_iterator* iter);
int bst_iterator_has_next(struct bst_iterator* iter);
int bst_iterator_next(struct bst_iterator* iter, void** value);

#endif
