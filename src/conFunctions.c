/*
 * Michael Dombrovsky
 */

#include "conFunctions.h"


/* 
 * I am choosing to use a different
 * style for my do while loops
 * because it increases readability
 */
 
 
 
 
int isStringANum(char *input, int min, int max, int *num)
{
    int i;

    for(i=0;i<strlen(input);i++)
    {
        if(!isdigit(input[i]))
        {
            return 0;
        }
    }
    
    /*Prevents overflow*/
    if(strlen(input)<=9)
    {
        sscanf(input, "%d", num);
        if((*num)>=min&&(*num)<=max)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        
    }
    else
    {
        return 0;
    }

}
 
 /*
  * Displays a given contact
  * Takes in a number input in string form
  */
int displayContact(cStruct *contacts, dStruct *data, char *buffer[5],int num,int count)
{
    
    
    char *input=NULL;
     
    if(!(num>=1&&num<=count))
    {
        return 0;
    }
    
    printf("Contact #%d\nFirst Name: %s\nLast Name: %s\nCompany Name: %s\nPhone Number: %lu\nEmail: %s\n",num,(data[num-1]).fName,(data[num-1]).lName,(data[num-1]).cName,contacts[num-1].phone_number,(data[num-1]).email);

    do{
        if(input)
        {
            free(input);
            input=NULL;
        }
        input=getLineNotEmpty("Action: ");
    }while(strcmp(input,"R")&&strcmp(input,"E")&&strcmp(input,"D"));
    
    
    /*Go back*/
    if(!strcmp(input,"R"))
    {
        if(input)
        {
            free(input);
            input=NULL;
        }
        
        return 0;
    }
    /*Delete*/
    else if(!strcmp(input,"D"))
    {
        if(input)
        {
            free(input);
            input=NULL;
        }
        
        return 1;
    }
    
    /*Edit*/
    if(input)
    {
        free(input);
        input=NULL;
    }   
    return editContact(contacts,data,buffer,num);   
}

/*
 * Edit a contact, returns a buffer with the data
 */
int editContact(cStruct *contacts, dStruct *data, char *buffer[5], int num)
{
    int i;
    for(i=0;i<5;i++)
    {
        if(buffer[i])
        {
            free(buffer[i]);
            buffer[i]=NULL;
        }
    }
    char *input=NULL;
  
    
    
    printf("Contact #%d\nFirst Name: %s\nLast Name: %s\nCompany Name: %s\n",num,(data[num-1]).fName,(data[num-1]).lName,(data[num-1]).cName);

    /*printf("First Name: ");
    buffer[0]=getLine();
    
    
    printf("Last Name: ");
    buffer[1]=getLine();*/
    
    
    /*If the last name is empty then the company name is required*/
    /*if(strlen(buffer[1])==0)
    {
        buffer[2]=getLineNotEmpty("Company Name: ");
    }
    else
    {
        printf("Company Name: ");
        buffer[2]=getLine();
    }*/    
    
    buffer[3]=getPhone("Phone Number (enter only numbers): ");

    buffer[4]=getEmail("Email: "); 
    
    
    do{
        if(input)
        {
            free(input);
            input=NULL;
        }
        input=getLineNotEmpty("Action: ");
    }while(strcmp(input,"S")&&strcmp(input,"R")&&strcmp(input,"D"));
    
    /*Go back*/
    if(!strcmp(input,"R"))
    {
        if(input)
        {
            free(input);
            input=NULL;
        }

        
        return 0;
    }
    
    /*Delete*/
    else if(!strcmp(input,"D"))
    {
        if(input)
        {
            free(input);
            input=NULL;
        }
        
        return 1;
    }
    
    /*Save*/
    else
    {       
        if(input)
        {
            free(input);
            input=NULL;
        }
        
        return 2; 
    }
    
    
    
}
 
/*
 * Removes a contact
 */
