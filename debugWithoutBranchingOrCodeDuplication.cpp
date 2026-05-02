#include <iostream>
#include <cstdint>

/*
this usage of inheritance will come in useful for debugging without having to use an if 
statement to check if the program is in debug mode every single time,
and at the same time not having to rewrite tons of code.
all that's needed is to write what's basically a wrapper function for every base function,
in the derived class.
the only catch is that base functions must be written to either have return values, or
pointers as parameters, in order for the wrapper derived function to be able to write
about the results
*/

struct Program {
    public:
    size_t testFunction() {
        std::cout << "base class test function ran" << std::endl;
        return 5;
    }
};

struct DebugProgram : public Program {
    public:
    size_t testFunction() {
        std::cout << "child class test function ran" << std::endl;
        size_t returnValue = Program::testFunction();
        std::cout << "return value of base class version of test function: " << returnValue << std::endl;
        return returnValue;
    }
};

int main(int argc, char** argv) {
    bool useDebug = true;
    if(useDebug == true) {
        DebugProgram program;
        program.testFunction();
    }
    else if(useDebug == false) {
        Program program;
        program.testFunction();
    }
}
