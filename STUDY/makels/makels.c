#include <stdio.h>
#include <dirent.h> //opendir
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

typedef struct __my_stat{
	struct stat buff;
	unsigned int f_type;
	char perm[11];
	int link_count;
	char *usrID;
	char *grpID;
	long size;
	char time[20];
}strsta;

strsta *myls;

void ls_time(strsta * lsls)
{
	struct tm* my_t;
	time_t t = (time_t)(lsls->buff).st_mtime;
	
	my_t = localtime(&t);
	sprintf(lsls->time, "%2d월 %2d %.2d:%.2d", 
			++my_t->tm_mon, my_t->tm_mday, my_t->tm_hour, my_t->tm_min);
	
}
void ls_size(strsta * lsls)
{
	lsls->size = (lsls->buff).st_size;
}
void ls_getID(strsta * lsls)
{
	struct passwd * my_uid;
	struct group * my_gid;
	my_uid = getpwuid((lsls->buff).st_uid);	
	lsls->usrID = my_uid->pw_name;
	my_gid = getgrgid((lsls->buff).st_gid);
	lsls->grpID = my_gid->gr_name;
}
void ls_link(strsta * lsls)
{
	lsls->link_count = (lsls->buff).st_nlink;
}
void ls_permission(strsta * lsls)
{
	
	if((lsls->buff).st_mode & S_IRUSR)
		lsls->perm[1] = 'r';
	else
		lsls->perm[1] = '-';
	if((lsls->buff).st_mode & S_IWUSR)
		lsls->perm[2] = 'w';
	else
		lsls->perm[2] = '-';
	if((lsls->buff).st_mode & S_IXUSR)
		lsls->perm[3] = 'x';
	else
		lsls->perm[3] = '-';
	if((lsls->buff).st_mode & S_IRGRP)
		lsls->perm[4] = 'r';
	else
		lsls->perm[4] = '-';
	if((lsls->buff).st_mode & S_IWGRP)
		lsls->perm[5] = 'w';
	else
		lsls->perm[5] = '-';
	if((lsls->buff).st_mode & S_IXGRP)
		lsls->perm[6] = 'x';
	else
		lsls->perm[6] = '-';
	if((lsls->buff).st_mode & S_IROTH)
		lsls->perm[7] = 'r';
	else
		lsls->perm[7] = '-';
	if((lsls->buff).st_mode & S_IWOTH)
		lsls->perm[8] = 'w';
	else
		lsls->perm[8] = '-';
	if((lsls->buff).st_mode & S_IXOTH)
		lsls->perm[9] = 'x';
	else
		lsls->perm[9] = '-';
	
}
void ls_mode(strsta * lsls)
{
	char p;

	if( S_ISDIR((lsls->buff).st_mode))
		p = 'd';
	else if( S_ISCHR((lsls->buff).st_mode))
		p = 'c';
	else if( S_ISBLK((lsls->buff).st_mode))
		p = 'b';
	else if( S_ISSOCK((lsls->buff).st_mode))
		p = 's';
	else if( S_ISLNK((lsls->buff).st_mode))
		p = 'l';
	else if( S_ISFIFO((lsls->buff).st_mode))
		p = 'p';
	else
		p = '-';

	lsls->perm[0] = p;
	
}
void my_ls(char *dname)
{
	DIR *dp;
	struct dirent *p;
	struct stat buf;
	int i = 0,j;
	time_t t;
	char * arr[20] = {0,};
	int k = 0;
	char * temp;
	
	chdir(dname);
	dp = opendir(".");
	while(p = readdir(dp))
	{
		arr[k] = p->d_name;
		printf("arr[%d] : %s\n", k, arr[k]);
		k++;
	}
	
	for(i=0;i<k;i++)
	{
		for(j=0;j<k;j++)
		{
			if(strcmp(arr[i], arr[j]) < 0)
			{
				temp = arr[i];
				arr[i] = NULL;
				arr[i] = arr[j];
				arr[j] = NULL;
				arr[j] = temp;
				temp = NULL;
			}
		}
		
	}

	for(i=0;i<6;i++)
		printf("arr : %s\n", arr[i]);

	rewinddir(dp);
//	while(p = readdir(dp))
//	{
	for(i=0;i<k;i++)
	{
		lstat(arr[i], &(myls->buff));
		ls_mode(myls);
		ls_permission(myls);
		ls_link(myls);
		ls_size(myls);
		ls_time(myls);
		ls_getID(myls);
		printf("%s %d %s %s %5ld %s %s\n", 
				myls->perm, myls->link_count, myls->usrID, myls->grpID, 
				myls->size, myls->time, arr[i]);
	}
//	}
	printf("\n");
	closedir(dp);
}
int main()
{
	int i;
	
	myls = (strsta*)malloc(sizeof(strsta));
	my_ls(".");
	return 0;
}
