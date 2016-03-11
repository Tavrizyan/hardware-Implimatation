#ifndef _HDD
#define _HDD

class HDD
{
	public:
		static	void savePId();
		static	char* CreateSharedMemory();
		static char* addres;
		int Write(int from, long to, int size);
		int Read(long from, int to, int size);
		int Copy(long from, long to, int size);
};


#endif
