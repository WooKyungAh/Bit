#include "msglib.h"

long RecvMQ(int qid,long mtype, MSG_t *msg)
{
	int st;
	st = msgrcv(qid,msg,sizeof(MSG_t)-sizeof(long),mtype,IPC_NOWAIT);
	if(st<0)
		return -1L;
	return msg->fm_mtype;
}
