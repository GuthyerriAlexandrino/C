#include "node.h"
#include <stdlib.h>
#include <stdbool.h>

struct node {
    const char* value;
    struct node* previous;
    struct node* next;
    bool allocated;
};

int get_node_size(void) {
    return sizeof(struct node);
}

const char* get_value(struct node* node) {
    if (node == NULL)
        return NULL;
    return node->value;
}

void set_value(struct node* node, const char* value) {
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

struct node* build_node(const char* value, bool allocated) {
    struct node* node = malloc(get_node_size());
    node->next = NULL;
    node->previous = NULL;
    node->value = value;
    return node;
}

void destroy_node(struct node* node) {
    if (node->allocated)
        free((char*)node->value);
    free(node);
}
