
#define NACL_C_INLINE
#include "nacl.h"

#include <assert.h>
#include <string.h>

// --------------------------------------------------------------------------------------------
// Global instance (There can be only one!)
// --------------------------------------------------------------------------------------------

PP_Instance                      g_NaclInstanceId;
int32_t                          g_NaclViewWidth;
int32_t                          g_NaclViewHeight;
PP_Resource                      g_NaclGraphics3dId;
int32_t                          g_NaclGraphics3dLastSwapResult;

// --------------------------------------------------------------------------------------------
// PPB Interface globals
// --------------------------------------------------------------------------------------------

const PPB_Audio*                 g_NaclAudio;                  // (5) functions
const PPB_AudioConfig*           g_NaclAudioConfig;            // (5) functions
const PPB_Core*                  g_NaclCore;                   // (6) functions
const PPB_FileIO*                g_NaclFileIO;                 // (10) functions
const PPB_FileRef*               g_NaclFileRef;                // (10) functions
const PPB_FileSystem*            g_NaclFileSystem;             // (4) functions
const PPB_Fullscreen*            g_NaclFullscreen;             // (3) functions
const PPB_Graphics2D*            g_NaclGraphics2D;             // (7) functions
const PPB_Graphics3D*            g_NaclGraphics3D;             // (8) functions
const PPB_ImageData*             g_NaclImageData;              // (7) functions
const PPB_InputEvent*            g_NaclInputEvent;             // (7) functions
const PPB_Instance*              g_NaclInstance;               // (2) functions
const PPB_KeyboardInputEvent*    g_NaclKeyboardInputEvent;     // (4) functions
const PPB_Messaging*             g_NaclMessaging;              // (1) functions
const PPB_MouseInputEvent*       g_NaclMouseInputEvent;        // (6) functions
const PPB_MouseLock*             g_NaclMouseLock;              // (2) functions
const PPB_OpenGLES2*             g_NaclOpenGLES2;              // (142) functions
const PPB_URLLoader*             g_NaclURLLoader;              // (10) functions
const PPB_URLRequestInfo*        g_NaclURLRequestInfo;         // (5) functions
const PPB_URLResponseInfo*       g_NaclURLResponseInfo;        // (3) functions
const PPB_Var*                   g_NaclVar;                    // (4) functions
const PPB_VarArrayBuffer*        g_NaclVarArrayBuffer;         // (4) functions
const PPB_View*                  g_NaclView;                   // (6) functions
const PPB_WebSocket*             g_NaclWebSocket;              // (14) functions
const PPB_WheelInputEvent*       g_NaclWheelInputEvent;        // (5) functions

// --------------------------------------------------------------------------------------------
// Internal functions
// --------------------------------------------------------------------------------------------
static void PPP_RenderLoop( void* user_data, int32_t result );

// --------------------------------------------------------------------------------------------
// PPP_Instance entry points
// --------------------------------------------------------------------------------------------

PP_Bool PPP_Instance_DidCreate(PP_Instance instance, uint32_t argc, const char* argn[], const char* argv[]) 
{
  if ( g_NaclInstanceId != kNaclInvalidInstance )
  {
    return PP_FALSE; // Only one instance allowed.
  }

  g_NaclInstanceId               = instance;
  g_NaclViewWidth                = 0;
  g_NaclViewHeight               = 0;
  g_NaclGraphics3dId             = kNaclInvalidResource;
  g_NaclGraphics3dLastSwapResult = 0;

  return NaclInstanceCreate( argc, argn, argv );
}

void PPP_Instance_DidDestroy(PP_Instance instance) 
{
  assert(instance == g_NaclInstanceId);

  NaclInstanceDestroy();

  g_NaclInstanceId = kNaclInvalidInstance;
}

void PPP_Instance_DidChangeView(PP_Instance instance, PP_Resource view_resource)
{
  assert(instance == g_NaclInstanceId);

  PP_Rect position;
  PP_Rect clip;

  if ( !NaclViewGetRect( view_resource, &position ) )
  {
    return;
  }

  if ( !NaclViewGetClipRect( view_resource, &clip ) )
  {
    return;
  }

  if ( g_NaclGraphics3dId == kNaclInvalidResource )
  {
    int32_t attribs[] = 
    {
      PP_GRAPHICS3DATTRIB_ALPHA_SIZE,           kNaclGraphicsAttribAlphaSize,
      PP_GRAPHICS3DATTRIB_DEPTH_SIZE,           kNaclGraphicsAttribDepthSize,
      PP_GRAPHICS3DATTRIB_STENCIL_SIZE,         kNaclGraphicsAttribStencilSize,
      PP_GRAPHICS3DATTRIB_SAMPLES,              kNaclGraphicsAttribSamples,
      PP_GRAPHICS3DATTRIB_SAMPLE_BUFFERS,       kNaclGraphicsAttribSampleBuffers,
      PP_GRAPHICS3DATTRIB_WIDTH,                position.size.width,
      PP_GRAPHICS3DATTRIB_HEIGHT,               position.size.height,
      PP_GRAPHICS3DATTRIB_NONE
    };

    g_NaclGraphics3dId  = NaclGraphics3DCreate( kNaclInvalidResource, attribs );
    int32_t success     = NaclInstanceBindGraphics( g_NaclGraphics3dId );

    if (success == PP_TRUE)  
    {
      PP_CompletionCallback cc = PP_MakeCompletionCallback( PPP_RenderLoop, NULL );
      NaclCoreCallOnMainThread(0, cc, PP_OK);
    }
  } 
  else if ((position.size.width != g_NaclViewWidth) || (position.size.height != g_NaclViewHeight))
  {
    NaclGraphics3DResizeBuffers( g_NaclGraphics3dId, position.size.width, position.size.height );
  }

  g_NaclViewWidth  = position.size.width;
  g_NaclViewHeight = position.size.height;

  NaclDidChangeView( view_resource );
}

