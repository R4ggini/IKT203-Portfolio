//
// Created by Lande on 10.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_TMOVIELIST_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_TMOVIELIST_H

#include "TMovieNode.h"

typedef bool (*FCheckMovie)(TMovie* movie, void* searchCriteria);

class TMovieList {
public:
    TMovieList();
    ~TMovieList();
    void Append(TMovie* movie);
    void Prepend(TMovie* movie);
    TMovie* GetAtIndex(int index);
    void Remove(int index);
    void Reverse();
    TMovie* SearchFor(FCheckMovie check, void* searchCriteria);
private:
    TMovieNode* head{};
    TMovieNode* tail;
};


#endif //IKT203_ALGORITHMS_DATASTRUCTURE_TMOVIELIST_H
