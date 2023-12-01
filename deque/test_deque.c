#include <stdio.h>
#include "deque.h"

void back_test(Deque deque) {
    push_back(deque, 10);
    push_back(deque, 20);
    printf("%d ", front(deque));
    printf("%d ", back(deque));
    printf("%d ", get_deque_size(deque));
    printf("%d ", pop_back(deque));
    printf("%d ", get_deque_size(deque));
    printf("%d ", pop_front(deque));
    printf("%d ", get_deque_size(deque));
}

void front_test(Deque deque) {
    push_front(deque, 10);
    push_front(deque, 20);
    push_front(deque, 30);
    printf("%d %d\n", front(deque), back(deque));
    printf("%d %d ", pop_front(deque), pop_front(deque));
    printf("%d ", pop_front(deque));
}

void iteration_test(Deque deque) {
    push_front(deque, 99);
    push_front(deque, 20);
    push_front(deque, 30);

    size_t size = get_deque_size(deque);
    for (size_t i = 0; i < size; i++) {
        printf("%d ", pop_front(deque));
    }

    push_back(deque, 99);
    push_back(deque, 20);
    push_back(deque, 30);

    // printf("%d ", get(deque, 0));
    // printf("%d ", get(deque, 1));
    // printf("%d ", get(deque, 2));
    size = get_deque_size(deque);
    for (size_t i = 0; i < size; i++) {
        printf("%d ", get(deque, 0));
        pop_back(deque);
    }
    printf("%d", get_deque_size(deque));
}

int main() {
    Deque deque = build_deque();
    // front_test(deque);
    iteration_test(deque);
}

//gcc test_deque.c deque.c ../node/node.c -o test
