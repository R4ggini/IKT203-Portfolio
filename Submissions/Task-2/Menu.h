//
// Created by Lande on 10.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_MENU_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_MENU_H
#include <iostream>
#include "Classes/TMovie.h"

inline void PrintMainMenu() {
    std::cout << "1: Show all movies in list\n"
                 "2: Get movie at index\n"
                 "3: Prepend movie to list\n"
                 "4: Append movie to list\n"
                 "5: Remove movie at index\n"
                 "6: Search by title\n"
                 "7: Search by director\n"
                 "8: Search by genre\n"
                 "9: Reverse list\n"
                 "0: Exit\n\n";
}

inline void PrintIndexGetter() {
    std::cout << "At index:\n\n";
}

inline TMovie *InputMovie() {
    std::cout << "Enter title\n";
    std::string title;
    std::getline(std::cin, title);
    std::cout << "Enter director\n";
    std::string director;
    std::getline(std::cin, director);
    std::cout << "Enter year\n";
    int year;
    std::cin >> year;
    std::cin.ignore();
    std::cout << "Enter genre\n";
    int genreAsInt;
    std::cin >> genreAsInt;
    std::cin.ignore();
    EMovieGenreType genre = static_cast<EMovieGenreType>(genreAsInt);
    std::cout << "Score\n";
    float score;
    std::cin >> score;
    std::cin.ignore();
    auto movie = new TMovie(title, director, year, genre, score);
    return movie;
}



#endif //IKT203_ALGORITHMS_DATASTRUCTURE_MENU_H
