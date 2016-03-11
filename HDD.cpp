#include <iostream>
#include "HDD.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HDD.h"
#include "CommandStruct.h"
#include <sys/shm.h>
#include <pthread.h>
#include "Common.h"

using namespace std;
Common common;
char* HDD::addres = CreateSharedMemory();
char* HDD::CreateSharedMemory()
{
	//shared memory id
	int shmid;
	
	//returned addres after attached
	char* ShMAddr;
	
	//shred memory key
	key_t key = common.sharedMemKey;
	
	//create shared memory
	shmid = shmget(key,common.memSize,IPC_CREAT|SHM_R|SHM_W);
	
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

//save process id in shared memory, for accses another process
void HDD::savePId()
{	
	pid_t pid = getpid();	
	char* addr1 = addres;
	addr1 += 3695;// 4 byte,from 3696 to 3700 for saveing process id
	memcpy(addr1, &pid,4);
}


//write to file, form shared memory
int HDD::Write(int from, long to, int size)
{
	
		//open file for write in it
		int fd = open("hdd.txt", O_WRONLY);
		if(fd == -1)
		{
			cout<<"file for write can not open"<<endl;
		}
		
		
		//get data from shared memory, for write in file 
		string str;	
		//get attached addres
		char* addr1 = addres;
		//go to addres ,from where started to read
		addr1 += from;
		for(int i = 0; i < size; i++)
		{
			str.push_back(addr1[i]);
		}		
		const char * result = str.c_str();	
		
		//move file pointer
		if(lseek(fd,to, SEEK_SET) == -1)
		{
			cout<<"lseek falid"<<endl;
		}
		
		//write in to file
		if(write(fd, result, size) == -1)
		{
			cout<<"can not write to file"<<endl;
		}		
		close(fd);
		
		return size;
}

//read from file,to shared memory
int HDD::Read(long from, int to, int size)
{		
		//open file for reading
		int fd = open("hdd.txt", O_RDONLY);
		if(fd == -1)
		{
			cout<<"file for write can not open "<<endl;
		}
		
		char* c = new char(size);
		
		//move file pointer
		if(lseek(fd,from, SEEK_SET) == -1)
		{
			cout<<errno<<endl;
			cout<<"lseek falid"<<endl;
		}
		
		//read from file
		if(read(fd, c, size) == -1)
		{
			cout<<"can not read from file"<<endl;
		}
				
		close(fd);
		
		//write to shared memory		
		char* addr1 = addres;
		addr1 += to;
		memcpy(addr1,c,size);	
	
		
		return size;
}


//copy from file, to file
int HDD::Copy(long from, long to, int size)
{
		//open file
		int fd = open("hdd.txt", O_RDONLY);
		if(fd == -1)
		{
			cout<<"file for write can not open "<<endl;
		}
		
		char* c = new char(size);
		
		//move file pointer
		if(lseek(fd,from, SEEK_SET) == -1)
		{
			cout<<errno<<endl;
			cout<<"lseek falid"<<endl;
		}
		
		//read from file
		if(read(fd, c, size) == -1)
		{
			cout<<"can not read from file"<<endl;
		}
				
		close(fd);
		
		//open file for writeing
		fd = open("hdd.txt", O_WRONLY);
		if(fd == -1)
		{
			cout<<"file for write can not open"<<endl;
		}
	
		//move file ponter
		if(lseek(fd,to, SEEK_SET) == -1)
		{
			cout<<"lseek falid"<<endl;
		}
		
		//write in to file
		if(write(fd, c, size) == -1)
		{
			cout<<"can not write to file"<<endl;
		}	
		
		close(fd);

	return size;
}
















