//
// Created by Lande on 15.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_TLINKEDLIST_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_TLINKEDLIST_H
#include <chrono>
#include <iostream>

#include "TBankAccount.h"

typedef int (*FCompareAccounts)(TBankAccount* a, TBankAccount* b);

struct OperationSummary {
    long long comparisons;
    long long swaps;
    double timeSpentMs;

    static std::chrono::steady_clock::time_point GetCurrentTime () {
        return std::chrono::steady_clock::now();
    }
    static double GetTimeDiff (std::chrono::steady_clock::time_point startTime) {
        return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startTime).count();
    }
    void Print() {
        std::cout << "Comparisons: " << comparisons << std::endl
        << "Swaps: " << swaps << std::endl
        << "Time Spent: " << timeSpentMs << std::endl << std::endl;
    }
};

class TLinkedList {
public:
    class TNode {
    public:
        TNode(TBankAccount *data, TNode *next);

        TNode* GetNext();

        void SetNext(TNode *next);

        TBankAccount* GetData();

        void SetData(TBankAccount* data);

    private:
        TNode* next;
        TBankAccount* data;
    };
    TLinkedList(bool ownsData);

    ~TLinkedList();

    void Print();

    void Append(TNode* node);

    TNode* GetHead();

    TNode* GetTail();

    TBankAccount* Find(FCompareAccounts aOnCompare, TBankAccount *searchKey, OperationSummary &searchSummary);

    TLinkedList *Every(FCompareAccounts aOnCompare, TBankAccount *searchKey, OperationSummary &searchSummary);

private:
    TNode *head;
    TNode* tail; // tail pointer to make append O(1) instead of O(n)
    bool ownsData;
};




#endif //IKT203_ALGORITHMS_DATASTRUCTURE_TLINKEDLIST_H