void removeContact(cStruct *contacts, dStruct *data, int num, int count)
{
    int i;
    
    for(i=num-1;i<count;i++)
    {
        free(data[i].fName);
        free(data[i].lName);
        free(data[i].cName);
        free(data[i].email);
        
        /*If not last element*/
        if(count-1!=i)
        {
            contacts[i].phone_number=contacts[i+1].phone_number;
            
            data[i].fName=malloc(strlen(data[i+1].fName)+1);
            strcpy(data[i].fName,data[i+1].fName);
            
            data[i].lName=malloc(strlen(data[i+1].lName)+1);
            strcpy(data[i].lName,data[i+1].lName);
            
            data[i].cName=malloc(strlen(data[i+1].cName)+1);
            strcpy(data[i].cName,data[i+1].cName);
            
            data[i].email=malloc(strlen(data[i+1].email)+1);
            strcpy(data[i].email,data[i+1].email);           
            
        }
        
    }   
                                
}
 
/*
 * Comparison function for qsort to work correctly
 */
int compareSuperStruct ( const void * x, const void * y)
{ 

    /*If the both have last names*/
    if(strlen((((sStruct*)x))->data.lName)!=0&&strlen((((sStruct*)y))->data.lName)!=0)
    {
        /*If they are the same, it goes  company name as the tiebreaker*/
        if(!strcmp((((sStruct*)x))->data.lName,(((sStruct*)y))->data.lName))
        {
            return strcmp((((sStruct*)x))->data.cName,(((sStruct*)y))->data.cName);
        }
        /*If they are different, there is no need for the tiebreaker*/
        else
        {            
            return strcmp((((sStruct*)x))->data.lName,(((sStruct*)y))->data.lName);
        }
    }
    /*If the first one has a last name*/
    else if(strlen((((sStruct*)x))->data.lName)!=0)
    {
        /* 
         * If the company names and the last names are the same
         * The one with the last name takes precedence
         */
        if(!strcmp((((sStruct*)x))->data.lName,(((sStruct*)y))->data.cName))
        {
            return 1;
        }
        /*If they are different, there is no need for the tiebreaker*/
        else
        {
            return strcmp((((sStruct*)x))->data.lName,(((sStruct*)y))->data.cName);
        }
        
    }
   /*If the second one has a last name*/
    else if(strlen((((sStruct*)y))->data.lName)!=0)
    {
        /* 
         * If the company names and the last names are the same
         * The one with the last name takes precedence
         */
        if(!strcmp((((sStruct*)x))->data.cName,(((sStruct*)y))->data.lName))
        {
            return -1;
        }
        /*If they are different, there is no need for the tiebreaker*/
        else
        {
            return strcmp((((sStruct*)x))->data.cName,(((sStruct*)y))->data.lName); 
        }        
    }
    /*If neither of them have last names*/
    else
    {
        return strcmp((((sStruct*)x))->data.cName,(((sStruct*)y))->data.cName);
    }
}


/* 
 * Asks user if they wish to add a contact
 * and returns the details in the input array
 */
int newContact(char *buffer[5])
{
    int i;
    
    char *input;   

    for(i=0;i<5;i++)
    {
        if(buffer[i])
        {
            free(buffer[i]);
            buffer[i]=NULL;
        }
    }
    
    /*Gets the input*/
    printf("New Contact\n");
    printf("First Name: ");
    buffer[0]=getLine();
     
    printf("Last Name: ");
    buffer[1]=getLine();
    
    /*If the last name is empty then the company name is required*/
    if(strlen(buffer[1])==0)
    {
        buffer[2]=getLineNotEmpty("Company Name: ");
    }
    else
    {
        printf("Company Name: ");
        buffer[2]=getLine();
    }    
    
    buffer[3]=getPhone("Phone Number (enter only numbers): ");

    buffer[4]=getEmail("Email: "); 

    do{
        input=getLineNotEmpty("Action: ");
        if(!strcmp(input,"R"))
        {
            free(input);
            input=NULL;
            return 0;
        }
        else if(!strcmp(input,"S"))
        {   
            free(input);
            input=NULL;
            return 1;
            
        }
        else
        {
            free(input);
        }
    }while(1);
    
}

/*
 *Adds the buffer contents into the corresponding structures
 */
