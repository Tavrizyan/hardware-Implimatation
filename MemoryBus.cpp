#include "MemoryBus.h"
#include "Memory.h"
#include <sys/file.h>
#include <iostream>
#include <errno.h>
using namespace std;
int MemoryBus::fd = 0;
void MemoryBus::Read(int addrFrom, void* addrTo, int size)
{
	
	Memory::Read(addrFrom,  addrTo, size);
}

void MemoryBus::Write(void* addrFrom, int addrTo, int size)
{
	Memory::Write(addrFrom, addrTo, size);
}

//lock Bus
void MemoryBus::Lock()
{
		//create lock file
		fd = open("lock.txt",  O_CREAT | O_RDWR, 0666); // open or create lockfile
		if(fd < 0)
		{
			cout<<"can not open file for lock "<<endl;
		}
		//check open success...
		int rc = flock(fd,  LOCK_EX | LOCK_NB); // Place a shared lock
		
		if (rc == -1)
		{
			cout<<errno<<endl;
			cout<<" fail creating lock file"<<endl;
		}
	
}

//unlock Bus
void MemoryBus::Unlock()
{
	 flock(fd, LOCK_UN);
}
