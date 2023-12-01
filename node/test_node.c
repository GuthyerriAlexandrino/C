#include <stdio.h>
#include "node.h"

int main() {
    Node a = build_node(10);
    printf("%d", get_value(get_next(set_next(a, 20))));
}
