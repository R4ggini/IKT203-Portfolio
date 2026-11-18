//
// Created by Lande on 08.11.2026.
//

#ifndef IKT203_ALGORITHMS_DATASTRUCTURE_TEMPLATES_H
#define IKT203_ALGORITHMS_DATASTRUCTURE_TEMPLATES_H

#include <iostream>
#include <tuple>

// 1.1 a. Prints size of input datatype.
template<typename T>
void PrintTypeSize(T v) {
    std::cout << sizeof(v) << std::endl;
}

// 1.1 b. Generic template function that return the larger of two variables
template<typename T>
T GetMax(T a, T b) {
    if (a > b) return a;
    return b;
}

// 1.2 a. Variadic template struct
template<typename ...Args>
struct TDataPack {
    std::tuple<Args...> data;
    TDataPack(Args ...args) : data(args...) {}
};

// 1.2 b. Template array
template<typename T, int Size>
class TStaticArray {
    public:
        void Set(T* arr, int size) {
            for (int i = 0; i < size; i++) {
                data[i] = arr[i];
            }
            dataCount = size;
        }

        void Print() {
            for (int i = 0; i < dataCount; i++) {
                std::cout << data[i] << std::endl;
            }
        }
    private:
        T data[Size];
        int dataCount = 0; // To keep print from printing uninitialized variables
};

// 1.2 c. Template-Template Parameters
template<template <typename T, int> class Container, typename T, int N>
void PrintContainer(Container<T, N> staticArray) {
    staticArray.Print();
}

// 3 a. Generic Type Alias
template<typename T>
using FActionFunc = void (*)(T&);

// 3 b. The Generic Processor
template<typename T>
void ProcessArray(T* arr, int size, FActionFunc<T> cb) {
    for (int i = 0; i < size; i++) {
        cb(arr[i]);
    }
}

// 4 The OOP Template Class
template<typename T>
class TDataAggregator {
    public:
        T GetStateTotal() {
            return stateTotal;
        }

        void Accumulate(T& val) {
            this->stateTotal += val;
            val *= 2;
        }

        static void StaticCallback(T& val, void* context) {
            static_cast<TDataAggregator<T>*>(context)->Accumulate(val);
        }

    private:
        T stateTotal = 0;
};

// 4 d. The C-Style API
template<typename T>
using FContextFunc = void (*)(T&, void*);

template<typename T>
void ProcessWithContext(T* arr, int size, FContextFunc<T> cb, void* context) {
    for (int i = 0; i < size; i++) {
        cb(arr[i], context);
    }
}

#endif //IKT203_ALGORITHMS_DATASTRUCTURE_TEMPLATES_H
