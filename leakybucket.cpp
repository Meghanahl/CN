#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#define bucketSize 512
using namespace std;

void bktInput(int a ,int b);

int main()
{
	int op,pktSize;
	cout<<"enter the output rate:";
	cin>>op;
	for(int i=1;i<=5;i++)
	{
		usleep(rand()%1000);
		pktSize=rand()%1000;
		cout<<"\n packet no"<<i<<"\t packet size="<<pktSize;
		bktInput(pktSize,op);
	}
	return 0;
}

void bktInput(int a,int b)
{
	if(a>bucketSize)
		cout<<"\n\t----bucket overflowww";
	else
		{
			usleep(500);
			
	while(a>b)
	{	
		cout<<"\n\t\t"<<b<<"bytes outputed";
		a-=b;
		usleep(500);
	}
	if(a>0)
		cout<<"\n\t last"<<a<<"bytes sent\t";
		cout<<"\n\t\t backet output successfully";
		}
}
/*---------------output----------
bmsce@bmsce-Precision-T1700:~/Desktop$ g++ -o leak leakybucket.cpp
bmsce@bmsce-Precision-T1700:~/Desktop$ ./leak
enter the output rate:100

 packet no1	 packet size=886
	----bucket overflowww
 packet no2	 packet size=915
	----bucket overflowww
 packet no3	 packet size=335
		100bytes outputed
		100bytes outputed
		100bytes outputed
	 last35bytes sent	
		 backet output successfully
 packet no4	 packet size=492
		100bytes outputed
		100bytes outputed
		100bytes outputed
		100bytes outputed
	 last92bytes sent	
		 backet output successfully
 packet no5	 packet size=421
		100bytes outputed
		100bytes outputed
		100bytes outputed
		100bytes outputed
	 last21bytes sent	
		 backet output successfully
