//
// Created by Lande on 10.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_TSTACK_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_TSTACK_H

class TStack {
public:
    void Push(int item);    // Time: O(1), Space: O(1)
    int Pop();              // Time: O(1), Space: O(1)
    int Peek();             // TIme: O(1), Space: O(1)
    bool IsEmpty();         // Time: O(1), Space: O(1)
private:
    static constexpr int MAX_SIZE = 10000;

    int num[MAX_SIZE] = {};
    int top = -1; // top = -1 means stack is empty
};


#endif //IKT203_ALGORITHMS_DATASTRUCTURE_TSTACK_H
