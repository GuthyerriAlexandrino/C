#include <stdio.h>
#include <assert.h>
#include "deque.h"

void back_test(Deque deque) {
    push_back(deque, 10);
    assert(10 == back(deque));
    push_back(deque, 20);
    assert(20 == back(deque));
    assert(2 == get_deque_size(deque));
    assert(20 == pop_back(deque));
    assert(1 == get_deque_size(deque));
    assert(10 == pop_front(deque));
    assert(0 == get_deque_size(deque));
}

void front_test(Deque deque) {
    push_front(deque, 10);
    assert(10 == front(deque));
    push_front(deque, 20);
    push_front(deque, 30);
    assert(30 == front(deque));
    assert(3 == get_deque_size(deque));
    assert(30 == pop_front(deque));
    assert(20 == pop_front(deque));
    pop_front(deque);
    assert(0 == get_deque_size(deque));
}

void iteration_test(Deque deque) {
    push_front(deque, 99);
    push_front(deque, 20);
    push_front(deque, 30);

    size_t size = get_deque_size(deque);
    short values[] = { 30, 20, 99 };
    for (size_t i = 0; i < size; i++) {
        assert(values[i] == pop_front(deque));
    }

    push_back(deque, 99);
    push_back(deque, 20);
    push_back(deque, 30);

    size = get_deque_size(deque);
    for (size_t i = 0; i < size; i++) {
        assert(99 == get(deque, 0));
        pop_back(deque);
    }
    assert(0 == get_deque_size(deque));
}

int main() {
    Deque deque = build_deque();
    front_test(deque);
    back_test(deque);
    iteration_test(deque);
    printf("All asserts passed");
}
