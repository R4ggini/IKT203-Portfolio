//
// Created by Lande on 15.11.2026.
//

#include "TSort.h"

#include <iostream>

#include "TLinkedList.h"

TSort::TSort(TLinkedList* list, TBankAccount** array, int size) : accountList(list), accountArray(array), size(size) {}

TSort::~TSort() {
    delete[] sortedArray;
}

// Swap for array
void TSort::Swap(TBankAccount*& a, TBankAccount*& b, OperationSummary* operationSummary) {
    operationSummary->swaps++;
    auto temp = a;
    a = b;
    b = temp;
}

// Swap for linked list
void TSort::Swap(TLinkedList::TNode* a, TLinkedList::TNode* b, OperationSummary* operationSummary) {
    operationSummary->swaps++;
    TBankAccount* temp = a->GetData();
    a->SetData(b->GetData());
    b->SetData(temp);
}

// Selection sort (list)
// Time: Best: O(n^2), Average: O(n^2), Worst: O(n^2), Space: O(n)*
// * Space complexity is n since the list is copied, O(1) under normal circumstances
TLinkedList *TSort::SelectionSort(FCompareAccounts aOnCompare, TLinkedList* list, OperationSummary* operationSummary) {
    // Initializes operation summary
    auto startTime = OperationSummary::GetCurrentTime();
    operationSummary->comparisons = 0;
    operationSummary->swaps = 0;

    TLinkedList* result = new TLinkedList(false);
    // Copies list
    for (TLinkedList::TNode* node = list->GetHead()->GetNext(); node != nullptr; node = node->GetNext()) {
        result->Append(new TLinkedList::TNode(node->GetData(), nullptr));
    }

    // Sorts copied list
    for (TLinkedList::TNode* nodeToBeSwapped = result->GetHead()->GetNext(); nodeToBeSwapped != nullptr; nodeToBeSwapped = nodeToBeSwapped->GetNext()) {
        auto smallest = nodeToBeSwapped; // resets smallest
        for (TLinkedList::TNode* current = nodeToBeSwapped->GetNext(); current != nullptr; current = current->GetNext() ) {
            operationSummary->comparisons++;
            if (aOnCompare(smallest->GetData(), current->GetData()) > 0) {
                smallest = current;
            }
        }

        // Flips what nodeToBeSwapped and smallest points to
        if (smallest != nodeToBeSwapped) {
            Swap(nodeToBeSwapped, smallest, operationSummary);
        }
    }
    operationSummary->timeSpentMs = OperationSummary::GetTimeDiff(startTime);
    return result;
}

// Selection sort (array)
// Time: Best: O(n^2), Average: O(n^2), Worst: O(n^2), Space: O(n)* (O(1))
TBankAccount** TSort::SelectionSort(FCompareAccounts aOnCompare, TBankAccount** array, int size, OperationSummary* operationSummary) {
    // Initializes operation summary
    auto startTime = OperationSummary::GetCurrentTime();
    operationSummary->comparisons = 0;
    operationSummary->swaps = 0;

    auto** result = new TBankAccount*[size];
    // copies array
    for (int i = 0; i < size; i++) {
        result[i] = array[i];
    }

    // Sorts array
    for (int i = 0; i < size - 1; i++) {
        int smallestIndex = i;
        for (int j = i + 1; j < size; j++) {
            operationSummary->comparisons++;
            if (aOnCompare(result[j], result[smallestIndex]) < 0) {
                smallestIndex = j;
            }
        }

        // Swaps array places
        if (smallestIndex != i) {
            Swap(result[i], result[smallestIndex], operationSummary);
        }
    }
    operationSummary->timeSpentMs = OperationSummary::GetTimeDiff(startTime);

    return result;
}

