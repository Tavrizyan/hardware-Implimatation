#ifndef _MEMORYBUS
#define _MEMORYBUS

class MemoryBus
{
	private:
	static int fd;
	public:
	    static void Read(int addrFrom, void* addrTo, int size);
		static void Write(void* addrFrom, int addrTo, int size);
		static void Lock();
		static void Unlock();
};

#endif 
