#ifndef _IDE
#define _IDE
#include "CommandStruct.h"
class IDE
{
	private:
		char* CreateSharedMemory();
		int* SharedMemForHddId();
	public:
	 void   In(Command command);
     void   Out(Command command);
}; 

#endif
