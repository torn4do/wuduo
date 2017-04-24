#ifndef WUDUO_NET_EVENTLOOP_H
#define WUDUO_NET_EVENTLOOP_H

#include "../base/Noncopyable.h"
#include <functional>
namespace wuduo
{
class EventLoop;

class Channel:public Noncopyable
{
	public:
	typedef std::function<void()> CallBackFunc;

	explicit Channel(EventLoop* loop,int fd);
	
	void handleEvent();//根据revents_值调用以下三个回调函数
	
	void setReadCallBack(const CallBackFunc& cb){readCallBack_=cb;};
	void setWriteCallBack(const CallBackFunc& cb){writeCallBack_=cb;};
	void setErroeCallBack(const CallBackFunc& cb){errorCallBack_=cb;};
	
	void enableReadEvent(){events_|=bitsReadEvent;update();};
	void enableWriteEvent(){events_|=bitsWriteEvent;update();};
	void disableReadEvent(){events_&=~bitsReadEvent;update();};
	void disableWriteEvent(){events_&=~bitsWriteEvent;update();};
	

	int fd(){return fd_;};
	int events(){return events_;};
	int setRevents(int revents){revents_=revents;};
	
	EventLoop* loop(){return loop_;};
	int index(){return index_;};
	void setIndex(int index){index_=index;};
	bool isNoneEvent(){return events_==bitsNoneEvent;};

	private:
		void update();

		static const int bitsNoneEvent;
		static const int bitsReadEvent;
		static const int bitsWriteEvent;

		EventLoop* loop_;
		int index_;//在pollfds_中的下标
		int   fd_;         /* file descriptor */
		short events_;     /* requested events */
		short revents_;    /* returned events */


		CallBackFunc readCallBack_;
		CallBackFunc writeCallBack_;
		CallBackFunc errorCallBack_;
};

}

#endif
