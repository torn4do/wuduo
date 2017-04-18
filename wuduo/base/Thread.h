#ifndef WUDUO_BASE_THREAD_H
#define WUDUO_BASE_THREAD_H

#include <pthread.h>
#include <functional>
#include <memory>
#include "Noncopyable.h"

class Thread
{
	typedef std::function<void()> ThreadFunc;
	//typedef void*(*ThreadFunc)(void *);
	public:
		explicit Thread(const ThreadFunc);
		~Thread();

		void start();
		int join();
		pid_t tid() const {return *tid_;};
		bool started() const {return started_;};

	private:
		static void* threadfunc(void*);

		pthread_t pthreadId_;
		std::shared_ptr<pid_t> tid_;//这个参数暂时没什么用
		ThreadFunc func_;
		bool started_;
		bool joined_;
};

#endif
