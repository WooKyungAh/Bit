
#include "msglib.h"
int CreateMQ(key_t key)
{
	return(msgget(key,IPC_CREAT|0777));
}
int OpenMQ(key_t  key)
{
	return(msgget(key,0));
}
