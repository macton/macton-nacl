#include "nacl.h"
#include <string.h>
#include <alloca.h>
#include <stdio.h>

// Ported from Nicholas Fullagar's ppapi_njf_demo 
//   See: https://groups.google.com/d/msg/native-client-discuss/r7SP2YwFBsE/Ig_mRpVYO3wJ
//   Hosted at: https://github.com/macton/ppapi_njf_demo

static void RenderFrameStartup();

int32_t          g_CursorX;
int32_t          g_CursorY;
volatile int32_t g_KeysPressed;

// --------------------------------------------------------------------------
// Required entry point functions -------------------------------------------
// --------------------------------------------------------------------------

PP_Bool NaclHandleInputEvent ( PP_Resource input_event )
{
  PP_InputEvent_Type type = NaclInputEventGetType ( input_event );

  switch ( type )
  {
    case PP_INPUTEVENT_TYPE_MOUSEMOVE:
    {
      PP_Point point;
      point     = NaclMouseInputEventGetPosition ( input_event );
      g_CursorX = point.x;
      g_CursorY = point.y;
    }
    break;
    case PP_INPUTEVENT_TYPE_MOUSEDOWN:
    case PP_INPUTEVENT_TYPE_KEYDOWN:
    {
      g_KeysPressed++;
    }
    break;
    case PP_INPUTEVENT_TYPE_MOUSEUP:
    case PP_INPUTEVENT_TYPE_KEYUP:
    {
      g_KeysPressed = ( g_KeysPressed == 0 ) ? 0 : g_KeysPressed - 1;
    }
    break;
    default:
      break;
  }

  return PP_TRUE;
}

PP_Bool NaclInstanceCreate ( uint32_t argc, const char* argn[], const char* argv[] )
{
  NaclMessagingPostUtf8 ( "Instance_DidCreate" );
  g_CursorX     = 0;
  g_CursorY     = 0;
  g_KeysPressed = 0;
  NaclInputEventRequestInputEvents ( PP_INPUTEVENT_CLASS_MOUSE | PP_INPUTEVENT_CLASS_KEYBOARD );
  return PP_TRUE;
}

void NaclInstanceDestroy()
{
}

void NaclDidChangeView ( PP_Resource view )
{
  NaclMessagingPostUtf8 ( "Instance_DidChangeView" );
}

void  NaclDidChangeFocus ( PP_Bool has_focus )
{
  NaclMessagingPostUtf8 ( "Instance_DidChangeFocus" );
}

PP_Bool NaclHandleDocumentLoad ( PP_Resource url_loader )
{
  return PP_TRUE;
}

void NaclHandleMessage ( PP_Var message )
{
}

void NaclMouseLockLost()
{
}

void NaclRenderFrame()
{
  static int32_t counter = 0;

  if ( counter == 0 )
  {
    RenderFrameStartup();
  }

  glEnable ( GL_SCISSOR_TEST );
  glViewport ( 0, 0, g_NaclViewWidth, g_NaclViewHeight );
  glScissor ( 0, 0,  g_NaclViewWidth, g_NaclViewHeight );
  glClearColor ( 0.0f, 1.0f, 0.0f, 1.0f );
  glClear ( GL_COLOR_BUFFER_BIT );
  glScissor ( 5, 5, g_NaclViewWidth - 10, g_NaclViewHeight - 10 );
  float blue = 1.0f;
  glClearColor ( 0.0f, 0.0f, blue, 1.0f );
  glClear ( GL_COLOR_BUFFER_BIT );
  // Draw a box under the cursor.  Need to flip vertically as gl expects
  // the origin to be the lower right corner.
  const int32_t box_size = 40;
  int32_t       box_x    = g_CursorX - box_size / 2;
  int32_t       box_y    = g_NaclViewHeight - g_CursorY - box_size / 2;
  glScissor ( box_x, box_y, box_size, box_size );
  glClearColor ( 1.0f, g_KeysPressed ? 1.0f : 0.0f, 0.0f, 1.0f );
  glClear ( GL_COLOR_BUFFER_BIT );
  counter++;
}

// --------------------------------------------------------------------------
// Application functions ----------------------------------------------------
// --------------------------------------------------------------------------

void RenderFrameStartup()
{
  char   message_buffer[ 4096 ];
  char*  ext;
  NaclMessagingPostUtf8 ( "---- Starting up 3d in NaCl\n" );
  ext = ( char* ) glGetString ( GL_EXTENSIONS );
  sprintf ( message_buffer, "extensions: %s\n", ext );
  NaclMessagingPostUtf8 ( message_buffer );
  int num_formats;
  glGetIntegerv ( GL_NUM_COMPRESSED_TEXTURE_FORMATS, &num_formats );
  sprintf ( message_buffer, "number of compressed formats: %d\n", num_formats );
  NaclMessagingPostUtf8 ( message_buffer );

  if ( num_formats > 0 )
  {
    int*        formats = ( int* ) alloca ( num_formats * sizeof ( int ) );
    const char* fmtstr;
    char        temp[1024];
    glGetIntegerv ( GL_COMPRESSED_TEXTURE_FORMATS, formats );

    for ( int i = 0; i < num_formats; i++ )
    {
      switch ( formats[i] )
      {
        case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
          fmtstr = "GL_COMPRESSED_RGB_S3TC_DXT1";
          break;
        case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
          fmtstr = "GL_COMPRESSED_RGBA_S3TC_DXT1";
          break;
        case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
          fmtstr = "GL_COMPRESSED_RGBA_S3TC_DXT3_EXT";
          break;
        case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
          fmtstr = "GL_COMPRESSED_RGBA_S3TC_DXT5_EXT";
          break;
        default:
          fmtstr = ( const char* ) sprintf ( temp, "Unknown: 0x%0x", formats[i] );
          break;
      }

      sprintf ( message_buffer, "format %d is %s\n", i, fmtstr );
      NaclMessagingPostUtf8 ( message_buffer );
    }
  }
}

