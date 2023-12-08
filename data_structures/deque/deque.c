#include "deque.h"
#include "../node/node.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct deque {
    struct node *first;
    struct node *last;
    struct node *next;

    size_t size;
};

static struct node* goto_position(size_t, size_t, struct deque*);
void nullify_deque(struct deque*);

static int get_deque_size() {
    return sizeof(struct deque);
}

size_t get_size(struct deque* deque) {
    return deque->size;
}

const char* iterate_next(struct deque* deque) {
    if (deque->next == NULL)
        return get_value(deque->next = deque->first);

    deque->next = get_next(deque->next);
    return get_value(deque->next);
}

const char* iterate_previous(struct deque* deque) {
    if (deque->next == NULL)
        return get_value(deque->next = deque->last);

    deque->next = get_previous(deque->next);
    return get_value(deque->next);
}

void push_front(struct deque* deque, const char* elem, bool allocated) {
    struct node *temp = deque->first;
    deque->first = build_node(elem, allocated);
    set_next(deque->first, temp);
    set_previous(temp, deque->first);
    if (deque->size++ == 0)
        deque->last = deque->first;
}

void push_back(struct deque* deque, const char* elem, bool allocated) {
    if (deque->first == NULL) {
        deque->size++;
        deque->first = deque->last = build_node(elem, allocated);
        return;
    }
    struct node* new_node = build_node(elem, allocated);
    set_next(deque->last, new_node);
    set_previous(new_node, deque->last);
    deque->size++;
    deque->last = get_next(deque->last);
}

const char* front(struct deque* deque) {
    return get_value(deque->first);
}

const char* back(struct deque* deque) {
    return get_value(deque->last);
}

const char* get(struct deque* deque, size_t index) {
    if (index < 0 || index >= deque->size)
        return NULL;

    struct node* node = goto_position(index, deque->size / 2, deque);
    return get_value(node);
}

void set(struct deque* deque, size_t index, const char* value) {
    if (index < 0 || index >= deque->size)
        return;

    struct node* node = goto_position(index, deque->size / 2, deque);
    set_value(node, value);
}

const char* pop_front(struct deque* deque) {
    if (is_empty(deque))
        return NULL;

    struct node* node = deque->first;
    deque->first = get_next(deque->first);
    set_previous(deque->first, NULL);
    deque->size--;
    const char* to_return = get_value(node);
    destroy_node(node);
    return to_return;
}

const char* pop_back(struct deque* deque) {
    if (is_empty(deque))
        return NULL;

    struct node* node = deque->last;
    deque->last = get_previous(deque->last);
    set_next(deque->last, NULL);
    deque->size--;
    const char* to_return = get_value(node);
    destroy_node(node);
    return to_return;
}

void clear(struct deque* deque) {
    struct node* node = deque->first;
    for (size_t i = 0; i < deque->size; i++) {
        struct node* next = get_next(node);
        destroy_node(node);
        node = next;
    }
    nullify_deque(deque);
}

bool is_empty(struct deque* deque) {
    return deque->size == 0;
}

struct deque* build_deque() {
    struct deque* deque = malloc(get_deque_size());
    nullify_deque(deque);
    return deque;
}

void destroy_deque(struct deque* deque) {
    if (deque == NULL)
        return;

    clear(deque);
    free(deque);
}

struct node* goto_position(size_t index, size_t middle, struct deque* deque) {
    struct node* node = NULL;
    if (index > middle) {
        node = deque->last;
        index = deque->size - index;
        for (size_t i = 0; i < index; i++)
            node = get_previous(node);
    } else {
        node = deque->first;
        for (size_t i = 0; i < index; i++)
            node = get_next(node);
    }

    return node;
}

void nullify_deque(struct deque* deque) {
    deque->first = NULL;
    deque->last = NULL;
    deque->next = NULL;
    deque->size = 0;
}
