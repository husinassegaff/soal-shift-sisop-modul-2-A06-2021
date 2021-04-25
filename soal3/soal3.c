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

void chip(char *textdl, int adder)
{
	for (int a=0;textdl[a]!='\0';a++)
	{
		if (textdl[a]>=65 && textdl[a]<=90)
		{
		adder = adder%26;
		textdl[a] += adder;
			if (textdl[a] > 90)
			{
			textdl[a] -= 26;
			}
		}
		else if (textdl[a]>=97 && textdl[a]<=122)
		{
		adder = adder%26;
			if (textdl[a]+adder > 122)
			{
			textdl[a] -= 26;
			}
			textdl[a] += adder;
		}
		if (textdl[a]>=48 && textdl[a]<=57)
		{
			adder = adder%10;
			if (textdl[a]+adder > 57)
			{
			textdl[a] -= 10;
			}
			textdl[a] += adder;
		}
	}
}

void cetakdownloadsuccess(char namafolder[])
{
    char downloadstatus[150];
    char textdl[20] = "Download Success";
    sprintf(downloadstatus, "%s/status.txt",namafolder);
    chip(textdl,5);
    FILE *downloaded = fopen(downloadstatus,"w");
    fprintf(downloaded,"%s",textdl);
    fclose(downloaded);
}

void bikinkiller(int argc,char **argv, int pid)
{
    FILE *fkiller = fopen("killer.sh","w");

    if (argc < 2)
    {
        printf("Kasih parameter dong yank :(\n");
        exit(0);
    }
    if (strcmp(argv[1],"-z") == 0)
    {
        fprintf(fkiller, "#!/bin/bash\nkillall -9 soal3\nrm \"$0\"");
    }
    else if (strcmp(argv[1],"-x") == 0)
    {
        fprintf(fkiller, "#!/bin/bash\nkill %d\nrm \"$0\"", pid);
    }

    fclose(fkiller);

    if(fork() == 0)
    {
        char *chmodarg[] = {"chmod", "+x", "killer.sh", NULL};
        execv("/bin/chmod", chmodarg);
    }
}

void makezip(char namafolder[])
{
    char zipname[150];
    sprintf(zipname,"%s.zip",namafolder);
    char *argv[] = {"zip", "-rmq", zipname, namafolder,NULL};
    if (fork() == 0)
        execv("/usr/bin/zip",argv);
    printf("Process Completed.\n");
}

int main (int argc, char **argv)
{
    int firstrun=1;
    pid_t pid, child_id;
    bikinkiller(argc,argv,(int)getpid());
    printf("Killer Created.\n");
    while(1)
    {
        setwaktusekarang();
        child_id = fork();
        if (child_id == 0)
        {
            buatfolder(buffer);
        }
        while (opendir(buffer) == NULL);
        printf("Folder Created.\n");
        char dir[80];
        strcpy(dir,buffer);
        child_id = fork();
        if (child_id == 0)
        {
            for (int a=0;a<10;a++)
            {
                getlink();
                child_id = fork();
                setwaktusekarang();
                char finaldir[200];
                sprintf(finaldir,"%s/%s",dir,buffer);
                if (child_id==0)
                    downloadgambar(finaldir);
                printf("Download Success.\n");
                sleep(5);
            }
            cetakdownloadsuccess(dir);
            sleep(1);
            makezip(dir);
        }
        sleep(40);
    }
}