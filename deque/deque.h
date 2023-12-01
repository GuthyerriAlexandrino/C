#pragma once
#include <stdbool.h>
#include <stddef.h>

struct deque;

typedef struct deque* Deque;

int get_size(void);

size_t get_deque_size(struct deque*);

void push_front(struct deque*, short);

void push_back(struct deque*, short);

short front(struct deque*);

short back(struct deque*);

short get(struct deque*, size_t);

void set(struct deque*, size_t, short);

short pop_front(struct deque*);

short pop_back(struct deque*);

void clear(struct deque*);

bool is_empty(struct deque*);

struct deque* build_deque(void);

void destroy_deque(struct deque*);
