#include <cassert>
#include "ThreadPool.h"

using namespace std;

static constexpr int kDefaultWorkThreads = 4;

namespace audio_alarm {

	static int cpu_count();

	ThreadPool::ThreadPool() :bRunning(false) {

	}

	ThreadPool::~ThreadPool() {

	}

	void ThreadPool::Start(int numThreads) {
		assert(vecWorkThd.empty());
		if (numThreads <= 0) {
			numThreads = std::thread::hardware_concurrency();
		}

		if ((numThreads = cpu_count()) <= 0) {
			numThreads = kDefaultWorkThreads;
		}

		bRunning = true;
		vecWorkThd.reserve(numThreads);
		for (int idx = 0; idx < numThreads; idx++) {
			//vecWorkThd.emplace_back(std::move(std::unique_ptr<std::thread>()));
			vecWorkThd.emplace_back(new std::thread(&ThreadPool::work, this));
		}
	}

	void ThreadPool::Stop() {
		{
			std::lock_guard<std::mutex> lk();
			bRunning = false;
			cvTask.notify_all();
		}

		for (auto& workThd : vecWorkThd) {
			if (workThd->joinable()) {
				workThd->join();
			}
		}

		//clear the task queue
		while (!taskQueue.empty()) {
			taskQueue.pop();
		}
	}

	bool ThreadPool::AddTask(std::function<void()>&& paraTask) {
		if (bRunning) {
			std::lock_guard<std::mutex> lk(mutexTask);
			taskQueue.push(paraTask);
			cvTask.notify_one();
			return true;
		}

		// if stopping is necessary, the adding operation will fail
		return false;
	}

	void ThreadPool::work() {
		while (bRunning) {
			Task task;
			{
				std::unique_lock<std::mutex> lk(mutexTask);
				while (taskQueue.empty() && bRunning)
				{
					cvTask.wait(lk, [this]() {
						return !taskQueue.empty() || !bRunning;
						});
				}
				if (!bRunning) {
					break;
				}

				task = taskQueue.empty() ? []() {} : std::move(taskQueue.front());
				taskQueue.pop();
			}

			// if acquiring one task successfully, the thread will finish it
			if (task) {
				task();
			}
		}
	}

	static int cpu_count()
	{
		int n;

#if defined (_SC_NPROCESSORS_ONLN)
		n = (int)sysconf(_SC_NPROCESSORS_ONLN);
#elif defined (_SC_NPROC_ONLN)
		n = (int)sysconf(_SC_NPROC_ONLN);
#elif defined (HPUX)
#include <sys/mpctl.h>
		n = mpctl(MPC_GETNUMSPUS, 0, 0);
#else
		n = -1;
		errno = ENOSYS;
#endif

		return n;
	}

}
