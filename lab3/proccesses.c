
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
int main()
{
	pid_t c_pid1 , c_pid2 , c_pid3 , c_pid4 ;
	struct timeval now , begin_time , end_time ;
	int pid_son3 ;
	int pid_son2 ;
	long time_spent;
	int status = 0 ;
	c_pid1 = fork();		// wise child  started  working 
	if(c_pid1 < 0)
	{
		printf("Fork error %d.\n", errno);
        		exit(EXIT_FAILURE);
	}
	else if( c_pid1 == 0)
	{ 
		printf(" the wise son started working \n");
		printf(" the child is sleeping for 1 second and  then exiting with status 16 \n");
		sleep(1);
		exit(16);
	}
	else
	{
		int status = 0 ;
		c_pid1 = wait(&status);
		if(WIFEXITED(status))
		{
			printf("child exited with status : %d\n" , WEXITSTATUS(status));
		}
	}
	printf(".................................................................................................\n");
	c_pid2 = fork();
	if( c_pid2 < 0)			// foolish child started working  
	{
		printf("Fork error %d.\n", errno);
        	exit(EXIT_FAILURE);
	}		
	else if( c_pid2 == 0)
	{
		printf(" foolish son started working \n");
		pid_son2 = getpid();
		printf(" child pid : %d , I am the foolish child \n", pid_son2);
		char *p =NULL;
		*p = 'a';
	}
	else
	{
		int status = 0 ;
		c_pid1 = wait(&status);
		if(WIFSIGNALED(status))
		{
			printf("Signal: %s\n", strsignal( WTERMSIG(status) ) );
		}
	}
	printf("................................................................................................\n");
	c_pid3 = fork();		//wicked son  started working 
	if(c_pid3 < 0) 
	{
		printf("Fork error %d.\n", errno);
        	exit(EXIT_FAILURE);
	}
	else if( c_pid3 == 0)
	{
		printf(" wicked son started working \n");
		pid_son3 = getpid();
		printf(" the wicked son with pid : %d is sending a signal to itself for killing itself \n" , pid_son3);
		kill(pid_son3 , SIGABRT) ;
	}
	else
	{
		int status = 0 ;
		c_pid1 = wait(&status);
		if(WIFSIGNALED(status))
		{
			printf("child exited with status : %d\n" , WEXITSTATUS(status));
		}
	}
	printf("................................................................................................\n");
	c_pid4 = fork();		//hardworking son started  working 
	if(c_pid4 < 0)
	{
		printf("Fork error %d.\n", errno);
        	exit(EXIT_FAILURE);
	}
	else if( c_pid4 == 0)
	{
		printf(" the hardworking son started working \n");
		gettimeofday(&begin_time, NULL);
		system("make systeminfo");
		system("./systeminfo");
		execve("./systeminfo",NULL,NULL);
		gettimeofday(&end_time, NULL);
		time_spent = (end_time.tv_sec - begin_time.tv_sec)*100000 + (end_time.tv_usec - begin_time.tv_usec) ;
		printf("\n the total time spent is : %d microseconds \n", time_spent);
		exit(10);
	}
	else
	{
		int status = 0 ;
		c_pid1 = wait(&status);
		printf("\n the total time spent is : %d microseconds \n", time_spent);
		if(WIFEXITED(status))
		{
			printf("child exited with status : %d\n" , WEXITSTATUS(status));
		}
	}
	printf("................................................................................................\n");
	printf(" closing main programme \n");
	return 0 ;
}