#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdalign.h>

//in the actual program, initialise to the user-defined maximums, which are used for the allocations, and then the structs contain the current numbers
//try to avoid nested dynamic structs unless necessary.

#define ALLOCATION_TYPE_NUMBER_TYPE UINTMAX_C(2)
#define GLDEV_PLATFORM_WINDOWS 0
#define GLDEV_PLATFORM_LINUX 1
#define GLDEV_PLATFORM GLDEV_PLATFORM_WINDOWS
#if GLDEV_PLATFORM == GLDEV_PLATFORM_WINDOWS
#define GLDEV_ALIGNED_ALLOC _aligned_malloc(allocationTotalSize, allocationType_Alignment[ALLOCATION_TYPE_NUMBER_TYPE])
#define GLDEV_ALIGNED_FREE _aligned_free
#elif GLDEV_PLATFORM == GLDEV_PLATFORM_LINUX
#define GLDEV_ALIGNED_ALLOC aligned_alloc(allocationType_Alignment[ALLOCATION_TYPE_NUMBER_TYPE], allocationTotalSize)
#define GLDEV_ALIGNED_FREE free
#endif

struct Test_0 {
    uint8_t test;
    uint16_t test2;
};

struct Test_1 {
    uint32_t test;
    uint8_t test2;
    struct Test_0* test0;
    size_t test0_Number;
};

uintptr_t getOffsetFromNextMultipleOfAlignment(uintptr_t size, uintptr_t alignment) {
    uintptr_t offset = UINTMAX_C(0);
    for (; (size + offset) % alignment != UINTMAX_C(0); ++offset) {

    }
    return offset;
}

//modify this signature as more types of objects are added to the pool
uint8_t create_memoryPool(void** memoryPool, struct Test_0** test_0, size_t test_0_Number, struct Test_1** test_1, size_t test_1_Number) {
    //modify the following (until next full-line comment, if any) as more types of objects are added to the pool

    //stays the same (until next full-line comment, if any)
    uint8_t returnValue = UINT8_C(1);
    size_t allocationType_Number_allocation[ALLOCATION_TYPE_NUMBER_TYPE];
    uintptr_t allocationType_Size_type[ALLOCATION_TYPE_NUMBER_TYPE];
    uintptr_t allocationType_Size_allocation[ALLOCATION_TYPE_NUMBER_TYPE];
    uintptr_t allocationType_Start[ALLOCATION_TYPE_NUMBER_TYPE];
    uintptr_t allocationType_Alignment[ALLOCATION_TYPE_NUMBER_TYPE + UINTMAX_C(1)];
    uintptr_t allocationTotalSize = UINTMAX_C(0);

    //modify the following (until next full-line comment, if any) as more types of objects are added to the pool
    allocationType_Number_allocation[0] = test_0_Number;
    allocationType_Number_allocation[1] = test_1_Number;
    allocationType_Size_type[0] = sizeof(struct Test_0);
    allocationType_Size_type[1] = sizeof(struct Test_1);
    allocationType_Alignment[0] = alignof(struct Test_0);
    allocationType_Alignment[1] = alignof(struct Test_1);

    //stays the same (until next full-line comment, if any)
    allocationType_Alignment[2] = UINTMAX_C(0); //maximum-alignment

    for (size_t allocationType_Number_type_current = UINTMAX_C(0); allocationType_Number_type_current < ALLOCATION_TYPE_NUMBER_TYPE; ++allocationType_Number_type_current) {
        if (allocationType_Alignment[ALLOCATION_TYPE_NUMBER_TYPE] < allocationType_Alignment[allocationType_Number_type_current])
            allocationType_Alignment[ALLOCATION_TYPE_NUMBER_TYPE] = allocationType_Alignment[allocationType_Number_type_current];
    }

    for (size_t allocationType_Number_type_current = UINTMAX_C(0); allocationType_Number_type_current < ALLOCATION_TYPE_NUMBER_TYPE; ++allocationType_Number_type_current) {
        allocationType_Start[allocationType_Number_type_current] = UINTMAX_C(0) + allocationTotalSize;
        allocationType_Size_allocation[allocationType_Number_type_current] = allocationType_Size_type[allocationType_Number_type_current] * allocationType_Number_allocation[allocationType_Number_type_current];
        allocationType_Size_allocation[allocationType_Number_type_current] += getOffsetFromNextMultipleOfAlignment(allocationType_Size_allocation[allocationType_Number_type_current], allocationType_Alignment[allocationType_Number_type_current + UINTMAX_C(1)]);
        allocationTotalSize += allocationType_Size_allocation[allocationType_Number_type_current];
    }

    *memoryPool = GLDEV_ALIGNED_ALLOC;
    if (*memoryPool != NULL) {
        allocationType_Start[0] = (uintptr_t)*memoryPool;

        //possibly modify this next line (only) as more types of objects are added to the pool
        *test_0 = (struct Test_0*)allocationType_Start[0];

        for (size_t allocationType_Number_type_current = UINTMAX_C(1); allocationType_Number_type_current < ALLOCATION_TYPE_NUMBER_TYPE; ++allocationType_Number_type_current) {
            allocationType_Start[allocationType_Number_type_current] += allocationType_Start[0];
            switch (allocationType_Number_type_current) {
                //add/write more cases as more types of objects are added to the pool
            case 1:
                *test_1 = (struct Test_1*)allocationType_Start[1];
                break;
            }
        }
    }
    else
        returnValue = UINT8_C(0);
    return returnValue;
}

void destroy_memoryPool(void** memoryPool) {
    GLDEV_ALIGNED_FREE(*memoryPool);
}

int main(int argc, char** argv) {
    void* memoryPool = NULL;
    struct Test_0* test_0 = NULL;
    size_t test_0_Number = UINTMAX_C(3);
    struct Test_1* test_1 = NULL;
    size_t test_1_Number = UINTMAX_C(5);
    if (create_memoryPool(&memoryPool, &test_0, test_0_Number, &test_1, test_1_Number)) {
        test_0[0].test = UINT8_C(12);
        test_0[0].test2 = UINT16_C(312);
        test_0[1].test = UINT8_C(42);
        test_0[1].test2 = UINT16_C(423);
        test_0[2].test = UINT8_C(17);
        test_0[2].test2 = UINT16_C(25);
        test_1[0].test = UINT32_C(1200);
        test_1[0].test2 = UINT8_C(1);
        test_1[1].test = UINT32_C(1201);
        test_1[1].test2 = UINT8_C(2);
        test_1[2].test = UINT32_C(1202);
        test_1[2].test2 = UINT8_C(3);
        test_1[3].test = UINT32_C(1204);
        test_1[3].test2 = UINT8_C(4);
        test_1[4].test = UINT32_C(1205);
        test_1[4].test2 = UINT8_C(5);
        for (size_t test_0_Current = UINTMAX_C(0); test_0_Current < test_0_Number; ++test_0_Current) {
            printf("test_0[%llu].test: %u\n", test_0_Current, (uint32_t)test_0[test_0_Current].test);
            printf("test_0[%llu].test2: %u\n", test_0_Current, (uint32_t)test_0[test_0_Current].test2);
        }
        for (size_t test_1_Current = UINTMAX_C(0); test_1_Current < test_1_Number; ++test_1_Current) {
            printf("test_1[%llu].test: %u\n", test_1_Current, (uint32_t)test_1[test_1_Current].test);
            printf("test_1[%llu].test2: %u\n", test_1_Current, (uint32_t)test_1[test_1_Current].test2);
        }
        destroy_memoryPool(&memoryPool);
    }
    return 0;
}
