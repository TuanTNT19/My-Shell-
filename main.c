

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

int main()
{
    init();
    takeInput(input);
 
    return 0;
}
