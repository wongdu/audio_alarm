#ifndef __Thread_Pool_H__
#define __Thread_Pool_H__

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <memory>
#include <functional>
#include <condition_variable>

namespace audio_alarm{

	class ThreadPool {
	public:
		using Task = std::function<void()>;
		ThreadPool();
		virtual ~ThreadPool();

	public:
		ThreadPool& operator=(const ThreadPool&) = delete;
		ThreadPool(const ThreadPool&) = delete;
		ThreadPool(ThreadPool&&) = default;
		ThreadPool& operator=(ThreadPool&&) = default;

	public:
		void Start(int numThreads);
		void Stop();
		bool AddTask(std::function<void()>&& paraTask); // add a task into the pool
	private:
		void work();

	private:
		bool bRunning;
		std::queue<Task> taskQueue;// a queue stored all the tasks
		std::mutex mutexTask;
		std::condition_variable cvTask;
		std::vector<std::unique_ptr<std::thread>> vecWorkThd;
	};

}

#endif
