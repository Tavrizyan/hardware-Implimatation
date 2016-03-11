#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HDD.h"
#include "CommandStruct.h"
#include <sys/shm.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
using namespace std;

//for ending a wile loop
bool br = true;

//Sending process ID
pid_t procID;

//finde and execute a command, in thread 
void* callCommand(void* com)
{	
	Command* cmd =(Command*)com;
	HDD h;
	Command command = *cmd;
	//check if command is write
	if(command.str == 'w')
	{		
		//call write function
		//if write 0 byte, send a signal to core
		if(h.Write(command.it, command.lg, command.size) == 0)
		{
			if(kill(procID, SIGILL ) == -1)
			{
				cout<<errno<<endl;
				cout<<"cant send a signal HDD"<<endl;
			}
		}	
		br = false;
		void* vague_pointer;
		return vague_pointer;
	}
	
	//check if command is read
	if(command.str == 'r')
	{	
		//call read function
		//if write 0 byte, send a signal to core
		if( h.Read( command.lg, command.it, command.size) == 0)
		{
			if(kill(procID, SIGILL ) == -1)
			{
				cout<<errno<<endl;
				cout<<"cant send a signal HDD"<<endl;
			}
		}
		
		br = false;
		void* vague_pointer;
		return vague_pointer;
	}
	
	////check if command is copy
	if(command.str == 'c')
	{	
		//call copy function
		//if write 0 byte, send a signal to core
		if(h.Copy( command.lg, command.lgForCpy, command.size) == 0)
		{
			if(kill(procID, SIGILL ) == -1)
			{
				cout<<errno<<endl;
				cout<<"cant send a signal from HDD"<<endl;
			}
		}	
		br = false;
		void* vague_pointer;
		return vague_pointer;
	}	

}

HDD h;
//handle a signal
void interrupt_handler(int num,siginfo_t *siginfo,void *context)
 {
	 if(num == SIGUSR2)
	 {		
		br = true;		
		
		procID = siginfo->si_pid;
		
		//get comand struct from shared memory
		Command command;				
		char* addr1 = h.CreateSharedMemory();			 
		addr1 += 3700; //last 300 byet for send struct				
		memcpy(&command, addr1, sizeof(command));
		
		pthread_t thread;
		 
		//create thread,anx execute command in thread
		int result = pthread_create( &thread, NULL, callCommand, (void*)&command);
		
	     if(result)
	     {
	         cout<<"Error - pthread_create() return code:   "<< result<<endl;
	         exit(EXIT_FAILURE);
	     }
	 }
 }

int main()
{	
	//save process id in shared memory		
	h.savePId();
	
	
	struct sigaction sa;
	//send a interrupt handler function
	sa.sa_sigaction = &interrupt_handler;	
	sa.sa_flags = SA_SIGINFO;
	//handle a signal
	
	if(sigaction(SIGUSR2,&sa,NULL) < 0)
	{
		cout<<"can't catch signal"<<endl;
	}	
	
	while(br)
	{
		
	}
	
	return 0;
}
