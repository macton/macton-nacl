#include "nacl.h"
#include <string.h>
#include "mariner.h"

// --------------------------------------------------------------------------
// Required entry point functions -------------------------------------------
// --------------------------------------------------------------------------

PP_Bool NaclHandleInputEvent( PP_Resource input_event )
{
  return PP_TRUE;
}

PP_Bool NaclInstanceCreate( uint32_t argc, const char* argn[], const char* argv[] )
{
  NaclMessagingPostUtf8("Instance_DidCreate");

  // #todo put all this boilerplate into a "Post" ddl method
  // #todo some shared scratchpad memory for output buffers
  // #todo generate a ddl method to calculate the needed size of the buffer
  {
    Mariner  mariner;
    char     output_buffer[ 2048 ];
    char*    output_start  = output_buffer;
    char*    output_cursor = output_buffer;
    size_t   output_size   = 0;

    output_size   += sprintf( output_cursor, "data: " );
    output_cursor += output_size;
 
    mariner.Init();
    mariner.GetPosition()->SetX( 101 );
    mariner.GetPosition()->SetY( 202 );
    mariner.GetWeapon()->Set( Weapon::kChainsaw );
    mariner.SetTimestamp( __TIMESTAMP__ );
    mariner.WriteJson( output_cursor, output_size );

    *output_cursor = 0;

    NaclMessagingPostUtf8( output_start );
  }  

  return PP_TRUE;
}

void NaclInstanceDestroy()
{
}

void NaclDidChangeView( PP_Resource view )
{
  NaclMessagingPostUtf8("Instance_DidChangeView");
}

void  NaclDidChangeFocus( PP_Bool has_focus )
{
  NaclMessagingPostUtf8("Instance_DidChangeFocus");
}

PP_Bool NaclHandleDocumentLoad( PP_Resource url_loader )
{
  return PP_TRUE;
}

void NaclHandleMessage( PP_Var message )
{
}

void NaclMouseLockLost()
{
}

void NaclRenderFrame()
{
}
