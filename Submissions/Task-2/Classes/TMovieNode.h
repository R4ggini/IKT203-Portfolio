//
// Created by Lande on 10.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_TMOVIENODE_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_TMOVIENODE_H

#include "TMovie.h"

class TMovieNode {
public:
    TMovieNode(TMovie* movie, TMovieNode* prev, TMovieNode* next);
    ~TMovieNode();

    void SetNext(TMovieNode* next);
    void SetPrev(TMovieNode* prev);
    TMovieNode* GetNext() const;
    TMovieNode* GetPrev() const;
    TMovie* GetMovie() const;
private:
    TMovie* data;
    TMovieNode* prev;
    TMovieNode* next;
};


#endif //IKT203_ALGORITHMS_DATASTRUCTURE_TMOVIENODE_H
