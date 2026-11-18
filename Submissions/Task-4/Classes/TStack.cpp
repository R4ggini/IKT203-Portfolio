//
// Created by Lande on 10.11.2026.
//

#include "TStack.h"

void TStack::Push(int item) {
    if (top == MAX_SIZE - 1) return;
    num[++top] = item;
}

int TStack::Pop() {
    if (top == -1) return -1;
    int i = num[top];
    num[top--] = 0;
    return i;
}

int TStack::Peek() {
    if (top == -1) return -1;
    return num[top];
}

bool TStack::IsEmpty() {
    if (top == -1) return true;
    return false;
}
