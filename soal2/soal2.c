#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <dirent.h>

char ziplocation[] = "/home/husin/modul2/pets/";

void ForkWaitFunction(char bash[], char *arg[]){
    int status;
    pid_t child;
    child = fork();
    if(child == 0){
        execv(bash, arg);
    }
    else{
        ((wait(&status))>0);
    }
}


void ExecuteFilesRecursively(char *basePath)
{
    char path[1000];
    const char *semicolon = ";", *underscore = "_";
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir){
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            if(dp->d_type == DT_DIR){
                char petslocation[100] = "/home/husin/modul2/pets/";
                strcat(petslocation, dp->d_name);

                char *argvrmFolder[] = {"rm", "-rf", petslocation, NULL};
                ForkWaitFunction("/usr/bin/rm", argvrmFolder);
            }
            else{
                char typepetsfoldername[100] = "";
                char typepetslocation[100] = "/home/husin/modul2/petshop/";
                
                strcpy(typepetsfoldername, dp->d_name);
                strtok(typepetsfoldername, semicolon);
                
                strcat(typepetslocation, typepetsfoldername);

                char *argvmkdirTypePets[] = {"mkdir", "-p", typepetslocation, NULL};
                ForkWaitFunction("/bin/mkdir", argvmkdirTypePets);

                char movefile[100] = "/home/husin/modul2/pets/";
                strcat(movefile, dp->d_name);

                if(!(strstr(movefile, underscore))){
                    char *argvmvFile[] = {"mv", "-f", movefile, typepetslocation, NULL};
                    ForkWaitFunction("/usr/bin/mv", argvmvFile);
                }
                else{
                    char copyfile[100] = "/home/husin/modul2/pets/";
                    strcat(copyfile, dp->d_name);
                    strtok(copyfile, ".");
                    strcat(copyfile, "(1)");
                    strcat(copyfile, ".jpg");

                    char *argvcpTypePets[] = {"cp", movefile, copyfile, NULL};
                    ForkWaitFunction("/usr/bin/cp", argvcpTypePets);

                    if(!(strstr(movefile, "(1)"))){
                        char *argvmvFile2[] = {"mv", "-f", movefile, typepetslocation, NULL};
                        ForkWaitFunction("/usr/bin/mv", argvmvFile2);
                    }
                }
    
            }
  
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            ExecuteFilesRecursively(path);
        }
    }

    closedir(dir);
}



int main() {
    int status;
    pid_t child1;

    char *argvmkdirPetshop[] = {"mkdir", "-p", "petshop", NULL};
    char *argvmkdirPets[] = {"mkdir", "-p", "pets", NULL};
    char *argvunzipPets[] = {"unzip", "pets.zip", "-d", "pets", NULL};

    ForkWaitFunction("/bin/mkdir", argvmkdirPetshop);
    ForkWaitFunction("/bin/mkdir", argvmkdirPets);
    ForkWaitFunction("/usr/bin/unzip", argvunzipPets);
    
    ExecuteFilesRecursively(ziplocation);

    return 0;
}
