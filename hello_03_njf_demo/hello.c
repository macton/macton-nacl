//
// Ported from Nicholas Fullagar's ppapi_njf_demo
//   Mike Acton <macton@gmail.com> <macton@insomniacgames.com> @mike_acton
//   See: https://groups.google.com/d/msg/native-client-discuss/r7SP2YwFBsE/Ig_mRpVYO3wJ
//   Hosted at: https://github.com/macton/ppapi_njf_demo
//

//
// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Demo for PPB_Graphics3D functions.
//

#include "nacl.h"
#include <string.h>
#include <alloca.h>
#include <stdio.h>

static void    RenderFrameStartup();
static void    AudioCallback ( void* sample_buffer, uint32_t buffer_size_in_bytes, void* user_data );
static int16_t TriangleWave ( int64_t counter, int32_t rate, int32_t freq, float amplitude );

int32_t             g_CursorX;
int32_t             g_CursorY;
volatile int32_t    g_KeysPressed;
PP_AudioSampleRate  g_SampleRate;
int32_t             g_SampleFrameCount;
PP_Resource         g_AudioConfigId;
PP_Resource         g_AudioId;

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
  NaclMessagingPostPrintf( "Instance_DidCreate" );

  g_CursorX     = 0;
  g_CursorY     = 0;
  g_KeysPressed = 0;

  // --------------------------------------------------------------------------
  // Request the event types that this instance will recieve.
  // --------------------------------------------------------------------------

  NaclInputEventRequestInputEvents ( PP_INPUTEVENT_CLASS_MOUSE | PP_INPUTEVENT_CLASS_KEYBOARD );

  // --------------------------------------------------------------------------
  // Create audio & register application audio callback.
  // --------------------------------------------------------------------------

  g_SampleRate = NaclAudioConfigRecommendSampleRate();

  // If RecommendSampleRate was unable to determine a sample rate, assume 48kHz.

  if ( g_SampleRate == PP_AUDIOSAMPLERATE_NONE )
  {
    g_SampleRate = PP_AUDIOSAMPLERATE_48000;
  }

  // Request a 10ms sample frame count; use what is recommended.
  g_SampleFrameCount = NaclAudioConfigRecommendSampleFrameCount ( g_SampleRate, g_SampleRate / 100 );

  // Create the audio device and start playback to trigger AudioCallback.
  // Note: The audio callback to fill the next buffer occurs on its own
  // dedicated thread.

  g_AudioConfigId = NaclAudioConfigCreateStereo16Bit ( g_SampleRate, g_SampleFrameCount );
  g_AudioId       = NaclAudioCreate ( g_AudioConfigId, AudioCallback, NULL /* user_data */ );

  NaclAudioStartPlayback ( g_AudioId );

  return PP_TRUE;
}

void NaclInstanceDestroy()
{
}

void NaclDidChangeView ( PP_Resource view )
{
  NaclMessagingPostPrintf( "Instance_DidChangeView" );
}

void  NaclDidChangeFocus ( PP_Bool has_focus )
{
  NaclMessagingPostPrintf( "Instance_DidChangeFocus" );
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
  char*  ext;

  NaclMessagingPostPrintf( "---- Starting up 3d in NaCl ----\n" );

  ext = ( char* ) glGetString ( GL_EXTENSIONS );
  NaclMessagingPostPrintf( "extensions: %s\n", ext );

  int num_formats;
  glGetIntegerv ( GL_NUM_COMPRESSED_TEXTURE_FORMATS, &num_formats );

  NaclMessagingPostPrintf( "number of compressed formats: %d\n", num_formats );

  if ( num_formats > 0 )
  {
    int*  formats = ( int* ) alloca ( num_formats * sizeof ( int ) );

    glGetIntegerv ( GL_COMPRESSED_TEXTURE_FORMATS, formats );

    for ( int i = 0; i < num_formats; i++ )
    {
      switch ( formats[i] )
      {
        case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
          NaclMessagingPostPrintf( "format %d is %s\n", i, "GL_COMPRESSED_RGB_S3TC_DXT1" );
          break;
        case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
          NaclMessagingPostPrintf( "format %d is %s\n", i, "GL_COMPRESSED_RGBA_S3TC_DXT1" );
          break;
        case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
          NaclMessagingPostPrintf( "format %d is %s\n", i, "GL_COMPRESSED_RGBA_S3TC_DXT3_EXT" );
          break;
        case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
          NaclMessagingPostPrintf( "format %d is %s\n", i, "GL_COMPRESSED_RGBA_S3TC_DXT5_EXT" );
          break;
        default:
          NaclMessagingPostPrintf( "format %d is Unknown: 0x%08x\n", i, formats[i] );
          break;
      }

    }
  }
}

int16_t TriangleWave ( int64_t counter, int32_t rate, int32_t freq, float amplitude )
{
  int32_t invfreq = rate / freq;
  float   range   = 4.0f * ( counter % invfreq ) / ( (float)invfreq );
  float   toint16 = 32767.0f;
  float   wave;

  if ( range > 3.0f )
  {
    wave = range - 4.0f;
  }
  else if ( range > 1.0f )
  {
    wave = 2.0f - range;
  }
  else
  {
    wave = range;
  }

  wave = wave * amplitude * toint16;

  if ( wave > toint16 )
  {
    wave = toint16;
  }
  else if ( wave < -toint16 )
  {
    wave = -toint16;
  }

  return (int16_t)wave;
}

// The AudioCallback function will be invoked periodically once StartPlayback()
// has been called.  It is important to fill the buffer quickly, as audio
// playback involves meeting realtime requirements.  Avoid invoking library
// calls that could cause the os scheduler to swap this thread out, such as
// mutex locks.

void AudioCallback ( void* sample_buffer, uint32_t buffer_size_in_bytes, void* user_data )
{
  int16_t*       stereo16 = ( int16_t* ) ( sample_buffer );
  static int16_t sample   = 0;
  static int64_t counter  = 0;

  for ( int32_t i = 0; i < g_SampleFrameCount; i++ )
  {
    if ( g_KeysPressed )
    {
      sample = TriangleWave ( counter, g_SampleRate, 440, 0.5f );
    }

    stereo16[i * 2 + 0] = sample;  // Left channel
    stereo16[i * 2 + 1] = sample;  // Right channel
    counter++;
  }
}

