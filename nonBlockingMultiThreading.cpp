/*test program
intended to test if atomic flags can be used to perform other tasks while shared
data is in use, instead of blocking

each thread enters the flag protected part of the loop 20 times before quitting
if the flag indicates that the if portion is already in use, the thread is intended to
execute the code in the else portion (only up to 5 times to avoid cluttering the output)

debug note: this doesn't work with std::cout because all the threads are using it at once
and it's not thread safe so it all gets garbled.  at least it didn't crash

real world usage
one thread renders and draws to the screen, while the other checks for input and
provides frameData for the renderer to use.  neither thread should ever block*/

#include <fstream>
#include <atomic>
#include <thread>
#include <string>

struct ThreadData {
	int numTimesToWriteToDebugIfBlockFile;
	int numTimesToWriteToDebugElseBlockFile;
};

class SharedData {
public:
	SharedData() {
		threadData = new ThreadData[10];
		for (int a = 0; a < 10; ++a) {
			threadData[a] = { 20, 5 };
		}
		flag.clear();
	}

	~SharedData() {
		delete[] threadData;
	}

	void runThread(int threadID) {
		while (this->threadData[threadID].numTimesToWriteToDebugIfBlockFile > 0) {
			if (this->flag.test_and_set(std::memory_order_acquire)) {
				std::string fileName = "debugIfBlockOutputThread#";
				fileName += std::to_string(threadID);
				fileName += ".txt";
				std::ofstream writeFile(fileName.c_str(), std::ios::app);
				writeFile << threadID << ", running, output #" << this->threadData[threadID].numTimesToWriteToDebugIfBlockFile << std::endl;
				writeFile.close();
				writeFile.clear();
				this->threadData[threadID].numTimesToWriteToDebugIfBlockFile -= 1;
				this->flag.clear(std::memory_order_release);
			}
			else {
				if (this->threadData[threadID].numTimesToWriteToDebugElseBlockFile > 0) {
					std::string fileName = "debugElseBlockOutputThread#";
					fileName += std::to_string(threadID);
					fileName += ".txt";
					std::ofstream writeFile(fileName.c_str(), std::ios::app);
					writeFile << threadID << ", standing by, output #" << this->threadData[threadID].numTimesToWriteToDebugElseBlockFile << std::endl;
					writeFile.close();
					writeFile.clear();
					this->threadData[threadID].numTimesToWriteToDebugElseBlockFile -= 1;
				}
			}
		}
	}
private:
	ThreadData* threadData;
	std::atomic_flag flag;
};

void runThread(int threadID, SharedData* sharedData) {
	sharedData->runThread(threadID);
}

int main() {
	SharedData sharedData;
	std::thread thread[10];
	for (int a = 0; a < 10; ++a) {
		thread[a] = std::thread(runThread, a, &sharedData);
	}
	thread[0].join();
	thread[1].join();
	thread[2].join();
	thread[3].join();
	thread[4].join();
	thread[5].join();
	thread[6].join();
	thread[7].join();
	thread[8].join();
	thread[9].join();
	return 0;
}