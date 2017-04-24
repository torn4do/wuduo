#ifndef WUDUO_NET_EVENTLOOP_H
#define WUDUO_NET_EVENTLOOP_H

#include "../base/Thread.h"
#include "../base/Noncopyable.h"

#include <vector>

namespace wuduo
{

class Poller;
class Channel;

using namespace CurrentThread;

pid_t CurrentThread::tid();

class EventLoop: public Noncopyable
{
	public:
		EventLoop();
		~EventLoop();

		void loop();
		void stop(){stop_=false;};
		
		void updateChannel(Channel*);

		bool isInLoopThread(){return tid_==CurrentThread::tid();}
		
		void abortNotInLoopThread();
		void assertInLoopThread()
		{
			if(!isInLoopThread())
			{
				abortNotInLoopThread();
			}
		}
	private:
		typedef std::vector<Channel*> ChannelVec;

		bool looping_;
		bool stop_;
		pid_t tid_;
		std::shared_ptr<Poller> poller_;
		ChannelVec activedChannels_;
};



}

#endif
