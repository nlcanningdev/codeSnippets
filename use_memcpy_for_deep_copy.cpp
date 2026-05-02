//bulk deep-copy an array of Test2 objects to a second Test2 array

#include <iostream>
#include <string.h>

class Test2 {
    public:
        void setA(int a) { this->a = a; }
        void setB(int b) { this->b = b; }
        void setC(const char* c) { strcpy(this->c, c); }
        int getA() { return this->a; }
        int getB() { return this->b; }
        char* getC() { return this->c; }
    private:
        int a;
        int b;
        char c[6];
};

class Test1 {
    public:
        Test1() {
            this->test2[0].setA(0);
            this->test2[0].setB(1);
            this->test2[0].setC("zero\0");
            this->test2[1].setA(2);
            this->test2[1].setB(3);
            this->test2[1].setC("one\0");
            this->test2[2].setA(4);
            this->test2[2].setB(5);
            this->test2[2].setC("two\0");
            this->test2[3].setA(6);
            this->test2[3].setB(7);
            this->test2[3].setC("three\0");
        }
        void copy(Test2* destination) {
            memcpy(destination, this->test2, sizeof(Test2) * 4); //deep copy here
        }
        void setA(size_t index, int a) {
            this->test2[index].setA(a);
        }
        void setB(size_t index, int b) {
            this->test2[index].setB(b);
        }
        void setC(size_t index, const char* c) {
            this->test2[index].setC(c);
        }
    private:
        Test2 test2[4];
};

int main()
{
    Test1 test1;
    Test2 test2[4];;
    test1.copy(test2);
    for(size_t a = 0; a < 4; ++a) { //test copy
        std::cout << a << ") a = " << test2[a].getA() << std::endl;
        std::cout << a << ") b = " << test2[a].getB() << std::endl;
        std::cout << a << ") c = " << test2[a].getC() << std::endl;
    }
    test1.setA(1, 9); //change data in test1 to test for proper deep-copy
    test1.setB(2, 12);
    test1.setC(0, "test\0");
    test1.setC(2, "yeah\0");
    for(size_t a = 0; a < 4; ++a) { //test for deep-copy, success!
        std::cout << a << ") a = " << test2[a].getA() << std::endl;
        std::cout << a << ") b = " << test2[a].getB() << std::endl;
        std::cout << a << ") c = " << test2[a].getC() << std::endl;
    }
    return 0;
}
