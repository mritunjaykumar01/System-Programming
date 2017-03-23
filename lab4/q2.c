#include <stdio.h>
#include <sys/stat.h>
#include <grp.h>
#include <dirent.h>
#include <pwd.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char const *argv[])
{
        DIR *dir;
        struct dirent *dir_ptr;
        struct stat file_stat;
        struct passwd *p;
        struct group *g;
        struct tm *t;
        char time[26];
        dir=opendir(".");
        
        //read the directory(dir);
        readdir(dir);
        while( (dir_ptr=readdir(dir))!=NULL)
        {
                stat(dir_ptr->d_name,&file_stat);
 	        printf( (S_ISDIR(file_stat.st_mode)) ? "d" : "-");
                printf( (file_stat.st_mode & S_IRUSR) ? "r" : "-");
                printf( (file_stat.st_mode & S_IWUSR) ? "w" : "-");
                printf( (file_stat.st_mode & S_IXUSR) ? "x" : "-");
                printf( (file_stat.st_mode & S_IRGRP) ? "r" : "-");
                printf( (file_stat.st_mode & S_IWGRP) ? "w" : "-");
                printf( (file_stat.st_mode & S_IXGRP) ? "x" : "-");
                printf( (file_stat.st_mode & S_IROTH) ? "r" : "-");
                printf( (file_stat.st_mode & S_IWOTH) ? "w" : "-");
                printf( (file_stat.st_mode & S_IXOTH) ? "x" : "-");
 
                p=getpwuid(file_stat.st_uid);
                printf(" %.8s",p->pw_name);

                // the name of Group 
                g=getgrgid(file_stat.st_gid);
                printf(" %-8.8s",g->gr_name);
                printf(" %8ld",file_stat.st_size);

                //Date and Time of modification
                t=localtime(&file_stat.st_mtime);
                strftime(time,sizeof(time),"%b %d %H:%M",t);
                printf(" %s",time);
                
                //File Name
                printf(" %s\n",dir_ptr->d_name);
        }
	return 0;
}