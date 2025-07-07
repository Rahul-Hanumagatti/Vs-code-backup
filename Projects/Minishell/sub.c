#include<stdio.h>
#include<string.h>
#include"main.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

char *external_commands[200]; // array of pointeres to store the external commands
int childf =0; // flag to check child is present or not
int status;

int childpid;
char command[20]; // array to hold the 1st word's address

Slist *head = NULL;  // head to store the linked list of childs

char ip[20];
void scan_input(char *prompt, char *input_string)
{
    extract_external_commands(external_commands);  // function call to store the external commands from .txt file to external_commands[] 2d array
    
    // registering the signal SIGINT , SIGTSTP. // registering signal before the while loop to avoid registering again and again inside loop
    signal(SIGINT,my_handler);   // ctrl+c , to terminate the process
    signal(SIGTSTP,my_handler);   // ctrl +z , to stop the process again we can start
    signal(SIGCHLD, own_handler);  // in bg(), child will become zombie, so the SIGCHLD signal will be generated, to clear that 
    // if these signals occurs in the starting itself, i.e, minishell$ , it will print minishell$ again and again

    while(1)  // infinite loop to make it work like a shell to take input from user continously
    {
        printf("%s ",prompt); // printing the minishell prompt
        scanf(" %[^\n]",input_string); // reading the commands from user
        //if input string is ^C or ^Z again the minishell$ will print instead of terminating or stopping the porcess
        getchar();
        strcpy(ip,input_string);   
        char ps1[4]= "PS1=";  // command to change the user name
        if(strlen(input_string) == 0)
             continue;
        else if(strstr(input_string,ps1)!=NULL)  // if the input string contains the username changing command
        {
            if(strchr(input_string,' ') == NULL)   // if no space is availabe means it is a environmental vaiable to change the user name
            {
                int i=4, j=0; 
                while(input_string[i] != '\0')  // staring from position 4 i.e, leaving ps1=
                {
                    prompt[j] = input_string[i];  // copying to prompt
                    i++;
                    j++;
                }
                //printf("Prompt is %s\n",prompt);

                prompt[j] = '\0'; // ending the string with null

            }
            else   //  if space is available in the input string means it is normal command
            {
               printf("not a command\n");

            }

        }
        else  // if the input_string contains command to execute
        {
            char *mod = get_command(input_string); // to get the first word to check whether it is an external command or builtin command
            //printf("command is %s\n",mod);
            int res = check_command_type(command); // function call to check whether the entered command is builtin or external or not a command
             if(res == BUILTIN)
             {
                //printf("Command %s is BUILTIN\n",command);
                execute_internal_commands(input_string); // function call to execute internal commands
             }   
             else if(res == EXTERNAL)
             {
                //printf("Command %s is EXTERNAL\n",command);
                pid_t pid = fork(); // system call to create the process
                childf =1; // setting childf when its created
                childpid = pid;  // copying pid to childpid to use in other function
                if(pid >0)   // parent
                {
                    
                    waitpid(pid,&status,WUNTRACED); // waiting for child to terminate , WUNTRACED if child stops also it returns where wait only returns if child terminates
                    childf =0;  // resetting child after its termination
                }
                else if(pid ==0)  // child
                {
                    // re- registering the signal in child to do its original task 
                    signal(SIGINT,SIG_DFL);   // ctrl+c , to terminate the process
                    signal(SIGTSTP,SIG_DFL);   // ctrl +z , to stop the process again we can start
                    // if these signals occur inside the function means it should to the original task
                    execute_external_commands(input_string);  // to execute external commands
                    exit(0);  // ensures that child process exits after command execution to prevent unintended continuation
                }
             }   
             else
               printf("Command %s is not a command\n",command);


        }

        memset(input_string,0,strlen(input_string)); // filling input_string with 0's to avoid filling garbage values
    }
}

//extern char prompt[];

char *get_command(char *input_string)
{
    strcpy(command,input_string); // copying the string
    int i=0;

    while(command[i] !='\0')
    {
        if(command[i] ==' ')
           break;
        
           i++;
    }

    command[i] ='\0';  // 1st word

    return command;

}

void extract_external_commands(char **external_commands)
{
    int fd = open("external_commands.txt",O_RDONLY); // opening the external_commands.txt file in read mode
    if(fd == -1)  // verifying the file
    {
        printf("Not able to open file\n");
        return;
    }
    char buf[20] , ch=0;
    int i=0,j=0;

    while(read(fd,&ch,1) >0)  // reading byte by byte till EOF
    {
        if(ch == '\n')  // if new line means
        {
            buf[i] = '\0';  // making that as '\0' to end the string
           
            external_commands[j] = malloc(strlen(buf)+1); // allocating memory for columns
            strcpy(external_commands[j],buf); // copying
            //printf("%d, %s\n",j,external_commands[j]);
            j++; 
            i=0; // resetting i to 0
            continue;  // skipping that iteration
        }

        buf[i++] = ch; // storing into buffer

    }

    if(i>0)   // EOF i.e, i will not be 0 because after reading till \n at last i will be incremented
    {
        
        buf[i] = '\0';  // making that as '\0' to end the string
        external_commands[j] = malloc(strlen(buf)+1); // allocating memory for columns
        strcpy(external_commands[j],buf); // copying
        //printf("%d,%s\n",j,external_commands[j]);
       return ;
    }

    close(fd); // closing the file

}

