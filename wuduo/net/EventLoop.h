#include "../base/Thread.h"
#include "../base/Noncopyable.h"

namespace wuduo
{

class Poller;
class Channel;

class EventLoop: public Noncopyable
{
	public:
		EventLoop();
		~EventLoop();

		void loop();
		void stop(){stop_=false;};
		
		void updateChannel(Channel*);

		bool isInLoopThread(){return tid_==wuduo::CurrentThread::tid();}
		
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
		shared_ptr<Poller> poller_;
		ChannelVec activedChannels_;
};



}
