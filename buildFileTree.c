/*
 * Filename: buildFileTree
 * Author: Jason Chau
 * Userid: cs30fie
 * Description: This function will create a file tree
 * Date: 11/7/18
 * Sources of Help: PIAZZA
 */

#include <string.h>
#include <stdlib.h>
#include "pa4.h"
#include "pa4Strings.h"
#include <dirent.h>
/*
   Function Name: buildFileTree
   Function Prototype:struct fileInfo * buildFileTree(const char * filename,
   SortBy sortby, int rev) 
Description: This function will create a file tree
Parameters: filename - the name of the file 
sortby - how do you sort 
rev - if you want it reversed or not
Side Effects: None
Error Conditions: if it fails to allocate memory errors will be thrown.
*/

struct fileInfo * buildFileTree(const char * filename, SortBy sortby, int rev) {
    struct fileInfo *direc = calloc(1,sizeof(struct fileInfo));
    //if there is error throw err
    if (direc == NULL) {
        perror(__func__);
        return NULL;
    }

    getFileInfo(direc,filename);

    DIR* ptr = opendir(filename);
    //in the case that the file is not a directory
    if (ptr == NULL ) {
        return direc;
    }
    //if it is a directory then set it to be true
    direc -> isDir = 1;

    struct dirent* subFile;

    while ( (subFile = readdir(ptr)) != NULL) {
        // if the names are those skip 
        if ( (strcmp(subFile -> d_name,STR_THIS ) != 0) && (strcmp(subFile -> d_name, STR_UP ) != 0)) {


            char buffer[BUFSIZ];
            sprintf(buffer, FILE_CONCAT_FORMAT, direc -> filename, subFile -> d_name);

            //if the number of children is the same as the size
            //reallocate more memory
            if ( (direc -> childrenSize) == (direc -> childrenCapacity)) {
                struct fileInfo** newMem = realloc(direc->children,((direc->childrenCapacity)+SIZEINC)*sizeof(struct fileInfo*));
                if (newMem == NULL ) {
                    perror(__func__);
                    //if it has children free it
                    if (direc->children != NULL ) {
                        free(direc->children);
                    }
                    //then free the struct
                    free(direc);
                    return NULL;
                }
                else {
                    direc->children = newMem;
                    //if reallocating works increment the childrenCapacity
                    (direc -> childrenCapacity) = (direc -> childrenCapacity) + SIZEINC;
                }
            }

            //recursive call
            direc -> children[direc->childrenSize]=buildFileTree(buffer,sortby, rev);
            //increment the number of children
            (direc -> childrenSize)++;
        }
    }
    closedir(ptr);
    //sort by non reversed
    if (rev == 0) {
        if ( sortby == NAME) {
            qsort(direc->children, direc -> childrenSize,sizeof(struct timeInfo*),nameCompare );
        }
        else {
            qsort(direc->children, direc -> childrenSize,sizeof(struct timeInfo*), timeCompare);
        }
    }
    //sort by reversed
    else {
        if ( sortby == NAME) {
            qsort(direc->children, direc -> childrenSize,sizeof(struct timeInfo*),nameCompareRev );
        }
        else {
            qsort(direc->children, direc -> childrenSize,sizeof(struct timeInfo*),timeCompareRev);
        }

    }    
    return direc;

}
