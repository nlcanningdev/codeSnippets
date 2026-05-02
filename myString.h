#include <fstream>
#include <cstddef>

/*ie. for reading in line of text to be used,
identifiers for object(?), should eliminate any need for text files, 
don't use for console input, used within limits of scene memory,
would only ever be needed for a single line
no need for any destructor*/
class String {
    private:
        uint8_t* str; //null terminated, holds address within pre-allocated memory
        uint8_t maxSize; //the biggest str can be in memory, ie. the space set aside for it
    public:
        void setupLine(std::ifstream &readFile, size_t &filePosition, uint8_t* &memoryPosition);
        uint8_t getSize(); //like length, but includes null byte, ie. not total memory that the string takes up, that is maxSize
        int getLength(); //does not include null byte, ie. length of text
        inline uint8_t getMaxSize() { return maxSize; } //size of string within pre-allocated memory
        bool operator==(String &string);
        bool operator==(const char* string);
        void operator=(String &string); //assumes this string's max size can accomodate the copy
        void operator=(const char* string);
        void operator+=(String &string); //likewise
        void operator+=(const char* string);
        void clear(); //sets all bytes from address of str to < maxSize to null byte
        inline uint8_t getElement(int index) { return str[index]; }
        inline void putElement(int index, uint8_t element) { str[index] = element; }
        void printLine(); //for testing only, uses iostream
};