void addNewContact(cStruct *contacts, dStruct *data, char *buffer[5], int count)
{
    int i;
    unsigned long phone=0;             

    sscanf(buffer[3], "%lu", &phone);
    
    (contacts[count-1]).phone_number=phone;
    

    (data[count-1]).fName=malloc(strlen(buffer[0])+1);
    (data[count-1]).lName=malloc(strlen(buffer[1])+1);
    (data[count-1]).cName=malloc(strlen(buffer[2])+1);
    (data[count-1]).email=malloc(strlen(buffer[4])+1);
    
    strcpy((data[count-1]).fName,buffer[0]);
   
    strcpy((data[count-1]).lName,buffer[1]);
    
    strcpy((data[count-1]).cName,buffer[2]);
    
    strcpy((data[count-1]).email,buffer[4]); 

    /*Frees the buffer*/
    for(i=0;i<5;i++)
    {
        if(buffer[i])
        {
            free(buffer[i]);
            buffer[i]=NULL;
        }
    }
    
    
}

/* 
 * Asks user if they wish to retrieve a contact
 * and returns the associated phone number
 */
int retrieveContact(cStruct *contacts, dStruct *data, int count)
{
    unsigned long phone=0;
    char *input;
    int flag=0;
    int i;
    
    do{
        printf("Do you wish to retrieve a contact (Yes or No)?: ");
        input=getLine();
        if(!strcmp(input,"No"))
        {
            free(input);
            input=NULL;
            return 0;
        }
        else if(!strcmp(input,"Yes"))
        {   
            flag=1;
            free(input);
            
        }
        else
        {
            free(input);
        }
    }while(!flag);
    
    
    printf("Phone Number: ");
    
    input=getLine();
    
    if(strlen(input)==0)
    {
        printf("No match found.\n");   
        free(input);
        input=NULL;
            
        return 1;    
    }
    
    for(i=0;i<strlen(input);i++)
    {
        if(!isdigit(input[i]))
        {
            printf("No match found.\n");   
            free(input);
            input=NULL;
                
            return 1;
        }
    }
  

    
    sscanf(input,"%lu",&phone);
    free(input);
    input=NULL;
    
  
    
    for(i=0;i<count;i++)
    {
        if((contacts[i]).phone_number==phone)
        {
            printf("First Name: %s\nLast Name: %s\nCompany Name: %s\nPhone Number: %lu\nEmail: %s\n",(data[i]).fName,(data[i]).lName,(data[i]).cName,contacts[i].phone_number,(data[i]).email);
            return 1;
        }
        
    }
    printf("No match found.\n");
    
    return 1;
    
}

/*
 * Writes the structs to file
 */
void writeContacts(char *fileName,cStruct *contacts, dStruct *data, int count)
{
  
    FILE *fptr;
    fptr = fopen (fileName, "wb");
    int i;
    long tempPosition;
    
    if(fptr==NULL)
    {
        return;
    }
        
    
    /*Writes one data entry at a time*/
    for(i=0;i<count;i++)
    {
        
        
        /*Calculates the correct value for first name position*/
        tempPosition=ftell(fptr)+sizeof(cStruct);
        
        /*Checks that the first name is not blanked*/
        if(strlen(data[i].fName)>0)
        {
            (contacts[i]).first_name_posn=tempPosition;            
        }
        else
        {
            (contacts[i]).first_name_posn=0;
            /*Accounts for the +1 in the calculation of the next tempPosition*/
            tempPosition--;
        }     
        
        /*The +1 accounts for the null terminator at the end of string*/
        tempPosition+=strlen(data[i].fName)+1;
        
        if(strlen(data[i].lName)>0)
        {
            (contacts[i]).last_name_posn=tempPosition;
        }
        else
        {
            (contacts[i]).last_name_posn=0;
            tempPosition--;
        }
        
        tempPosition+=strlen(data[i].lName)+1;
        
        if(strlen(data[i].cName)>0)
        {
            (contacts[i]).company_name_posn=tempPosition;          
        }
        else
        {
            (contacts[i]).company_name_posn=0;          
            tempPosition--;           
        }
        
        tempPosition+=strlen(data[i].cName)+1;
        
        if(strlen(data[i].email)>0)
        {
            (contacts[i]).email_posn=tempPosition;
        }
        else
        {
            (contacts[i]).email_posn=0;
            tempPosition--;            
        }        
        tempPosition+=strlen(data[i].email)+1;
          
        (contacts[i]).next=tempPosition;
     
        /*Writes the contacts struct to the file after all its values have been complicated*/
        fwrite(&(contacts[i]),sizeof(cStruct),1,fptr);       
        
        /*If the first name is not empty*/
        if((contacts[i]).first_name_posn!=0)
        {
            /*Seeks the correct position and writes the data to it*/
            fseek(fptr,(contacts[i]).first_name_posn,SEEK_SET);      
            fwrite((data[i]).fName, strlen((data[i]).fName)+1, 1,fptr);
        }
        
        if((contacts[i]).last_name_posn!=0)
        {
            fseek(fptr,(contacts[i]).last_name_posn,SEEK_SET);     
            fwrite((data[i]).lName,strlen((data[i]).lName)+1,1,fptr);
        }
        
        if((contacts[i]).company_name_posn!=0)
        {
            fseek(fptr,(contacts[i]).company_name_posn,SEEK_SET);
            fwrite((data[i]).cName,strlen((data[i]).cName)+1,1,fptr);
        }
        
        if((contacts[i]).email_posn!=0)
        {
            fseek(fptr,(contacts[i]).email_posn,SEEK_SET);
            fwrite((data[i]).email,strlen((data[i]).email)+1,1,fptr);
        }
        
        /*Seeks the address of the next structure*/
        fseek(fptr,(contacts[i].next),SEEK_SET);
        
    }
    
    fclose(fptr);
}

