#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>


void chgDir(const char* path, char* currDir) {

    printf("length: %zu\n", strlen(path));
    //char real_path[strlen(path)-1];
    //for (int i = 0; i < strlen(path) -1; i++) {
        //real_path[i] = path[i];
    //}

    // printf("Real Path: %s %zu %zu\n", real_path, strlen(path), strlen(real_path));
    if ( chdir(path) == -1) {
        // real_path
        printf("Error: cannot change directory\n");
        perror("fail");
        return;
    }

    if ((getcwd(currDir, 1000)) == NULL) {
        perror("getcwd() error");
    }
    setenv("pwd", currDir, 1);
}

void showpid(int idList[]) {
    for (int i = 0; i < 5; i++) {
        printf("%d\n", idList[i]);
    }
    return;
}

int main() {
    pid_t pid;
    int status;
    int idList[5];
    char* command;
    char* tokenArr;
    char* argumentList[10];
    char str[1000];
    char currDir[1000];

    for (int i = 0; i < 10; i++) {
        //argumentList[i] = (char*) malloc(sizeof(char) * 81);
        argumentList[i] = NULL;
    }


    while (1) {
        
        // Get user input using fgets
        
        printf("\033[0;31m%s$ ", getcwd(currDir, 1000)); 
        printf("\033[0m");
        if (fgets(str, 1000, stdin) != NULL) {
            // Do something
            tokenArr = strtok(str, " ");
            int i = 0;
            while (tokenArr != NULL) {
                if (i == 0) {
                    command = strdup(tokenArr);
                }
                argumentList[i] = strdup(tokenArr);
                printf("%s %zu\n", argumentList[i], strlen(argumentList[i]));
                tokenArr = strtok(NULL, " ");
                i++;
            }

            if (strncmp(command, "cd", 2) == 0) {
                chgDir(argumentList[1], currDir);
            }
            else if (strncmp(command, "showpid", 7) == 0) {
                showpid(idList);
            }
            else if (strncmp(str, "exit", 4) == 0) {
                printf("EXTING!\n");
                break;
            }
            else {
                
                if ((pid = fork()) == 0) {
                    int execStatus = execvp(command, argumentList);
                    if (execStatus == -1) {
                        printf("Error: Command could not be executed\n");
                        exit(1);
                    }
                    kill(pid, SIGTERM);
                }
                else {
                    waitpid(pid, &status, 0);
                }

            }
        }
    }
}