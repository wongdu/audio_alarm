#ifndef __Timer_H__
#define __Timer_H__

#include <functional>
//#include <list>
#include <map>
#include <mutex>
#include <thread>

struct TimerEvent;

class Timer final{
public:
	Timer();
	~Timer();

public:
	bool StartTimer(int nIndex, std::function<void()> func, unsigned int nMilliSeconds, bool repeat=true);
	void StopTimer();
	void KillTimer(int nIndex);

private:
	void funcThread();

private:
	bool bRun;
	std::thread thdLoop;
	//std::list<TimerEvent> listTimers;
	//std::mutex mutexList;
	std::map<int, TimerEvent> mapEvent;
	std::mutex mutexMap;


};

#endif
