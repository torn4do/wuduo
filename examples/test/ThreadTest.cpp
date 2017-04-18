#include "../../wuduo/base/Thread.h"
#include <iostream>

using namespace std;

void* add(void*)
{
	cout<<"enter add function"<<endl;
}

int main()
{
	Thread thread1(add);
	thread1.start();
	thread1.join();
}

