#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "populate.h"

int validate_phone(char *str);
int validate_email(char *str);
int searchbyoption(AddressBook *addressBook, char *value, int option);
void loadContactsFromFile(AddressBook *addressBook);

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization
    loadContactsFromFile(addressBook);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.csv", "r");
    if (file == NULL)
    {
        printf("Failed to open contacts file.\n");
        return;
    }
    char data[4];
    fscanf(file, "%s\n", data);
    data[3] ='\0';
    addressBook->contactCount = atoi(data);
    printf("%d",addressBook->contactCount);
    
    for(int i=0; i<addressBook->contactCount;i++)
    {
        fscanf(file, " %[^,], %[^,], %[^, \n]", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(file);
}

void saveContactsToFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.csv", "w");
    if (file == NULL) {
        printf("Failed to open contacts file.\n");
        return;
    }
    fprintf(file,"%d\n",addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s, %s, %s \n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(file);
}

void listContacts(AddressBook *addressBook) 
{
    // Print header
    printf("%-4s %-20s %-25s %-43s\n", "SI", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------------------\n");

    // Listing all contacts in a single line
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        
        printf("%-4d %-20s %-25s %-43s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address book is full. Cannot add more contacts.\n");
        return;
    }

    Contact new_contact;
    printf("Enter the name: \n");
    scanf(" %[^\n]",new_contact.name);
    getchar();

    printf("Enter the number: \n");
    int valid=0,exists;
    do
    {
        exists = 0;
        scanf(" %[^\n]",new_contact.phone);
        getchar();
        valid= validate_phone(new_contact.phone);
        if(valid)
        {
            printf("Invalid number. Please re-enter the number: \n");
        }

        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].phone,new_contact.phone) == 0)
            {
                exists = 1;
                break;
            }
        }
        
        if(exists)
        {
            printf("Number already exists. Please re-enter the number: \n");
        }
    } while(valid || exists);
    
    printf("Enter the email: \n");
    do
    {
        exists = 0;
        scanf(" %[^\n]",new_contact.email);
        getchar();
        valid = validate_email(new_contact.email);

        if(!valid)
        {
            printf("Invalid email. Please re-enter the email: \n");
        }

        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].email,new_contact.email) == 0)
            {
                exists = 1;
                break;
            }
        }
        
        if(exists)
        {
            printf("Email already exists. Please re-enter the email: \n");
    
        }
    }while(!valid || exists);
    addressBook->contacts[addressBook->contactCount] = new_contact;
    addressBook->contactCount++;
}

void searchContact(AddressBook *addressBook) 
{
    int option;
    do
    {
        printf("Search by:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter the option: \n");
        scanf("%d",&option);
        getchar();
        switch(option)
        {
            case 1:
            {
                char name[50];
                printf("Enter the name: \n");
                scanf("%[^\n]",name);
                int flag = 0;
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strcmp(addressBook->contacts[i].name,name)==0)
                    {
                        printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        flag = 1;
                        break;
                    }
                }
                if(!flag)
                {
                    printf("Contact not found.\n");
                }
                break;
            }

            case 2:
            {
                char phone[50];
                printf("Enter the number: \n");
                scanf("%[^\n]",phone);
                int flag = 0;
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strcmp(addressBook->contacts[i].phone,phone)==0)
                    {
                        printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        flag = 1;
                        break;
                    }
                }
                if(!flag)
                {
                    printf("Contact not found.\n");
                }
                break;
            }

            case 3:
            {
                char email[50];
                printf("Enter the email: \n");
                scanf("%[^\n]",email);
                int flag = 0;
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strcmp(addressBook->contacts[i].email,email)==0)
                    {
                        printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        flag = 1;
                        break;
                    }
                }
                if(!flag)
                {
                    printf("Contact not found.\n");
                }
                break;
            }

            default:
                printf("Invalid option. \n");
        }
    } while(option < 1 || option >3);
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int option;
    char value[50];

    printf("Edit by: \n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter the option: \n");
    scanf("%d",&option);
    getchar();

    switch(option)
    {
        case 1:
            printf("Enter the name: \n");
            scanf(" %[^\n]",value);
            break;

        case 2:
            printf("Enter the number: \n");
            scanf(" %[^\n]",value);
            break;

        case 3:
            printf("Enter the email: \n");
            scanf(" %[^\n]",value);
            break;

        default:
            printf("Invalid option.\n");
            break;
    }

    int index = searchbyoption(addressBook,value,option);

    if(index == -1)
    {
        printf("Contact not found.\n");
        return;
    }

    char name[50];
    if(option == 1) 
    {
        printf("Enter the new name: \n");
        scanf(" %[^\n]",addressBook->contacts[index].name);
        getchar(); 
        printf("Contact edited successfully\n");
    }

    char phone[20];
    if(option == 2) 
    {
        printf("Enter the new number: \n");
        scanf(" %[^\n]",addressBook->contacts[index].phone);
        getchar();  
        printf("Contact edited successfully\n");
    }

    char email[20];
    if(option == 3) 
    {
        printf("Enter the new email: \n");
        scanf(" %[^\n]",addressBook->contacts[index].email);
        getchar(); 
        printf("Contact edited successfully\n"); 
    }
}

int searchbyoption(AddressBook *addressBook, char *value, int option)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if((option == 1 && strcmp(addressBook->contacts[i].name,value) == 0) || (option == 2 && strcmp(addressBook->contacts[i].phone,value) == 0) || (option == 3 && strcmp(addressBook->contacts[i].email,value) == 0))
        {
            return i;
        }
    }
    return -1;
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int option;
    char value[50];

    printf("Delete by: \n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter the option: \n");
    scanf("%d",&option);
    getchar();

    switch(option)
    {
        case 1:
            printf("Enter the name: \n");
            scanf(" %[^\n]",value);
            break;

        case 2:
            printf("Enter the number: \n");
            scanf(" %[^\n]",value);
            break;

        case 3:
            printf("Enter the email: \n");
            scanf(" %[^\n]",value);
            break;

        default:
            printf("Invalid option.\n");
            break;
    }

    int index = searchbyoption(addressBook,value,option);
    
    if(index == -1)
    {
        printf("Contact not found.\n");
        return;
    } 
    
    for(int i = index; i < addressBook->contactCount-1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("Contact Deleted successfully\n");
}

int validate_phone(char *str)
{
    int count = 0;
    int len = strlen(str);
    for(int i=0;i<len;i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            count ++;
        }
    }
   
    if(count == 10)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int validate_email(char *str)
{
    int len=strlen(str);
    const char*check_at=strchr(str,'@');
    if(check_at == NULL)
    {
        return 0;
    }
    if(check_at == str)
    {
        return 0;
    }
    const char *dotcom = strstr(check_at,".com");
    if(dotcom == NULL || dotcom <= check_at)
    {
        return 0;
    }
    
    for(int i=0;i<len;i++)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
        {
            return 0;
        }
    }
    return 1;
}
