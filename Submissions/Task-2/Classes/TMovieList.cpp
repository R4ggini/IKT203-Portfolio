//
// Created by Lande on 10.11.2026.
//

#include "TMovieList.h"

// Initializes by creating two dummy nodes
TMovieList::TMovieList() {
    head = new TMovieNode(nullptr, nullptr, nullptr);
    tail = new TMovieNode(nullptr, head, nullptr);
    head->SetNext(tail);
}

TMovieList::~TMovieList() {
    while (head != nullptr) {
        TMovieNode* toBeDeleted = head; // Sets a delete pointer to first object in list
        head = head->GetNext(); // Sets head as next node
        delete toBeDeleted; // Deletes first node in list
    }
}

// The time complexity has went from O(n)->O(1), since we can directly access the tail
void TMovieList::Append(TMovie* movie) {
    tail->GetPrev()->SetNext(new TMovieNode(movie, tail->GetPrev(), tail));
    tail->SetPrev(tail->GetPrev()->GetNext());
}

void TMovieList::Prepend(TMovie* movie) {
    head->GetNext()->SetPrev(new TMovieNode(movie, head, head->GetNext()));
    head->SetNext(head->GetNext()->GetPrev());
}

TMovie* TMovieList::GetAtIndex(int index) {
    if (index < 1) return nullptr; // OoB prevention
    TMovieNode* node = head; // Initialized outside of for loop to no go out of scope
    for (; node != tail && index != 0; node = node->GetNext()) {
        index--; // Reduces index by 1 until index hits 0
    }
    if (node == tail) return nullptr;
    return node->GetMovie();
}

void TMovieList::Remove(int index) {
    if (index < 1) return; // OoB prevention
    TMovieNode* node = head->GetNext(); // Gets first actual node in list
    for (; node != tail && index != 1; node = node->GetNext()) {
        index--;
    }
    if (node == tail) return;
    // Moves pointers to adjacent nodes
    node->GetPrev()->SetNext(node->GetNext());
    node->GetNext()->SetPrev(node->GetPrev());

    delete node; // Node deletion will also delete data through its destructor
}

void TMovieList::Reverse() {
    if (head->GetNext() == tail) return; // Safeguard if list is empty

    for (TMovieNode* node = head->GetNext(), *nextNode = node->GetNext(); node != tail; node = nextNode, nextNode = node->GetNext()) {
        node->SetNext(node->GetPrev());
        node->SetPrev(nextNode);
    }
    // Flips head and tail
    auto listStart= head->GetNext();
    auto listEnd = tail->GetPrev();

    head->SetNext(listEnd);
    listEnd->SetPrev(head);
    tail->SetPrev(listStart);
    listStart->SetNext(tail);
}

TMovie* TMovieList::SearchFor(FCheckMovie check, void* searchCriteria) {
    for (TMovieNode* node = head->GetNext(); node != tail; node = node->GetNext()) {
        if (check(node->GetMovie(), searchCriteria)) {
            return node->GetMovie(); // First match
        }
    }
    return nullptr; // No match
}