#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

// function declarations for validation part
int validate_name(char *name);
int validate_phone(char *mobile);
int validate_email(char *email_id);

// function declaration to check wheather same name, mobile or email is already present in contacts or not
int isduplicate(AddressBook *addressBook,char name[], char phone[], char email[]);

// function declarations for searching part
int search_name(char *name,AddressBook *addressBook);
int search_phone(char *mobile,AddressBook *addressBook);
int search_email(char *email,AddressBook *addressBook);


int isduplicate(AddressBook *addressBook,char name[], char phone[], char email[])
{
  for(int i=0; i<addressBook->contactCount;i++)
  {
    if ((strcmp(addressBook->contacts[i].name, name) == 0) ||
        (strcmp(addressBook->contacts[i].phone, phone) == 0) ||
        (strcmp(addressBook->contacts[i].email, email) == 0))
    {
      return 1; // Duplicate found
    }
  }
  return 0; // No duplicate
}

int search_name(char *name,AddressBook *addressBook)
{   

    int i ,flag=0;  
    for(i=0;i<addressBook->contactCount;i++)
    {  
        if(strcmp(addressBook->contacts[i].name,name)==0)
        {
             printf("Contact Details are:\n");
             printf("Name:%s\n",addressBook->contacts[i].name);
             printf("Phone:%s\n",addressBook->contacts[i].phone);
             printf("Email:%s\n",addressBook->contacts[i].email);
             flag=1;
             break;
        }
        else 
            flag=0;
    }

    return flag;
        // if(!flag)
        //   printf("Contact not found\n");
    
}

int search_phone(char *mobile,AddressBook *addressBook)
{
    int i, flag=0;
    //char mobile[20];
        // printf("Enter mobile:\n");
        // scanf(" %[^\n]",mobile);
        for(i=0;i<addressBook->contactCount;i++)
        {
            //printf("%s %s\n",addressBook->contacts[i].phone,mobile);
           if(strcmp(addressBook->contacts[i].phone,mobile)==0)
            {
               printf("Contact Details are:\n");
               printf("Name:%s\n",addressBook->contacts[i].name);
               printf("Phone:%s\n",addressBook->contacts[i].phone);
               printf("Email:%s\n",addressBook->contacts[i].email);
               flag=1;
               break;
            }
            else
             flag=0;
        }
        return flag;

        // if(!flag)
        //  printf("Contact not found\n");
           

}

int search_email(char *email_id,AddressBook *addressBook)
{
    int i, flag=0;
    //char email_id[50];
   // printf("Enter email:\n");
        // scanf(" %[^\n]",email_id);
        for(i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].email,email_id)==0)
            {
             printf("Contact Details are:\n");
             printf("%s\n",addressBook->contacts[i].name);
             printf("%s\n",addressBook->contacts[i].phone);
             printf("%s\n",addressBook->contacts[i].email);
             flag=1;
             break;
            }
            else 
             flag=0;
          
        }

        return flag;

    //  if(!flag)
    //    printf("Contact not found\n");
    
          
}

int validate_name(char *name)
{
    int flag, i=0;
    while(name[i]!='\0')
    {
        flag =0;
        if(((name[i]>=65 && name[i]<=90) || (name[i]>=97 && name[i]<=122) || name[i]==' ' || name[i]=='.'))
        {
            flag=1;
            i++;
        }
        else
        {
            flag=0;
             break;

        }
   
    }
    return flag;
}

int validate_phone(char *mobile)
{
    int i=0, flag;
    while(mobile[i]!='\0')
    {
        flag=0;
        if((mobile[i]>=48 && mobile[i]<=57) && (strlen(mobile)==10))
        {
           flag=1;
           i++;
        }
        else
        {
            flag=0;
            break;
        }
     
          
    }
   return flag;
}

int validate_email(char *email_id)
{
    int i=0, flag=0;
    char *ret, *ret1;
    char com[5] = ".com";
    char at[5] = "@";

    ret = strstr(email_id,at); // returns the address of @ in email_id
    if(ret!=NULL) // if not null, i.e, contains some address
    {
        ret1 = strstr(ret,com); // returns the address of .com from ret 
        if(ret1!= NULL && strcmp(ret1,com)==0) // if ret is not null and comparision of ret1 and .com is 0
        {
            flag =1; // raise a flag
        }
        
    }
    else
    {
         flag = 0;
    }
    
   
   return flag;
}

