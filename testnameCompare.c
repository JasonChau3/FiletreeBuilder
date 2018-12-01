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

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/*
 * Unit Test for nameCompare.s
 *
 * long hash( char * src );
 *
 */
void testnameCompare() {
  struct fileInfo * test1 = calloc(1, sizeof(struct fileInfo));
  struct fileInfo * test2 = calloc(1, sizeof(struct fileInfo));

  test1->filename[0] = 'a';
  test2->filename[0] = 'b';

 TEST( nameCompare(&test1, &test2) == -1);
  /* Validate the hash value. */
   test1->filename[0] = 'a';
  test2->filename[0] = 'a';

  /* Validate the hash value. */
  TEST( nameCompare(&test1, &test2) == 0);

  test1->filename[0] = 'c';
  test2->filename[0] = 'b';

  /* Validate the hash value. */
  TEST( nameCompare(&test1, &test2) == 1);


  free(test1);
  free(test2);
}

int main() {
  fprintf( stderr, "Testing hash...\n\n" );
  testnameCompare();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
