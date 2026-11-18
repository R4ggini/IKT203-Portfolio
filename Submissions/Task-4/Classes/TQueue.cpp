//
// Created by Lande on 10.11.2026.
//

#include "TQueue.h"

int TQueue::Enqueue(int item) {
    if (back - front == MAX_SIZE) return -1;
    return num[back++ % MAX_SIZE] = item;
}

int TQueue::Dequeue() {
    // Moves front of queue instead of entire queue
    if (front == back) return -1;
    return num[front++ % MAX_SIZE];
}

int TQueue::Peek() {
    return num[front % MAX_SIZE];
}

bool TQueue::IsEmpty() {
    if (front == back) return true;
    return false;
}
