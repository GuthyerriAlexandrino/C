#pragma once

struct big_number;
typedef struct big_number BigNumber;

char* sum(struct big_number*, struct big_number*);
char* multiply(struct big_number*, struct big_number*);

struct big_number* build_big_number(const char*, short);
void destroy_big_number(struct big_number*);
