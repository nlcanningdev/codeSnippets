#include <iostream>
#include <thread>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable>

#define GLDEV_MAIN_THREAD_ID 0
#define GLDEV_RENDERING_THREAD_ID 1

struct ThreadFlag {
	std::mutex mutex;
	std::condition_variable conditionVariable;
};

class ThreadTest {
public:
	void prepareThreads() {
		value = 0;
		mainThreadRenderSyncReady = true;
		renderingThreadRenderSyncReady = false;
	}
	void runMainThread() {
		for (int a = 4; a > 0; --a)
			this->mainThreadFunction();
	}

	void mainThreadFunction() {
		std::unique_lock<std::mutex> lock(this->renderSyncFlag.mutex);
		while (!this->mainThreadRenderSyncReady)
			this->renderSyncFlag.conditionVariable.wait(lock);
		++this->value;
		std::cout << "main thread value: " << this->value << std::endl;
		this->mainThreadRenderSyncReady = false;
		this->renderingThreadRenderSyncReady = true;
		renderSyncFlag.conditionVariable.notify_all();
	}

	void runRenderingThread() {
		for (int a = 4; a > 0; --a)
			this->renderingThreadFunction();
	}

	void renderingThreadFunction() {
		std::unique_lock<std::mutex> lock(this->renderSyncFlag.mutex);
		while (!this->renderingThreadRenderSyncReady)
			this->renderSyncFlag.conditionVariable.wait(lock);
		++this->value;
		std::cout << "rendering thread value: " << this->value << std::endl;
		this->renderingThreadRenderSyncReady = false;
		this->mainThreadRenderSyncReady = true;
		renderSyncFlag.conditionVariable.notify_all();
	}


private:
	bool mainThreadRenderSyncReady; //true == continue
	bool renderingThreadRenderSyncReady;
	ThreadFlag renderSyncFlag;
	int value;
};

void runProgramThread(ThreadTest* threadTest, int threadID) {
	switch (threadID) {
	case GLDEV_MAIN_THREAD_ID :
		threadTest->runMainThread();
		break;
	case GLDEV_RENDERING_THREAD_ID :
		threadTest->runRenderingThread();
		break;
	default:
		break;
	}
}

int main() {
	ThreadTest threadTest;
	threadTest.prepareThreads();
	std::thread programThread[2];
	programThread[0] = std::thread(runProgramThread, &threadTest, GLDEV_MAIN_THREAD_ID);
	programThread[1] = std::thread(runProgramThread, &threadTest, GLDEV_RENDERING_THREAD_ID);
	programThread[0].join();
	programThread[1].join();
	return 0;
}
