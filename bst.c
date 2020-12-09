/*
 * Name: Michael Smith
 * Email: smitmic5@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "bst.h"
#include "stack.h"

struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};

struct bst {
  struct bst_node* root;
};

/*
 * This function  allocates and initializes a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  struct bst* bst = malloc(sizeof(struct bst));
  bst->root = NULL;
  return bst;
}

/*
 * This function frees the memory associated with a BST. 
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  free(bst);
}

/*
 * This function returns the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  if (bst == NULL) {
    return 0;
  }
  return bst_helper(bst->root);
}

int bst_helper(struct bst_node *n) {
  if (n == NULL) {
    return 0;
  }
  return 1 + bst_helper(n->left) + bst_helper(n->right);
}

/*
 * This function inserts a new key/value pair into the BST and orders it. 
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */

struct bst_node* newNode(int key, void *val) {
  struct bst_node* temp = (struct bst_node *)malloc(sizeof(struct bst_node));
  temp->key = key;
  temp->value = val;
  temp->left = temp->right = NULL;
  return temp;
}

void bst_insert(struct bst* bst, int key, void* value) {
  if (bst != NULL) {
    bst->root = insert_helper(bst->root, key, value);
  }
}

struct bst_node* insert_helper(struct bst_node *n, int key, void *val) {
  if (n == NULL) {
    return newNode(key, val);
  }
  if (key < n->key) {
    n->left = insert_helper(n->left, key, val);
  } else {
    n->right = insert_helper(n->right, key, val);
  }
  return n;
}

/*
 * This function removes a key/value pair with a specified key from a
 * given BST. 
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  if (bst == NULL) {
    return;
  }
  bst->root = deleteNode(bst->root, key);
}

struct bst_node * inSuccess(struct bst_node* node) {
  struct bst_node* current = node;
  while (current && current->left != NULL) {
    current = current->left;
  }
  return current;
}

struct bst_node* deleteNode(struct bst_node* root, int key) {
  if (root == NULL) {
    return root;
  }
  if (key < root->key) {
    root->left = deleteNode(root->left, key);
  } else if (key > root->key) {
    root->right = deleteNode(root->right, key);
  } else {
    if (root->left == NULL) {
      struct bst_node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct bst_node *temp = root->left;
      free(root);
      return temp;
    }
    struct bst_node* temp = inSuccess(root->right);
    root->key = temp->key;
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

/*
 * This function returns the value associated with a specified key in a
 * given BST. 
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  if (bst == NULL) {
    return NULL;
  }
  return find_helper(bst->root, key);
}

void *find_helper(struct bst_node *n, int key) {
  if (n == NULL) {
    return NULL;
  } else if (n->key == key) {
    return n->value;
  } else if (key < n->key) {
    return find_helper(n->left, key);
  } else {
    return find_helper(n->right, key);
  }
}

/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};

/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
  return NULL;
}

/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator* iter) {
  stack_free(iter->stack);
  free(iter);
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
  if (stack_isempty(iter->stack) == 1) {
    return 0;
  } else {
    return 1;
  }
}

/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {
  if (value) {
    *value = NULL;
  }
  return 0;
}
