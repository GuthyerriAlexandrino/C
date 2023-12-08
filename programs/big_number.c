// numero de algarismos que pode existir em cada node
// inteiro 1
// inteiro 2
// soma e multiplicação
#include "big_number.h"
#include "../data_structures/deque/deque.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

struct big_number {
    Deque* value;
    Deque* allocated_strings;
    short node_size;
};

static size_t sum_calc(const char*, const char*);
static size_t mult_calc(BigNumber*, const char*, const char*);
static char* build_output_string(size_t);
static char* padd_string(const char*, size_t);
static size_t karatsuba(Deque*, const char*, const char*);
static const char* allocate_string(Deque*, size_t);

static int get_big_number_size() {
    return sizeof(struct big_number);
}

char* sum(struct big_number* a, struct big_number* b) {
    if (a == NULL || b == NULL)
        return "Invalid big number";
    if (a->node_size != b->node_size)
        return "Not implemented yet!";

    Deque* output_deque = build_deque();
    unsigned short carry = 0;
    const char* first = iterate_previous(a->value);
    const char *second = iterate_previous(b->value);;
    while (first) {
        size_t res = sum_calc(first, second) + carry;
        char converted[a->node_size + 2];
        sprintf(converted, "%llu", res);
        carry = (strlen(converted) > a->node_size) ? converted[a->node_size] - '0' : 0;

        char* to_output = calloc(a->node_size + 1, sizeof(char));
        strncpy(to_output, converted, a->node_size);
        push_front(output_deque, to_output, true);
        first = iterate_previous(a->value);
        second = iterate_previous(b->value);
    }

    char* output = build_output_string(get_size(a->value) + get_size(b->value) + 1);
    while (first = iterate_next(output_deque))
        strcat(output, first);

    return output;
}

char* multiply(struct big_number* a, struct big_number* b) {
    if (a == NULL || b == NULL)
        return "Invalid big number";
    if (a->node_size != b->node_size)
        return "Not implemented yet!";


    Deque* output_deque = build_deque();
    struct carry { bool is_carry; uint32_t carry_value; } carry = { .carry_value = 0, .is_carry = false };
    const char* first = iterate_previous(a->value);
    const char *second = iterate_previous(b->value);
    uint32_t to_right = 0;
    // Vou precisar de uma struct pra armazenar o número de zeros!!
    typedef struct { size_t number; size_t zeroes; } value;
    while (first) {
        // while(second) {
        //     size_t res = mult_calc(a, first, second);
        //     char converted[a->node_size + 2];
        //     sprintf(converted, "%llu", res);

        //     size_t carry_size = strlen(converted) - a->node_size;
        //     if (carry_size > 0) {
        //         carry.carry_value = 0;
        //         carry.is_carry = true;
        //         for (size_t i = 0; i < carry_size; ++i)
        //             carry.carry_value += converted[a->node_size + i] - '0';
        //     } else {
        //         carry.is_carry = false;
        //     }
        //     to_right += a->node_size;
        // }

        // char* to_output = calloc(a->node_size + 1, sizeof(char));
        // strncpy(to_output, converted, a->node_size);
        // push_front(output_deque, to_output, true);
        // first = iterate_previous(a->value);
        // second = iterate_previous(b->value);
    }

    if (carry.is_carry) {
        char* to_output = calloc(a->node_size + 1, sizeof(char));
        char converted[a->node_size + 1];
        sprintf(converted, "%llu", carry.carry_value);
        strncpy(to_output, converted, a->node_size);
        push_back(output_deque, to_output, true);
    }

    char* output = build_output_string(get_size(a->value) + get_size(b->value) + 1);
    while (first = iterate_next(output_deque)) {
        printf("%s  ", first);
        strcat(output, first);
    }

    //printf("%s%u", output, carry);

    return output;
}

struct big_number* build_big_number(const char* number, short node_size) {
    if (node_size > strlen(number))
        return NULL;

