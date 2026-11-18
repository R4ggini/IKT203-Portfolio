#include <iostream>
#include <string>
#include "Classes/TMovieList.h"
#include "Menu.h"

bool SearchByTitle(TMovie* movie, void* searchCriteria) {
    auto* title = static_cast<std::string*>(searchCriteria);
    if (movie->GetTitle() == *title) return true;
    return false;
}

bool SearchByDirector(TMovie* movie, void* searchCriteria) {
    auto* director = static_cast<std::string*>(searchCriteria);
    if (movie->GetDirector() == *director) return true;
    return false;
}

bool SearchByGenre(TMovie* movie, void* searchCriteria) {
    auto* genre = static_cast<EMovieGenreType*>(searchCriteria);
    if (movie->GetGenre() & *genre) return true;
    return false;
}

std::string GenreToString(EMovieGenreType genre) {
    std::string result;
    if (genre & Action)    result += "Action, ";
    if (genre & Adventure) result += "Adventure, ";
    if (genre & Biography) result += "Biography, ";
    if (genre & Crime)     result += "Crime, ";
    if (genre & Drama)     result += "Drama, ";
    if (genre & Fantasy)   result += "Fantasy, ";
    if (genre & History)   result += "History, ";
    if (genre & Western)   result += "Western, ";
    if (result.empty()) return "None";
    return result.substr(0, result.size() - 2); // Removes the trailing ", "
}

void PrintMovie(const TMovie* movie) {
    if (movie == nullptr) {
        std::cout << "(no movie)" << std::endl;
        return;
    }
    std::cout << movie->GetTitle() << " | " << movie->GetDirector() << " | " << movie->GetYear()
              << " | " << GenreToString(movie->GetGenre()) << " | " << movie->GetScore() << std::endl;
}

void PrintList(TMovieList& list) {
    for (int i = 1; TMovie* movie = list.GetAtIndex(i); i++) {
        std::cout << i << ". ";
        PrintMovie(movie);
    }
}

void AddTestData(TMovieList& list) {
    list.Append (new TMovie("The Shawshank Redemption", "Frank Darabont", 1994, Drama, 9.3f));
    list.Prepend(new TMovie("The Godfather", "Francis Ford Coppola", 1972, Crime | Drama, 9.2f));
    list.Append (new TMovie("The Dark Knight", "Christopher Nolan", 2008, Action | Crime | Drama, 9.1f));
    list.Prepend(new TMovie("The Godfather Part II", "Francis Ford Coppola", 1974, Crime | Drama, 9.0f));
    list.Append (new TMovie("12 Angry Men", "Sidney Lumet", 1957, Crime | Drama, 9.0f));
    list.Prepend(new TMovie("The Lord of the Rings: The Return of the King", "Peter Jackson", 2003, Adventure | Drama | Fantasy, 8.9f));
    list.Append (new TMovie("Schindler's List", "Steven Spielberg", 1993, Biography | Drama | History, 8.9f));
    list.Prepend(new TMovie("The Lord of the Rings: The Fellowship of the Ring", "Peter Jackson", 2001, Adventure | Drama | Fantasy, 8.8f));
    list.Append (new TMovie("Pulp Fiction", "Quentin Tarantino", 1994, Crime | Drama, 8.9f));
    list.Prepend(new TMovie("The Good, the Bad and the Ugly", "Sergio Leone", 1966, Western, 8.8f));
}

int main() {
    TMovieList list;
    AddTestData(list);

    int menu = 0;
    int index = 0;
    std::string title;
    std::string director;
    int genreAsInt = 0;
    EMovieGenreType genre;
    while (true) {
        PrintMainMenu();
        std::cin >> menu;
        std::cin.ignore();
        switch (menu) {
            case 1:
                PrintList(list);
                break;
            case 2:
                PrintIndexGetter();
                std::cin >> index;
                std::cin.ignore();
                PrintMovie(list.GetAtIndex(index));
                break;
            case 3:
                list.Prepend(InputMovie());
                break;
            case 4:
                list.Append(InputMovie());
                break;
            case 5:
                PrintIndexGetter();
                std::cin >> index;
                std::cin.ignore();
                list.Remove(index);
                break;
            case 6:
                std::cout << "Write title:\n";
                std::getline(std::cin, title);
                PrintMovie(list.SearchFor(SearchByTitle, &title));
                break;
            case 7:
                std::cout << "Write director:\n";
                std::getline(std::cin, director);
                PrintMovie(list.SearchFor(SearchByDirector, &director));
                break;
            case 8:
                std::cout << "Write genre as power of 2:\n";
                std::cin >> genreAsInt;
                std::cin.ignore();
                genre = static_cast<EMovieGenreType>(genreAsInt);
                PrintMovie(list.SearchFor(SearchByGenre, &genre));
                break;
            case 9:
                list.Reverse();
                break;
            case 0:
                return 0;
            default:
                break;
        }
    }

    return 0;
}
