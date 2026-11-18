//
// Created by Lande on 10.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_EMOVIEGENRETYPE_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_EMOVIEGENRETYPE_H

// 2
enum EMovieGenreType {
    Action = 1,
    Adventure = 2,
    Biography = 4,
    Crime = 8,
    Drama = 16,
    Fantasy = 32,
    History = 64,
    Western = 128
};

// Overrides | operator to function as a bitmask
inline EMovieGenreType operator|(EMovieGenreType a, EMovieGenreType b) {
    return static_cast<EMovieGenreType>(static_cast<int>(a) | static_cast<int>(b));
}

#endif //IKT203_ALGORITHMS_DATASTRUCTURE_EMOVIEGENRETYPE_H
