
#include "avl.h"
#include <string.h>
#include <stdio.h>

int avl_height(AVLNode *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

static int avl_balance(AVLNode *node)
{
    if (node == NULL)
        return 0;
    return avl_height(node->left) - avl_height(node->right);
}

static int max(int a, int b)
{
    return (a > b) ? a : b;
}

static void update_height(AVLNode *node)
{
    node->height = 1 + max(avl_height(node->left), avl_height(node->right));
}

AVLNode *avl_create_node(const char *key, void *data)
{
    AVLNode *node = malloc(sizeof(AVLNode));
    if (node == NULL)
        return NULL;
    node->key = strdup(key);
    if (node->key == NULL)
    {
        free(node);
        return NULL;
    }
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static AVLNode *rotate_right(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    update_height(y);
    update_height(x);
    return x;
}

static AVLNode *rotate_left(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    update_height(x);
    update_height(y);
    return y;
}

AVLNode *avl_insert(AVLNode *root, const char *key, void *data, AVLNode **found)
{
    if (root == NULL)
    {
        AVLNode *node = avl_create_node(key, data);
        if (found)
            *found = node;
        return node;
    }

    int cmp = strcmp(key, root->key);
    if (cmp < 0)
    {
        root->left = avl_insert(root->left, key, data, found);
    }
    else if (cmp > 0)
    {
        root->right = avl_insert(root->right, key, data, found);
    }
    else
    {
        if (found)
            *found = root;
        return root;
    }

    update_height(root);
    int balance = avl_balance(root);

    if (balance > 1 && strcmp(key, root->left->key) < 0)
        return rotate_right(root);

    if (balance < -1 && strcmp(key, root->right->key) > 0)
        return rotate_left(root);

    if (balance > 1 && strcmp(key, root->left->key) > 0)
    {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && strcmp(key, root->right->key) < 0)
    {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

AVLNode *avl_search(AVLNode *root, const char *key)
{
    if (root == NULL)
        return NULL;
    int cmp = strcmp(key, root->key);
    if (cmp < 0)
        return avl_search(root->left, key);
    if (cmp > 0)
        return avl_search(root->right, key);
    return root;
}

void avl_traverse_reverse(AVLNode *root, void (*callback)(AVLNode *, void *), void *arg)
{
    if (root == NULL)
        return;
    avl_traverse_reverse(root->right, callback, arg);
    callback(root, arg);
    avl_traverse_reverse(root->left, callback, arg);
}

void avl_free(AVLNode *root, void (*free_data)(void *))
{
    if (root == NULL)
        return;
    avl_free(root->left, free_data);
    avl_free(root->right, free_data);
    free(root->key);
    if (free_data && root->data)
        free_data(root->data);
    free(root);
}

int avl_count(AVLNode *root)
{
    if (root == NULL)
        return 0;
    return 1 + avl_count(root->left) + avl_count(root->right);
}
