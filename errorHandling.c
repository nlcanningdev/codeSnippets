#include <stdio.h>

//note to self: 0b11111111'11111111'11111111'11111111 is -1, the
//opposite of positive numbers

#define NCAN_ERROR_NONE 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000
#define NCAN_ERROR_ONE  0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000001
#define NCAN_ERROR_TWO  0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000010

int main(int argc, char** argv) {
    size_t error = NCAN_ERROR_NONE; //0
    error = error | NCAN_ERROR_ONE; //1
    error = error | NCAN_ERROR_TWO; //3
    error = error | NCAN_ERROR_ONE; //3
    error = error | NCAN_ERROR_NONE; //3, works as intended, can represent 64 errors (plus none)
    printf("error = %zu", error);
    return 0;
}