int check_command_type(char *command)
{
    char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval","set", 
        "unset", "export", "declare", "typeset", "readonly", "getopts", "source","exit", "exec", "shopt", 
        "caller", "true", "type", "hash", "bind", "help", "jobs", "fg", "bg", NULL};

    int res=0;
    for(int i=0;i<30;i++)  // checking through builtins
    {
        if(strcmp(builtins[i],command) == 0)
           return BUILTIN;
    }
 
    for(int i=0;i<152;i++)  // checking through externals
    {
        if(strcmp(external_commands[i],command) == 0)
           return EXTERNAL;
    }

    return NO_COMMAND; // default if the command is not valid
}


void execute_internal_commands(char *input_string)
{
    if(strcmp(input_string,"exit") ==0)  // exit(0), exiting from the program
    {
        printf("Exiting from the program\n");
        exit(0);
    }
    else if(strcmp(input_string,"pwd")==0)   // pwd , preset working directory
    {
        char buf[100]; // buffer to store the pwd
        getcwd(buf,sizeof(buf)); // pwd path will be stored in buf
        printf("%s\n",buf);
    }
    else if (strncmp(input_string, "cd", 2) == 0) // If input starts with "cd"
    {
        // Find the first space after "cd"
        char *ptr = strstr(input_string, " ");
    
        // If there is an argument (i.e., a space after "cd")
        if (ptr != NULL)
        {
            // Skip all spaces
            while (*ptr == ' ')
                ptr++;
    
            // If only spaces after "cd", treat as no argument
            if (*ptr == '\0')
            {
                chdir(getenv("HOME")); // No path given, go to HOME
            }
            else
            {
                // Try to change to specified directory
                if (chdir(ptr) != 0)
                {
                    perror("chdir"); // Print error if directory change fails
                }
            }
        }
        else
        {
            // No space found => just "cd", go to HOME
            chdir(getenv("HOME"));
        }
    }
    else if(strcmp(input_string,"echo $$")==0) // echo$$ , printing the pid of this process i.e, ./a.out
    {
          printf("%d\n",getpid());  // getting pid of this process
    }
    else if(strcmp(input_string,"echo $")==0)  //printing the exit status of this previous/last process
    {
        printf("%d\n", WEXITSTATUS(status));  // exit status of last terminated process
    }
    else if(strcmp(input_string,"echo $SHELL")==0)  // to print the path of the shell
    {
        printf("%s\n",getenv("SHELL"));  // printing the path of shell
    }
    else if(strcmp(input_string,"jobs")==0)  // to print the list of stopped process
    {
        print_list();  // printing the stopped process
    }
    else if(strcmp(input_string,"fg")==0)  // resume the last stopped process in foreground wiht some delay
    {
        fg(); // continue the last stopped process in foreground , with little delay
    }
    else if(strcmp(input_string,"bg")==0)  // resume the last stopped process in background immedieatly
    {
        bg();    // continue the last stopped process in background immedieatly
    }
}

void print_list()
{
    if (head == NULL)
    {
        //printf("No Stopped Processes\n");
        return;
    }
    else
    {
        Slist *temp = head;  // temp to traverse the list

        while (temp)		
        {
            printf("pid -> %d, ", temp->pid);
            printf("process ->%s", temp->ips);
            temp = temp->link;
            printf("\n");
        }

       // printf("NULL\n");
    }
}


void fg()
{
    Slist *temp = head;
    Slist *prev = NULL;

    if(head == NULL)
    {
        //printf("No\n");
        return ;
    }
    else
    {
        while(temp ->link != NULL)
        {
            prev = temp;
            temp = temp->link;
        }

       
        kill(temp->pid,SIGCONT); // continue the last stopped process , i.e, delete at last process in single linked list

        childpid = temp->pid;
        waitpid(childpid, &status, WUNTRACED);  // wait after resuming


      if(prev == NULL) // if only one process
         head = NULL;
      else
         prev->link = NULL;

         free(temp);

    }
    
}


void bg()
{
    Slist *temp = head;
    Slist *prev = NULL;

    if(head == NULL)
    {
       // printf("No\n");
        return ;
    }
    else
    {
        while(temp ->link != NULL)
        {
            prev = temp;
            temp = temp->link;
        }

        kill(temp->pid,SIGCONT); // continue the last stopped process

        //signal(SIGCHLD,SIG_DFL);
       // childpid = temp->pid;
        // waitpid(childpid, &status, WUNTRACED);  // wait after resuming

    //   if(prev == NULL)
    //      head = NULL;
    //   else
    //      prev->link = NULL;

    //      free(temp);
    }    
}


