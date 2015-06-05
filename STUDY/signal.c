#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signo)
{
	printf("sig_handler call \n");
}

int main()
{
	int i=0;
	signal(SIGINT, (void*)sig_handler);

	while(1)
	{
		printf(".\n");
		sleep(1);
	}
	return 0;
}
