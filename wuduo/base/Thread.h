#ifndef WUDUO_BASE_THREAD_H
#define WUDUO_BASE_THREAD_H

#include <pthread.h>
#include <functional>
#include <memory>
#include <unistd.h> 
#include <sys/syscall.h>
#include "Noncopyable.h"

namespace wuduo
{

namespace CurrentThread
{
	pid_t tid()
	{
		return static_cast<pid_t>(::syscall(SYS_gettid));
	}
}

class Thread
{
	typedef std::function<void()> ThreadFunc;
	public:
		explicit Thread(const ThreadFunc);
		~Thread();

		void start();
		int join();
		pid_t tid() const {return tid_;};
		bool started() const {return started_;};

	private:
		static void* threadfunc(void*);//static原因：若为普通成员函数，则参数为（Thread*）,不符合pthread_create的的参数(void*)
		pthread_t pthreadId_;//pthread库的线程id
		//shared_ptr<pid_t> tid_;//内核线程id
		pid_t tid_;//内核线程id
		ThreadFunc func_;
		bool started_;
		bool joined_;
};
}
#endif
