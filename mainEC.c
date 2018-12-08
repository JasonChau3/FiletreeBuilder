/*
 * Filename: main.c
 * Author: Jason Chau
 * Userid: cs30fie
 * Description: This function builds a file tree from a current directory
 *and then prints out all the files in the directory in the order specified by 
 *you(either sorted by time, name or in reverse). It also can print out the 
 *files in long format which includes the permission, the time it was modified,
 *and so forth.It also can print out the number of files there are if you 
 specify it to as well

 * Date: 11/7/18
 * Sources of Help: PIAZZA
 */

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "pa4Strings.h"
#include "pa4.h"
#include "pa4EC.h"
/*
   Function Name: main.c
   Function Prototype:int main( int argc, char *argv[]) {
Description: This function will builds a file tree from a current directory
and then prints out all the files in the directory in the order specified by 
you(either sorted by time, name or in reverse). It also can print out the 
files in long format which includes the permission, the time it was modified,
and so forth.It also can print out the number of files there are if you specify
it to as well


Parameters: argc - the argument count
argv[] the array of arguments
Side Effects: None
Error Conditions: 
1. Error accessing the file 
2. No input file Specified
3. Extra Arguments for the input flags
*/
int main( int argc, char *argv[]) {
    int opt;
    int hidden = 0;
    int longfmt = 0;
    int fileCount = 0;
    int reverse = 0;

    SortBy sort = NAME; 
    char *file = STR_THIS;
    int count =0;
    //loop the opt arg through all the arguments in the flag
    while(( opt = getopt(argc,argv, EC_FLAGS)) != -1){
        switch (opt) {
            //when there is a flag h
            case FLAG_HELP:
                fprintf(stderr,STR_USAGE,argv[0]);
                return EXIT_SUCCESS;
                break;
                //when there is a flag a
            case FLAG_SHOWHIDDEN:
                hidden = 1;
                break;
                //when there is a flag c
            case FLAG_COUNT:
                fileCount = 1;
                break;
                //when there is a flag l
            case FLAG_LONGFMT:
                longfmt = 1;
                break;
                //when there is a flag r
            case FLAG_REVERSE:
                reverse = 1;
                break;
                //when there is a flag t
            case FLAG_TIME:
                sort = TIME;
                break;

                //default case
            default:
                break;


        }
    }

    //if there are more args than normal
    //check if the access file can be opened or not
    char* buffer[BUFSIZ];
    struct fileInfo* treeArr[BUFSIZ];
    int treeCount = 0;

    for ( int x = 1; x < argc; x++ ) {
        if (argv[x][0] != DASH) {
            buffer[count] = argv[x];
            count++;
        }
    }
    for (int x = 0; x < count; x++) {
        if ( access(buffer[x],F_OK) == -1) {
            fprintf(stderr,ERR_DNE,file);
            return EXIT_FAILURE;
        }
    }

    if ( count == 0 ) {
        buffer[0] = CURDIR;
        count++;
    }
    struct fileInfo *rootNode;
    for ( int x =0; x < count; x++ ) {
        rootNode = buildFileTree(buffer[x],sort,reverse);
        if (rootNode == NULL) {
            return EXIT_FAILURE;
        }
        treeArr[treeCount] = rootNode;
        treeCount++;
    }

    if (reverse == 0) {
        if ( sort == NAME) {
            qsort(treeArr, treeCount,
                    sizeof(struct fileInfo*),nameCompare );
        }
        else {
            qsort(treeArr, treeCount,
                    sizeof(struct fileInfo*), timeCompare);
        }
    }
    //sort by reversed
    else {
        if ( sort == NAME) {
            qsort(treeArr, treeCount,
                    sizeof(struct fileInfo*),nameCompareRev );
        }
        else {
            qsort(treeArr, treeCount,
                    sizeof(struct fileInfo*),timeCompareRev);
        }

    }    


    //if there was file count flag print out the filecount
    //print the files 
    for ( int x =0; x < treeCount; x++ ) {
        printFiles(treeArr[x],hidden,longfmt,0); 
        if (fileCount == 1) {
            fprintf(stdout,STR_COUNT,file,getFileCount(treeArr[x])); 
        }
        freeFileTree(treeArr[x]);    
    }
    //recursively free all the memory


    return EXIT_SUCCESS;

}
