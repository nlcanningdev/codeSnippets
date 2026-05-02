#include "myString.h"
#include <fstream>
#include <cstddef>
#include <iostream>

void String::setupLine(std::ifstream &readFile, size_t &filePosition, uint8_t* &memoryPosition) {
    //readFile is already at the correct filePosition
    readFile.read(reinterpret_cast<char*>(&maxSize), sizeof(uint8_t));
    filePosition += 1;
    str = memoryPosition;
    int size;
    char input = '-';
    for(size = 0; input != '\0'; ++size) {
        readFile.read(&input, 1);
    }
    ++size;
    readFile.seekg(filePosition);
    readFile.read((char*)str, size);
    filePosition = readFile.tellg();
    memoryPosition += maxSize; //increment for the next object to use the block
}

uint8_t String::getSize() { //includes null byte
    uint8_t value;
    for(value = 0; str[value] != 0; ++value) {}
    return value + 1;
}

int String::getLength() {
    int value;
    for(value = 0; str[value] != 0; ++value) {}
    return value;
}

bool String::operator==(String &string) {
    if(string.getSize() != this->getSize())
        return false;
    for(int a = 0; a < this->getLength(); ++a) {
        if(this->str[a] != string.getElement(a))
            return false;
    }
    return true;
}

bool String::operator==(const char* string) {
    int size;
    for(size = 0; string[size] != '\0'; ++size) {}
    if(getSize() != size)
        return false;
    for(int a = 0; a < this->getLength(); ++a) {
        if(str[a] != string[a])
            return false;
    }
    return true;
}

void String::operator=(String &string) {
    for(int a = 0; a < string.getSize(); ++a) {
        this->str[a] = string.getElement(a);
    }
}

void String::operator=(const char* string) {
    int a;
    for(a = 0; string[a] != '\0'; ++a) {
        str[a] = string[a];
    }
    str[a] = '\0';
}

void String::operator+=(String &string) {
    int size = this->getLength();
    for(int a = size; a < (size + string.getLength()); ++a) {
        this->str[a] = string.getElement(a - size);
    }
    this->str[this->getLength()] = '\0';
}

void String::operator+=(const char* string) {
    int size = getLength();
    int size2;
    for(size2 = 0; string[size2] != '\0'; ++size2) {}
    for(int a = size; a < (size + size2); ++a) {
        str[a] = string[a - size];
    }
    str[this->getLength()] = '\0';
}

void String::clear() {
    for(int a = 0; a < maxSize; ++a) {
        str[a] = '\0';
    }
}

void String::printLine() {
    std::cout << str << std::endl; //this
}
