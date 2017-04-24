#include "Poller.h"
#include <iostream>
#include <assert.h>
#include "EventLoop.h"
#include "Channel.h"

using namespace wuduo;

EventLoop::EventLoop()
	:looping_(false),
	stop_(false),
	tid_(CurrentThread::tid()),
	poller_(new Poller(this))
{
}

EventLoop::~EventLoop()
{
}

void abortNotInLoopThread()
{
	std::cout<<"abort! Not In Loop Thread!"<<std::endl;
}

void EventLoop::loop()
{
	assert(!looping_);
	assertInLoopThread();
	looping_=true;;

	while(!stop_)
	{
		ChannelVec activedChannels;
		poller_->poll(activedChannels,1);
		for(auto iter=activedChannels.begin();iter!=activedChannels.end();++iter)
		{
			(*iter)->handleEvent();
		}
	}
	std::cout<<"Loop stoped"<<std::endl;
	looping_=false;
}

void EventLoop::updateChannel(Channel* pChannel)
{
	poller_->updateChannel(pChannel);
}
