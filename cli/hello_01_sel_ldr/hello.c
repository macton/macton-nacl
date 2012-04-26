
// How to run?
//   $(NACL_SDK_ROOT)/tools/sel_ldr_x86_64 -B $(NACL_SDK_ROOT)/tools/irt_x86_64.nexe hello_x86_64.nexe < hello.c
//   ...should print this file.

// See also native-client-discuss thread: "Segmentation fault: sel_ldr (Pepper 18)"
//   https://groups.google.com/d/topic/native-client-discuss/u68-MImnT0U/discussion

#include <stdio.h>
#include <alloca.h>
#include <stdint.h>

int
main ( int argc, char** argv )
{
  printf ( "Hello, world! Echo input file (stdin)\n" );
  size_t input_max_size = 4 * 1024 * 1024;
  char*  input_buffer   = alloca ( input_max_size );

  if ( !input_buffer )
  {
    printf ( "ERROR: Could not allocate buffer from stack." );
    return ( -1 );
  }

  int    c;
  size_t input_size   = 0;

  while ( EOF != ( c = fgetc ( stdin ) ) )
  {
    input_buffer[ input_size ] = ( char ) ( uint8_t ) c;
    input_size++;

    if ( input_size == input_max_size )
    {
      printf ( "Warning: File larger than maximum space allocated.\n" );
      break;
    }
  }

  printf ( "Size of input file: %lu\n", (unsigned long)input_size );
  printf ( "----- INPUT BEGIN -----\n" );
  fwrite ( input_buffer, input_size, 1, stdout );
  printf ( "----- INPUT END -----\n" );
  return ( 0 );
}
