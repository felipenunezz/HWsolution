#include <iostream>

class A {
    int size;
    int capacity;
public:
        A();
        A(int size);
        A push_back(int v);

};

A::A() {
    size = 0;
    capacity = 15;
}
A::A(int size) { this->size = size; capacity = size + 15; }

A A::push_back(int v) { return *this; }

int main() {
    int n = 0;
    A Mvalue;
    int v = 0;

    int* f = new int[15];
    std::cout << "Input values for insert (enter to finish): ";
    do {
        std::cin >> f[n];
        Mvalue.push_back(v);
        n++;
    } while (std::cin.get() != '\n');

    for (size_t i = 0; i < 15; i++) { std::cout << f[i]; }
    return 0;
}