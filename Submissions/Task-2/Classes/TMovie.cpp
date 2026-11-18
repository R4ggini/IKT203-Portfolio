//
// Created by Lande on 10.11.2026.
//

#include "TMovie.h"

// 1.1 c
TMovie::TMovie(std::string title, std::string director, int year, EMovieGenreType genre, float score)
    : title(std::move(title)), director(std::move(director)), year(year), genre(genre), score(score) {}

// 1.1 d
std::string TMovie::GetTitle() const { return title; }
std::string TMovie::GetDirector() const { return director; }
int TMovie::GetYear() const { return year; }
EMovieGenreType TMovie::GetGenre() const { return genre; }
float TMovie::GetScore() const { return score; }
