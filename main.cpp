#include <iostream>
#include "CPU.h"
#include "Memory.h"
#include <signal.h>
#include <unistd.h>
using namespace std;

int main()
{
	Memory m;
	m.init();	
	CPU c;	
//	c.RunHDD();
	c.Run(3);	
	
	//wait for creatin all processes	
	//	usleep(10000);
	
	//send interrupt
	//c.Interrupt(SIGUSR1);
	
	return 0;
}
