/*i
 * Filename: freeFileTree.c
 * Author: Jason Chau
 * Userid: cs30fie
 * Description: This function will recursively free the memory 
 * Date: 11/7/18
 * Sources of Help: PIAZZA
 */
#include "pa4Strings.h"
#include <string.h>
#include <stdlib.h>
#include "pa4.h"
/*
   Function Name: freeFileTree
   Function Prototype:void freeFileTree( struct fileInfo *fi);
Description: This function will recursively free the memory
Parameters: fi a fileinfo pointer.
Side Effects: None
Error Conditions: None
*/

void freeFileTree( struct fileInfo *fi) {
    for ( int x = 0; x < fi -> childrenSize; x++) {
        freeFileTree(fi->children[x]);
    }
    free(fi->children);
    free(fi);
}
