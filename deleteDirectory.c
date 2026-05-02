#include <stdio.h>
#include <stdint.h>

//C:\Users\nlcan\Desktop\testDirectory

#define NCAN_OPERATING_SYSTEM_WINDOWS 0
#define NCAN_OPERATING_SYSTEM_LINUX 1
#define NCAN_OPERATING_SYSTEM NCAN_OPERATING_SYSTEM_WINDOWS

#if NCAN_OPERATING_SYSTEM == NCAN_OPERATING_SYSTEM_WINDOWS
#include <Windows.h>
#include <shellapi.h>
int WINAPI wWinMain(_In_ HINSTANCE instance_Handle, _In_opt_ HINSTANCE previousInstanceHandle, _In_ PWSTR commandLineArgument, _In_ int styleFlag) {
	char returnValue[1];
	returnValue[0] = '1';
	uint16_t path[45];
	path[0] = (uint16_t)UINT8_C(67); //C
	path[1] = (uint16_t)UINT8_C(58); //:
	path[2] = (uint16_t)UINT8_C(92); //windows slash
	path[3] = (uint16_t)UINT8_C(85); //U
	path[4] = (uint16_t)UINT8_C(115); //s
	path[5] = (uint16_t)UINT8_C(101); //e
	path[6] = (uint16_t)UINT8_C(114); //r
	path[7] = (uint16_t)UINT8_C(115); //s
	path[8] = (uint16_t)UINT8_C(92); //windows slash
	path[9] = (uint16_t)UINT8_C(103); //g
	path[10] = (uint16_t)UINT8_C(111); //o
	path[11] = (uint16_t)UINT8_C(108); //l
	path[12] = (uint16_t)UINT8_C(105); //i
	path[13] = (uint16_t)UINT8_C(103); //g
	path[14] = (uint16_t)UINT8_C(104); //h
	path[15] = (uint16_t)UINT8_C(116); //t
	path[16] = (uint16_t)UINT8_C(108); //l
	path[17] = (uint16_t)UINT8_C(121); //y
	path[18] = (uint16_t)UINT8_C(100); //d
	path[19] = (uint16_t)UINT8_C(101); //e
	path[20] = (uint16_t)UINT8_C(118); //v
	path[21] = (uint16_t)UINT8_C(92); //windows slash
	path[22] = (uint16_t)UINT8_C(68); //D
	path[23] = (uint16_t)UINT8_C(101); //e
	path[24] = (uint16_t)UINT8_C(115); //s
	path[25] = (uint16_t)UINT8_C(107); //k
	path[26] = (uint16_t)UINT8_C(116); //t
	path[27] = (uint16_t)UINT8_C(111); //o
	path[28] = (uint16_t)UINT8_C(112); //p
	path[29] = (uint16_t)UINT8_C(92); //windows slash
	path[30] = (uint16_t)UINT8_C(116); //t
	path[31] = (uint16_t)UINT8_C(101); //e
	path[32] = (uint16_t)UINT8_C(115); //s
	path[33] = (uint16_t)UINT8_C(116); //t
	path[34] = (uint16_t)UINT8_C(68); //D
	path[35] = (uint16_t)UINT8_C(105); //i
	path[36] = (uint16_t)UINT8_C(114); //r
	path[37] = (uint16_t)UINT8_C(101); //e
	path[38] = (uint16_t)UINT8_C(99); //c
	path[39] = (uint16_t)UINT8_C(116); //t
	path[40] = (uint16_t)UINT8_C(111); //o
	path[41] = (uint16_t)UINT8_C(114); //r
	path[42] = (uint16_t)UINT8_C(121); //y
	path[43] = (uint16_t)UINT8_C(NULL); //NULL
	path[44] = (uint16_t)UINT8_C(NULL); //NULL

	SHFILEOPSTRUCT fileOperation;
	fileOperation.hwnd = NULL;
	fileOperation.wFunc = FO_DELETE;
	fileOperation.pFrom = (PCZZWSTR)path;
	fileOperation.pTo = NULL;
	fileOperation.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;
	fileOperation.fAnyOperationsAborted = FALSE;
	fileOperation.lpszProgressTitle = NULL;
	fileOperation.hNameMappings = NULL;

	if (SHFileOperation(&fileOperation) != 0)
		returnValue[0] = '0';

	FILE* file = fopen("test.txt", "w");
	fwrite((void*)returnValue, sizeof(char), 1, file);
	fclose(file);
	return 0;
}
#elif NCAN_OPERATING_SYSTEM == NCAN_OPERATING_SYSTEM_LINUX
#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <unistd.h>
int deleteDirectoryCallbackFunction_linux(char* path, struct stat* statObject, int flag, struct FTW* ftwBuffer) {
	return remove(path);
}

