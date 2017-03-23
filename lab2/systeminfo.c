

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printCPUinfo();						//function to print cpuinfo
void LinuxKernalVersion();						//function to print the version details
void boottime();						//function to print the last boottime
void averageLoad();						//function to print avgload in the last 15 minutes
void freeMemory();						//function to print the free memory of the system
void swapMemory();						// function to print the swap memory
void cpuTime();							//function to print the cpu time
void ctxtSwitches();						//function to print the number of context switches
void interrupts();						//function to print the number of interrupts

int main(int argc , char **argv)
{
	/* In the main function different functions are called according to the specific need*/

	printf(" CPU details are : ");
	printCPUinfo();
	printf("\n*****************************************************************************************************\n");

	printf(" LinuxKernalVersion running on your system : ");
	LinuxKernalVersion();
	printf("\n*****************************************************************************************************\n");

	printf(" The time when system was booted last time : ");
	boottime();
	printf("\n*****************************************************************************************************\n");

	printf("Average load on system in last 15 minutes : \n");
	averageLoad();
	printf("\n*****************************************************************************************************\n");

	printf(" total usable and free memory in the system : \n");
	freeMemory();
	printf("\n*****************************************************************************************************\n");

	printf("Details about swap memory : \n");
	swapMemory();
	printf("\n*****************************************************************************************************\n");

	printf("Details of cpu time  : \n");
	cpuTime();
	printf("\n*****************************************************************************************************\n");

	printf("The number of context switches made by the system so far : \n");
	ctxtSwitches();
	printf("\n*****************************************************************************************************\n");

	printf("number of interrupts are : \n");
	interrupts();
	printf("\n*****************************************************************************************************\n");

	return 0 ;
}

void printCPUinfo()
{
	printf("\n");
	FILE *cpuinfo = fopen("/proc/cpuinfo","rb");			// opening /proc/cpuinfo to read the cpu details 
	char line[1024];
	int count = 0 ;
	while(fgets(line,1024,cpuinfo) != NULL)
	{
		if(strstr(line,"cpu cores") != NULL)
		{
			puts(line);
		}
		if(strstr(line,"processor") != NULL)
		{
			printf("\n");
			puts(line);
			count++ ;
		}
		if(strstr(line,"cpu MHz") != NULL)
		{
			puts(line);
		}
	}
	printf("\n");
	printf(" The total number of CPU are : %d \n", count);
	fclose(cpuinfo);
	printf("\n");
}

void LinuxKernalVersion()
{
	FILE *version = fopen("/proc/version","rb");             //open /proc/version to print the version
	char version1[1024];
	fscanf(version,"Linux\tversion\t%s",version1);
	printf(" The LinuxKernalVersion is : %s\n", version1);
	fclose(version);
	printf("\n");
}

void boottime()	
{
	FILE *boottime = fopen("/proc/stat","rb");			//open the /proc/stat and print the last boot time
	char line[1024];
	fgets(line,1024,boottime);
	while(strstr(line,"ctxt")==NULL)
	{
		fgets(line,1024,boottime); 
	}
	long long int btime1 ;
	fscanf(boottime,"btime\t%lld",&btime1);
	time_t btime ;
	btime = btime1 ;
	printf(" the last boot time was : %s \n", ctime(&btime));	// to convert the unix epoch time to day:hour:min:sec
	fclose(boottime);
}

void interrupts()
{
	FILE *interrupts = fopen("/proc/stat","rb"); //open /proc/stat and print the number of interrupts handled by the system so far
	int i = 0 ; int j = 0 ;
	char line[1024];
	fgets(line,1024,interrupts);
	while(strstr(line,"intr") == NULL)
	{
		fgets(line,1024,interrupts);
	}
	while(j != 2)
	{
		putchar(line[i]);
		if(line[i++] == ' ')
		{
			j++ ;	
		}
	}
	fclose(interrupts);
}
void swapMemory()
{
	FILE *swapMemory1 = fopen("/proc/meminfo","rb"); //open /proc/meminfo and /proc/swaps to print the swap memory details
	char a[1024] , b[1024] ;
	char line[1024];
	fgets(line,1024,swapMemory1);
	while(strstr(line,"SwapTotal") == NULL)
	{
		fgets(line,1024,swapMemory1);
	}
	puts(line);
	fclose(swapMemory1);

	FILE *swapMemory2 = fopen("/proc/swaps","rb");
	int size , used , partition ;
	fscanf(swapMemory2,"Filename\t\t\t\tType\t\tSize\tUsed\tPriority\n%s\t\t\t\t%s\t\t%d\t%d\t%d\n",a,b,&size,&used,&partition);
	printf(" The total used swap space is : %d\n ",used);
	printf("\nThe swap partitions and their size : \n");
	printf("Filename\t\t\tType\t\tSize\tUsed\tPriority\n%s\t\t\t%s\t%d\t%d\t%d\n",a,b,size,used,partition);
   	fclose(swapMemory2);
}


void cpuTime()
{
	FILE *cpuTime = fopen("/proc/stat","rb");    //open /proc/stat and print the cputime
	int user , b , kernal ;
	fscanf(cpuTime,"cpu\t%d\t%d\t%d",&user,&b,&kernal);
	printf("CPU\tUser\t\tKernel\ncpu\t%d seconds \t%dseconds\n",user,kernal);
	fclose(cpuTime);
}

void freeMemory()
{
	FILE *freeMemory  = fopen("/proc/meminfo","rb");  //open proc/meminfo to print the memory details about the system
	int i = 0 ; int j = 0 ;
	char line[1024];
	fgets(line,1024,freeMemory);
	puts(line);
	fgets(line,1024,freeMemory);
	puts(line);
	fclose(freeMemory);
	printf("\n");
}
 
void ctxtSwitches()
{
	FILE *ctxtSwitches = fopen("/proc/stat","rb"); //open /proc/stat and print the number of context switches made by the system
	int i = 0 ; int j = 0 ;
	char line[1024];
	fgets(line,1024,ctxtSwitches);
	while(strstr(line,"ctxt") == NULL)
	{
		fgets(line,1024,ctxtSwitches);
	}
	puts(line);
	fclose(ctxtSwitches);
}
void averageLoad()
{
   	FILE *avgload = fopen("/proc/loadavg", "rb");         //open /proc/loadavg to print the details of the avg load in 15 minutes
   	float min5,min10,min15;
   	fscanf(avgload,"%f %f %f",&min5,&min10,&min15);
  	printf("%f\n",min15);
   	fclose(avgload);
}































