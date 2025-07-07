#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "types.h"
#include "view.h"
#include "edit.h"

int main(int argc, char *argv[])
{
    TagInfo mp3tagInfo;
    TagData mp3tagData;

    if(argc < 2)
    {
        printf("Argument count should be greater than 2\n");
        return FAILURE;
    }
    else
    {
        OperationType res = check_operation (argv);
        if(res == p_view)
        {
            printf("You have selected for view option\n");
            if(read_and_validate_mp3_file (argv, &mp3tagInfo)==SUCCESS)
            {
                printf("Read and validation successfull for view operation\n");
                if(view_tag (argv, &mp3tagInfo)== SUCCESS)
                {
                   printf("View operation done successfully\n");
                   return 0;

                }
                else
                {
                    printf("Failed to view\n");
                    return 0;
                }
            }
            else 
            {
                printf("read and validation of arguments failed\n");
                return 0;
            }

        }
        else if(res == p_edit)
        {
            printf("You have selected for edit option\n");
            if(read_and_validate_mp3_file_args(argv, &mp3tagData)== SUCCESS)
            {
                printf("Read and validation successfull for edit operation\n");
                if(edit_tag (argv, &mp3tagData)== SUCCESS)
                {
                    printf("Edit operation done successfully\n");
                    return 0;
                }
                else
                {
                    printf("Failed to edit\n");
                    return 0;
                }
            }
            else 
            {
                printf("Read and validation of arguments failed\n");
                return 0;
            }


        }
        else if (res == p_help)			//If the return value from the function is to show the Help Menu, display all the details regarding the usage of MP3 Tag Reader & Editor.
        {
            printf ("INFO: Help Menu for Tag Reader and Editor:\n");
            printf ("INFO: For Viewing the Tags -> ./mp3_tag_reader -v <file_name.mp3>\n");
            printf ("INFO: For Editing the Tags -> ./mp3_tag_reader -e <modifier> \"New_Value\" <file_name.mp3>\n");
            printf ("INFO: Modifier Functions:\n");
            printf ("-t\tModify Title Tag\n-A\tModify Artist Tag\n-a\tModify Album Tag\n-y\tModify Year Tag\n-G\tModify Content Type Tag\n-c\tModify Comments Tag\n");
        }
        else if (res == p_unsupported)	//If the return value from the function is other than to perform View/Edit/Help, print an error message.
        {
            printf ("ERROR: Unsupported Operation.\n");
            printf ("INFO: Use \"./mp3_tag_reader --help\" for Help menu.\n");
        }
    }
    
    return 0;
}


/* Check Operation type */
OperationType check_operation (char* argv[])
{
    if(strcmp(argv[1],"-v")==0)
    {
       printf("View option\n");
       return p_view;   
    }
    else if(strcmp(argv[1],"-e")==0)
    {
        printf("Edit option\n");
        return p_edit;
    }
    else if(strcmp(argv[1],"-h")==0)
    {
        printf("help option\n");
        return p_help;
    }
    else if (strncmp (argv [1], "--help", 6) == 0)
    {
        return p_help;
    }
    else
    {
        printf("Edit option\n");
        return p_unsupported;
    }
}