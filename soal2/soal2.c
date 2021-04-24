#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <dirent.h>

char ziplocation[] = "/home/husin/modul2/petshop";
const char semicolon[] = ";";
const char udr[] = "_";

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

void listDir(char *basePath)
{

    struct dirent *dp;

    FILE * fp;

    char typepetsfoldername[200] = "";
    char filepetsname[100] = "";
    char typepetslocation[100] = "/home/husin/modul2/petshop";
    char *token;
    char *limit;
    char *age;
    char name[20];
    char echoke[100];
    char file[20];
    char file1[20];
    char binatang[20];
    char test[20];
    char hewan[100];
    char text[100];

    int notif = 0;
    int cek = 0;
    int more = 0;
    
    DIR *dir = opendir(basePath);

    while ((dp = readdir(dir)))
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_type == DT_DIR)
        {
            char petslocation[100] = "/home/husin/modul2/petshop";
            strcat(petslocation,"/");
            strcat(petslocation, dp->d_name);
            char *argvrmfolder[] = {"rm", "-rf", petslocation, NULL};
            ForkWaitFunction("/bin/rm", argvrmfolder);
        }
    }
    DIR *mer = opendir(basePath);
    while ((dp = readdir(mer)))
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_type != DT_DIR)
        {

            notif = 0;
            cek = 0;
            more = 0;

            strcpy(file,dp->d_name);
            strcpy(file1,dp->d_name);

            strcpy(hewan,typepetslocation);
            strcat(hewan,"/");

            strcpy(filepetsname,typepetslocation);
            strcat(filepetsname,"/");
            strcat(filepetsname,dp->d_name);

            limit = strtok(dp->d_name, udr);

            while(limit != NULL)
            {
                more ++;
                cek = 0;
                notif = 0;  
                strcpy(hewan,typepetslocation);
                strcat(hewan,"/");
                strcat(hewan,limit);
                char *argvmvPets[]={"cp", filepetsname, hewan,NULL};
                ForkWaitFunction("/bin/cp", argvmvPets);

                
                printf("\nlimit = %s\n",limit);
                limit = strtok(NULL,udr);    
            }
            if(more>1){
                strcpy(hewan,typepetslocation);
                strcat(hewan,"/");
                strcat(hewan,file);
                printf("\n%s\nmasuk\n",file);
                char *argvrm[] = {"rm", hewan, NULL};
                ForkWaitFunction("/bin/rm", argvrm);
                continue;    
            }
        }
    }
    DIR *mar = opendir(basePath);
    while ((dp = readdir(mar)))
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_type != DT_DIR)
        {
            strcpy(filepetsname,typepetslocation);
            strcat(filepetsname,"/");
            strcat(filepetsname,dp->d_name);

            strcpy(file1,dp->d_name);

            token = strtok(dp->d_name, semicolon);
            char folder[20];
            notif = 0;
            cek = 0;

            while(token != NULL)
            {
                if(cek == 0){
                    strcpy(typepetsfoldername,typepetslocation);
                    strcat(typepetsfoldername,"/");
                    strcat(typepetsfoldername,token);
                    strcpy(folder,token);

                    char *argvmkdirTypePets[] = {"mkdir", "-p", typepetsfoldername, NULL};
                    ForkWaitFunction("/bin/mkdir", argvmkdirTypePets);

                    strcpy(text,typepetslocation);
                    strcat(text,"/");
                    strcat(text,token);
                    strcat(text,"/keterangan.txt");

                    char *argvmktxt[] = {"touch", text, NULL};
                    ForkWaitFunction("/usr/bin/touch", argvmktxt);

                    cek = 1;
                    notif++;
                    token = strtok(NULL, semicolon);
                    continue;
                }
                else if((notif%2)==1&& cek == 1){
                    strcpy(name,token);

                    char nama[20];
                    char mvke[100];
                    char rename[100];

                    strcpy(rename,typepetsfoldername);
                    strcat(rename,"/");
                    strcat(rename,file);                        

                    strcpy(mvke,typepetsfoldername);
                    strcat(mvke,"/");
                    strcat(mvke,name);
                    strcat(mvke,".jpg");

                    strcpy(echoke,typepetsfoldername);
                    strcat(echoke,"/keterangan.txt");

                    strcpy(nama,"nama : ");
                    strcat(nama, name);

                    char *argvmvPets[]={"cp", hewan, typepetsfoldername,NULL};
                    ForkWaitFunction("/bin/cp", argvmvPets);

                    char *argvmvrnPets[] = {"mv", rename,mvke,NULL};
                    ForkWaitFunction("/bin/mv", argvmvrnPets);

                    fp = fopen(echoke,"a");
                    fprintf(fp,"%s\n",nama);
                    fclose(fp);

                    notif++;
                    token = strtok(NULL, semicolon);
                    continue;
                }else if((notif%2)==0&& cek == 1){
                    
                    if(strstr(token,"jpg")!= NULL){
                        age = strtok(token, "jpg");
                        while(age != NULL){
                            age[strlen(age)-1] = '\0';
                            fp = fopen(echoke,"a");
                            fprintf(fp,"umur : %s\n\n",age);
                            fclose(fp);
                            age = strtok(NULL, ".jpg");
                    }
                    }else{
                        fp = fopen(echoke,"a");
                        fprintf(fp,"umur : %s\n\n",token);
                        fclose(fp);
                    } 
                    notif++;
                    token = strtok(NULL, semicolon);
                    continue;                         
                }
                token = strtok(NULL, semicolon);
            }

            char *argvrm[] = {"rm", filepetsname, NULL};
            ForkWaitFunction("/bin/rm", argvrm);
        }
    }
    closedir(dir);
}
            

int main() {
    int status;
    pid_t child1;

    char *argvmkdirpets[] = {"mkdir", "petshop", NULL};
    char *argvunzippets[] = {"unzip", "pets.zip", "-d", "petshop", NULL};
    
    ForkWaitFunction("/bin/mkdir", argvmkdirpets);
    ForkWaitFunction("/usr/bin/unzip", argvunzippets);
    
    listDir(ziplocation);

    return 0;
}