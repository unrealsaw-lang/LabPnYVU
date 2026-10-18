#pragma once
#include <iostream>
#include <vector>
#include <type_traits>
#include <ostream>

template<typename T> class collection {
std::vector<T> objects;

public:
	void add(const T& O) { objects.push_back(O); }

	void remove(const T& O) {
		for (size_t i = 0; i < objects.size(); i++) {
			if (objects[i] == O){
				objects.erase(objects.begin() + i);
				break;
			}
		}
	}

	T get(int index) const {
		if (index < 0 || index >= static_cast<int>(objects.size())) return T();
		else return objects[index];
	}

	int find(const T& O) {
		size_t i = 0;
		for (; i < objects.size(); i++) {
			if (objects[i] == O) return static_cast<int>(i);
		}
		return -1;
	}

	template<typename LambdaType> T findBy(LambdaType condition) const {
		for (const T& object : objects) {
			if (condition(object)) return object;
		}
		return T();
	}

	int getSize() const { return static_cast<int>(objects.size());}

	void clear() {
		objects.clear();
		std::cout << "\nCleared!\n";
	}

	void print(std::ostream &os = std::cout) const {
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
};