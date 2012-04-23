#include "nacl.h"
#include <string.h>

void nacl_log_message(const char* msg); // Helper function

// --------------------------------------------------------------------------
// Required entry point functions -------------------------------------------
// --------------------------------------------------------------------------

PP_Bool NaclHandleInputEvent( PP_Resource input_event )
{
  return PP_TRUE;
}

PP_Bool NaclInstanceCreate( uint32_t argc, const char* argn[], const char* argv[] )
{
  nacl_log_message("Instance_DidCreate");
  return PP_TRUE;
}

void NaclInstanceDestroy()
{
}

void NaclDidChangeView( PP_Resource view )
{
  nacl_log_message("Instance_DidChangeView");
}

void  NaclDidChangeFocus( PP_Bool has_focus )
{
  nacl_log_message("Instance_DidChangeFocus");
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

// --------------------------------------------------------------------------
// Helper functions ---------------------------------------------------------
// --------------------------------------------------------------------------

// void nacl_log_message(const char* msg)
// Also see: Yuriy O'Donnell's ArcadeShooter NaCl Postmortem
//     http://www.kayru.org/articles/arcadeshooter-nacl-postmortem/
//     http://www.kayru.org/articles/arcadeshooter-nacl-postmortem/index.html.txt
//     http://www.kayru.org/articles/arcadeshooter-nacl-postmortem/minimal_nacl_gles2.cpp.txt

void nacl_log_message(const char* msg)
{
  PP_Var msg_var = NaclVarVarFromUtf8( msg, strlen(msg) );
  NaclMessagingPostMessage(msg_var);
  NaclVarRelease(msg_var);
}

