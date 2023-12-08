#pragma once
#include <stdbool.h>

struct node;

typedef struct node Node;

int get_node_size(void);

const char* get_value(struct node*);

void set_value(struct node*, const char*);

struct node* get_next(struct node*);

struct node* get_previous(struct node*);

struct node* set_next(struct node*, struct node*);

struct node* set_previous(struct node*, struct node*);

struct node* build_node(const char*, bool);

void destroy_node(struct node*);