    struct big_number* bn = malloc(get_big_number_size());
    bn->node_size = node_size;
    bn->value = build_deque();
    bn->allocated_strings = build_deque();

    char* padded_string = padd_string(number, node_size);
    bool padded = true;
    if (padded_string == NULL) {
        padded_string = (char*)number;
        padded = false;
    }

    size_t size = strlen(padded_string);
    for (size_t i = 0; i < size; i += node_size) {
        char* substr = calloc(node_size + 1, sizeof(char));
        strncat(substr, padded_string + i, node_size);
        push_back(bn->value, substr, true);
    }

    if (padded)
        free(padded_string);

    return bn;
}

void destroy_big_number(struct big_number* bn) {
    destroy_deque(bn->value);
    destroy_deque(bn->allocated_strings);
    free(bn);
}

static size_t sum_calc(const char* first, const char* second) {
    size_t first_value = atoi(first);
    size_t second_value = atoi(second);

    return first_value + second_value;
}

static size_t mult_calc(BigNumber* bn, const char* first, const char* second) {
    size_t res = karatsuba(bn->allocated_strings, first, second);
    clear(bn->allocated_strings);
    return res;
}

static size_t max(size_t a, size_t b) {
    return (a > b) ? a : b;
}

static size_t karatsuba(Deque* deque, const char* x, const char* y) {
    if (strlen(x) == 1 && strlen(y) == 1)
        return atoll(x) * atoll(y);

    size_t n = max(strlen(x), strlen(y));
    size_t m = ceil(n/2);

    size_t x_number = atoll(x);
    size_t x_H  = floor(x_number / pow(10, m));
    size_t x_L = x_number % (size_t) pow(10, m);

    size_t y_number = atoll(y);
    size_t y_H = floor(y_number / pow(10, m));
    size_t y_L = y_number % (size_t) pow(10, m);

    const char* x_Ha = allocate_string(deque, x_H);
    const char* x_La = allocate_string(deque, x_L);
    const char* y_Ha = allocate_string(deque, y_H);
    const char* y_La = allocate_string(deque, y_L);
    size_t a = karatsuba(deque, x_Ha, y_Ha);
    size_t d = karatsuba(deque, x_La, y_La);
    size_t e = karatsuba(deque, allocate_string(deque, x_H + x_L), allocate_string(deque, y_H + y_L)) - a - d;

    return a*(pow(10, (m*2))) + e*(pow(10, m)) + d;
}

static const char* allocate_string(Deque* deque, size_t value) {
    int digits = (value == 0) ? 1 : floor(log10(value)) + 1;
    char* string = build_output_string(digits + 1);
    push_back(deque, string, true);
    sprintf(string, "%llu", value);
    return string;
}

static char* build_output_string(size_t size) {
    return calloc(size, sizeof(char));
}

static char* padd_string(const char* number, size_t node_size) {
    int string_size = strlen(number);
    int diff = string_size % node_size;

    if (diff == 0)
        return NULL;

    int padd_value = node_size - diff;
    // Initialize null string
    char* padded = malloc((string_size + padd_value + 1) * sizeof(char));
    memset(padded, '\0', sizeof(padded));

    // Do the padding
    memset(padded, '0', padd_value);
    strcat(padded, number);
    return padded;
}

int main() {
    // Deque *d = build_deque();
    // printf("%llu", karatsuba(d, "15", "15"));
    // BigNumber* bn = build_big_number("1236", 3);
    // BigNumber* bn2 = build_big_number("1234", 3);
    // char* x = sum(bn, bn2);
    // printf("%s", x);
    // free(x);
    // destroy_big_number(bn);
    // destroy_big_number(bn2);
    // free(bn);
    // free(bn2);
    BigNumber* bn = build_big_number("15", 1);
    BigNumber* bn2 = build_big_number("10", 1);
    char* x = multiply(bn, bn2);
    printf("%s", x);
}
