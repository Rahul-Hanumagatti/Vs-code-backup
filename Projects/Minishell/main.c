#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<unistd.h>
#include"main.h"


int main()
{
    system("clear");  // system call to clear the terminal
    //char prompt[80] = "rahulhh@Rahul-H-Hanumagatti:~/LI/Projects/minishell$";  // new username
    char prompt[20] = "minishell$";
    char input_string[20]; // commands that we enter

    scan_input(prompt, input_string);  // function call to read the input from user

    return 0;
}