                                        /********************************
                                                Jitendra kumar        	
                                                1401cs19              		 
                                                 lab-6                		 
                                               lab6_shell :- lab5_shell.c with  added functionalities  as  asked  in  question                 		 
                                        ********************************/                                                
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char* argv[], char** envp)
{
        	// allocating memory for taking input the command 
	char* cmd = malloc(sizeof(char)*512);

	char* cmd2 = malloc(sizeof(char)*512);

        	if(cmd == NULL || cmd2 == NULL)
        	{
                		printf("Memory allocation error !\n");
                		exit(-1);
        	}
               int count = 0 ;  // for number of 
               int num = 0 ;
               char* d = " \t\r\n\a";
        	char* token;
        	printf("\n*********************************************************************************************************\n");
        	//printf("enter only those  commands which are mentioned in question\n");
        	printf("--------------------------------------! Here you Go !----------------------------------------\n\n");
        	do
        	{  
	               	printf("my_shell-$ ");
	               	if(num == 0)
	                	fgets(cmd, sizeof(char)*512, stdin);
	                		// if(strlen(cmd)> 0 && cmd[strlen(cmd)-1] == '\n')
	                		// cmd[strlen(cmd)-1] = '\0';
	                		// token = strtok(cmd, d);
	                	if(strlen(cmd) == 1)
	      		{
	        			cmd[1] = '\0';
	        			if(strcmp(cmd,"\n") == 0) 
	        				count++;
	      		}
	      		else
	      		{
	        			if(strlen(cmd)> 0 && cmd[strlen(cmd)-1] == '\n') 
	        			cmd[strlen(cmd)-1] = '\0';
	        			count = 0;
	      		}

	     		 char* x;
	     		if(( x = strstr(cmd, ";")) != NULL)
	     		{
	        			num = 2;
	        			char* y = x;
	        			if(y[1] != ' ')
	        				y++;
	        			else
	        				{
	          					y = y+2;
	          					strcpy(cmd2, y);
	        				}
	        				(x[0]) = '\0';
	      		}


	      		//execute ls in this case of  double tapping enter 
	      		if(count == 2)
	      		{

			          	pid_t a, b;
			          	int status;
			         	a = fork();
			          	if(a == 0)
			          	{
			            		char* ls[3] = {"ls", "-l", NULL};
			            		if(execvp(ls[0],ls) == -1)
			            		{
			              			perror("Error ");
		            			}
		          		}
		          		else if(a < 0)
		          		{
		            			perror("Error ");
		          		}
		          		else
		          		{
		            			b = wait(&status);
		            			count = 0;
		          		}
	        		}

	        		if(num == 2)
	        		{
	          			token = strtok(cmd, d);
	          			if(token == NULL)
	          				continue;
	          				num--; 
	        		}
	        		else if(num == 1)
	        		{
	          			token = strtok(cmd2, d);
	          			if(token == NULL) 
	          				continue;
	          				num--; 
	        		}
	        		else
	        		{
	          			token = strtok(cmd, d);
	          			if(token == NULL)
	          			 	continue; 
	        		}
               		 // if change directory cmd is taken
                		if(strcmp(token, "cd") == 0)
                		{
                        			char* destination_directory = strtok(NULL, d);
                        			if(destination_directory == NULL)
                        			{
                                			printf("specify the directory\n");
                                			continue;
                        			}
                        			if(strtok(NULL, d) != NULL)
                        			{
                                			printf("format: cd [destination_directory]\n");
                                			continue;
                        			}

                        			int stat = chdir(cmd+3);
                        			if(stat == -1)
                                		perror("Error ");
                		}
                        		//if pwd cmd is given
                		else if(strcmp(token, "pwd") == 0)
                		{
                        			token = strtok(NULL, d);
                        			if(token != NULL)
                        			{
                                			printf("Format: pwd");
                               		 	continue;
                        			}

			              getcwd(cmd, sizeof(char)*512);
		                              printf("%s\n", cmd);
                		}

                        		//if echo is used
                		else if(strcmp(token, "echo") == 0)
                		{
                        			char* print = strtok(NULL, d);
                        			while(print != NULL)
                        			{
                                			if(print[0] == '$')
                                			{
                                        				printf("%s ", getenv(print+1));
                                			}
                                			else
                                			{
                                        				printf("%s ", print);
                                			}
                                			print = strtok(NULL, d);
                        			}
                        			printf("\n");
                		}

                        		//if env is used
                		else if(strcmp(token, "env") == 0)
                		{
                        			if(strtok(NULL, d) != NULL)
                        			{
                                			printf("Format: env\n");
                                			continue;
                        			}
                       		 	char** env;
                        			for (env = envp; *env != 0; env++)
                        			{
                                			char* thisEnv = *env;
                                			printf("%s\n", thisEnv);    
                        			}
                		}

                        		//if setenv is used
                		else if(strcmp(token, "setenv") == 0)
                		{
                        			char* name = strtok(NULL, d);
                        			if(name == NULL)
                        			{
                                			printf("Format: setenv [name] [value]\n");
                                			continue;
                        			}
                        			char* value = strtok(NULL, d);
                                		if(value == NULL)
                        			{
                                			printf("Format: setenv [name] [value]\n");
                                			continue;
                        			}
                        			if(strtok(NULL, d) != NULL)
                        			{
                                			printf("Can set only one env variable at a time!\n");
                                			continue;
                        			}
                        			int error = setenv(name, value, 1);
                        			if(error == -1)
                        			{
                                			perror("Error ");
                        			}
                		}
                		else if (strcmp(token, "exit") != 0)
      			{

	        			char* args[100];
	        			int j = 0 ;
	        			for(j = 0;j<100 ;j++)
	        			{
	          				args[j] = NULL;
	        			}

	        			args[0] = token;
	        			int i;
	        
	        			for(i =1; i< 100; i++)
	        			{
	          				args[i] = strtok(NULL, d);
	          				if(args[i] == NULL) 
	          					break;
	        			}

	        			pid_t pid, wpid;
	        			int status;
	        			pid = fork();
	        			if(pid == 0)
	        			{
	          				if( execvp(args[0], args) == -1 )
	          				{
	            					perror("Error ");
	          				}  
	          				exit(EXIT_FAILURE);
	        			}

	        			else if(pid < 0)
	        			{
	          				perror("Error: ");
	        			}
	        			else 
	        			{
	          				do
	          				{
	            					wpid = waitpid(pid, &status, WUNTRACED);

	          				}while(!WIFEXITED(status) && !WIFSIGNALED(status));

		          			if(WEXITSTATUS(status) == 0)
		          			{
		            				printf("Program terminated successfully!\n");
		          			}
		          			else
		          			{
		            				printf("Program terminated unsuccessfully :(\nExit status: %d\n", WEXITSTATUS(status));
		          			}

	        			}       
	        
      			}
	}while(strcmp(cmd, "exit") != 0);
        	printf("\n----------------------------------! terminating the shell !----------------------------------\n");
        	printf("*********************************************************************************************************\n\n");
        	exit(0);
}