#include "program.h"
#include "thread"
#include <iostream>

void initialiseLoadingThread(Program* program) {
	program->runLoadingThread();
}

void initialiseInputThread(Program* program) {
	program->runInputThread();
}

int main(int argc, char** argv) {
	Program program;
	std::thread loadingThread(initialiseLoadingThread, &program);
	loadingThread.join();
	std::thread inputThread(initialiseInputThread, &program);
	program.runRenderingThread();
	inputThread.join();
	return 0;
}