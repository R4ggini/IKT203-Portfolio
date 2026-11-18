#include <iostream>
#include <random>
#include <thread>
#include "Classes/TStack.h"
#include "Classes/TQueue.h"

constexpr int COLUMNS = 100;
constexpr int ROWS = 100;

int grid[COLUMNS][ROWS] = {};
bool visitedCells[COLUMNS][ROWS] = {};

// Time: O(n), Space: O(n)
/* The stack is perfect for this kind of task, since it outputs the last added item.
 * This will lead to the order being reversed for elements that are added and then
 * removed from the stack.
 */
std::string StringReversal(std::string str, TStack stack) {
    for (int i = 0 ; i < str.length() ; i++) {
        stack.Push(str[i]);
    }
    for (int i = 0 ; !stack.IsEmpty() ; i++) {
        str[i] = stack.Pop();
    }
    return str;
}

// Time: O(n), Space: O(n)
int FactorialCalculation(int factorial, TStack stack) {
    int result = 1;

    while (factorial > 1) {
        stack.Push(factorial--);
    }
    while (!stack.IsEmpty()) {
        result *= stack.Pop();
    }
    return result;
}

// Time: O(n), Space: O(1)
void WaitingLine(TQueue queue, int steps) {
    int customerNumber = 0;
    for (; steps > 0 ; steps--) {
        int rng = std::rand() % 10;
        if (rng <= 3) {
            if (!queue.IsEmpty()) {
                std::cout << "Serving customer No. " << queue.Dequeue() << std::endl;
            }
        }
        else {
            std::cout << "Customer No. " << queue.Enqueue(customerNumber++) << " arrived." << std::endl;
        }
    }
}

// Encodes and decodes to simplify data transfer between functions
// Time: O(1), Space: O(1)
int EncodeCell(int row, int column) {
    return row * COLUMNS + column;
}

// Time: O(n), Space: O(n)
/* DFS utilizes a stack. The LIFO behavior of the stack means whenever a cell
 * is visited, its neighbors will be pushed to the top of the stack. It will keep
 * going like this until all adjacent cells are visited. It will then go to older cells
 */
int DFSSearch(int startingCell[2], TStack stack) {
    stack.Push(EncodeCell(startingCell[0], startingCell[1]));
    visitedCells[startingCell[0]][startingCell[1]] = true;
    while (true) {
        int id = stack.Pop();
        int row = id / COLUMNS;
        int col = id % COLUMNS;
        if (grid[row][col] == 0) return id;
        if (row + 1 < ROWS && visitedCells[row + 1][col] == false) {
            stack.Push(EncodeCell(row + 1, col));
            visitedCells[row + 1][col] = true;
        }
        if (row - 1 >= 0 && visitedCells[row - 1][col] == false) {
            stack.Push(EncodeCell(row - 1, col));
            visitedCells[row - 1][col] = true;
        }
        if (col + 1 < COLUMNS && visitedCells[row][col + 1] == false) {
            stack.Push(EncodeCell(row, col + 1));
            visitedCells[row][col + 1] = true;
        }
        if (col - 1 >= 0 && visitedCells[row][col - 1] == false) {
            stack.Push(EncodeCell(row, col - 1));
            visitedCells[row][col - 1] = true;
        }
        if (stack.IsEmpty()) return -1;
    }
}

// Time: O(n), Space: O(n)
/*
 * BFS utilizes a queue. The FIFO behavior of a queue means that it will process
 * the starting cell, then every cell adjacent to the starting cell, then every
 * cell adjacent to them again. This makes the search expand level by level. Since
 * it explores evenly in every direction, it will always find the closest 0.
 */
int BFSSearch(int startingCell[2], TQueue queue) {
    queue.Enqueue(EncodeCell(startingCell[0], startingCell[1]));
    visitedCells[startingCell[0]][startingCell[1]] = true;
    while (true) {
        int id = queue.Dequeue();
        int row = id / COLUMNS;
        int col = id % COLUMNS;
        if (grid[row][col] == 0) return id;
        if (row + 1 < ROWS && visitedCells[row + 1][col] == false) {
            queue.Enqueue(EncodeCell(row + 1, col));
            visitedCells[row + 1][col] = true;
        }
        if (row - 1 >= 0 && visitedCells[row - 1][col] == false) {
            queue.Enqueue(EncodeCell(row - 1, col));
            visitedCells[row - 1][col] = true;
        }
        if (col + 1 < COLUMNS && visitedCells[row][col + 1] == false) {
            queue.Enqueue(EncodeCell(row, col + 1));
            visitedCells[row][col + 1] = true;
        }
        if (col - 1 >= 0 && visitedCells[row][col - 1] == false) {
            queue.Enqueue(EncodeCell(row, col - 1));
            visitedCells[row][col - 1] = true;
        }
        if (queue.IsEmpty()) return -1;
    }
}

