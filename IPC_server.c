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
	if(mkfifo(FIFO1,PERMS)<0)
		printf("cant create FIFO files\n");
	if(mkfifo(FIFO2,PERMS)<0)
		printf("cant create FIFO files\n");
	printf("waiting for connection request\n");
	readfd=open(FIFO1,O_RDONLY,0);
	writefd=open(FIFO2,O_WRONLY,0);
	printf("connection establishment\n");
	read(readfd,fname,255);
	printf("client has requested file %s\n",fname);
	if((fd=open(fname,O_RDWR))<0)
	{
		strcpy(buff,"file does not exist..\n");
		write(writefd,buff,strlen(buff));
	}else
	{
	while((n=read(fd,buff,512))>0)
	write(writefd,buff,n);
}
close(readfd);
unlink(FIFO1);
close(writefd);
unlink(FIFO2);
}
/*output
bmsce@bmsce-Precision-T1700:~$ cd Desktop/
bmsce@bmsce-Precision-T1700:~/Desktop$ cc IPCserver.c -o server
bmsce@bmsce-Precision-T1700:~/Desktop$ ./server
waiting for connection request
connection establishment
client has requested file sc*/
