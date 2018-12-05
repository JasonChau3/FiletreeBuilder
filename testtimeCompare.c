/*
 * Filename: testtimeCompare
 * Author: Jason Chau
 * Userid: cs30fie
 * Description: Unit test program to test the function timeCompare().
 * Date: 11/7/18
 * Sources of Help: PIAZZA
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/*
 * Unit Test for timeCompare.s
 *
 * long hash( char * src );
 *
 */
void testtimeCompare() {
  struct fileInfo * test1 = calloc(1, sizeof(struct fileInfo));
  struct fileInfo * test2 = calloc(1, sizeof(struct fileInfo));
 
 test1 -> time = 10000;
 test2 -> time = 5000;
 TEST( timeCompare(&test1, &test2) == 1);
 
 test1 -> time = 10000;
 test2 -> time = 10000;
 TEST( timeCompare(&test1, &test2) == 0);

 test1 -> time = 100;
 test2 -> time = 10000;
 TEST( timeCompare(&test1, &test2) == -1);
  free(test1);
  free(test2);
}

int main() {
  fprintf( stderr, "Testing hash...\n\n" );
  testtimeCompare();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
