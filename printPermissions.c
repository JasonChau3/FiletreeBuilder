/*i
 * Filename: printPermissions.c
 * Author: Jason Chau
 * Userid: cs30fie
 * Description: This function will create a file tree
 * Date: 11/7/18
 * Sources of Help: PIAZZA
 */
#include "pa4Strings.h"
#include <string.h>
#include <stdlib.h>
#include "pa4.h"
/*
   Function Name: printPermissions.c
   Function Prototype:void printPermissions( const mode_t mode);
Description: This function will print the permissions of a file
Parameters: mode the mode that the file is in.
Side Effects: None
Error Conditions: if it fails to allocate memory errors will be thrown.
*/

void printPermissions(const mode_t mode) {
    //check if it is a directory
    printf((S_ISDIR(mode)) ? D_PERMISSION : NO_PERMISSION);
    //check is user has read
    printf((mode & S_IRUSR) ? R_PERMISSION : NO_PERMISSION);
    //check if user has write
    printf((mode & S_IWUSR) ? W_PERMISSION : NO_PERMISSION);
    //check if user has execute
    printf((mode & S_IXUSR) ? X_PERMISSION : NO_PERMISSION);
    //check if group has read
    printf((mode & S_IRGRP) ? R_PERMISSION : NO_PERMISSION);
    //check if group has write
    printf((mode & S_IWGRP) ? W_PERMISSION : NO_PERMISSION);
    //check if group has write
    printf((mode & S_IXGRP) ? X_PERMISSION : NO_PERMISSION);
    //check if other has read
    printf((mode & S_IROTH) ? R_PERMISSION : NO_PERMISSION);
    //check if others has write
    printf((mode & S_IWOTH) ? W_PERMISSION : NO_PERMISSION);
    //check if others has execute
    printf((mode & S_IXOTH) ? X_PERMISSION : NO_PERMISSION);

}
