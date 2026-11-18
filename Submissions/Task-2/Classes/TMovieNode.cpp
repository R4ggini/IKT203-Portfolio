//
// Created by Lande on 10.11.2026.
//

#include "TMovieNode.h"

TMovieNode::TMovieNode(TMovie* movie, TMovieNode* prev, TMovieNode *next) : data(movie), prev(prev), next(next) {}
TMovieNode::~TMovieNode() {
    delete data;
}

void TMovieNode::SetNext(TMovieNode* next) {
    this->next = next;
}

void TMovieNode::SetPrev(TMovieNode* prev) {
    this->prev = prev;
}

TMovieNode* TMovieNode::GetNext() const {
    return next;
}

TMovieNode* TMovieNode::GetPrev() const {
    return prev;
}

TMovie* TMovieNode::GetMovie() const {
    return data;
}