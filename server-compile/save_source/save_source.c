#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SOURCE_SIZE_MAX   ( 1024 * 1024 )
#define VAR_LENGTH        4 /* "src=" */
#define CONTENT_SIZE_MAX  SOURCE_SIZE_MAX+VAR_LENGTH+2
#define OUTPUT_FILE_PATH  "../hello.c"

void unencode ( char* src, char* last, char* dest )
{
  for ( ; src != last; src++, dest++ )
  {
    if ( *src == '+' )
    {
      *dest = ' ';
    }
    else if ( *src == '%' )
    {
      unsigned int code;

      if ( sscanf ( src + 1, "%2x", &code ) != 1 )
      {
        code = '?';
      }

      *dest = code;
      src += 2;
    }
    else
    {
      *dest = *src;
    }
  }

  *dest   = '\n';
  *++dest = '\0';
}

int main ( void )
{
  char*  lenstr;
  char   input[CONTENT_SIZE_MAX];
  char   data[CONTENT_SIZE_MAX];
  long   len;
  int    id;

  // srand( time(NULL) );
  id = time(NULL);

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
    printf ( "{ \"Ready\":true, \"Message\": \"%s\", \"Id\": %d }\r\n\r\n", "Source saved", id );
  }

  return 0;
}