void PPP_Instance_DidChangeFocus(PP_Instance instance, PP_Bool has_focus) 
{
  assert(instance == g_NaclInstanceId);
  NaclDidChangeFocus( has_focus );
}

PP_Bool PPP_Instance_HandleDocumentLoad(PP_Instance instance, PP_Resource url_loader) 
{
  assert(instance == g_NaclInstanceId);
  return NaclHandleDocumentLoad( url_loader );
}

// --------------------------------------------------------------------------------------------
// PPP_InputEvent entry points
// --------------------------------------------------------------------------------------------

PP_Bool PPP_InputEvent_HandleInputEvent( PP_Instance instance, PP_Resource input_event )
{
  assert(instance == g_NaclInstanceId);
  return NaclHandleInputEvent( input_event );
}

// --------------------------------------------------------------------------------------------
// PPP_Messaging entry points
// --------------------------------------------------------------------------------------------

void PPP_Messaging_HandleMessage( PP_Instance instance, PP_Var message )
{
  assert(instance == g_NaclInstanceId);
  NaclHandleMessage( message );
}

// --------------------------------------------------------------------------------------------
// PPP_MouseLock entry points
// --------------------------------------------------------------------------------------------

void PPP_MouseLock_MouseLockLost( PP_Instance instance )
{
  assert(instance == g_NaclInstanceId);
  NaclMouseLockLost();
}

// --------------------------------------------------------------------------------------------
// Module entry points
// --------------------------------------------------------------------------------------------

