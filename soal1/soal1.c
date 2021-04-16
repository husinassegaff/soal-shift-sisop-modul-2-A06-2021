//menggunakan exec
//mkdir -> download -> unzip -> mv -> tunggu -> zip -> delete

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h> 
#include <dirent.h>

int main() {
  pid_t pids, sids;        // Variabel untuk menyimpan PID

  pids = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pids < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pids > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sids = setsid();
  if (sids < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/osd0081/Desktop/Sisop/soal-shift-sisop-modul-2-A06-2021/soal1")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    // Tulis program kalian di sini
    time_t rawtime;
    struct tm * timeinfo;
    int i, stat;
    pid_t pid;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    char link[3][100]={
        "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
        "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
        "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"
    };
    char rn[3][20]={
        "Musyik.zip",
        "Pyoto.zip",
        "Fylm.zip"
    };
    char n1[3][20]={
        "MUSIK",
        "FOTO",
        "FILM"
    };
    char n[3][20]={
        "Musyik",
        "Pyoto",
        "Fylm"
    };

    if(timeinfo->tm_mon == 3 && timeinfo->tm_mday== 9 && timeinfo->tm_hour== 16 && timeinfo->tm_min==22 && timeinfo->tm_sec==0){
    
        // komponen donwload 



        DIR *dp;
        struct dirent *ep;
        char file[50];
        char target[50];
        char path[100];
        
        for (i=0; i<3; i++)
        {
            if ((pid = fork()) == 0)
            {
                if ((pid = fork()) == 0)
                {    
                    if((pid=fork())==0)
                    {
                        char *argv[] = {"mkdir",n[i], NULL};
                        execv("/bin/mkdir", argv);
                    }else{
                        waitpid(pid,&stat,0);
                        if (WIFEXITED(stat))
                        {
                            char *argv[] = {"wget", "--no-check-certificate",link[i],"-O",rn[i], NULL};
                            execv("/usr/bin/wget", argv);
                        }
                    }
                }else{
                    waitpid(pid,&stat,0);
                    if (WIFEXITED(stat))
                    {
                        if((pid=fork())==0)
                        {
                            char *argv[] = {"unzip",rn[i], NULL};
                            execv("/usr/bin/unzip", argv);
                        }else{
                            waitpid(pid,&stat,0);
                            if (WIFEXITED(stat))
                            {
                                getcwd(path, sizeof(path));
                                strcat(path,"/");
                                strcpy(target,"");
                                strcpy(target,path);
                                strcat(target,n[i]);
                                strcat(path,n1[i]);
                                dp = opendir(path);
                                while ((ep = readdir (dp))) {
                                    strcpy(file,"");
                                    strcpy(file,path);
                                    if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0){
                                        if ((pid = fork()) == 0)
                                        {
                                                strcat(file,"/");
                                                strcat(file,ep->d_name);
                                                char *argv[] = {"mv",file, target, NULL};
                                                execv("/bin/mv", argv);      
                                        }else{
                                            waitpid(pid, &stat,0);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }else{
                waitpid(pid, &stat,0);
            }
        }

        if (WIFEXITED(stat))
            printf("\ndone\n");
    
    }
    
    else if (timeinfo->tm_mon == 3 && timeinfo->tm_mday== 9 && timeinfo->tm_hour== 22 && timeinfo->tm_min==22 && timeinfo->tm_sec==0){

        // komponen zip
        
        if ((pid = fork()) == 0)
        {    
            char *argv[] = {"zip","-r","Lopyu_Stevany.zip",n[0],n[1],n[2], NULL};
            execv("/usr/bin/zip", argv);
        }else{
            waitpid(pid,&stat,0);
            if (WIFEXITED(stat)){
                char *argv[] = {"rm","-r",n[0],n[1],n[2],n1[0],n1[1],n1[2], NULL};
                execv("/bin/rm", argv);
            }
        }

    }
  sleep(1);
  }
}