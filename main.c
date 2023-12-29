
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
char *command1[10] = {"ps", "-aux"};
char *command2[10] = {"grep", "test"};

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

void runsinglecommad(char *str[])
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

void rundoublecommand(char **command1, char **command2)
{
    pid_t pid1, pid2;
    int fds[2];

    if (pipe(fds) < 0)
    {
        printf("ERROR: Can not create pipe\n");
        return ;
    }

    pid1 = fork();
    
    if (pid1 < 0)
    {
        printf("ERROR: Can not fork\n");
        return ;
    }
    else if (pid1 == 0)
    {
        close(fds[0]);
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);

        if (execvp(command1[0], command1) < 0){
            printf("ERROR: Can not run command 1\n");
            return ;
        }
        exit(0);
    }
    else{
        pid2 = fork();
        
        if (pid2 < 0)
        {
            printf("ERROR: Can not fork\n");
            return ;
        }
        else if (pid2 == 0)
        {
            close(fds[1]);
            dup2(fds[0], STDIN_FILENO);
            close(fds[0]);

            if (execvp(command2[0], command2) < 0)
            {
                printf("ERROR: Can not run command 2\n");
                return ;
            }
        }
        else{
            wait(NULL);
            wait(NULL);
        }
    }
}
    

int main()
{
    init();
    takeInput(input);
    printfCurDir();
    runsinglecommad(test);
    rundoublecommand(command1, command2);
   
    return 0;
}
