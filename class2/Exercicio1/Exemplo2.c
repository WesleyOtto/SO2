#include <stdio.h>
#include <unistd.h>

int main()
{
	while(1)
	{ 
		fprintf(stderr,".");
		usleep(10000);
	}
}