// Bubble sort
// Time: Best: O(n), Average: O(n^2), Worst: O(n^2), Space O(n)* (O(1))
TBankAccount** TSort::BubbleSort(FCompareAccounts aOnCompare, TBankAccount** array, int size, OperationSummary* operationSummary) {
    // Initialization
    bool swapped = true;
    auto** result = new TBankAccount*[size];
    auto startTime = OperationSummary::GetCurrentTime();
    operationSummary->comparisons = 0;
    operationSummary->swaps = 0;

    // Copies array
    for (int i = 0; i < size; i++) {
        result[i] = array[i];
    }

    while (swapped != false) {
        // Starts walkthrough of list
        swapped = false;
        for (int i = 0; i < size - 1; i++) {
            // Compares
            operationSummary->comparisons++;
            if (aOnCompare(result[i+1], result[i]) < 0) {
                // Swaps
                Swap(result[i], result[i + 1], operationSummary);
                swapped = true;
            }
        }
    }
    operationSummary->timeSpentMs = OperationSummary::GetTimeDiff(startTime);
    return result;
}

// Quick Sort methods
// Helper method for quicksort
int TSort::Partition(FCompareAccounts aOnCompare, TBankAccount** array, int left, int right, OperationSummary *operationSummary) {
    // Choose pivot
    TBankAccount* pivot = array[right];

    // Index for last position of smaller elements
    int lastSmall = left - 1;

    // Compares and swaps
    for (int i = left; i < right; i++) {
        operationSummary->comparisons++;
        if (aOnCompare(array[i], pivot) < 0) {
            lastSmall++;
            if (i != lastSmall) Swap(array[i], array[lastSmall], operationSummary);
        }
    }
    Swap(array[lastSmall + 1], array[right], operationSummary); // Moves pivot to the correct place

    return lastSmall + 1; // Returns position of pivot
}

// Private method
void TSort::QuickSortRecursive(FCompareAccounts aOnCompare, TBankAccount** array, int left, int right, OperationSummary* operationSummary) {
    // Base Case
    if (left >= right) return;

    // Sort array and return pivot
    int pivot = Partition(aOnCompare, array, left, right, operationSummary);

    // Recursively call method on areas around pivot
    QuickSortRecursive(aOnCompare, array, left, pivot - 1, operationSummary);
    QuickSortRecursive(aOnCompare, array, pivot + 1, right, operationSummary);
}

// Publicly facing method
// Quick sort
// Time: Best: O(n log n), Average: O(n log n), Worst: O(n^2), Space: O(n)* (Best/Average: O(log n), Worst: O(n))
TBankAccount** TSort::QuickSort(FCompareAccounts aOnCompare, TBankAccount **array, int size, OperationSummary *operationSummary) {
    // Initialize OperationSummary
    operationSummary->comparisons = 0;
    operationSummary->swaps = 0;
    auto startTime = OperationSummary::GetCurrentTime();

    // Copy array
    auto result = new TBankAccount*[size];
    for (int i = 0; i < size; i++) {
        result[i] = array[i];
    }

    // Start recursion
    QuickSortRecursive(aOnCompare, result, 0, size - 1, operationSummary);

    // Finalize OperationSummary
    operationSummary->timeSpentMs = OperationSummary::GetTimeDiff(startTime);

    return result;
}

