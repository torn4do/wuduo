/*
 * pthread_create:创建线程
 * pthread_join：等待线程执行完
 * pthread_detach:分离线程
 * pthread_exit:终止线程
 * pthread_self:获取库线程id
 * syscall(SYS_gettid)：获取内核线程id
*/

#include "Thread.h"
#include <iostream>

using namespace wuduo;

Thread::Thread(const ThreadFunc func)
	:pthreadId_(0),
	//tid_(new pid_t(0)),
	tid_(0),
	func_(func),
	started_(false),
	joined_(false)
	{}	

Thread::~Thread()
{
	if(started_&&!joined_)
	{
		pthread_detach(pthreadId_);
	}
}

void* Thread::threadfunc(void* self)
{
	Thread* t=static_cast<Thread*>(self);
	t->tid_= wuduo::CurrentThread::tid();//获取内核线程id
	t->func_();//执行任务函数
	return NULL;
}

void Thread::start()
{
	started_=true;
	tid_=CurrentThread::tid();
	//if(pthread_create(&pthreadId_,NULL,*func_.target<void*(void*)>(),NULL))
	if(pthread_create(&pthreadId_,NULL,&threadfunc,this))
	{
		started_=false;
		std::cout<<"Failed in pthread_create"<<std::endl;
	}
}

int Thread::join()
{
	joined_=true;
	return pthread_join(pthreadId_,NULL);
}
