
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
char check_ending[10] = "exit";
char *command1[100];
char *command2[100] ;

//Starting shell
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

//take input and store it to str
int takeInput(char* str)
{
    char* buf;
    buf = readline("\nTuanTNT19% >> ");
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

//Display current Dictory
void printfCurDir()
{
    char dir[1000];
    getcwd(dir, sizeof(dir));
    printf("Current_Dictory: %s ",dir);
}

//Funstion to run single command
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

//Function to run double command
void rundoublecommand(char **command1, char **command2)
{
    pid_t pid1, pid2;
    int fds[2];
    int status;

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
        dup2(fds[1], STDOUT_FILENO);//redirects the standard output to whatever file or resource is associated with the file descriptor at index 1 in the fds array.
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
            dup2(fds[0], STDIN_FILENO); //redirects the standard input to whatever file or resource is associated with the file descriptor at index 1 in the fds array.
            close(fds[0]);

            if (execvp(command2[0], command2) < 0)
            {
                printf("ERROR: Can not run command 2\n");
                return ;
            }
        }
        else{
            close(fds[0]);
            close(fds[1]);

            // Wait for both child processes
            waitpid(pid1, &status, 0);
            waitpid(pid2, &status, 0);

            return ;
        }
    }
}

//function to process string double command
int process_doublecommand(char *command, char **str)
{
    int i = 0;
    char *token = strtok(command, "|");
    while (token != NULL)
    {
        str[i] = token;
        i++;
        token = strtok(NULL, "|");

    }
    
    if (i == 1)
    {
        return 0;
    }
    else{
        return 1;
    }

}

//function to process strong single command
void process_singlecommand(char *command, char **str)
{
    int i = 0;
    char *token = strtok(command, " ");
    while (token != NULL)
    {
        str[i] = token;
        i++;
        token = strtok(NULL, " ");

    }
}

//process input to command1 and command2
int process_input(char *input, char **command1, char **command2)
{
    int check ;
    char *str[2];
    
    check = process_doublecommand(input, str);
    
    if (check)//if input is double command
    {
        process_singlecommand(str[0], command1);
        process_singlecommand(str[1], command2);
        return 2;
    }

    else//if input is single command
    {
        process_singlecommand(str[0], command1);
        return 1;

    }

}

//Function to ending
int ending(char *str1, char *str_check)
{
    if (strcmp(str1, str_check) == 0)
    {
        return 1;
    }
    else{
        return 0;
    }
}

//Clear memory for string command
void free_mem_command(char **command)
{
    for (int i=0; i<100; i++)
    {
        command[i] = NULL;
    }
}
    

int main()
{
    int c ;
    init();

    while(1)
    {
    printfCurDir();
    takeInput(input);
    c = process_input(input, command1, command2);
    
    if (ending(input, check_ending))
    {
        printf("GOODBYE FROM TUANTNT19 's shell\n");
        break;
    }

    if (c == 1)
    {
        runsinglecommad(command1);
    }
    else{
        rundoublecommand(command1, command2);
    }

    free_mem_command(command1);
    free_mem_command(command2);
}

   return 0;
}