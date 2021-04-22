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
    
    char *argv[] = {"wget", "-q" ,"-O", dir , site, NULL};
    execv("/usr/bin/wget", argv);
}

int main ()
{
    int firstrun=1;
    pid_t child_id;
    while(1)
    {
        setwaktusekarang();
        child_id = fork();
        if (child_id == 0)
        {
            buatfolder(buffer);
        }
        child_id = fork();
        while (opendir(buffer) == NULL);
        char dir[80];
        strcpy(dir,buffer);
        child_id = fork();
        if (child_id == 0)
        {
            for (int a=0;a<10;a++)
            {
                printf("Download Success\n");
                getlink();
                child_id = fork();
                setwaktusekarang();
                char finaldir[100];
                sprintf(finaldir,"%s/%s",dir,buffer);
                if (child_id==0)
                    downloadgambar(finaldir);
                sleep(5);
            }
        }
        sleep(40);
    }
}