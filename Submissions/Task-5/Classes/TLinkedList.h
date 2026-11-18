//
// Created by Lande on 15.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_TLINKEDLIST_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_TLINKEDLIST_H
#include <chrono>

#include "TBankAccount.h"

struct SearchSummary {
    long long comparisons;
    double timeSpentMs;

    static std::chrono::steady_clock::time_point GetCurrentTime () {
        return std::chrono::steady_clock::now();
    }
    static double GetTimeDiff (std::chrono::steady_clock::time_point startTime) {
        return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startTime).count();
    }
};

typedef bool (*FCompareAccounts)(TBankAccount* account, void* searchKey);

class TLinkedList {
public:
    TLinkedList(bool ownsData);

    ~TLinkedList();

    void Print();

    void Append(TBankAccount *data);

    TBankAccount* Find(FCompareAccounts aOnCompare, void* searchKey, SearchSummary& searchSummary);

    TLinkedList *Every(FCompareAccounts aOnCompare, void *searchKey, SearchSummary &searchSummary);

private:
    // Singly linked list. Reasoning in README.md
    class TNode {
    public:
        TNode(TBankAccount *data, TNode *next);

        TNode* GetNext();

        void SetNext(TNode *next);

        TBankAccount* GetData();

    private:
        TNode* next;
        TBankAccount* data;
    };

    TNode* head;
    TNode* tail; // tail pointer to make append O(1) instead of O(n)
    bool ownsData;
};


#endif //IKT203_ALGORITHMS_DATASTRUCTURE_TLINKEDLIST_H
