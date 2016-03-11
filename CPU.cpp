//London is the capital of Great Britain
#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include "CPU.h"
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

int CPU::coresNum = 0;
using namespace std;

bool CPU::SetCoreIDs(vector<int> arrayNumberOfCores)
{
	int * coreIDs;
	coreIDs = new int [coresNum];
	//copy data from vector to array
	for(int i = 0; i < arrayNumberOfCores.size(); i++)
	{
		coreIDs[i] = arrayNumberOfCores[i];
	}
	//get attached shared memory addres
		int* addr1 = fillCoreIDsInSharedMem();
		
		//copy data to attached addres (shared memory)
		memcpy(addr1, coreIDs, sizeof(coresNum*sizeof(int)));
	
	return true;
	
	
}

vector<int> CPU::GetCoreIDs()
{	
		vector<int> retCoreIDs;
		//get attached shared memory addres		
		int* addr1 = fillCoreIDsInSharedMem();			
				
		//allocates a memory		
		int* getval = (int*)(malloc(sizeof(coresNum*sizeof(int))));		
		
		//check if memory allocated
		if(getval == NULL)
		{
			cout<<"there is no free space"<<endl;
		}
		
		//copy data from attached memory to allocated memory,and return it
		memcpy(getval, addr1, sizeof(coresNum*sizeof(int)));
		
		//save IDs in vector
		for(int i = 0; i < coresNum; i++)
		{
			retCoreIDs.push_back(getval[i]);
		}		
		
		return retCoreIDs;	
	
}

void CPU::Run(int numberOfCores)
{
	coresNum = numberOfCores;
	
	vector<int> arrayNumberOfCores;
	
	for(int i = 0; i < numberOfCores; i++)
	{
		//create a new process
		pid_t pid = fork();
		
		//check if in child process
		if(pid == 0)
		{
			// replaces the current process  with a  new "c" process 
			if(execl("c","c",NULL) == -1)
			{
				cout<<"execl faild in CPU"<<endl;
			}
		}
		if(pid < 0)
			{
				cout<<"can not create a process"<<endl;
			}
			else
			{	
				//save child processes IDs 			
				if(pid != 0)				
				arrayNumberOfCores.push_back(pid);					
			}
	}
	
	SetCoreIDs(arrayNumberOfCores);
}

void CPU::RunHDD()
{
	//create a new process
		pid_t pid = fork();
		
		//check if in child process
		if(pid == 0)
		{
			// replaces the current process  with a  new "c" process 
			if(execl("h","h",NULL) == -1)
			{
				cout<<"execl faild in HDD"<<endl;
			}
		}
		if(pid < 0)
			{
				cout<<"can not create a process"<<endl;
			}
			
}


int* CPU::fillCoreIDsInSharedMem()
	{
		//shared memory id
		int shmid;
		
		//returned addres after attached
		int* addr1;
		
		//shred memory key
		key_t key = 4165249;
		
		//create shared memory
		shmid = shmget(key,sizeof(coresNum*sizeof(int)),IPC_CREAT|SHM_R|SHM_W);
		
		//check if shared memory created
		if(shmid == -1)
		{
			cout<<"can not allocate a shared memory "<<endl;
		}
		//attached shared memory			
		addr1 = (int*)shmat(shmid,0,0);
		
		//check if attached 
		if(addr1 == (int*)-1)
		{
			cout<<"can not attached"<<endl;
		}
		//return addres
		return addr1;
}
	 
	 
bool CPU::Interrupt(int interruptNumber)
{
	vector<int> ids = GetCoreIDs();
	for(int i = 0; i < ids.size(); i++)
	{
		//send interrupt to processes
		if(kill(ids[i], interruptNumber) == -1)
		{
			cout<<"cant send a signal"<<endl;
		}	
	}
	
	return true;
}	 


