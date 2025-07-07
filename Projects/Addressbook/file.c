#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr;
    fptr = fopen("contacts.csv","w");

    if(fptr==NULL)
    {
        printf("failed to open file\n");
        return;
    }
    fprintf(fptr,"#%d\n",addressBook->contactCount); // printing the contactCount 1st
       
    
    int i=0;
    for(i=0;i<addressBook->contactCount;i++) // running loop till contactCount 
    {
        // printing to file
       fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
       printf("\n");
    }

    fclose(fptr);
    printf("Contacts saved to file successfully\n");
    
  
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contacts.csv","r"); // opening the file in reading mode
    if(fptr==NULL)
    {
        printf("failed to open file\n");
        return;
    }
    // scaning from the file (reading)

    fscanf(fptr,"#%d\n",&(addressBook->contactCount)); // reading the contactCount first
    
    for(int i=0;i<addressBook->contactCount;i++) // running loop till contactCount
    {
        fscanf(fptr,"%49[^,],%19[^,],%49[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fptr);
    printf("Contacts loaded from file successfully\n");

}
