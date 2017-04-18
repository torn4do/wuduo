#include "../../wuduo/base/Thread.h"
#include <iostream>

using namespace std;
using namespace wuduo;

void add()
{
	cout<<"enter add function"<<endl;
}

int main()
{
	Thread thread1(add);
	thread1.start();
	thread1.join();
}