/*
 * Gets a phone number
 *
 * This returns a character array 
 * because I don't want to change
 * the rest of my program
 */
char* getPhone(char*prompt)
{
    char *buffer=NULL;
    int i;
    int flag;
    
    do{
        flag=1;
        if(buffer)
            free(buffer);
        
        buffer=getLineNotEmpty(prompt);
        
        for(i=0;i<strlen(buffer);i++)
        {
            if(!isdigit(buffer[i]))
                flag=0;            
        }
        
        if(strlen(buffer)!=7&&strlen(buffer)!=10)
            flag=0;
        
    }while(!flag);
    
    return buffer;
}

/* 
 * Gets a line from stdin
 */
char* getLine()
{
    char *buffer=malloc(sizeof(char)*2);
    char input;
    
    int length=0;
    do{    
        input=getc(stdin);
        buffer=realloc(buffer,sizeof(char)*(length+1));
        buffer[length]=input;
        length++;
        
    }while(input!='\n');
    
    buffer[length-1]='\0';
    buffer=realloc(buffer,sizeof(char)*(length));
    
    return buffer;
}

/*
 * Gets a line from stdin and makes
 * sure that it is not empty
 */
char* getLineNotEmpty(char *prompt)
{
    char* buffer=NULL;
    
    do{
        if(buffer)
            free(buffer);
        
        printf("%s",prompt);
        buffer=getLine();
       
    }while(strlen(buffer)==0);
    return buffer;
}

/*
 * Gets an email
 */
char* getEmail(char *prompt)
{
    char *buffer=NULL;
    int flag=0;
    int at=0;
    int atPos=0;
    int i;
    
    do{
        at=0;
        atPos=0;

        
        if(buffer)
            free(buffer);
        
        printf("%s",prompt);
        
        buffer=getLine();
        
        if(strlen(buffer)==0)
            return buffer;
        
        for(i=0;i<strlen(buffer);i++)
        {
            /*Checks that @ exists and is not at the first position*/
            if(buffer[i]=='@'&&(!at)&&(i!=0))
            {
                atPos=i;
                at=1;

            }
            
            /* Checks that dot exists,that an @ has happened, that the . is not the
             * last character, and that it is not right after the @
             */
            else if(buffer[i]=='.'&&(!flag)&&at&&((i+1)!=strlen(buffer))&&((atPos+1)!=i))
            {
                flag=1;
            }
        }
            
        
    }while(!(flag));
    
    return buffer;
}

/* 
 * Gets a line from stdin
 */
char* readData(FILE *fptr)
{
    char *buffer=malloc(sizeof(char)*2);
    char input;
    
    int length=0;
    do{    
        input=getc(fptr);
        buffer=realloc(buffer,sizeof(char)*(length+1));
        buffer[length]=input;
        length++;
        
    }while(input!='\0');
        
    return buffer;
}