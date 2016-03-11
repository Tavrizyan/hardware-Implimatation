#include <iostream>
#include "core.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//signal handler
//handel a sirnal from HDD
void interrupt_handler(int num)
 {
	 if(num == SIGILL)
	 {
		cout<<"signal  hendled "<<endl;
		exit(num);
	 }
 }
 
int main()
{
	//try to catch signal
	if(signal(SIGILL, interrupt_handler) == SIG_ERR)
	{
		cout<<"can't catch signal"<<endl;
	}	
	
	core c;
	c.Run();	
	//usleep(3000000);

	return 0;
}


 
