/*
 * Filename: readTables()
 * Author: Jason Chau
 * Userid: cs30fie
 * Description: This function will check if the table will contain
 * the string or not
 * Date: 11/7/18
 * Sources of Help: PIAZZA
 */

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "pa3.h"
/*
   Function Name: readTables()
   Function Prototype:void readTables( FILE *infile, table_t *htbl,
   table_t *rtbl, table_t *eotbl) {

Description: This function will check if the tables contain a certain string
or not 
Parameters: infile - the file to be read
htbl - the table for regular hashing
rtbl - the table for reverse hashing
eotbl - the table for eveon odd hashing
Side Effects: None
Error Conditions: fail to allocate memory
*/
void readTables( FILE *infile, table_t *htbl, table_t *rtbl, table_t *eotbl) {
    int numBytes = 8;
    int arr = 7;
    int size; 

    //write in the sizes
    fread(&size,sizeof(int), 1, infile);
    // size = (size - arr)*numBytes;
    //you write it in the file of the bit arrays
    //set their sizes
    htbl->size = size;
    rtbl->size = size;
    eotbl->size = size; //(size*8)-7;

    //allocate memory for their arrays
    errno = 0;
    htbl->bitArray = calloc((size+arr)/numBytes,sizeof(char));
    //if there is error throw err
    if ( errno != 0 ) {
        perror(MEM_ERR);
        return;
    }

    errno = 0;
    rtbl->bitArray = calloc((size+arr)/numBytes,sizeof(char));
    //if there is error throw error
    if ( errno != 0 ) {
        free(rtbl->bitArray);
        perror(MEM_ERR);
        return;
    }

    fread((htbl->bitArray),1,(size+arr)/numBytes, infile);
    fread((rtbl->bitArray),1,(size+arr)/numBytes, infile);


    errno = 0;
    eotbl->llArray = calloc(size,sizeof(linkedList_t*));
    //if there is error free and throw error
    if ( errno !=0 ) {
        free(htbl->bitArray);
        free(rtbl->bitArray);
        perror(MEM_ERR);
        return;
    }
    char str[BUFSIZ];
    int count = 0;
    int llArrayIdx = 0;
    int prepended = 1;
    int c;
    while((c = fgetc(infile)) != EOF) {
        if(prepended == 1 && (char)c == '\0')
        {
            llArrayIdx++;
        }
        else if(prepended == 1)
        {
            prepended = 0;
        }

        str[count] = (char)c;

        if (str[count] == '\0') {
            errno = 0;
            prependNode(eotbl->llArray + llArrayIdx,str);
            //if prepend node fails
            if (errno != 0 ) {
                for ( int x = 0; x < eotbl->size; x++) {
                    //free all the memory
                    freeLinkedList(eotbl->llArray[x]);
                }
                free(eotbl->llArray);
                free(htbl->bitArray);
                free(rtbl->bitArray);
                perror(MEM_ERR);
                return;
            }
            //otherwise reset the counter and set prepend to 1
            count = 0;
            prepended = 1;
        }
        //if didnt prepend node then it will work
        else if (prepended == 0){
            count++;
        }
    }

    //set their hashfunctions 
    htbl->hashFunction = &hash;
    rtbl->hashFunction = &revHash;
    eotbl->hashFunction = &evenOddHash;


}

