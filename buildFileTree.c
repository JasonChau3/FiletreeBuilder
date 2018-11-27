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
#include "pa3.h"
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
    int SIZEINC = 8;
    struct fileInfo *direc = calloc(1,sizeof(struct fileInfo));
    //if there is error throw err
    if (direc == NULL) {
        perror(__func__);
        return NULL;
    }

    getFileInfo(direc,filename);

    DIR* ptr = opendir(filename):
        //in the case that the file is not a directory
        if (ptr == NULL ) {
            return direc;
        }
    //if it is a directory then set it to be true
    direc -> isDir = 1;

    struct dirent* subFile;

    struct fileInfo* sub;
    while ( (subFile = readdir(ptr)) != NULL) {
        // if the names are those skip 
        if ( (strcmp(subFile -> d_name,".") == 0) || (strcmp(subFile -> d_name, "..") == 0)) {
        }
        else{
            char buffer[BUFSIZ];
            sprintf(buffer, FILE_CONCAT_FORMAT, direc -> filename, subFile -> d_name);

            //if the number of children is the same as the size
            //reallocate more memory
            if ( (direc -> childrenSize) == (direc -> childrenCapacity)) {
                struct fileInfo* newMem = realloc(direc,SIZEINC);
                if (newMem == NULL ) {
                    perror(__func__);
                    //if it has children free it
                    if (direc->children != NULL ) {
                        free(direc->children);
                    }
                    //then free the struct
                    free(direc);

                }
                else {
                    //if reallocating works increment the childrenCapacity
                    (direc -> childrenCapacity) = (direc -> childrenCapacity) + SIZEINC;
                }
            }
        }
        //recursive call
        sub = buildFileTree(direc -> filename,sortby, rev);
        (direc -> children[direc->childrenSize]) = sub; 
        //increment the number of children
        (direc -> childrenSize)++;
    }
    closedir(ptr);
    qsort(direc,direc->childrenSize,sizeof(struct fileInfo), sortby,rev);
    //sort the shit here 
    return direc;

}
