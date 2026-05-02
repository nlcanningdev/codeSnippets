#include <iostream>
#include <cstddef>

int main() {
    uint8_t* memblock = new uint8_t[2];
    uint8_t* address = memblock;
    std::cout << (void*)memblock << std::endl;
    std::cout << (void*)address << std::endl;
    memblock[0] = 1;
    memblock[1] = 2;
    std::cout << (int)memblock[0] << std::endl;
    std::cout << (int)memblock[1] << std::endl;
    uint8_t* test = address;
    test[0] = 3;
    std::cout << (void*)test << std::endl;
    test += 1;
    test[0] = 4;
    std::cout << (void*)test << std::endl;
    std::cout << (int)memblock[0] << std::endl;
    std::cout << (int)memblock[1] << std::endl;
    delete[] memblock;
    return 0;
}
