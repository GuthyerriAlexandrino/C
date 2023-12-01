#include "node.h"
#include <stdlib.h>

struct node {
    int value;
    struct node* previous;
    struct node* next;
};

short get_node_size(void) {
    return sizeof(struct node);
}

short get_value(struct node* node) {
    return node->value;
}

void set_value(struct node* node, short value) {
    node->value = value;
}

struct node* get_next(struct node* node) {
    return (node != NULL) ? node->next : NULL;
}

struct node* get_previous(struct node* node) {
    return (node != NULL) ? node->previous : NULL;
}

struct node* set_next(struct node* node, struct node* other) {
    if (node != NULL)
        node->next = other;
    return node;
}

struct node* set_previous(struct node* node, struct node* other) {
    if (node != NULL)
        node->previous = other;
    return node;
}

struct node* build_node(short value) {
    struct node* node = malloc(get_node_size());
    node->next = NULL;
    node->previous = NULL;
    node->value = value;
    return node;
}

void destroy_node(struct node* node) {
    free(node);
}
