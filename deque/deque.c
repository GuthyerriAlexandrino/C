#include "deque.h"
#include "../node/node.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct deque {
    struct node *first;
    struct node *last;
    size_t size;
};

struct node* goto_position(size_t, size_t, struct deque*);


int get_size() {
    return sizeof(struct deque);
}

size_t get_deque_size(struct deque* deque) {
    return deque->size;
}

void push_front(struct deque* deque, short elem) {
    struct node *temp = deque->first;
    deque->first = build_node(elem);
    set_next(deque->first, temp);
    set_previous(temp, deque->first);
    if (deque->size++ == 0)
        deque->last = deque->first;
}

void push_back(struct deque* deque, short elem) {
    if (deque->first == NULL) {
        deque->size++;
        deque->first = deque->last = build_node(elem);
        return;
    }
    struct node* new_node = build_node(elem);
    set_next(deque->last, new_node);
    set_previous(new_node, deque->last);
    deque->size++;
    deque->last = get_next(deque->last);
}

short front(struct deque* deque) {
    return get_value(deque->first);
}

short back(struct deque* deque) {
    return get_value(deque->last);
}

short get(struct deque* deque, size_t index) {
    if (index < 0 || index >= deque->size)
        return -1;

    struct node* node = goto_position(index, deque->size / 2, deque);
    return get_value(node);
}

void set(struct deque* deque, size_t index, short value) {
    if (index < 0 || index >= deque->size)
        return;

    struct node* node = goto_position(index, deque->size / 2, deque);
    set_value(node, value);
}

short pop_front(struct deque* deque) {
    if (is_empty(deque))
        return -1;

    struct node* node = deque->first;
    deque->first = get_next(deque->first);
    set_previous(deque->first, NULL);
    deque->size--;
    short to_return = get_value(node);
    destroy_node(node);
    return to_return;
}

short pop_back(struct deque* deque) {
    if (is_empty(deque))
        return -1;

    struct node* node = deque->last;
    deque->last = get_previous(deque->last);
    set_next(deque->last, NULL);
    deque->size--;
    short to_return = get_value(node);
    destroy_node(node);
    return to_return;
}

void clear(struct deque* deque) {
    struct node* node = deque->first;
    for (size_t i = 0; i < deque->size; i++) {
        struct node* next = get_next(node);
        free(node);
        node = next;
    }
    deque->size = 0;
}

bool is_empty(struct deque* deque) {
    return deque->size == 0;
}

struct deque* build_deque() {
    struct deque* deque = malloc(get_size());
    deque->first = NULL;
    deque->last = NULL;
    deque->size = 0;
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

void destroy_deque(struct deque* deque) {
    clear(deque);
    free(deque);
}
