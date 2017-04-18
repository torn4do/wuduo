#include "Thread.h"
#include <iostream>

Thread::Thread(const ThreadFunc func)
	:pthreadId_(0),
	tid_(new pid_t(0)),
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
	t->func_();
	return NULL;
}

void Thread::start()
{
	started_=true;
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
