#include "Channel.h"
#include "EventLoop.h"
#include <poll.h>
#include <iostream>

using namespace wuduo;

const int Channel::bitsNoneEvent=0;
const int Channel::bitsReadEvent=POLLIN | POLLPRI;
const int Channel::bitsWriteEvent=POLLOUT;

Channel::Channel(EventLoop* loop,int fd)
	:loop_(loop),
	index_(-1),
	fd_(fd),
	events_(0),
	revents_(0)
{
}

void Channel::handleEvent()
{
	//fd未打开
	if(revents_&POLLNVAL)
	{
		std::cout<<"fd not open!"<<std::endl;
	}
	//未打开或出错时调错误处理函数
	if(revents_&(POLLNVAL | POLLERR))
	{
		if(errorCallBack_)
			errorCallBack_();
	}
	//可读或高优先级可读或  POLLRDHUP? 时调用读处理函数
	if(revents_&(POLLIN | POLLPRI | POLLRDHUP))
	{
		if(readCallBack_)
			readCallBack_();
	}
	//可写时调用写处理函数
	if(revents_&POLLOUT)
	{
		if(writeCallBack_)
			writeCallBack_();
	}
}

void Channel::update()
{
	loop_->updateChannel(this);
}

