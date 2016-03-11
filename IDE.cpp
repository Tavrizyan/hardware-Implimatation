#include <iostream>
#include "IDE.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
using namespace std;

char* IDE::CreateSharedMemory()
{
	//shared memory id
	int shmid;
	
	//returned addres after attached
	char* ShMAddr;
	
	//shred memory key
	key_t key = 4169696;
	
	//create shared memory
	shmid = shmget(key,4000,IPC_CREAT|SHM_R|SHM_W);
	
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
		cout<<"can not attached "<<endl;
	}
	
		
	return ShMAddr;

}
void IDE::In(Command command)
{
		
}


void IDE::Out(Command command)
{	
		char* addr1 = CreateSharedMemory();
		//find process id, for sending a signal
		char* addrhold = addr1 +  3695; 
		addr1 += 3700; //last 300 byet for send struct
		
		//save sruct in to shared memory		
		memcpy(addr1,&command,sizeof(command));
		
		//get process id,from shared memory		
		pid_t pid;
		memcpy(&pid, addrhold, 4);			
		
		//send a signal		
		if(kill(pid,SIGUSR2) == -1)
		{
			cout<<errno<<endl;
			cout<<"cant send a signal from IDE OUT"<<endl;
		}		
	
}

















