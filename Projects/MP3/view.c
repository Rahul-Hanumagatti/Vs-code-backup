#include "view.h"
#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Perform Validation of the Arguments passed and store in the Structure */
Status read_and_validate_mp3_file (char* argv[], TagInfo* mp3tagInfo)
{
    if(argv[2] == NULL)
    {
        printf("File name not available\n");
        return FAILURE;
    }

    char *dot = strstr(argv[2],".");
    if(strcmp(dot,".mp3") == 0)
    {
        printf("Entered file is %s\n",argv[2]);

        // opening the file in read mode to validate the version of the file
        mp3tagInfo->fptr_mp3 = fopen(argv[2],"r");
        if(mp3tagInfo->fptr_mp3 != NULL)
        {
            char id[3];
            fread(id,3,1,mp3tagInfo->fptr_mp3);
            if(strcmp(id,"ID3") == 0)
            {
                printf ("     Version ID: v2.3     \n");
                printf ("--------------------------\n");
            }
            else
            {
                printf ("ERROR: The file Signature is not matching with that of a '.mp3' file.\n");
                printf ("INFO: For Viewing the Tags -> ./mp3_tag_reader -v <file_name.mp3>\n");
                return FAILURE;
            }
        }
        else
        {
            printf("Failed to open file %s\n",argv[2]);
            printf ("INFO: For Viewing the Tags -> ./mp3_tag_reader -v <file_name.mp3>\n");
            return FAILURE;
        }

        fclose(mp3tagInfo->fptr_mp3);
    }
    else
    {
        printf("Entered file is %s not a .mp3 file\n",argv[2]);
        return FAILURE;
    }

    return SUCCESS;


}



/* Perform the Viewing Tag details Operation */
Status view_tag (char* argv[], TagInfo* mp3tagInfo)
{
    mp3tagInfo->fptr_mp3 = fopen(argv[2],"r");
    if(mp3tagInfo->fptr_mp3 == NULL)
    {
        printf("Failed to open %s\n",argv[2]);
        return FAILURE;
    }
    fseek(mp3tagInfo->fptr_mp3,10,SEEK_SET); // skipping 1st 10 bytes of header
    
    
	//Function call with the necessary parameters to display the Information about Title tag.
    if(get_and_display_data ("Title: ", "TIT2", mp3tagInfo->frame_Id, &mp3tagInfo->title_tag_size, mp3tagInfo->title_tag, mp3tagInfo->fptr_mp3) == FAILURE)
    {
        //If the function doesn't display the data successfully, the process of Displaying will terminate.
        printf ("ERROR: Title Frame ID Contents cannot be displayed.\n");
        return FAILURE;
    }
    
	//Function call with the necessary parameters to display the Information about Artist tag.
    if(get_and_display_data ("Artist: ", "TPE1", mp3tagInfo->frame_Id, &mp3tagInfo->artist_tag_size, mp3tagInfo->artist_tag, mp3tagInfo->fptr_mp3)== FAILURE)
    {
        //If the function doesn't display the data successfully, the process of Displaying will terminate.
        printf ("ERROR: Artist Frame ID Contents cannot be displayed.\n");
        return FAILURE;
    }

	//Function call with the necessary parameters to display the Information about Album tag.
    if(get_and_display_data ("Album: ", "TALB", mp3tagInfo->frame_Id, &mp3tagInfo->album_tag_size, mp3tagInfo->album_tag, mp3tagInfo->fptr_mp3) == FAILURE)
    {
        //If the function doesn't display the data successfully, the process of Displaying will terminate.
        printf ("ERROR: Album Frame ID Contents cannot be displayed.\n");
        return FAILURE;

    }

	//Function call with the necessary parameters to display the Information about Year tag.
    if(get_and_display_data ("Year: ", "TYER", mp3tagInfo->frame_Id, &mp3tagInfo->year_size, mp3tagInfo->year, mp3tagInfo->fptr_mp3)== FAILURE)
    {
        //If the function doesn't display the data successfully, the process of Displaying will terminate.
        printf ("ERROR: Year Frame ID Contents cannot be displayed.\n");
        return FAILURE;
    }

	//Function call with the necessary parameters to display the Information about Content tag.
    if(get_and_display_data ("Content: ", "TCON", mp3tagInfo->frame_Id, &mp3tagInfo->content_type_size, mp3tagInfo->content_type, mp3tagInfo->fptr_mp3)== FAILURE)
    {
        //If the function doesn't display the data successfully, the process of Displaying will terminate.
        printf ("ERROR: Content Type Frame ID Contents cannot be displayed.\n");
        return FAILURE;
    }

	//Function call with the necessary parameters to display the Information about Comments tag.
    if(get_and_display_data ("Comments: ", "COMM", mp3tagInfo->frame_Id, &mp3tagInfo->comment_size, mp3tagInfo->comments, mp3tagInfo->fptr_mp3) == FAILURE)
    {
        //If the function doesn't display the data successfully, the process of Displaying will terminate.
        printf ("ERROR: Content Type Frame ID Contents cannot be displayed.\n");
        return FAILURE;
    }

    printf ("--------------------------\n");
    fclose (mp3tagInfo->fptr_mp3);				//To close the Source MP3 file.

    //No FAILURE returned above, then return SUCCESS.
    return SUCCESS;

}

