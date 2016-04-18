#ifndef _MEMORY
#define _MEMORY

class Memory
{
	private:		
				static char* CreateSharedMemory();
				static char* addres;
	
	public:	
		//read from shared memory
		static void Read(int addrFrom, void* addrTo, int size);
		//write to shared memory
		static void Write(void* addrFrom, int addrTo, int size);
		//init shared memory
		static int init();
};



#endif
