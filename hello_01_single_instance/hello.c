#include "nacl.h"
#include <string.h>

// --------------------------------------------------------------------------
// Required entry point functions -------------------------------------------
// --------------------------------------------------------------------------

PP_Bool NaclHandleInputEvent( PP_Resource input_event )
{
  return PP_TRUE;
}

PP_Bool NaclInstanceCreate( uint32_t argc, const char* argn[], const char* argv[] )
{
  NaclMessagingPostPrintf("Instance_DidCreate");
  return PP_TRUE;
}

void NaclInstanceDestroy()
{
}

void NaclDidChangeView( PP_Resource view )
{
  NaclMessagingPostPrintf("Instance_DidChangeView");
}

void  NaclDidChangeFocus( PP_Bool has_focus )
{
  NaclMessagingPostPrintf("Instance_DidChangeFocus");
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
