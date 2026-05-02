#include <stdint.h>
#include <stdio.h>
#include <string.h>
/*
binary literals note:
as can be seen below, if we consider each binary literal to be an array of bytes, we put the bytes in right to left order.
however, if the array is meant to represent a larger type eg. uint16_t, the bytes that make up said type are arranged left
to right, while the array structure is still right to left.
the main point of this is to somewhat cut down on the size of code related to strings.
*/

#include <stdlib.h>
#include <stdalign.h>

#define NCAN_OPERATING_SYSTEM_WINDOWS 0
#define NCAN_OPERATING_SYSTEM_LINUX 1
#define NCAN_OPERATING_SYSTEM NCAN_OPERATING_SYSTEM_WINDOWS

#define NCAN_EXECUTABLE_TYPE_IS_CALLER_EXECUTABLE 0
#define NCAN_EXECUTABLE_TYPE_IS_CALLEE_EXECUTABLE 1
#define NCAN_EXECUTABLE_TYPE NCAN_EXECUTABLE_TYPE_IS_CALLER_EXECUTABLE

#define NCAN_MAX_PATH 256

#if NCAN_OPERATING_SYSTEM == NCAN_OPERATING_SYSTEM_LINUX
#include <unistd.h>
#define NCAN_PATH_TYPE uint8_t
#define NCAN_BINARY_LITERAL_NUMBER 2
//e s <linux-slash> c o r p <linux-slash>
#define NCAN_BINARY_LITERAL_LINUX_READLINK_ARGUMENT_0 0b01100101'01110011'00101111'01100011'01101111'01110010'01110000'00101111
//NULL NULL e x e <linux-slash> l f
#define NCAN_BINARY_LITERAL_LINUX_READLINK_ARGUMENT_1 0b00000000'00000000'01100101'01111000'01100101'00101111'01100110'01101100
#elif NCAN_OPERATING_SYSTEM == NCAN_OPERATING_SYSTEM_WINDOWS
#include "windows.h"
#include <Psapi.h>
#define NCAN_PATH_TYPE uint16_t
#define NCAN_BINARY_LITERAL_NUMBER 5
//P t e G
#define NCAN_BINARY_LITERAL_WINDOWS_PATH_ARGUMENT_0 0b00000000'01010000'00000000'01110100'00000000'01100101'00000000'01000111
//S h t a
#define NCAN_BINARY_LITERAL_WINDOWS_PATH_ARGUMENT_1 0b00000000'01010011'00000000'01101000'00000000'01110100'00000000'01100001
//p p i n
#define NCAN_BINARY_LITERAL_WINDOWS_PATH_ARGUMENT_2 0b00000000'01110000'00000000'01110000'00000000'01101001'00000000'01101110
//e . t e
#define NCAN_BINARY_LITERAL_WINDOWS_PATH_ARGUMENT_3 0b00000000'01100101'00000000'00101110'00000000'01110100'00000000'01100101
//NULL NULL e x
#define NCAN_BINARY_LITERAL_WINDOWS_PATH_ARGUMENT_4 0b00000000'00000000'00000000'00000000'00000000'01100101'00000000'01111000
#endif

void gldev_set_binaryLiteral(uint64_t* binaryLiteral) {
#if NCAN_OPERATING_SYSTEM == NCAN_OPERATING_SYSTEM_WINDOWS
	binaryLiteral[0] = NCAN_BINARY_LITERAL_WINDOWS_PATH_ARGUMENT_0;
	binaryLiteral[1] = NCAN_BINARY_LITERAL_WINDOWS_PATH_ARGUMENT_1;
	binaryLiteral[2] = NCAN_BINARY_LITERAL_WINDOWS_PATH_ARGUMENT_2;
	binaryLiteral[3] = NCAN_BINARY_LITERAL_WINDOWS_PATH_ARGUMENT_3;
	binaryLiteral[4] = NCAN_BINARY_LITERAL_WINDOWS_PATH_ARGUMENT_4;
#elif NCAN_OPERATING_SYSTEM == NCAN_OPERATING_SYSTEM_LINUX
	binaryLiteral[0] = NCAN_BINARY_LITERAL_LINUX_READLINK_ARGUMENT_0;
	binaryLiteral[1] = NCAN_BINARY_LITERAL_LINUX_READLINK_ARGUMENT_1;
#endif

}

