#pragma once
#include <ranges>

/**
* @file   TCollection.hpp
* @brief  Dear student, this file contains the definition of the TCollection class template, which serves as a base class for all collection types in the project.
*         You will create this as a template class typeically holding "GetSize", "IsEmpty", and "Clear" methods, which are common to all collections.
*         Please ask for help in Discord if you have any questions or need assistance with the implementation.
*/

// Add your template here:
template<typename T>
class TCollection {
public:
    int GetSize() const;        // Get how many elements are in collection
    bool IsEmpty() const;       // Check to see if the collection is empty
    virtual void Clear() = 0;   // To be overridden by classes inheriting from it
protected:
    int size = 0;
};

template<typename T>
int TCollection<T>::GetSize() const {
    return size;
}

template<typename T>
bool TCollection<T>::IsEmpty() const {
    if (size == 0) return true;
    return false;
}

