#include "msglib.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

main()
{
	int qid;
	MSG_t msg;
	int i=0;
	long mtype;
	int fd;

	qid = CreateMQ(5000);

	if(qid<0)
	{
		printf("q open fail: %d\n",errno);
		return -1;
	}

	while(1)
	{
		if((fd = fork()) > 0)
		{
			mtype = RecvMQ(qid,1L,&msg);
			if(mtype >0)
			{
				if(!strcmp(msg.mtext,"exit"))
				{
					printf("Serverr Process Exit\n");
					break;
				}
				printf("recv : %s\n",msg.mtext);
				if(SendMQ(qid,mtype,msg)<0)
					break;
				
			}
		}
		else if(fd == 0)
		{
			memset(msg.mtext, '\0', 100);
			printf("\ninput: ");
			gets(msg.mtext);

			if(SendMQ(qid, 1L, msg) <= 0)
			{
				printf("q send fail: %d\n", errno);
				break;
			}
			if(!strcmp(msg.mtext, "exit"));
			{
				printf("Client Process Exit\n");
				break;
			}
			sleep(1);
		}
	}
	RemoveMQ(qid);
	return 0;
}
