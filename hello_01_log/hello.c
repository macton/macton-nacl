
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

// PP_Var is not typedef'd
typedef struct PP_Var PP_Var;

// PPAPI Interfaces
const PPB_Core*      PPBCore      = NULL;
const PPB_Instance*  PPBInstance  = NULL;
const PPB_Messaging* PPBMessaging = NULL;
const PPB_Var*       PPBVar       = NULL;

const int kInvalidInstance = 0;
const int kInvalidResource = 0;

struct InstanceInfo 
{
  PPB_GetInterface browser_interface;
  PP_Instance      instance_id;
};

typedef struct InstanceInfo InstanceInfo;

InstanceInfo global;

// Helper -------------------------------------------------------------------

void nacl_log_message(const char* msg)
{
  PP_Var msg_var = PPBVar->VarFromUtf8( msg, strlen(msg) );
  PPBMessaging->PostMessage(global.instance_id, msg_var);
  PPBVar->Release(msg_var);
}

// Instance entrypoints ------------------------------------------------------

PP_Bool Instance_DidCreate(PP_Instance instance_id, uint32_t argc, const char* argn[], const char* argv[]) 
{
  // Only allow one instance.
  assert(global.instance_id == kInvalidInstance);

  global.instance_id   = instance_id;

  nacl_log_message("Instance_DidCreate");

  return PP_TRUE;
}

void Instance_DidDestroy(PP_Instance instance_id) 
{
  assert(instance_id == global.instance_id);

  global.instance_id = kInvalidInstance;

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

  memset(&global, 0, sizeof(global));

  global.instance_id       = kInvalidInstance;
  global.browser_interface = get_browser_interface;

  PPBCore      = (const PPB_Core*)      get_browser_interface(PPB_CORE_INTERFACE);
  PPBInstance  = (const PPB_Instance*)  get_browser_interface(PPB_INSTANCE_INTERFACE);
  PPBMessaging = (const PPB_Messaging*) get_browser_interface(PPB_MESSAGING_INTERFACE);
  PPBVar       = (const PPB_Var*)       get_browser_interface(PPB_VAR_INTERFACE);

  if (!PPBCore || !PPBInstance || !PPBMessaging | !PPBVar)
  {
    return -1;
  }

  nacl_log_message("PPP_InitializeModule done.");

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
