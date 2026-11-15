#pragma once
#include <iostream>
#include <vector>
#include <type_traits>
#include <ostream>
#include "MissingObjectException.h"
#include "CourseLimitViolationException.h"

template<typename T> class collection {
    std::vector<T> objects;

public:
    void add(const T& O) { objects.push_back(O); }

    void remove(const T& O) {
        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i] == O) {
                objects.erase(objects.begin() + i);
                return;
            }
        }
        throw MissingObjectException("Collection does not include given object");
    }

    T get(int index) const {
        if (index < 0 || index >= static_cast<int>(objects.size()))
            throw CourseLimitViolationException("Index shoud be >= 0 and < collection size");
        return objects[index];
    }

    int find(const T& O) {
        for (size_t i = 0; i < objects.size(); i++)
            if (objects[i] == O) return static_cast<int>(i);
        return -1;
    }

    template<typename LambdaType> T findBy(LambdaType condition) const {
        for (const T& object : objects)
            if (condition(object)) return object;
        throw MissingObjectException("No object matching given condition");
    }

    int getSize() const { return static_cast<int>(objects.size()); }

    void clear() { objects.clear(); }

    void print(std::ostream& os = std::cout) const {
        for (size_t i = 0; i < objects.size(); ++i) {
            os << "\nObject " << i + 1 << "): ";
            if constexpr (std::is_pointer_v<T>) {
                if (objects[i]) os << *objects[i];
                else os << "nullptr";
            }
            else os << objects[i];
            os << "\n";
        }
    }

    auto begin() { return objects.begin(); }
    auto end() { return objects.end(); }
    auto begin() const { return objects.begin(); }
    auto end() const { return objects.end(); }
};