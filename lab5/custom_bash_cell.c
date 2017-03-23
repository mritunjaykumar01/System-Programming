                                        /********************************/
                                        /*        Jitendra kumar        */
                                        /*        1401cs19              */
                                        /*        lab-5                 */
                                        /*        shell implementation  */
                                        /*        in c                  */
                                        /********************************/                                                
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
        if(cmd == NULL)
        {
                printf("Memory allocation error!\n");
                exit(-1);
        }
        char* d = " ";
        char* token;
        printf("*********************************************************************************************************\n");
        printf("enter only those  commands which are mentioned in question\n");
        printf("here you go :\n");
        do
        {  
                printf("my_shell-$ ");
                fgets(cmd, sizeof(char)*512, stdin);
                if(strlen(cmd)> 0 && cmd[strlen(cmd)-1] == '\n')
                cmd[strlen(cmd)-1] = '\0';
                token = strtok(cmd, d);

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
	}while(strcmp(cmd, "exit") != 0);
        printf("terminating the shell\n");
        printf("*********************************************************************************************************\n");
        exit(0);
}