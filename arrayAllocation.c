#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int* test = NULL;
    test = malloc(sizeof(int) * 2);
    if(test != NULL) {
        test[0] = 2; //equivalent to *test = 2, the array subscript automatically dereferences the pointer
        test[1] = 5; //however, if test were a nonpointer, you could not use [0]
        printf("test: %d\n", test[0]); //this is obviously different in c++
        printf("test: %d", test[1]);
        free((void*)test);
    }
    return 0;
}
