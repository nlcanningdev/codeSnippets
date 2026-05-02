#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//uint16_t (stored as uint64_t from big endian to little endian,
//ie. flip the order of the two bytes
//followed by a uint24_t. the middle byte remains in the same place.
//followed by a uint32_t
//note: the printf should really use the more portable versions, see google search,
//but who cares

int main(int argc, char** argv) {
	uint64_t bigEndian = 55057; //1101011100010001
	uint64_t littleEndian = (UINTMAX_C(0) | (bigEndian >> 8) | ((bigEndian << 56) >> 48));
	printf("littleEndian: %llu\n", littleEndian); //should be 4567, ie. 0001000111010111
	bigEndian = 13439447; //110011010001000111010111
	littleEndian = (UINTMAX_C(0) | (bigEndian >> 16) | (((bigEndian << 48) >> 56) << 8) | ((bigEndian << 56) >> 40));
	printf("littleEndian: %llu\n", littleEndian); //should be 14094797, ie. 110101110001000111001101
	return 0;
}
