#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// The documentation is in the includes files:
//   ~/nacl_sdk/pepper_18/toolchain/linux_x86_newlib/x86_64-nacl/include/ppapi/
//   Note: it's not totally accurate.

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_errors.h"
#include "ppapi/c/pp_var.h"
#include "ppapi/c/ppb.h"
#include "ppapi/c/ppp.h"
#include "ppapi/c/ppb_core.h"
#include "ppapi/c/ppb_instance.h"
#include "ppapi/c/ppp_instance.h"
#include "ppapi/c/ppb_messaging.h"
#include "ppapi/c/ppb_var.h"

#include "mariner.h"

// PP_Var is not typedef'd?
typedef struct PP_Var PP_Var;

// PPAPI Interfaces
const PPB_Core*      g_NaclCore      = NULL;
const PPB_Instance*  g_NaclInstance  = NULL;
const PPB_Messaging* g_NaclMessaging = NULL;
const PPB_Var*       g_NaclVar       = NULL;

// App globals

enum
{
  kInvalidInstance = 0,
};

PP_Instance g_InstanceId = kInvalidInstance;


// Helper -------------------------------------------------------------------
// Also see: Yuriy O'Donnell's ArcadeShooter NaCl Postmortem
//     http://www.kayru.org/articles/arcadeshooter-nacl-postmortem/
//     http://www.kayru.org/articles/arcadeshooter-nacl-postmortem/index.html.txt
//     http://www.kayru.org/articles/arcadeshooter-nacl-postmortem/minimal_nacl_gles2.cpp.txt

void nacl_log_message(const char* msg)
{
  PP_Var msg_var = g_NaclVar->VarFromUtf8( msg, strlen(msg) );
  g_NaclMessaging->PostMessage(g_InstanceId, msg_var);
  g_NaclVar->Release(msg_var);
}

// Instance entrypoints ------------------------------------------------------

PP_Bool Instance_DidCreate(PP_Instance instance_id, uint32_t argc, const char* argn[], const char* argv[]) 
{
  // Only allow one instance.
  assert(g_InstanceId == kInvalidInstance);

  g_InstanceId   = instance_id;

  nacl_log_message("Instance_DidCreate");

  {
    Mariner  mariner;
    char     output_buffer[ 2048 ];
    char*    output_start  = output_buffer;
    char*    output_cursor = output_buffer;
    size_t   output_size   = 0;

    output_size   += sprintf( output_cursor, "data: " );
    output_cursor += output_size;
 
    mariner.Init();
    mariner.GetPosition()->SetX( 100 );
    mariner.GetPosition()->SetY( 200 );
    mariner.GetWeapon()->Set( Weapon::kChainsaw );
    mariner.WriteJson( output_cursor, output_size );

    *output_cursor = 0;

    nacl_log_message( output_start );
  }  

  return PP_TRUE;
}

void Instance_DidDestroy(PP_Instance instance_id) 
{
  assert(instance_id == g_InstanceId);

  g_InstanceId = kInvalidInstance;

  nacl_log_message("Instance_DidDestroy");
}

void Instance_DidChangeView(PP_Instance instance_id, PP_Resource view_resource)
{
  nacl_log_message("Instance_DidChangeView");
}

void Instance_DidChangeFocus(PP_Instance instance_id, PP_Bool has_focus) 
{
  nacl_log_message("Instance_DidChangeFocus");
}

PP_Bool Instance_HandleDocumentLoad(PP_Instance instance_id, PP_Resource pp_url_loader) 
{
  nacl_log_message("Instance_HandleDocumentLoad");
  return PP_FALSE;
}

// Global entrypoints --------------------------------------------------------

PP_EXPORT int32_t PPP_InitializeModule(PP_Module module, PPB_GetInterface get_browser_interface) 
{
  if (!get_browser_interface)
  {
    return -1;
  }

  g_InstanceId    = kInvalidInstance;

  g_NaclCore      = (const PPB_Core*)      get_browser_interface(PPB_CORE_INTERFACE);
  g_NaclInstance  = (const PPB_Instance*)  get_browser_interface(PPB_INSTANCE_INTERFACE);
  g_NaclMessaging = (const PPB_Messaging*) get_browser_interface(PPB_MESSAGING_INTERFACE);
  g_NaclVar       = (const PPB_Var*)       get_browser_interface(PPB_VAR_INTERFACE);

  if (!g_NaclCore || !g_NaclInstance || !g_NaclMessaging | !g_NaclVar)
  {
    return -1;
  }

  return PP_OK;
}

PP_EXPORT void PPP_ShutdownModule() 
{
}

PP_EXPORT const void* PPP_GetInterface(const char* interface_name) 
{
  static PPP_Instance instance_interface = 
  {
    &Instance_DidCreate,
    &Instance_DidDestroy,
    &Instance_DidChangeView,
    &Instance_DidChangeFocus,
    &Instance_HandleDocumentLoad
  };

  if (strcmp(interface_name, PPP_INSTANCE_INTERFACE) == 0)
  {
    return &instance_interface;
  }

  return NULL;
}
