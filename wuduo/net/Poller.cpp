#include "Poller.h"
#include <poll.h>
#include <iostream>

using namespace wuduo;

Poller::Poller(EventLoop* loop)
	:loop_(loop)
{
}

Poller::~Poller()
{
}

void Poller::poll(ChannelVec& activeChannels,int timeout)
{
	int eventNum;
	eventNum=poll(&(*pollfds_.begin()),pollfds_.size(),timeout);
	if(eventNum>0)
	{
		fillActiveChannels(activeChannels,eventNum);
	}
	else if(eventNum==0)
	{
		std::cout<<"no event happended!"<<std::endl;
	}
	else
	{
		std::cerr<<“poll error”<<std::endl;
	}
}

void Poller::updateChannel(Channel* channel)
{
	if(channel->index()<0)
	{
		//若为新的channel
		//创建新pollfd,并保存在pollfds_中
		struct pollfd pfd;
		pfd.fd=channel->fd();
		pfd.events=channel->events();
		pfd.revents=0;
		pollfds_.push_pack(pfd);
		//更新channel
		int index =pollfds_.size()-1;
		channel->setIndex(index);
		//更新channels_
		channels_[pdf.fd]=channel;
	}
	else
	{
		//若为原有的channel
		//更新pollfds_中的pollfd
		struct pollfd& pfd=pollfds_[channel->index()];
		pfd.events=channel->events();
		pfd.reevets=0;
		//为什么？
		if(channel->isNoneEvent())
		{
			pfd.fd=-1；
		}
	}


}

void Poller::fillActiveChannels(ChannelVec& Channels,int eventNum)
{
	for(auto iter=pollfds_.begin();iter!=pollfds_.end()&&eventNum>0;++iter )
	{
		if(iter->revent>0)
		{
			eventNum--;



		}

	}


}
