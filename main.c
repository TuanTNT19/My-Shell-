

// C Program to design a shell in Linux 
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

#define clear() printf("\033[H\033[J") 


char input[50];
char *test[] = {"ls","-l",NULL};

void init()
{
    char *username ;
    clear();
    printf("*****************************************\n");
    printf("\nWELCOME TO TUAN TNT19 's Shell\n");
    printf("Please enjoy this moment\n");
    username = getenv("LOGNAME");
    printf("USER : @%s\n",username);
    printf("\n*****************************************\n");

}

int takeInput(char* str)
{
    char* buf;
    buf = readline("\n>> ");
    if (strlen(buf) != 0)
    {
        add_history(buf);
        strcpy(str, buf);
        return 1;
    }
    else{
        return 0;
    }
}

void printfCurDir()
{
    char dir[1000];
    getcwd(dir, sizeof(dir));
    printf("%s\n",dir);
}

void runcommad(char *str[])
{
    pid_t child_pid;
    child_pid = fork();

    if (child_pid >= 0)
    {
        if (child_pid == 0)
        {
            execvp(str[0], str); //str[0]: Name of run file ; str :  array of strings representing the command-line arguments of the new program, where the last element must be a NULL pointer.
            exit(0);
        }
        else if (child_pid > 0)
        {
            wait(NULL);
            return ;
        }
        
    }
    else{
        printf("ERROR\n");
        return ;
    }
}


int main()
{
    init();
    takeInput(input);
    printfCurDir();
    runcommad(test);
   
 
    return 0;
}