void execute_external_commands(char *input_string)
{
     // we have to convert the input_string to 2d array because , execvp accepts 2d array
      char *buf[20]; // array of pointers
      char str[10]; // to store single command
      int i=0, j=0, k=0;
      while(input_string[i] !='\0')
      {
            if(input_string[i] == ' ')  // if space means i.e 1 command
            {
                str[j] ='\0'; // terminating that with '\0
                buf[k] = malloc(strlen(str)+1);
                strcpy(buf[k],str); // copying each string to buf
                k++;
                i++; // incrementing i to skip this iteration to next character in input string
                j=0; // to again start the str from 0
                continue; // skipping that iteration
            }
            else
            {
                str[j++] = input_string[i++];  // copying each character to str from input_string
    
            }
                                
                                
      }
    
        // because of last word's last character 
        str[j] ='\0';
        buf[k] = malloc(strlen(str)+1);
        strcpy(buf[k++],str); // copying each string to buf
    
    
        buf[k] =NULL;   // ending the 2d array with NULL

    int pipe_count =0;
    for(int i=0;buf[i] != NULL;i++)
    {
        if(strcmp(buf[i], "|")==0)  // if pipe is present in the input string
        {
             pipe_count++;   // taking the count of the pipe
        }
    }

    if(pipe_count !=0)  // multipipe implementation
    {
          n_pipe(buf, pipe_count);   // function call to execute n pipe by passing 2d array
    }
    else if(pipe_count == 0)  // normal execution of commands using execvp
    {
        execvp(buf[0],buf);  // executing external commands without pipe
    }
    
    
}


void n_pipe(char *buf[], int pipe_count)
{
    int index[pipe_count + 2];  // to store starting index of each command
    int j = 1; // start from 1 to handle 0 separately

    int ip = dup(0); // backup stdin
    int op = dup(1); // backup stdout

    index[0] = 0; // first command starts from 0

    for (int i = 0; buf[i] != NULL; i++)
    {
        if (strcmp(buf[i], "|") == 0)
        {
            buf[i] = NULL;     // break arguments
            index[j++] = i + 1; // next command starts after '|'
        }
    }

    int in = ip; // input fd
    int fd[2];  // fd to store the pipe

    for (int i = 0; i <= pipe_count; i++)
    {
        if (i < pipe_count)  // checking if the last command or not
        {
            if (pipe(fd) == -1)  // creating the pipe
            {
                perror("pipe");
                return;
            }
        }

        pid_t pid = fork();  // creating child process

        if (pid == 0) // child
        {
            dup2(in, 0); // set stdin
            if (i < pipe_count)
            {
                close(fd[0]);  // close read end
                dup2(fd[1], 1); // set stdout to write end
            }

            //printf("Command %s is EXTERNAL\n", buf[index[i]]); // your printf

            execvp(buf[index[i]], buf + index[i]);  // executing the commands till NULL
            perror("execvp");  // it will no print if the command is correct
            exit(1);
        }
        else if (pid > 0) // parent
        {
            if (in != ip)
                close(in); // close previous read end
            if (i < pipe_count)
            {
                close(fd[1]); // close write end
                in = fd[0];   // next input is read end
            }
        }
        else
        {
            perror("fork");
            return;
        }
    }

    // Only parent comes here after all forks
    for (int i = 0; i <= pipe_count; i++)  // clearing the resources of the childs
        wait(NULL);

    dup2(ip, 0); // restore stdin
    dup2(op, 1); // restore stdout
    close(ip);
    close(op);
}

char prompt[20] = "minishell"; 
//char prompt[20] = "minishell$";  // new username

void own_handler(int signum)
{
    // Use waitpid with -1 to handle any child process that exited
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)  // waiting till the process get complete
    {
        // Now remove the node with this pid from the job list
        Slist *temp = head;
        Slist *prev = NULL;

        while (temp != NULL) // removing the process from jobs list after it completes it task
        {
            if (temp->pid == pid)
            {
                if (prev == NULL)
                    head = temp->link;
                else
                   prev->link = temp->link;

                free(temp);
                break;
            }

            prev = temp;
            temp = temp->link;
        }
    }
}

void my_handler(int signum)
{
    if(signum == SIGINT)
    {
        if(childf) // child present means , skipping the printing of prompt, because it will print to times here 1, and in while(1) 2 time
        { 
            
        }
        else  // simply printing the prompt , if child not present means
          printf("%s \n",prompt);
    }
    else if(signum == SIGTSTP)
    {
        if(childf) // child present means
        {
             if(head == NULL)  // if list dont have nodes i.e, list is empty
             {
                Slist *newnode = malloc(sizeof(Slist));  // creation of newnode
                if(newnode == NULL)
                {
                    printf("Memory not allocated\n");
                    return;
                }
                newnode->pid = childpid;
                strcpy(newnode->ips,ip);
                newnode->link = NULL;

                head = newnode;
             }
             else
             {
                Slist *newnode = malloc(sizeof(Slist));  // creation of newnode
                if(newnode == NULL)
                {
                    printf("Memory not allocated\n");
                    return;
                }
                newnode->pid = childpid;
                strcpy(newnode->ips,ip);
                newnode->link = NULL;

                Slist *temp = head;
                while(temp->link != NULL)  // inserting at last 
                {
                    temp = temp->link;
                }
                temp->link = newnode;
             }
          
               

        }
        else
          printf("%s \n",prompt);

    }
}