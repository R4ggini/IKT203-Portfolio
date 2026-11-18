//
// Created by Lande on 18.11.2026.
//

#include "TSong.h"

#include <utility>

TSong::TSong(std::string artist, std::string title, int releaseYear, EMusicGenreType genre)
    : artist(std::move(artist)), title(std::move(title)), releaseYear(releaseYear), genre(genre) {}

TSong::~TSong() = default;

// Returns name of artist as string
std::string TSong::GetArtist() const {
    return artist;
}

// Returns song title as string
std::string TSong::GetTitle() const {
    return title;
}

// Returns release year of song as int
int TSong::GetReleaseYear() const {
    return releaseYear;
}

// Returns genre of song as EMusicGenreType
EMusicGenreType TSong::GetGenre() const {
    return genre;
}