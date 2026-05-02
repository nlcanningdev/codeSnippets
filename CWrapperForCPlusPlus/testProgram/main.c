#include <stdio.h>
#include "dependancy/wrapperFunctions.h"
#pragma comment(lib, "dependancy/wrapperProgramWindows.lib")

int main(int argc, char** argv) {
	int value = wrapperFunction0();
	printf("value: %d\n", value);
	struct WrapperClass wrapperClass;
	WrapperClass_constructor(&wrapperClass);
	printf("value: %d\n", WrapperClass_classWrappedFunction(&wrapperClass));
	WrapperClass_destructor(&wrapperClass);
	return 0;
}