#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <dirent.h>

char buffer[80];
char site[80];

void buatfolder(char namafolder[])
{
    char *argv[] = {"mkdir", "-p", namafolder, NULL};
    execv("/bin/mkdir", argv);
    return;
}

void setwaktusekarang()
{
    time_t rawtime;
    struct tm *info;
    time( &rawtime );
    info = localtime( &rawtime );
    strftime(buffer,80,"%Y-%m-%d_%H:%M:%S", info);
}

void getlink()
{
    time_t t = time(NULL);
    sprintf(site, "https://picsum.photos/%ld", ((t%1000)+100));
    return;
}

void downloadgambar(char dir[])
{
    
    char *argv[] = {"wget", "-q", "-O", dir , site, NULL};
    execv("/usr/bin/wget", argv);
}

int main ()
{
    pid_t child_id;
    child_id = fork();
    int status;
    if (child_id==0)
    {
        while(1)
        {
            pid_t child_id;
            child_id = fork();
            setwaktusekarang();
            if (child_id == 0)
                buatfolder(buffer);
            while(wait(&status) > 0);
            sleep(40);
        }
    }
    else
    {
        sleep(1);
        DIR *dp;
        struct dirent *ep;
        char path[]="/home/soraas/shiftmodul2/soal3folder";

        dp = opendir(path);

        if (dp != NULL)
        {
            while ((ep = readdir (dp))) 
            {
                if (strcmp(ep->d_name,".")==0 || strcmp(ep->d_name,"..")==0)
                    continue;
                char dir[500];
                for (int a=0;a<10;a++)
                {
                    setwaktusekarang();
                    sprintf(dir, "%s/%s",ep->d_name,buffer);
                    printf("%s\n",dir);
                    child_id = fork();
                    getlink();
                    if (child_id==0)
                        downloadgambar(dir);
                    sleep(5);
                }
            }
        (void) closedir (dp);
        } else perror ("Couldn't open the directory");
    }
}