void listContacts(AddressBook *addressBook) 
{
    int i=0;
    for(i=0;i<addressBook->contactCount;i++)
    {
        printf("%d ",i+1);
        printf("Name: %s   ",addressBook->contacts[i].name);
        printf("Mobile: %s   ",addressBook->contacts[i].phone);
        printf("Email: %s\n",addressBook->contacts[i].email);
        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("\n");
    }
    
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook); 
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{

    char name[50];
    char mobile_no[20];
    char email_id[50];
    int isvalid, isdupli;

    do
    {
        printf("Enter Name of the contact:\n");
        scanf(" %[^\n]",name);
        getchar();
        //printf("%d\n",validate_name(name));
        isdupli = isduplicate(addressBook, name, "",""); // function call to check if the enterd name is already exist in addressbook or not
        // passing only name to check for duplicate
        if(isdupli==1)
        {
            printf("Duplicate name found. Please re-enter.\n");
            // re- entering new non duplicate name
            printf("Enter Name of the contact:\n");
            scanf(" %[^\n]",name);
            getchar();
           //break; 
        }
        isvalid = validate_name(name); // function call to validate name, returns 1 on valid or 0 if name is not valid
         
        if(isvalid==0) // 0 means invalid
          printf("Invalid Name\n");
    } while(isvalid==0); // repeats untill isvalid is not equal to 0
      // if isvalid becomes 1, exits the loop and copies the name to that particular name's index
      strcpy(addressBook->contacts[addressBook->contactCount].name,name);

    do
    {
        printf("Enter Mobile number:\n");
        scanf(" %[^\n]",mobile_no);
        getchar();
        isdupli = isduplicate(addressBook, "",mobile_no,"");
        if(isdupli==1)
        {
            printf("Duplicate mobile found. Please re-enter.\n");
            // re- entering new non duplicate mobile no
            printf("Enter mobile number:\n");
            scanf(" %[^\n]",mobile_no);
            getchar();
           //break; 
        }
        isvalid = validate_phone(mobile_no); // function call to validate mobile, returns 1 on valid or 0 if mobile in invalid
        if(isvalid==0)
        {
            printf("Invalid Mobile\n");
        }  // 0 means invalid
         
    } while(isvalid==0); // repeats untill isvalid is not equal to 0
     // if isvalid becomes 1, comes out of the loop and copies the mobile_no to that particular phone's index
      strcpy(addressBook->contacts[addressBook->contactCount].phone,mobile_no);
    
    do
    {
        printf("Enter email_id:\n");
        scanf(" %[^\n]",email_id);
        getchar();
        isdupli = isduplicate(addressBook, "","",email_id);
        if(isdupli==1)
        {
            printf("Duplicate email found. Please re-enter.\n");
            // re- entering new non duplicate email-id
            printf("Enter email_id:\n");
            scanf(" %[^\n]",email_id);
            getchar();
           //break; 
        }
        isvalid = validate_email(email_id); // function call to validate email_id, returns 1 on valid or 0 if email is invalid
        if(isvalid==0) // if 0 means invalid email_id
        {
            // if(isdupli==0)
            //  printf("Duplicate of this email-id is found, Please enter new one\n");
           printf("Invalid Email\n");
        }
         
    } while(isvalid==0); // repeats untill isvalid is not equal to 0
     // if isvalid becomes 1, comes out of the loop and copies email_id to that particular email's index
       strcpy(addressBook->contacts[addressBook->contactCount].email,email_id);

    addressBook->contactCount++; // increementing contactcount to store next contact
    printf("Contact created successfully\n");
    
}

