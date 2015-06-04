#include "msglib.h"

long SendMQ(int qid,long mtype, MSG_t msg)
{
	int st;
	msg.to_mtype = mtype;
	msg.fm_mtype = getpid();

	st = msgsnd(qid,&msg,(sizeof(MSG_t)-sizeof(long)),IPC_NOWAIT);

	if(st<0)
		return -1L;
	return msg.fm_mtype;
}
