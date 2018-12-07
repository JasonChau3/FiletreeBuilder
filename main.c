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
#include "pa4.h"
#include "pa4Strings.h"
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
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
    //loop the opt arg through all the arguments in the flag
    while(( opt = getopt(argc,argv, FLAGS)) != -1){
        switch (opt) {
            //when there is a flag f
            case FLAG_FILENAME :
                file = optarg;
                break;

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
                fprintf(stderr,STR_USAGE,argv[0]);
                return EXIT_FAILURE;
                break;


        }
    }

    //if there are more args than normal
    if (optind != argc) {
        fprintf(stderr, STR_EXTRA_ARG ,argv[optind]); 
        fprintf(stderr, STR_USAGE, argv[0]);
        return EXIT_FAILURE;
    }
    //check if the access file can be opened or not
    if ( access(file,F_OK) == -1) {
        fprintf(stderr,ERR_DNE,file);
        return EXIT_FAILURE;
    }
    //build the tree and check it is not null
    struct fileInfo *rootNode = buildFileTree(file,sort,reverse);
    if (rootNode == NULL) {
        return EXIT_FAILURE;
    }
    //if there was file count flag print out the filecount
    if (fileCount == 1) {
        fprintf(stdout,STR_COUNT,file,getFileCount(rootNode)); 
    }
    //print the files 
    printFiles(rootNode,hidden,longfmt,0); 

    //recursively free all the memory
    freeFileTree(rootNode);    

    return EXIT_SUCCESS;

}
