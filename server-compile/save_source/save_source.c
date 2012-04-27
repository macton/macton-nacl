#include <stdio.h>
#include <stdlib.h>

#define SOURCE_SIZE_MAX   ( 1024 * 1024 )
#define VAR_LENGTH        4 /* "src=" */
#define CONTENT_SIZE_MAX  SOURCE_SIZE_MAX+VAR_LENGTH+2
#define OUTPUT_FILE_PATH  "../hello.c"

int main ( void )
{
  char*  lenstr;
  char   input[CONTENT_SIZE_MAX];
  char   data[CONTENT_SIZE_MAX];
  long   len;
  printf ( "Content-type: application/json\r\n\r\n" );
  lenstr = getenv ( "CONTENT_LENGTH" );

  if ( lenstr == NULL || sscanf ( lenstr, "%ld", &len ) != 1 || len > SOURCE_SIZE_MAX )
  {
    printf ( "{ \"Ready\":false, \"Message\": \"%s\" }\r\n\r\n", "Can't read the source" );
    fgets ( input, SOURCE_SIZE_MAX, stdin );
  }
  else
  {
    FILE* f;
    fgets ( input, len + 1, stdin );
    unencode ( input + VAR_LENGTH, input + len, data );
    f = fopen ( OUTPUT_FILE_PATH, "w" );

    if ( f == NULL )
    {
      printf ( "{ \"Ready\":false, \"Message\": \"%s\" }\r\n\r\n", "Can't save the source" );
    }
    else
    {
      fputs ( data, f );
    }

    fclose ( f );
    printf ( "{ \"Ready\":true, \"Message\": \"%s\" }\r\n\r\n", "Source saved" );
  }

  return 0;
}
