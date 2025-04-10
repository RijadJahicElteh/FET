#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include "MojVektor.hpp"  // Pretpostavljam da je MojVektor u ovom fajlu

int main() {
    try {
        // Testiranje default konstruktora
        MojVektor<int> v1;
        std::cout << "v1 size: " << v1.size() << ", capacity: " << v1.capacity() << std::endl;

        // Testiranje push_back
        v1.push_back(10);
        v1.push_back(20);
        v1.push_back(30);
        std::cout << "v1 after push_back: ";
        for (const auto& el : v1) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        // Testiranje push_front
        v1.push_front(5);
        std::cout << "v1 after push_front: ";
        for (const auto& el : v1) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        // Testiranje at() sa validnim indeksom
        std::cout << "v1[1] (at index 1): " << v1.at(1) << std::endl;

        // Testiranje at() sa nevalidnim indeksom (izbacuje iznimku)
        try {
            std::cout << "v1[10] (out of range): " << v1.at(10) << std::endl;
        } catch (const std::out_of_range& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }

        // Testiranje pop_back
        v1.pop_back();
        std::cout << "v1 after pop_back: ";
        for (const auto& el : v1) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        // Testiranje pop_front
        v1.pop_front();
        std::cout << "v1 after pop_front: ";
        for (const auto& el : v1) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        // Testiranje front() i back()
        std::cout << "v1 front: " << v1.front() << ", back: " << v1.back() << std::endl;

        // Testiranje resize()
        v1.resize(5, 100);
        std::cout << "v1 after resize to 5: ";
        for (const auto& el : v1) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        // Testiranje clear()
        v1.clear();
        std::cout << "v1 after clear: size: " << v1.size() << ", capacity: " << v1.capacity() << std::endl;

        // Testiranje operator==
        MojVektor<int> v2;
        v2.push_back(10);
        v2.push_back(20);
        v2.push_back(30);
        std::cout << "v1 == v2: " << (v1 == v2 ? "True" : "False") << std::endl;

        // Testiranje full()
        std::cout << "v1 full: " << (v1.full() ? "True" : "False") << std::endl;

        // Testiranje iteratora
        v2.push_back(40);
        v2.push_back(50);
        std::cout << "v2 with iterators: ";
        for (auto it = v2.begin(); it != v2.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        // Testiranje find()
        auto it = v2.find(20);
        if (it != v2.end()) {
            std::cout << "Found value: " << *it << std::endl;
        } else {
            std::cout << "Value not found!" << std::endl;
        }

        // Testiranje erase()
        v2.erase(v2.begin() + 1);  // Erase second element
        std::cout << "v2 after erase: ";
        for (const auto& el : v2) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        // Testiranje insert()
        v2.insert(v2.begin() + 1, 60);  // Insert at second position
        std::cout << "v2 after insert: ";
        for (const auto& el : v2) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        // Testiranje rotate()
        v2.rotate();
        std::cout << "v2 after rotate: ";
        for (const auto& el : v2) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        // Testiranje for_each
        v2.for_each([](int& a) { a += 1; });
        std::cout << "v2 after for_each: ";
        for (const auto& el : v2) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        // Testiranje remove_if
        v2.remove_if([](int a) { return a % 2 == 0; });
        std::cout << "v2 after remove_if: ";
        for (const auto& el : v2) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}

