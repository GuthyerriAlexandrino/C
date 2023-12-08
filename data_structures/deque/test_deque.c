#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "deque.h"

#define cmp(a, b) !strcmp(a, b)

void back_test(Deque *deque) {
    push_back(deque, "10");
    assert(cmp("10", back(deque)));
    push_back(deque, "20");
    assert(cmp("20", back(deque)));
    assert(2 == get_size(deque));
    assert(cmp("20", pop_back(deque)));
    assert(1 == get_size(deque));
    assert(cmp("10", pop_front(deque)));
    assert(0 == get_size(deque));
}

void front_test(Deque *deque) {
    push_front(deque, "10");
    assert(cmp("10", front(deque)));
    push_front(deque, "20");
    push_front(deque, "30");
    assert(cmp("30", front(deque)));
    assert(3 == get_size(deque));
    assert(cmp("30", pop_front(deque)));
    assert(cmp("20", pop_front(deque)));
    pop_front(deque);
    assert(0 == get_size(deque));
}

void iteration_test(Deque *deque) {
    push_front(deque, "99");
    push_front(deque, "20");
    push_front(deque, "30");

    size_t size = get_size(deque);
    const char* values[] = { "30", "20", "99" };
    for (size_t i = 0; i < size; i++) {
        assert(cmp(values[i], pop_front(deque)));
    }

    push_back(deque, "99");
    push_back(deque, "20");
    push_back(deque, "30");

    size = get_size(deque);
    for (size_t i = 0; i < size; i++) {
        assert(cmp("99", get(deque, 0)));
        pop_back(deque);
    }
    assert(0 == get_size(deque));
}

int main() {
    Deque *deque = build_deque();
    front_test(deque);
    back_test(deque);
    iteration_test(deque);
    printf("All asserts passed");
    destroy_deque(deque);
}
