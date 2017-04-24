#ifndef WUDUO_NET_POLLER_H
#define WUDUO_NET_POLLER_H

#include <vector>
#include <map>

struct pollfd;
namespace wuduo
{
	
class Channel;
class EventLoop;

class Poller
{
	public:
		typedef std::vector<Channel*> ChannelVec;
		explicit Poller(EventLoop*);
		~Poller();
		
		void poll(ChannelVec& activeChannels,int timeout);
 		void updateChannel(Channel*);
	private:
		void fillActiveChannels(ChannelVec&,int);//填充activeChannels

		typedef std::vector<struct pollfd> PollFdVec;
		typedef std::map<int,Channel*> ChannelMap;//<fdp，pchannel>

		EventLoop* loop_;
		PollFdVec pollfds_;
		ChannelMap channels_;
};
}

#endif
