#ifndef _CPU
#define _CPU
#include <vector>

class CPU
{
	private:
		//core count
		static int coresNum;
		//write process IDs in shared memory		
		static	bool SetCoreIDs(std::vector<int>);
		//allocates a shared memory ,  returns the address of the attached shared memory , on error (void *) -1 is returned
		static int* fillCoreIDsInSharedMem();
		static int* SharedMemForHddId();
	public:	
		//create HDD process
		static void RunHDD();
		//create a new processes
		static void Run(int numberOfCores);	
		//get from shared memory proecess IDs	
		static std::vector<int> GetCoreIDs();
		//get interrupt,and send all processes
		static bool Interrupt(int interruptNumber);
};

#endif
