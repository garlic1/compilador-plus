#include "stack.h"

void push(pointer_table_node* new_table) {
    if (is_full()) {
        printf("TABLE STACK FULL, ABORTING PUSH");

        return;
    }
    top_index++;
    stack[top_index] = new_table;
    return;
};

pointer_table_node* pop() {
    if (is_empty()) {
        printf("UNDERFLOW IN TABLE STACK, ABORTING POP");
        return NULL;
    }

    pointer_table_node* table = stack[top_index];
    top_index--;
    return table;
};

pointer_table_node* peek(int index) {
    if (is_empty()) {
        printf("TRYING TO ACCESS EMPTY TABLE STACK");
        return NULL;
    }
    return stack[index];
};

bool is_empty() {
    return top_index == -1;
};

bool is_full() {
    return top_index == MAX_STACK_SIZE - 1;
};