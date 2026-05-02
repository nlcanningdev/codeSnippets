#include <iostream>

/*
return value evaluation:
function evaluated as true when given 0
function evaluated as false when given 1
*/

bool test(int testNum) {
    bool returnValue = false;
    if(testNum == 1)
        returnValue = false;
    else if(testNum == 0)
        returnValue = true;
    return returnValue;
}

int main(int argc, char** argv) {
    bool testResult = false;
    if((testResult = test(1)) == true)
        std::cout << "function evaluated as true when given 1" << std::endl;
    if((testResult = test(0)) == true)
        std::cout << "function evaluated as true when given 0" << std::endl;
    if((testResult = test(1)) == false)
        std::cout << "function evaluated as false when given 1" << std::endl;
    if((testResult = test(0)) == false)
        std::cout << "function evaluated as false when given 0" << std::endl;
    return 0;
}
