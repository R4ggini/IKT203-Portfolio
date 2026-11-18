//
// Created by Lande on 15.11.2026.
//

#include "TLinkedList.h"

#include <chrono>
#include <iostream>

// TNode Functions
TLinkedList::TNode::TNode(TBankAccount* data, TNode* next) : next(next), data(data) {}

TLinkedList::TNode* TLinkedList::TNode::GetNext() {
    return next;
}

void TLinkedList::TNode::SetNext(TNode* next) {
    this->next = next;
}

TBankAccount* TLinkedList::TNode::GetData() {
    return data;
}

// TLinkedList Functions
TLinkedList::TLinkedList(bool ownsData) : ownsData(ownsData) {
    head = new TNode(nullptr, nullptr);
    tail = head;
}

TLinkedList::~TLinkedList() {
    TNode* current = head;

    while (current != nullptr) {
        TNode* next = current->GetNext();
        if (ownsData) delete current->GetData();
        delete current;
        current = next;
    }
}

void TLinkedList::Print() {
    for (TNode* current = head->GetNext(); current != nullptr; current = current->GetNext()) {
        TBankAccount* account = current->GetData();
        std::cout << "Account Number: " << account->GetAccountNumber() << ", "
            << "Account Type: " << account->AccountTypeToString(account->GetAccountType()) << ", "
            << "First Name: " << account->GetOwnerFirstName() << ", "
            << "Last Name: " << account->GetOwnerLastName() << ", "
            << "Creation Timestamp: " << account->GetCreationTimestamp() << ", "
            << "Balance: " << account->GetBalance() << std::endl;
    }
}

void TLinkedList::Append(TBankAccount* data) {
    tail->SetNext(new TNode(data, nullptr));
    tail = tail->GetNext();
}

TBankAccount* TLinkedList::Find(FCompareAccounts aOnCompare, void* searchKey, SearchSummary& searchSummary) {
    // Initializes search summary
    searchSummary.comparisons = 0;
    auto startTime = SearchSummary::GetCurrentTime();

    for (TNode* current = head->GetNext(); current != nullptr; current = current->GetNext()) {
        searchSummary.comparisons++;
        if (aOnCompare(current->GetData(), searchKey)) {
            searchSummary.timeSpentMs = SearchSummary::GetTimeDiff(startTime);

            return current->GetData();
        }
    }
    searchSummary.timeSpentMs = SearchSummary::GetTimeDiff(startTime);
    return nullptr;
}

TLinkedList* TLinkedList::Every(FCompareAccounts aOnCompare, void* searchKey, SearchSummary& searchSummary) {
    auto* result = new TLinkedList(false);

    // Initializes search summary
    searchSummary.comparisons = 0;
    auto startTime = SearchSummary::GetCurrentTime();

    for (TNode* current = head->GetNext(); current != nullptr; current = current->GetNext()) {
        searchSummary.comparisons++;
        if (aOnCompare(current->GetData(), searchKey)) {
            result->Append(current->GetData());
        }
    }

    searchSummary.timeSpentMs = SearchSummary::GetTimeDiff(startTime);

    // Checks if list has entries
    if (result->head->GetNext() != nullptr) return result;
    delete result;
    return nullptr;
}