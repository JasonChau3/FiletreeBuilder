/*
 * Filename: testnameCompare
 * Author: Jason Chau
 * Userid: cs30fie
 * Description: Unit test program to test the function nameCompare().
 * Date: 11/7/18
 * Sources of Help: PIAZZA
 */

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/*
 * Unit Test for nameCompare.s
 *
 * long hash( char * src );
 *
 */
int main(int argc, char *argv[]) {
  struct fileInfo * test1 = buildFileTree(argv[1], NAME, 1);
  int x = 0;
  while ( test1->children[x] != NULL) {
 fprintf(stdout, "%s\n", test1->children[x]);
 x++;
 }
 printPermissions(test1->mode);
}


