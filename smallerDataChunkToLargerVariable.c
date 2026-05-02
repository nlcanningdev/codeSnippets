#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define GLDEV_OPERATING_SYSTEM_WINDOWS 0
#define GLDEV_OPERATING_SYSTEM_LINUX 1
#define GLDEV_OPERATING_SYSTEM GLDEV_OPERATING_SYSTEM_WINDOWS

int main(int argc, char** argv) {
    size_t error = 0;
    uint32_t test0 = 0;
    uint16_t test1 = 0;
    uint8_t write = 215;
    FILE* file;
#if GLDEV_OPERATING_SYSTEM == GLDEV_OPERATING_SYSTEM_WINDOWS
    error = fopen_s(&file, "test.bin", "wb");
#elif GLDEV_OPERATING_SYSTEM == GLDEV_OPERATING_SYSTEM_LINUX
    file = fopen("test.bin", "wb");
#endif
    if (!error) {
        error = fwrite(&write, sizeof(uint8_t), 1, file);
        write = 17;
        error = fwrite(&write, sizeof(uint8_t), 1, file);
        fclose(file);
    }
#if GLDEV_OPERATING_SYSTEM == GLDEV_OPERATING_SYSTEM_WINDOWS
    error = fopen_s(&file, "test.bin", "rb");
#elif GLDEV_OPERATING_SYSTEM == GLDEV_OPERATING_SYSTEM_LINUX
    file = fopen("test.bin", "rb");
#endif
    if (!error) {
        error = fread(&test0, sizeof(uint8_t) * 2, 1, file);
        fclose(file);
    }
    printf("number: %d\n", test0);
    return 0;
}

//prints the correct value, ie. reading a smaller chunk of data into a
//larger variable is not a problem
