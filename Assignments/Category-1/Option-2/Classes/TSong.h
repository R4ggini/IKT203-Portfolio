//
// Created by Lande on 18.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_TSONG_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_TSONG_H
#include <string>

#include "EMusicGenreType.h"


class TSong {
public:
    // Creates a song with parameters artist, title, releaseYear and genre
    TSong(std::string artist, std::string title, int releaseYear, EMusicGenreType genre);
    // Default destructor
    ~TSong();

    std::string GetArtist() const;
    std::string GetTitle() const;
    int GetReleaseYear() const;
    EMusicGenreType GetGenre() const;

private:
    std::string artist;
    std::string title;
    int releaseYear;
    EMusicGenreType genre;
};


#endif //IKT203_ALGORITHMS_DATASTRUCTURE_TSONG_H
