#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "../node/node.h"

struct deque;
typedef struct deque Deque;

size_t get_size(struct deque*);

const char* iterate_next(struct deque*);

const char* iterate_previous(struct deque*);

void push_front(struct deque*, const char*, bool allocated);

void push_back(struct deque*, const char*, bool allocated);

const char* front(struct deque*);

const char* back(struct deque*);

const char* get(struct deque*, size_t);

void set(struct deque*, size_t, const char*);

const char* pop_front(struct deque*);

const char* pop_back(struct deque*);

void clear(struct deque*);

bool is_empty(struct deque*);

struct deque* build_deque(void);

void destroy_deque(struct deque*);
