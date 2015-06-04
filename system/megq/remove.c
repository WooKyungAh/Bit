#include "msglib.h"

int RemoveMQ(int qid)
{
	return(msgctl(qid,IPC_RMID,0));
}
