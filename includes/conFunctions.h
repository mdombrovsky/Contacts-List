/*
 * Michael Dombrovsky
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * Struct to keep phone number
 * and the memory location of 
 * several piecees of data
 */
struct contact
{
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;
};

typedef struct contact cStruct;

/*
 * Struct to store the actual data
 */
typedef struct dataSet
{
    char *fName;
    char *lName;
    char *cName;
    char *email;
    
}dStruct;

/*
 * Struct that has both struct
 * for sorting purposes
 */
 typedef struct superStruct
 {
    cStruct contacts;
    dStruct data;
     
 }sStruct;
 
 
char* getEmail(char *prompt);
char* getPhone(char*prompt);
char* getLine();
char* readData(FILE *fptr);
char* getLineNotEmpty(char *prompt);
int displayContact(cStruct *contacts, dStruct *data, char *buffer[5],int num,int count);
int compareSuperStruct ( const void * x, const void * y);
int newContact(char *buffer[5]);
int retrieveContact(cStruct *contacts, dStruct *data, int count);
int editContact(cStruct *contacts, dStruct *data, char *buffer[5], int num);
int isStringANum(char *input, int min, int max, int *num);
void addNewContact(cStruct *contacts, dStruct *data, char *buffer[5],int count);
void writeContacts(char *fileName,cStruct *contacts, dStruct *data, int count);
void removeContact(cStruct *contacts, dStruct *data, int num, int count);
