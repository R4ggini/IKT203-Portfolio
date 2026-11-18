//
// Created by Lande on 15.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_TSORT_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_TSORT_H
#include "TBankAccount.h"
#include "TLinkedList.h"

class TSort {
public:
    TSort(TLinkedList* list, TBankAccount** array, int size);

    ~TSort();

    TLinkedList* SelectionSort(FCompareAccounts aOnCompare, TLinkedList *list, OperationSummary* operationSummary);
    TBankAccount** SelectionSort(FCompareAccounts aOnCompare, TBankAccount** array, int size, OperationSummary* operationSummary);
    TBankAccount** BubbleSort(FCompareAccounts aOnCompare, TBankAccount** array, int size, OperationSummary* operationSummary);
    TBankAccount** QuickSort(FCompareAccounts aOnCompare, TBankAccount **array, int size, OperationSummary *operationSummary);
    TLinkedList* MergeSort(FCompareAccounts aOnCompare, TLinkedList *list, OperationSummary* operationSummary);
    TBankAccount* BinarySearch(FCompareAccounts aOnCompare, TBankAccount* searchParam, OperationSummary *operationSummary);

    void SortArrayByLastName(FCompareAccounts aOnCompare, OperationSummary *operationSummary);

private:
    static void Swap(TBankAccount *&a, TBankAccount *&b, OperationSummary *operationSummary);
    static void Swap(TLinkedList::TNode *a, TLinkedList::TNode *b, OperationSummary *operationSummary); // Swaps in linked list

    void QuickSortRecursive(FCompareAccounts aOnCompare, TBankAccount **array, int left, int right, OperationSummary *operationSummary);
    int Partition(FCompareAccounts aOnCompare, TBankAccount **array, int left, int right, OperationSummary *operationSummary);
    TLinkedList* MergeSortRecursive(FCompareAccounts aOnCompare, TLinkedList *list, OperationSummary *operationSummary);
    int BinarySearchRecursive(FCompareAccounts aOnCompare, TBankAccount* searchParam, TBankAccount **array, int left, int right, OperationSummary * operationSummary);

    TLinkedList* accountList = nullptr;
    TBankAccount** accountArray = nullptr;
    bool sorted = false;
    TBankAccount **sortedArray = nullptr;
    int size;
};


#endif //IKT203_ALGORITHMS_DATASTRUCTURE_TSORT_H
