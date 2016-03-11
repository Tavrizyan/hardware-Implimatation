#ifndef _COMMON
#define _COMMON

#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>


class Common
{
	public:
	static const int memSize = 4000;
	static const int stackBegan = 3000;
	static const int stackEnd = 3300;
	static const key_t sharedMemKey = 4169696;
	static const int codeSegmentSize = 3000;
};

#endif