/* Common function to display the various Frame contents of the MP3 file */
Status get_and_display_data (const char* str_frame, const char* str_Id, char* frame_Id, uint* tag_size, char* tag, FILE* fptr)
{
    //printf ("MP3 position = %ld.\n", ftell (fptr));
    int count;
    count = fread(frame_Id,4,1,fptr); // reading 4 bytes of title id

    if(count<1)    // for validation
    {
        printf("hi\n");
        printf ("ERROR: Unable to read from the MP3 file.\n");
        return FAILURE;
    }
    else
    {
        if(strcmp(frame_Id,str_Id) == 0)   // comparing title id with given str_Id 
        {
            count = fread(tag_size,4,1,fptr); // next reading 4 bytes of size and storing in tag_size
            if(count < 1) // validation
            {
                printf("hello\n");
                printf ("ERROR: Unable to read from the MP3 file.\n");
                return FAILURE;
            }
            else
            {
                // Reversing of bytes of size because , it is stored in the form of big endian to little endian to get exact size 
                
                char *pos = (char *)tag_size; // typecasting tag_size to 1 byte for reversal
                for(int i=0;i<((sizeof(uint)) / 2);i++) // swapping using bitwise method
                {
                    pos[i] = pos[i] ^ pos[(sizeof(uint)) - i - 1];
                    pos[(sizeof(uint)) - i - 1] = pos[i] ^ pos[(sizeof(uint)) - i - 1];
                    pos[i] = pos[i] ^ pos[(sizeof(uint)) - i - 1];
                }

                //printf("Size of %s is %ls\n",frame_Id,tag_size);

                tag = (char *)malloc ((*tag_size) * (sizeof(char))); // *tag_size contains total bytes of that particular id's info with extra byte for '\0'

                fseek(fptr,3,SEEK_CUR); // to skip 3 bytes of flag

                count = fread(tag,1,(*tag_size - 1),fptr); // reading the tag i.e, size of *tag_size -1 times byte by byte and storing it in tag
                if(count < (*tag_size - 1)) // validation
                {
                    printf("hihello\n");
                    printf ("ERROR: Unable to read from the MP3 file.\n");
                    return FAILURE;
                }
                else
                {
                    tag[*tag_size - 1] = '\0';						//To end the Frame ID content with '\0' as last character.
                    //printf ("End: %ld.\n", ftell (fptr));
                    printf ("%-10s%s.\n", str_frame, tag);			//To display the Frame ID Contents.
                }




            }
        }
        else		//If the Frame ID extracted from '.mp3' file doesn't matches with the desired Frame ID, the process of Displaying shall terminate.
        {
            printf ("ERROR: %s Frame ID not found.\n", str_Id);
            return FAILURE;
        }

      free (tag);			//To free the memory allocated to the Frame ID content.
      tag = NULL;			//To prevent the 'tag' from becoming a dangling pointer.

      return SUCCESS;
    }
}