/* Comparison between DFS and BFS
 * DFS and BFS have the same worst case complexity (O(n) time and space), but explore
 * the grid in different orders. DFS uses a stack (LIFO), so it continues in a
 * direction until it backtracks. BFS uses a queue, so cells are processed in the
 * order they are found. This makes it explore evenly in every direction. As a result,
 * BFS will always find the closest match, while DFS can find results far away.
 * The main advantage of DFS is that in large areas it usually takes up less memory
 * than BFS, since it only saves the current path and its neighbors, not the entire
 * next level.
 *
 * BFS is better if the goal is to find the shortest path, as it will always reach
 * the goal in the shortest amount of steps.
 * DFS is a better fit for when you need to know if a path exists. They search at the
 * same speed, but since DFS usually takes up less memory, it is preferred. It is also
 * simpler to develop, as you can utilize the program's stack instead of developing
 * your own.
 */


// Main consists of tests for each step
int main() {
    // Setup for random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis9(0, 9);
    std::uniform_int_distribution<> dis99(0, 99);

    std::cout << std::boolalpha; // Prints bools as true/false

    {
        std::cout << "1: Implementing a Stack" << std::endl;
        TStack stack;
        std::cout << stack.IsEmpty() << std::endl; // Check if new stack is empty
        stack.Push(1); // Add item to stack
        stack.Push(2);
        stack.Push(3);
        std::cout << stack.IsEmpty() << std::endl; // Check if stack with items is empty
        std::cout << stack.Peek() << std::endl; // Peek at top item
        std::cout << stack.Pop() << std::endl; // Remove items from stack (LIFO)
        std::cout << stack.Pop() << std::endl;
        std::cout << stack.Pop() << std::endl;
        std::cout << stack.IsEmpty() << std::endl; // Check if stack is empty again
        std::cout << stack.Pop() << std::endl; // Remove item from empty stack
    }

    {
        std::cout << "2: Implementing a Queue" << std::endl;
        TQueue queue;
        std::cout << queue.IsEmpty() << std::endl;  // Tests is same format as in 1
        queue.Enqueue(10);
        queue.Enqueue(20);
        queue.Enqueue(30);
        std::cout << queue.IsEmpty() << std::endl;
        std::cout << queue.Peek() << std::endl;
        std::cout << queue.Dequeue() << std::endl;
        std::cout << queue.Dequeue() << std::endl;
        std::cout << queue.Dequeue() << std::endl;
        std::cout << queue.IsEmpty() << std::endl;
        std::cout << queue.Dequeue() << std::endl;
    }

    {
        std::cout << "3: String Reversal with a Stack" << std::endl;
        TStack stack;
        std::cout << StringReversal("Hello World", stack) << std::endl;
    }

    {
        std::cout << "4: Recursive Functions with a Stack" << std::endl;
        TStack stack;
        std::cout << FactorialCalculation(0, stack) << std::endl; // Edge case
        std::cout << FactorialCalculation(1, stack) << std::endl; // Another edge case
        std::cout << FactorialCalculation(5, stack) << std::endl; // Normal calculation
    }

    {
        std::cout << "5: Wait Line Simulation with a Queue" << std::endl;
        TQueue queue;
        WaitingLine(queue, 20);
    }

    int startingCell[2] = {};
    startingCell[0] = dis99(gen);
    startingCell[1] = dis99(gen);
    {
        std::cout << "6: Setup: The 100x100 Grid" << std::endl;
        // Initializes Grid
        for (auto & i : grid) {
            for (int & j : i) {
                j = dis9(gen);
            }
        }
        std::cout << startingCell[0] << " " << startingCell[1] << std::endl; // Starting cell (row, col)
        std::cout << EncodeCell(startingCell[0], startingCell[1]) << std::endl;
    }

    {
        std::cout << "7: Depth-First Search (DFS) with a Stack" << std::endl;
        TStack stack;
        int result = DFSSearch(startingCell, stack);
        if (result != -1) {
            std::cout << result / COLUMNS << " " << result % COLUMNS << std::endl; // Found cell
            std::cout << grid[result / COLUMNS][result % COLUMNS] << std::endl; // Value of found cell
        } else {
            std::cout << "No 0 found" << std::endl;
        }
    }

    {
        std::cout << "8: Breadth-First Search (BFS) with a Queue" << std::endl;
        for (auto & i : visitedCells) { // Resets visited cells
            for (bool & j : i) {
                j = false;
            }
        }
        TQueue queue;
        int result = BFSSearch(startingCell, queue);
        if (result != -1) { // same as previous
            std::cout << result / COLUMNS << " " << result % COLUMNS << std::endl;
            std::cout << grid[result / COLUMNS][result % COLUMNS] << std::endl;
        } else {
            std::cout << "No 0 found" << std::endl;
        }
    }
    return 0;
}