int main(int argc, char** argv) {
	char returnValue[1];
	returnValue[0] = '1';
	char path[44];
	path[0] = (char)UINT8_C(67); //C
	path[1] = (char)UINT8_C(58); //:
	path[2] = (char)UINT8_C(92); //windows slash
	path[3] = (char)UINT8_C(85); //U
	path[4] = (char)UINT8_C(115); //s
	path[5] = (char)UINT8_C(101); //e
	path[6] = (char)UINT8_C(114); //r
	path[7] = (char)UINT8_C(115); //s
	path[8] = (char)UINT8_C(92); //windows slash
	path[9] = (char)UINT8_C(103); //g
	path[10] = (char)UINT8_C(111); //o
	path[11] = (char)UINT8_C(108); //l
	path[12] = (char)UINT8_C(105); //i
	path[13] = (char)UINT8_C(103); //g
	path[14] = (char)UINT8_C(104); //h
	path[15] = (char)UINT8_C(116); //t
	path[16] = (char)UINT8_C(108); //l
	path[17] = (char)UINT8_C(121); //y
	path[18] = (char)UINT8_C(100); //d
	path[19] = (char)UINT8_C(101); //e
	path[20] = (char)UINT8_C(118); //v
	path[21] = (char)UINT8_C(92); //windows slash
	path[22] = (char)UINT8_C(68); //D
	path[23] = (char)UINT8_C(101); //e
	path[24] = (char)UINT8_C(115); //s
	path[25] = (char)UINT8_C(107); //k
	path[26] = (char)UINT8_C(116); //t
	path[27] = (char)UINT8_C(111); //o
	path[28] = (char)UINT8_C(112); //p
	path[29] = (char)UINT8_C(92); //windows slash
	path[30] = (char)UINT8_C(116); //t
	path[31] = (char)UINT8_C(101); //e
	path[32] = (char)UINT8_C(115); //s
	path[33] = (char)UINT8_C(116); //t
	path[34] = (char)UINT8_C(68); //D
	path[35] = (char)UINT8_C(105); //i
	path[36] = (char)UINT8_C(114); //r
	path[37] = (char)UINT8_C(101); //e
	path[38] = (char)UINT8_C(99); //c
	path[39] = (char)UINT8_C(116); //t
	path[40] = (char)UINT8_C(111); //o
	path[41] = (char)UINT8_C(114); //r
	path[42] = (char)UINT8_C(121); //y
	path[43] = (char)UINT8_C(NULL); //NULL

	switch (nftw(path, deleteDirectoryCallbackFunction_linux, 64, FTW_DEPTH | FTW_PHYS)) {
	case 0:
		FILE * file = fopen("test.txt", "w");
		fwrite((void*)returnValue, sizeof(char), 1, file);
		fclose(file);
		break;
	default:
		returnValue[0] = '0';
		FILE* file = fopen("test.txt", "w");
		fwrite((void*)returnValue, sizeof(char), 1, file);
		fclose(file);
		break;
	}
	return 0;
}
#endif