void gldev_appendBinaryLiteralToString(uint8_t* string, uint8_t* binaryLiteral_Pointer, size_t binaryLiteralToAppend_Number, size_t string_StartAppendIndex) {
	for (size_t binaryLiteralToAppend_Count = UINTMAX_C(0); binaryLiteralToAppend_Count < binaryLiteralToAppend_Number; ++binaryLiteralToAppend_Count) {
		memcpy(&string[string_StartAppendIndex], binaryLiteral_Pointer, sizeof(uint64_t));
		string_StartAppendIndex += UINTMAX_C(8);
		binaryLiteral_Pointer += sizeof(uint64_t);
	}
}

#if NCAN_OPERATING_SYSTEM == NCAN_OPERATING_SYSTEM_WINDOWS
int WINAPI wWinMain(_In_ HINSTANCE instance_Handle, _In_opt_ HINSTANCE previousInstanceHandle, _In_ PWSTR commandLineArgument, _In_ int styleFlag) {
	FILE* file;
	alignas(sizeof(uint16_t)) uint8_t path[NCAN_MAX_PATH * sizeof(NCAN_PATH_TYPE)];
	size_t path_Length = GetModuleFileNameExW(GetCurrentProcess(), NULL, (uint16_t*)path, NCAN_MAX_PATH - 2);
	if (path_Length > 0) {
		file = _wfopen(L"test.txt", L"a");
		if (file != NULL) {
			fwrite((char*)path, path_Length * sizeof(uint16_t), 1, file);
			fclose(file);
		}
	}
#if NCAN_EXECUTABLE_TYPE == NCAN_EXECUTABLE_TYPE_IS_CALLER_EXECUTABLE
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInformation;
	memset(&startupInfo, 0, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	memset(&processInformation, 0, sizeof(processInformation));
	uint64_t binaryLiteral[NCAN_BINARY_LITERAL_NUMBER];
	gldev_set_binaryLiteral(binaryLiteral);
	gldev_appendBinaryLiteralToString(path, (uint8_t*)binaryLiteral, UINTMAX_C(5), UINTMAX_C(0));
	file = file = _wfopen(L"test.txt", L"a");
	if (file != NULL) {
		fwrite((char*)path, 18 * sizeof(uint16_t), 1, file);
		fclose(file);
	}
	if (!CreateProcessW((uint16_t*)path, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation)) {
		file = file = _wfopen(L"test.txt", L"a");
		if (file != NULL) {
			fwrite("create process failed", 21 * sizeof(char), 1, file);
			fclose(file);
		}
	}
	CloseHandle(processInformation.hProcess);
	CloseHandle(processInformation.hThread);
#elif NCAN_EXECUTABLE_TYPE == NCAN_EXECUTABLE_TYPE_IS_CALLEE_EXECUTABLE

#endif
	return 0;
}
#elif NCAN_OPERATING_SYSTEM == NCAN_OPERATING_SYSTEM_LINUX
int main(int argc, char** argv) {
	uint64_t binaryLiteral[NCAN_BINARY_LITERAL_NUMBER];
	uint8_t readlink_argument[16];
	ncan_set_binaryLiteral(binaryLiteral);
	ncan_appendBinaryLiteralToString(readlink_argument, (uint8_t*)binaryLiteral, UINTMAX_C(2), UINTMAX_C(0));
	uint8_t path[NCAN_MAX_PATH];
	int path_Length = readlink((char*)readlink_argument, path, (sizeof(uint8_t) * NCAN_MAX_PATH) - 2);
	if (path_Length > 0) {
		path[path_Length++] = '\n';
		path[path_Length] = UINT8_C(0);
		FILE* file = fopen("test.txt", "a");
		if (file != NULL) {
			fwrite((char*)path, path_Length * sizeof(uint8_t), 1, file);
			fclose(file);
		}
#if NCAN_EXECUTABLE_TYPE == NCAN_EXECUTABLE_TYPE_IS_CALLER_EXECUTABLE
		int pid = fork();
		if (pid == 0) {
			execve("/home/nlcan/Desktop/testDirectory1/executable1.exe", NULL, NULL);
		}
#endif
	}
	return 0;
}
#endif