// Private method
TLinkedList* TSort::MergeSortRecursive(FCompareAccounts aOnCompare, TLinkedList* list, OperationSummary* operationSummary) {
    // Base case
    if (list->GetHead()->GetNext() == nullptr || list->GetHead()->GetNext()->GetNext() == nullptr) return list;

    TLinkedList::TNode* fast = list->GetHead()->GetNext();
    TLinkedList::TNode* slow = list->GetHead()->GetNext();
    for (; fast != nullptr && fast->GetNext() != nullptr; fast = fast->GetNext()->GetNext(), slow = slow->GetNext()) {}

    // Create new lists
    TLinkedList firstList(false);
    TLinkedList secondList(false);

    // Add elements to list
    for (TLinkedList::TNode* current = list->GetHead()->GetNext(); current != slow; current = current->GetNext()) {
        firstList.Append(new TLinkedList::TNode(current->GetData(), nullptr));
    }
    for (TLinkedList::TNode* current = slow; current != nullptr; current = current->GetNext()) {
        secondList.Append(new TLinkedList::TNode(current->GetData(), nullptr));
    }

    // Recursively call
    TLinkedList* sortedFirstList = MergeSortRecursive(aOnCompare, &firstList, operationSummary);
    TLinkedList* sortedSecondList = MergeSortRecursive(aOnCompare, &secondList, operationSummary);

    // Merge lists
    auto* mergedList = new TLinkedList(false);
    TLinkedList::TNode* a = sortedFirstList->GetHead()->GetNext();
    TLinkedList::TNode* b = sortedSecondList->GetHead()->GetNext();

    // While both has elements
    while (a != nullptr && b != nullptr) {
        operationSummary->comparisons++;
        if (aOnCompare(a->GetData(), b->GetData()) <= 0) {
            mergedList->Append(new TLinkedList::TNode(a->GetData(), nullptr));
            a = a->GetNext();
        } else {
            mergedList->Append(new TLinkedList::TNode(b->GetData(), nullptr));
            b = b->GetNext();
        }
    }

    // When one runs out of elements
    for (; a != nullptr; a = a->GetNext()) {
        mergedList->Append(new TLinkedList::TNode(a->GetData(), nullptr));
    }
    for (; b != nullptr; b = b->GetNext()) {
        mergedList->Append(new TLinkedList::TNode(b->GetData(), nullptr));
    }

    // Delete redundant lists
    if (sortedFirstList != &firstList) delete sortedFirstList;
    if (sortedSecondList != &secondList) delete sortedSecondList;

    return mergedList;
}

// Public method
// Merge sort
// Time: Best: O(n log n), Average: O(n log n), Worst: O(n log n), Space: O(n)* (O(n))
TLinkedList *TSort::MergeSort(FCompareAccounts aOnCompare, TLinkedList *list, OperationSummary *operationSummary) {
    // Initialize operationSummary
    auto startTime = OperationSummary::GetCurrentTime();
    operationSummary->comparisons = 0;
    operationSummary->swaps = 0;

    auto* sortedList = MergeSortRecursive(aOnCompare, list, operationSummary); // is on the heap

    // Finalize operationSummary
    operationSummary->timeSpentMs = OperationSummary::GetTimeDiff(startTime);
    return sortedList;
}

int TSort::BinarySearchRecursive(FCompareAccounts aOnCompare, TBankAccount* searchParam, TBankAccount** array, int left, int right, OperationSummary* operationSummary) {
    if (left > right) return -1;
    int middle = (left + right) / 2;

    int result = aOnCompare(array[middle], searchParam);
    operationSummary->comparisons++;

    if (result < 0) return BinarySearchRecursive(aOnCompare, searchParam, array, middle + 1, right, operationSummary);
    if (result > 0) return BinarySearchRecursive(aOnCompare, searchParam, array, left, middle - 1, operationSummary);
    return middle;
}

// Binary search
// Time: Best: O(1), Average: O(log n), Worst: O(log n), Space: O(log n)
TBankAccount* TSort::BinarySearch(FCompareAccounts aOnCompare, TBankAccount* searchParam, OperationSummary *operationSummary) {
    if (this->sorted == false) return nullptr;

    // Initialize operation summary
    operationSummary->comparisons = 0;
    operationSummary->swaps = 0;
    auto startTime = OperationSummary::GetCurrentTime();

    // Start recursion
    int result = BinarySearchRecursive(aOnCompare, searchParam, sortedArray, 0, size - 1, operationSummary);

    operationSummary->timeSpentMs = OperationSummary::GetTimeDiff(startTime);
    if (result < 0) return nullptr;
    return sortedArray[result];
}


void TSort::SortArrayByLastName(FCompareAccounts aOnCompare, OperationSummary *operationSummary) {
    delete[] sortedArray;
    sortedArray = QuickSort(aOnCompare, accountArray, size, operationSummary);
    sorted = true;
}
