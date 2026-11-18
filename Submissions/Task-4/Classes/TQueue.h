//
// Created by Lande on 10.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_TQUEUE_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_TQUEUE_H

// % Makes queue circular
class TQueue {
public:
    int Enqueue(int item);  // Time: O(1), Space: O(1)
    int Dequeue();          // Time: O(1), Space: O(1)
    int Peek();             // Time: O(1), Space: O(1)
    bool IsEmpty();         // Time: O(1), Space: O(1)
private:
    static constexpr int MAX_SIZE = 10000;

    int num[MAX_SIZE] = {};
    int front = 0;
    int back = 0;
};


#endif //IKT203_ALGORITHMS_DATASTRUCTURE_TQUEUE_H
