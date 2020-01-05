/*
 * Michael Dombrovsky
 */
 
#include "conFunctions.h"

int main()
{
    
    cStruct *contacts=malloc(sizeof(cStruct));
    dStruct *data=malloc(sizeof(dStruct));
    sStruct *fullContacts=malloc(sizeof(sStruct));
    
    char fileName[]="myContactList.db";

    char *buffer[5]={NULL,NULL,NULL,NULL,NULL};

    int count=0;
   
    char currLetter;
    FILE *fptr;
    
    int i;
    int num;
   
    
    long end=0;
    cStruct *cBuffer=malloc(sizeof(cStruct));
    char *dBuffer;
    
    char *input=NULL;
    int (*compare_ptr)(const void *a, const void *b)=NULL;
    compare_ptr=&compareSuperStruct;
    
    fptr = fopen (fileName, "rb");

    /*Reads from the file*/
    if(fptr!=NULL)
    {
        i=0;   
        fseek(fptr,0,SEEK_END);

        
        end=ftell(fptr);
        fseek(fptr,0,SEEK_SET);
        

        /*Reads from the file while the end is not reached*/
        while(ftell(fptr)<end){
            
            /*Reads a contacts struct to a buffer*/
            fread(cBuffer,sizeof(cStruct),1,fptr);             
         
            /*Resizes the structs*/
            contacts=realloc(contacts,sizeof(cStruct)*(i+1));
            data=realloc(data,sizeof(dStruct)*(i+1));
            
            /*Populates the contacts struct*/
            (contacts[i]).phone_number=cBuffer->phone_number;
            (contacts[i]).first_name_posn=cBuffer->first_name_posn;
            (contacts[i]).last_name_posn=cBuffer->last_name_posn;
            (contacts[i]).company_name_posn=cBuffer->company_name_posn;
            (contacts[i]).email_posn=cBuffer->email_posn;
            (contacts[i]).next=cBuffer->next;
            
            
            /*Populates the data struct*/
           
            /*If the data exists*/
            if((contacts[i]).first_name_posn!=0)
            {          
                /*Seeks to the data position*/
                fseek(fptr, (contacts[i]).first_name_posn,SEEK_SET); 
                
                /*Reads the data into a buffer*/
                dBuffer=readData(fptr);
                
                /*Copies the buffer to the struct element*/
                (data[i]).fName=malloc(strlen(dBuffer)+1);
                strcpy(data[i].fName,dBuffer);
                
                /*Discards the buffer*/
                free(dBuffer);
            }
            /*If the data does not exist*/
            else
            {
                /*Makes the data entry be equal to a null terminators*/
                (data[i]).fName=malloc(sizeof(1));
                data[i].fName[0]='\0';
            }
            
            if((contacts[i]).last_name_posn!=0)
            {
                fseek(fptr, (contacts[i]).last_name_posn,SEEK_SET);         
                dBuffer=readData(fptr);
                (data[i]).lName=malloc(strlen(dBuffer)+1);
                strcpy(data[i].lName,dBuffer);
                free(dBuffer);
                
            }
            else
            {
                (data[i]).lName=malloc(sizeof(1));
                data[i].lName[0]='\0';
            }
            
            if((contacts[i]).company_name_posn!=0)
            {
                fseek(fptr, (contacts[i]).company_name_posn,SEEK_SET);         
                dBuffer=readData(fptr);
                (data[i]).cName=malloc(strlen(dBuffer)+1);
                strcpy(data[i].cName,dBuffer);
                free(dBuffer);
                
            }
            else
            {
                (data[i]).cName=malloc(sizeof(1));
                data[i].cName[0]='\0';
            }

            if((contacts[i]).email_posn!=0)
            {
                fseek(fptr, (contacts[i]).email_posn,SEEK_SET);         
                dBuffer=readData(fptr);
                (data[i]).email=malloc(strlen(dBuffer)+1);
                strcpy(data[i].email,dBuffer);
                free(dBuffer);
                
            }
            else
            {
                (data[i]).email=malloc(sizeof(1));
                data[i].email[0]='\0';
            }            
                                   
            i++;
        }
        fclose(fptr);
        
        /*Sets the count of seperate data entries*/
        count=i; 
         
         
        
    }
    
    /*Frees the contacts buffer once it is used*/
    free(cBuffer);

    
    
    
    
    
    
    
   

    
    
    
    
    

    

    /*
     * Non-file reading part starts here
     */
    do
    {       

        /*
         * Print names section START
         */
               
        if(fullContacts)
        {
            free(fullContacts);
            fullContacts=NULL;
        }
        fullContacts=malloc(sizeof(sStruct)*count);
        
        /*Copies elements from the data and contacts structs into a super struct*/
        for(i=0;i<count;i++)
        {
            fullContacts[i].contacts.phone_number=contacts[i].phone_number;
                    
            fullContacts[i].contacts.first_name_posn=contacts[i].first_name_posn;
            
            fullContacts[i].contacts.last_name_posn=contacts[i].last_name_posn;
            
            fullContacts[i].contacts.company_name_posn=contacts[i].company_name_posn;
            
            fullContacts[i].contacts.email_posn=contacts[i].email_posn;
                 
            fullContacts[i].contacts.next=contacts[i].next;     
        
            fullContacts[i].data.fName=malloc(strlen(data[i].fName)+1);            
            strcpy(fullContacts[i].data.fName,data[i].fName);
            free(data[i].fName);

            fullContacts[i].data.lName=malloc(strlen(data[i].lName)+1);            
            strcpy(fullContacts[i].data.lName,data[i].lName);
            free(data[i].lName);
     
            fullContacts[i].data.cName=malloc(strlen(data[i].cName)+1);
            strcpy(fullContacts[i].data.cName,data[i].cName);
            free(data[i].cName);
            
            fullContacts[i].data.email=malloc(strlen(data[i].email)+1);
            strcpy(fullContacts[i].data.email,data[i].email);
            free(data[i].email);     
        }       
        
        /*Sorts the super struct*/
        qsort(fullContacts,count,sizeof(sStruct),compare_ptr);
        
        /*Copies the data from the super struct into the data and contacts structs*/
        for(i=0;i<count;i++)
        {
            contacts[i].phone_number=fullContacts[i].contacts.phone_number;
            
            contacts[i].first_name_posn=fullContacts[i].contacts.first_name_posn;
            
            contacts[i].last_name_posn=fullContacts[i].contacts.last_name_posn;
            
            contacts[i].company_name_posn=fullContacts[i].contacts.company_name_posn;
            
            contacts[i].email_posn=fullContacts[i].contacts.email_posn;
            
            contacts[i].next=fullContacts[i].contacts.next;
            
            data[i].fName=malloc(strlen(fullContacts[i].data.fName)+1);
            strcpy(data[i].fName,fullContacts[i].data.fName);
            free(fullContacts[i].data.fName);
            
            data[i].lName=malloc(strlen(fullContacts[i].data.lName)+1);
            strcpy(data[i].lName,fullContacts[i].data.lName);
            free(fullContacts[i].data.lName);
            
            data[i].cName=malloc(strlen(fullContacts[i].data.cName)+1);
            strcpy(data[i].cName,fullContacts[i].data.cName);
            free(fullContacts[i].data.cName);
            
            data[i].email=malloc(strlen(fullContacts[i].data.email)+1);
            strcpy(data[i].email,fullContacts[i].data.email);
            free(fullContacts[i].data.email); 

        }
        

        /*Prints a sorted list of contacts*/
        printf("Number of Contacts = %d\n",count);
        for(i=0;i<count;i++)
        {
            /*If last name exists*/
            if(strlen(data[i].lName)!=0)
            {   
                /*If the current letter has not been set or is different*/
                if(i==0||currLetter!=data[i].lName[0])
                {
                    currLetter=data[i].lName[0];
                    printf("%c\n",currLetter);
                }
                
                printf("\t%d. %s %s\n",i+1,data[i].lName,data[i].fName);
            }
            /*Otherwise the company name exists*/
            else
            {
                /*If the current letter has not been set or is different*/
                if(i==0||currLetter!=data[i].cName[0])
                {
                    currLetter=data[i].cName[0];
                    printf("%c\n",currLetter);
                }
                printf("\t%d. %s\n",i+1,data[i].cName);
            }
            
        }
        
        /*
         * Print names section END
         */
    
    

        
        do{
            num=0;
            
            /*Frees input if its not NULL*/
            if(input)
            {
                free(input);
                input=NULL;
            }
            
            printf("Action: ");
            input=getLine();
            if(!isStringANum(input,1,count,&num))
                num=0;
        }while((!(num>=1&&num<=count))&&(strcmp(input,"A"))&&(strcmp(input,"X")));
        /*Add contact*/
        if(!strcmp(input,"A"))
        {
            if(newContact(buffer))
            {
                count++;
                data=realloc(data,(sizeof(dStruct))*(count));
                contacts=realloc(contacts,(sizeof(cStruct))*(count));
                addNewContact(contacts,data,buffer,count);
            }
        }
        /*If it is a valid integer*/
        else if(isStringANum(input,1,count,&num))
        {
            
            switch(displayContact(contacts,data,buffer,num,count))
            {
                /*Delete*/
                case 1:
                    removeContact(contacts,data,num,count);
                    count--;
                    data=realloc(data,(sizeof(dStruct))*(count));
                    contacts=realloc(contacts,(sizeof(cStruct))*(count));
                    break;  
                
                /*Save*/
                case 2:
                    
                    free(data[num-1].email);
                    
                    sscanf(buffer[3], "%lu", &(contacts[num-1]).phone_number);

                    
                    (data[num-1]).email=malloc(strlen(buffer[4])+1);
                    strcpy((data[num-1]).email,buffer[4]); 
                    
                    /*Frees the buffer*/
                    for(i=3;i<5;i++)
                    {
                        if(buffer[i])
                        {
                            free(buffer[i]);
                            buffer[i]=NULL;
                        }
                    }
                    
                    break;
                    
            }
          
        }
    
        
    }while(strcmp(input,"X"));
    
    /*Frees the superStruct, once it is done being used*/
    if(fullContacts)
    {
        free(fullContacts);
        fullContacts=NULL;
    }
   
    
    /*Frees the input variable once its donce being used*/
    if(input)
    {
        free(input);
        input=NULL;
    }
    

    /*Writes data entries to the file*/
    writeContacts(fileName,contacts, data, count);

    /*Frees the data struct elements*/
    for(i=0;i<count;i++)
    {
        if(data[i].fName)
        {
            free(data[i].fName);
            data[i].fName=NULL;
        }
        if(data[i].lName)
        {
            free(data[i].lName);
            data[i].lName=NULL;
        }
        if(data[i].cName)
        {
            free(data[i].cName);
            data[i].cName=NULL;
        }
        if(data[i].email)
        {
            free(data[i].email);
            data[i].email=NULL;
        }
    }
    
    for(i=0;i<5;i++)
    {
        if(buffer[i])
        {
            free(buffer[i]);
            buffer[i]=NULL;
        }
    }
    
    /*Frees the actual structs*/
    if(contacts)
    {
        free(contacts); 
        contacts=NULL;
    }
    
    /*Frees the data struct once its done being used*/
    if(data)
    {
        free(data);
        data=NULL;
    }
        
        
    /*Program is finished*/
    return 0;
}