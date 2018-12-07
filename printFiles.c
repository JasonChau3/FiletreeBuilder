/*
 * Filename: printFiles.c
 * Author: Jason Chau
 * Userid: cs30fie
 * Description: This function will print all of the files in a file tree
 * Date: 11/7/18
 * Sources of Help: PIAZZA
 */
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pa4.h"
#include "pa4Strings.h"
#include <dirent.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h> 
/*
   Function Name: printFiles.c
   Function Prototype:void printFiles (const struct fileInfo * fi,
   int showHidden,int showLongFmt, int ident) {
Description: This function will print all of the files in a file tree
Parameters:fi a pointer to a struct fileInfo,
showHidden- defines whether or not you want to show hidden files
showlongFmt - whether or not you want to print it out in long format
indent- how much to inddent
Side Effects: None
Error Conditions: None
*/
void printFiles (const struct fileInfo * fi, int showHidden,
        int showLongFmt, int indent) {
    //if showhidden is true print it or if the file is not hidden 
    if ( showHidden == 1 || isHidden(fi->filename) == 0) {
        //print it out in long format
        if (showLongFmt == 1) {
            //print the permissions
            printPermissions(fi->mode);
            fprintf(stdout,CHA, SPACE);//print out the pwuid
            if (getpwuid(fi->uid) != NULL) {//make sure it is not null to print
                printf(STR_PWNAME, (getpwuid(fi->uid))->pw_name);

            }
            else {
                printf(STR_PWNAME, EMPTY);
            }
            if (getgrgid(fi->gid) != NULL) { //make sure it is not null
                printf(STR_GNAME,(getgrgid(fi->gid))->gr_name);//print guid
            }
            else{ //otherwise print an empty string
                printf(STR_GNAME,EMPTY);
            }
            printf(STR_SIZE, fi->size); //print the size
            char *tmptr = ctime(&(fi->time));//get the time

            tmptr = tmptr + PTRINC;//trim some of the stuff
            tmptr[ENDPTR]  = NTERM; 
            printf(STR , tmptr);
            fprintf(stdout,CHA, SPACE);
        }
        //size is 
        //ptr +4 add null term for time
        for (int x = 0; x < indent; x++) {
            fprintf(stdout,CHA, SPACE);
        }
        //print the filename
        fprintf(stdout,STRPLUSNEWLINE, fi->filename);
        int x = 0;
        while ( x < fi->childrenSize) {
            printFiles(fi->children[x], showHidden , showLongFmt, indent+1); 
            x++;
        }


    }
}