void searchContact(AddressBook *addressBook) 
{
    while(1) // loop repeats infinitely until user inputs exit condition i.e, choice 4
    {
       int i, choice;
       printf("1.Search by Name\n2.Search by mobile\n3.Search by email\n4.Exit\nPlease enter choice\n");
       scanf("%d",&choice);
    
      if(choice ==1) // 1 means search by name
      {
        char name[50];
        printf("Enter name:\n");
        scanf(" %[^\n]",name);
        getchar();
        int res = search_name(name,addressBook); // function call
        if(res==0)
         printf("Contact not found by this name\n");
          
      }
      else if(choice==2) // 2 means search by mobile
      {
        char mobile[20];
        printf("Enter mobile:\n");
        scanf(" %[^\n]",mobile);
        getchar(); 
        int res = search_phone(mobile,addressBook);
        if(res==0)
         printf("Contact not found by this phone number\n");
       
      }
      else if(choice==3) // 3 means search by email
      {
        char email[50];
        printf("Enter email\n");
        scanf(" %[^\n]",email);
        getchar();
       int res = search_email(email,addressBook);
       if(res==0)
        printf("Contact not found by this email id\n");
      } 

      else if(choice==4) // 4 means exit, the loop 
      {
        printf("Exit\n");
        break;
      }
      else
       printf("Enter valid choice\n"); 
    }
    
    
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    char name[50];
    char mobile[20];
    char email[50];

    // new values
    char new_name[50];
    char new_mobile[20];
    char new_email[50];
    int i, choice;
    
    printf("1.Edit Name\n2.Edit mobile\n3.Edit email\nEnter your choice:\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        printf("Enter name:\n");
        scanf(" %[^\n]",name);
        getchar();
        int res =  search_name(name,addressBook);// function call, print the details if the name is present
        if(res==1)
        {
          printf("Enter new_name:\n");
          scanf(" %[^\n]",new_name);
          getchar();
          if(validate_name(new_name)==1)
          {
            int flag=0;
            for(i=0;i<addressBook->contactCount;i++)
            {
              if(strcmp(addressBook->contacts[i].name,name)==0)
              {
                 strcpy(addressBook->contacts[i].name,new_name); // fills that index's name with new_name
                 printf("\n");
                 printf("Name edited successfully\n");
                 flag=1;
                  break;
              }
            
            }
            // if(!flag)
            //  printf("Contact not found\n");
          }
          else
          {
            printf("Invalid new_name");
          }
        
        }
        else
         printf("Contact not found by this name\n");
    }

    else if(choice==2)
    {
         printf("Enter mobile:\n");
         scanf(" %[^\n]",mobile);
         getchar();
         int res = search_phone(mobile,addressBook);
         if(res==1)
         {
            printf("Enter new mobile:\n");
            scanf(" %[^\n]",new_mobile);
            getchar();
           if(validate_phone(new_mobile)==1)
           {
             int flag=0;
             for(i=0;i<addressBook->contactCount;i++)
             {
               if(strcmp(addressBook->contacts[i].phone,mobile)==0)
               {
                strcpy(addressBook->contacts[i].phone,new_mobile); // fills that index's name with new_name
                printf("\n");
                printf("Mobile edited successfully\n");
                flag=1;
                break;
               }
               
             }
            //  if(!flag)
            //   printf("Contact not found\n");
           }
           else
           {
            printf("Invalid new_mobile");
           }

         }
         else
          printf("Contact not found by this phone number\n");
            
        
    }

    else if(choice==3)
    {
         printf("Enter email\n");
         scanf(" %[^\n]",email);
         getchar();
         int res = search_email(email,addressBook); // prints the details
         if(res==1)
         {
            printf("Enter new email:\n");
           scanf(" %[^\n]",new_email);
           getchar();
          if(validate_email(new_email)==1)
          {
            int flag=0;
            for(i=0;i<addressBook->contactCount;i++)
            {
              if(strcmp(addressBook->contacts[i].email,email)==0)
              {
                strcpy(addressBook->contacts[i].email,new_email); // fills that index's name with new_name
                printf("\n");
                printf("email edited successfully\n");
                flag=1;
                break;
              }
             
            }
            // if(!flag)
            //   printf("Contact not found\n");
          }
          else
          {
           printf("Invalid new_email\n");
          }

         }
         else
          printf("Contact not found by this email-id\n"); 
        
    }
    else
     printf("Invalid choice: Please enter correct choice\n");
          
}
    


void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    char name[50];
    char mobile[20];
    char email[50];
    int i, choice;

    printf("1.Delete Name\n2.Delete mobile\n3.Delete email\n Enter your choice\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        printf("Enter name:\n");
        scanf(" %[^\n]",name);
        getchar();
        int res = search_name(name,addressBook); // function call to search that by name
        if(res==1)
        {
            for(i=0;i<addressBook->contactCount;i++)
            {
              int cmp = strcmp(addressBook->contacts[i].name,name);
              if(cmp==0)
              {
                int j;
                for(j=i;j<addressBook->contactCount;j++)
                {
                   strcpy(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
                   strcpy(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
                   strcpy(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
                }
                printf("Contact Deleted Successfully\n");
                break;
              }
            //   else
            //    printf("name not found\n");
            }
        }
        else
         printf("Contact not found by this name\n");
        

        addressBook->contactCount--;

    }
    else if(choice==2)
    {
        printf("Enter mobile:\n");
        scanf(" %[^\n]",mobile);
        getchar();
        int res = search_phone(mobile,addressBook); // function call to search by mobile
        // printf("Enter mobile to be deleted\n");
        // scanf(" %[^\n]",mobile);
        if(res==1)
        {
            for(i=0;i<addressBook->contactCount;i++)
            {
              int cmp = strcmp(addressBook->contacts[i].phone,mobile);
              if(cmp==0)
              {
                int j;
                for(j=i;j<addressBook->contactCount;j++)
                {
                   strcpy(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
                   strcpy(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
                   strcpy(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
                }
                printf("Contact Deleted Successfully\n");
                break;
              }
            //   else
            //    printf("Contact not found\n");
            }
        }
        else
         printf("Contact not found by this phone number\n");
        
        addressBook->contactCount--;

    }
    else if(choice==3)
    {
        printf("Enter email:\n");
        scanf(" %[^\n]",email);
        getchar();
        int res = search_email(email,addressBook); // function call to search by email
        // printf("Enter email to be deleted\n");
        // scanf(" %[^\n]",email);
        // getchar();
        if(res==1)
        {
            for(i=0;i<addressBook->contactCount;i++)
            {
              int cmp = strcmp(addressBook->contacts[i].email,email);
              if(cmp==0)
              {
                int j;
                for(j=i;j<addressBook->contactCount;j++)
                {
                    strcpy(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
                    strcpy(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
                    strcpy(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
                }
                printf("Contact Deleted Successfully\n");
                break;
              }
            
            }
        }
        else
         printf("Contact not found by that email-id\n");
        addressBook->contactCount--;

    }

   
}
