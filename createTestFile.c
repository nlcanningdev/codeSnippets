#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	FILE* file = fopen("./testData_0.bin", "wb");
	if (file != NULL) {
		size_t invariant_0 = 56;
		size_t value_0 = 1;
		size_t invariant_1 = 131;
		size_t value_1 = 2;
		fwrite((void*)&invariant_0, sizeof(size_t) * 1, 1, file);
		fwrite((void*)&value_0, sizeof(size_t) * 1, 1, file);
		fwrite((void*)&invariant_1, sizeof(size_t) * 1, 1, file);
		fwrite((void*)&value_1, sizeof(size_t) * 1, 1, file);
		fclose(file);
	}
	return 0;
}
