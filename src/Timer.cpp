//#include <list>
#include <unistd.h>

#include <glog/logging.h>

#include "Timer.h"

struct TimerEvent {
	TimerEvent() {
		bRepeat = false;
		nDelay = 0;
		nElapse = 0;
		funcProc = nullptr;
	}

	bool bRepeat;
	unsigned int nDelay;
	unsigned int nElapse;

	std::function<void()>  funcProc;
};

Timer::Timer() :bRun(false) {

}

Timer::~Timer() {
	StopTimer();
}

bool Timer::StartTimer(int nIndex, std::function<void()> func, unsigned int nMilliSeconds, bool repeat) {
	LOG(INFO) << "add timer task,index:" << nIndex;
	if (!func) {
		LOG(ERROR) << "the function should not be null";
		return false;
	}

	if (0 == nMilliSeconds) {
		LOG(WARNING) << "current task elapse is zero,index:" << nIndex;
		func();
		return true;
	}

	std::lock_guard<std::mutex> lk(mutexMap);
	if (!bRun) {
		bRun = true;
		thdLoop = std::thread([this] {
			funcThread();
			});
	}

	TimerEvent event;
	event.bRepeat = repeat;
	event.nDelay = nMilliSeconds;
	event.funcProc = func;

	mapEvent[nIndex] = event;

	return true;
}

void Timer::StopTimer() {
	bRun = false;
	LOG(INFO) << "stop all task";
	if (thdLoop.joinable()) {
		thdLoop.join();
	}
	
	std::lock_guard<std::mutex> lk(mutexMap);
	mapEvent.clear();
}

void Timer::KillTimer(int nIndex) {
	LOG(INFO) << "kill a task,index:" << nIndex;
	std::lock_guard<std::mutex> lk(mutexMap);
	mapEvent.erase(nIndex);
}

void Timer::funcThread() {
	LOG(INFO) << "start run the task loop";
	while (bRun) {
		usleep(500 * 1000);

		std::map<int, TimerEvent> mapLoop;
		{
			std::lock_guard<std::mutex> lk(mutexMap);
			//reduce the lock range
			mapLoop = mapEvent;
		}

		std::map<int, TimerEvent>::iterator iter = mapLoop.begin();
		while (iter != mapLoop.end()) {
			iter->second.nElapse += 500;
			if (iter->second.nElapse >= iter->second.nDelay) {
				iter->second.funcProc();
				std::lock_guard<std::mutex> lk(mutexMap);
				//mapEvent[iter->first]
				std::map<int, TimerEvent>::iterator it = mapEvent.find(iter->first);
				if (it != mapEvent.end()) {
					if (iter->second.bRepeat) {
						it->second.nElapse = 0;
					}
					else {
						mapEvent.erase(iter->first);
					}
				}
			}
			else {
				std::lock_guard<std::mutex> lk(mutexMap);
				std::map<int, TimerEvent>::iterator it = mapEvent.find(iter->first);
				if (it != mapEvent.end()) {
					it->second.nElapse += 500;
				}
			}

			iter++;
		}

	}

}
