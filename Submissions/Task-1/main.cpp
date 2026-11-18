#include <iostream>
#include <string>
#include "StructureReader.h"
#include "Templates.h"
#include <cctype>

// 1.1 a
struct TDataStruct {
    int intVar = 5;
    double doubleVar = 4.5;
    char charVar = 'a';
};

// 1.1 b-c
struct TStudent {
    int grade;

    bool operator>(const TStudent& other) const {
        return grade > other.grade;
    }
};

//2 a
int Add(int a, int b) {
    return a + b;
}

// 2 b
std::string Greet(std::string name) {
    return "Hello, " + std::move(name);
}

using GreetPtr = std::string (*)(std::string);

// 2 c
bool IsEven(int a) {
    if (a % 2 == 0) return true;
    return false;
}

bool IsOdd(int a) {
    if (a % 2 == 0) return false;
    return true;
}

void FilterAndPrint(int *arr, int size, bool cb(int)) {
    for (int i = 0; i < size; i++) {
        if (cb(arr[i])) {
            std::cout << arr[i] << " ";
        }
    }
    std::cout << std::endl;
}

// 2 d
void Play() {
    std::cout << "Playing game..." << std::endl;
}

void Pause() {
    std::cout << "Game paused." << std::endl;
}

void Quit() {
    std::cout << "Quitting game." << std::endl;
}

// 3 c
void DoubleInt(int& val) {
    val *= 2;
}

void CapitalizeChar(char& val) {
    val = toupper(val);
}

// Main consists of tests for each step
int main() {
    {
        std::cout << "1.1 a: Basic Template Functions" << std::endl;
        int a = 10;
        double b = 10.1;
        TDataStruct dataStruct; // Values already initialized
        PrintTypeSize(a);
        PrintTypeSize(b);
        PrintTypeSize(dataStruct);
    }

    {
        std::cout << "1.1 b-c: Basic Template Functions" << std::endl;
        TStudent student1 {70};
        TStudent student2 {85};
        TStudent a = GetMax(student1, student2); // Compares using the overloaded operator
        std::cout << a.grade << std::endl;
    }

    {
        std::cout << "1.2 a: Variadic Template Struct" << std::endl;
        auto a = TDataPack(4, 4.4, 'a');
        std::cout << std::get<0>(a.data) << std::endl;
        std::cout << std::get<1>(a.data) << std::endl;
        std::cout << std::get<2>(a.data) << std::endl;
    }

    {
        std::cout << "1.2 b-c: Template Array & Template-Template Parameters" << std::endl;
        int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        TStaticArray<int, 50> array;
        array.Set(arr, 10);
        array.Print();
        PrintContainer(array);
    }

    {
        std::cout << "2 a: Basic Assignment and Invocation" << std::endl;
        int (*ptr)(int, int) = &Add;
        int a = (*ptr)(1, 2);
        int b = ptr(3, 4);
        std::cout << a << " " << b << std::endl;
    }

    {
        std::cout << "2 b: Making It Readable with Type Aliases" << std::endl;
        GreetPtr greetPtr = &Greet;
        std::cout << greetPtr("Ragnar") << std::endl;
    }

    {
        std::cout << "2 c: Passing Functions as Arguments" << std::endl;
        int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        FilterAndPrint(arr, 10, &IsEven);
        FilterAndPrint(arr, 10, &IsOdd);
    }

    {
        std::cout << "2 d: Array of Function Pointers" << std::endl;
        using FuncPtr = void (*)();
        for (FuncPtr ptrs[3] = {&Play, &Pause, &Quit}; const auto & ptr : ptrs) {
            ptr();
        }
    }

    {
        std::cout << "3. The Bridge" << std::endl;
        int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        char charArr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
        for (int var : arr) {
            std::cout << var << std::endl;
        }
        ProcessArray(arr, 10, DoubleInt);
        for (int var : arr) {
            std::cout << var << std::endl;
        }
        for (char var : charArr) {
            std::cout << var << std::endl;
        }
        ProcessArray(charArr, 8, CapitalizeChar);
        for (char var : charArr) {
            std::cout << var << std::endl;
        }
    }

    {
        std::cout << "4. The OOP Template Class & Context Pointers" << std::endl;
        TDataAggregator<int> dataAggregator;
        int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        ProcessWithContext(arr, 10, TDataAggregator<int>::StaticCallback, &dataAggregator);
        for (int var : arr) {
            std::cout << var << std::endl;
        }
        std::cout << dataAggregator.GetStateTotal() << std::endl;
    }
    return 0;
}