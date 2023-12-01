#pragma once

struct node;

typedef struct node* Node;

short get_node_size(void);

short get_value(struct node*);

void set_value(struct node*, short);

struct node* get_next(struct node*);

struct node* get_previous(struct node*);

struct node* set_next(struct node*, struct node*);

struct node* set_previous(struct node*, struct node*);

struct node* build_node(short value);

void destroy_node(struct node*);
