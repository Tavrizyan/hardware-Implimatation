#include <sys/ipc.h>
#include <sys/shm.h>
#include "Memory.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "Common.h"
using namespace std;
char* Memory::addres = CreateSharedMemory();
char* Memory::CreateSharedMemory()
{
	Common common;
	
	//shared memory id
	int shmid;
	
	//returned addres after attached
	char* ShMAddr;
	
	//shred memory key
	key_t key = common.sharedMemKey;
	
	//create shared memory
	shmid = shmget(key, common.memSize, IPC_CREAT|SHM_R|SHM_W);
	
	//check if shared memory created
	if(shmid == -1)
	{
		cout<<"can not allocate a shared memory "<<endl;
	}
	//attached shared memory			
	ShMAddr = (char*)shmat(shmid,0,0);	
	
	//check if attached 
	if(ShMAddr == (char*)-1)
	{
		cout<<errno<<endl;
		cout<<"can not attached  "<<endl;
	}
	
		
	return ShMAddr;
}

int Memory::init()
{ 
	//read code from file to memory
	std::ifstream in("example.txt");
	std::string contents((std::istreambuf_iterator<char>(in)), 
    std::istreambuf_iterator<char>());  
  
	const char * newLine = contents.c_str();
  
	//get attached shared memory addres
	char* addr1 = addres;
	
	//copy data to attached addres (shared memory)
	memcpy(addr1, newLine, contents.size());
	
	return 0;  
  
}

void Memory::Read(int addrFrom, void* addrTo, int size)
{	
	//get attached addres
	char* addr1 = addres;
	//go to addres ,from where started to read
	addr1 += addrFrom;		
	char* to = (char*)addrTo;
	//copy reads byte to given addres 
	memcpy(to, addr1, size);	

}

void Memory::Write(void* addrFrom, int addrTo, int size)
{
		string result;
		char* addr = (char*)addrFrom;		
		char* addr1 = addres;
		addr1 += addrTo;
		//copy bytes from given addres to shared memory
		memcpy(addr1, addr, size);
		
}