PP_EXPORT int32_t PPP_InitializeModule(PP_Module module, PPB_GetInterface get_browser_interface) 
{
  if (!get_browser_interface)
  {
    return -1;
  }

  g_NaclInstanceId            = kNaclInvalidInstance;
  g_NaclAudio                 = (const PPB_Audio*)               get_browser_interface(PPB_AUDIO_INTERFACE);
  g_NaclAudioConfig           = (const PPB_AudioConfig*)         get_browser_interface(PPB_AUDIO_CONFIG_INTERFACE);
  g_NaclCore                  = (const PPB_Core*)                get_browser_interface(PPB_CORE_INTERFACE);
  g_NaclFileIO                = (const PPB_FileIO*)              get_browser_interface(PPB_FILEIO_INTERFACE);
  g_NaclFileRef               = (const PPB_FileRef*)             get_browser_interface(PPB_FILEREF_INTERFACE);
  g_NaclFileSystem            = (const PPB_FileSystem*)          get_browser_interface(PPB_FILESYSTEM_INTERFACE);
  g_NaclFullscreen            = (const PPB_Fullscreen*)          get_browser_interface(PPB_FULLSCREEN_INTERFACE);
  g_NaclGraphics2D            = (const PPB_Graphics2D*)          get_browser_interface(PPB_GRAPHICS_2D_INTERFACE);
  g_NaclGraphics3D            = (const PPB_Graphics3D*)          get_browser_interface(PPB_GRAPHICS_3D_INTERFACE);
  g_NaclImageData             = (const PPB_ImageData*)           get_browser_interface(PPB_IMAGEDATA_INTERFACE);
  g_NaclInputEvent            = (const PPB_InputEvent*)          get_browser_interface(PPB_INPUT_EVENT_INTERFACE);
  g_NaclInstance              = (const PPB_Instance*)            get_browser_interface(PPB_INSTANCE_INTERFACE);
  g_NaclKeyboardInputEvent    = (const PPB_KeyboardInputEvent*)  get_browser_interface(PPB_KEYBOARD_INPUT_EVENT_INTERFACE);
  g_NaclMessaging             = (const PPB_Messaging*)           get_browser_interface(PPB_MESSAGING_INTERFACE);
  g_NaclMouseInputEvent       = (const PPB_MouseInputEvent*)     get_browser_interface(PPB_MOUSE_INPUT_EVENT_INTERFACE);
  g_NaclMouseLock             = (const PPB_MouseLock*)           get_browser_interface(PPB_MOUSELOCK_INTERFACE);
  g_NaclOpenGLES2             = (const PPB_OpenGLES2*)           get_browser_interface(PPB_OPENGLES2_INTERFACE);
  g_NaclURLLoader             = (const PPB_URLLoader*)           get_browser_interface(PPB_URLLOADER_INTERFACE);
  g_NaclURLRequestInfo        = (const PPB_URLRequestInfo*)      get_browser_interface(PPB_URLREQUESTINFO_INTERFACE);
  g_NaclURLResponseInfo       = (const PPB_URLResponseInfo*)     get_browser_interface(PPB_URLRESPONSEINFO_INTERFACE);
  g_NaclVar                   = (const PPB_Var*)                 get_browser_interface(PPB_VAR_INTERFACE);
  g_NaclVarArrayBuffer        = (const PPB_VarArrayBuffer*)      get_browser_interface(PPB_VAR_ARRAY_BUFFER_INTERFACE);
  g_NaclView                  = (const PPB_View*)                get_browser_interface(PPB_VIEW_INTERFACE);
  g_NaclWebSocket             = (const PPB_WebSocket*)           get_browser_interface(PPB_WEBSOCKET_INTERFACE);
  g_NaclWheelInputEvent       = (const PPB_WheelInputEvent*)     get_browser_interface(PPB_WHEEL_INPUT_EVENT_INTERFACE);

  if ( (!g_NaclInstance)
    || (!g_NaclAudio)
    || (!g_NaclAudioConfig)
    || (!g_NaclCore)
    || (!g_NaclFileIO)
    || (!g_NaclFileRef)
    || (!g_NaclFileSystem)
    || (!g_NaclFullscreen)
    || (!g_NaclGraphics2D)
    || (!g_NaclGraphics3D)
    || (!g_NaclImageData)
    || (!g_NaclInputEvent)
    || (!g_NaclInstance)
    || (!g_NaclKeyboardInputEvent)
    || (!g_NaclMessaging)
    || (!g_NaclMouseInputEvent)
    || (!g_NaclMouseLock)
    || (!g_NaclOpenGLES2)
    || (!g_NaclURLLoader)
    || (!g_NaclURLRequestInfo)
    || (!g_NaclURLResponseInfo)
    || (!g_NaclVar)
    || (!g_NaclVarArrayBuffer)
    || (!g_NaclView)
    || (!g_NaclWebSocket)
    || (!g_NaclWheelInputEvent) )
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
    &PPP_Instance_DidCreate,
    &PPP_Instance_DidDestroy,
    &PPP_Instance_DidChangeView,
    &PPP_Instance_DidChangeFocus,
    &PPP_Instance_HandleDocumentLoad
  };

  static PPP_InputEvent input_event_interface =
  {
    &PPP_InputEvent_HandleInputEvent
  };

  static PPP_Messaging messaging_interface =
  {
    &PPP_Messaging_HandleMessage
  };

  static PPP_MouseLock mouse_lock_lost_interface = 
  {
    &PPP_MouseLock_MouseLockLost
  };

  if (strcmp(interface_name, PPP_INSTANCE_INTERFACE) == 0)
  {
    return &instance_interface;
  }

  if (strcmp(interface_name, PPP_INPUT_EVENT_INTERFACE) == 0)
  {
    return &input_event_interface;
  }

  if (strcmp(interface_name, PPP_MESSAGING_INTERFACE) == 0)
  {
    return &messaging_interface;
  }

  if (strcmp(interface_name, PPP_MOUSELOCK_INTERFACE) == 0)
  {
    return &mouse_lock_lost_interface;
  }

  return NULL;
}

// --------------------------------------------------------------------------------------------
// Internal functions
// --------------------------------------------------------------------------------------------

void PPP_RenderLoop( void* user_data, int32_t result ) 
{
  glSetCurrentContextPPAPI( g_NaclGraphics3dId );

  NaclRenderFrame();

  glSetCurrentContextPPAPI(0);

  PP_CompletionCallback cc       = PP_MakeCompletionCallback( PPP_RenderLoop, NULL );
  g_NaclGraphics3dLastSwapResult = PPBGraphics3D->SwapBuffers(instance->graphics3d_id, cc);
}


// --------------------------------------------------------------------------------------------
// Utility functions (not part of API)
// --------------------------------------------------------------------------------------------

// void NaclMessagingPostUtf8(const char* msg)
// Also see: Yuriy O'Donnell's ArcadeShooter NaCl Postmortem
//     http://www.kayru.org/articles/arcadeshooter-nacl-postmortem/
//     http://www.kayru.org/articles/arcadeshooter-nacl-postmortem/index.html.txt
//     http://www.kayru.org/articles/arcadeshooter-nacl-postmortem/minimal_nacl_gles2.cpp.txt

void NaclMessagingPostUtf8(const char* msg)
{
  PP_Var msg_var = NaclVarVarFromUtf8( msg, strlen(msg) );
  NaclMessagingPostMessage(msg_var);
  NaclVarRelease(msg_var);
}


