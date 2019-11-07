#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define PERMS 0666

char fname[256];

int main()
{
	int readfd,writefd,fd;
	ssize_t n;
	char buff[512];
	
	printf("trying to connect to server\n");
	writefd=open(FIFO1,O_WRONLY,0);
	readfd=open(FIFO2,O_RDONLY,0);
	printf("connected\n");
	printf("enter the filename to request the server:");
	scanf("%s",fname);
	write(writefd,fname,strlen(fname));
	printf("waitng for server to replay");
	while((n=read(readfd,buff,512))>0)
		write(1,buff,n);
	

close(readfd);

close(writefd);
return 0;

}


//output
bmsce@bmsce-Precision-T1700:~/Desktop$ cc IPCclient.c -o client
bmsce@bmsce-Precision-T1700:~/Desktop$ ./client
trying to connect to server
connected
enter the filename to request the server:sc
hiiiiiiiiiiiii,,,,BMSCE
waitng for server to replay
