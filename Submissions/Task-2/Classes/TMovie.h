//
// Created by Lande on 10.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_TMOVIE_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_TMOVIE_H
#include <string>

#include "../EMovieGenreType.h"

// 1.1 a
class TMovie {
    public:
        // 1.1 c
        TMovie(std::string title, std::string director, int year, EMovieGenreType genre, float score);

        // 1.1 d
        std::string GetTitle() const;
        std::string GetDirector() const;
        int GetYear() const;
        EMovieGenreType GetGenre() const;
        float GetScore() const;
    private:
        // 1.1 b
        std::string title;
        std::string director;
        int year;
        EMovieGenreType genre;
        float score;
};


#endif //IKT203_ALGORITHMS_DATASTRUCTURE_TMOVIE_H
