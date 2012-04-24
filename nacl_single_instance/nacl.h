#pragma once
// --------------------------------------------------------------------------------------------
// DO NOT EDIT: This is generated code.
// --------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------
// Native Client (NaCl) single instance interface (Pepper 18)
// Mike Acton <macton@insomniacgames.com> <macton@gmail.com> @mike_acton
//
// This interface makes two assumptions for the common case:
//   - You only want one instance of a module. (*1)
//   - The NaCl API functions are all called from the same (main) thread (*2) (*3).
//
// (*1) See also: https://groups.google.com/d/msg/native-client-discuss/70hXg3AACeE/3Fau7EpCFUEJ
// (*2) Functions which add NaCl API calls to a queue to be called from the main thread could
//      also be generated to relieve this constraint. This is also the recommended approach from
//      Colt McAnlis @ Google. Check out his talk from #GDC12: http://youtu.be/R281PhQufHo
// (*3) With this constraint, most PP_Var conversion can be handled internally. #todo.
//
// #todo Also remove the OGL context params to make equivalent to gl_* calls.
//       ...or just remove them entirely since they're redundant.
// --------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------
// Except for instance parameters, documentation corresponds to what's in the NaCl include files:
//   ~/nacl_sdk/pepper_18/toolchain/linux_x86_newlib/x86_64-nacl/include/ppapi/
//   Note: The documentation in those headers isn't totally accurate.
// --------------------------------------------------------------------------------------------
#include "ppapi/c/pp_point.h"
#include "ppapi/c/pp_rect.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_size.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_time.h"
#include "ppapi/c/pp_var.h"
#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_errors.h"
#include "ppapi/c/pp_file_info.h"
#include "ppapi/c/pp_graphics_3d.h"
#include "ppapi/c/pp_input_event.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_module.h"
#include "ppapi/c/ppp_graphics_3d.h"
#include "ppapi/c/ppp.h"
#include "ppapi/c/ppp_input_event.h"
#include "ppapi/c/ppp_instance.h"
#include "ppapi/c/ppp_messaging.h"
#include "ppapi/c/ppp_mouse_lock.h"
#include "ppapi/c/ppb_audio_config.h"
#include "ppapi/c/ppb_audio.h"
#include "ppapi/c/ppb_core.h"
#include "ppapi/c/ppb_file_io.h"
#include "ppapi/c/ppb_file_ref.h"
#include "ppapi/c/ppb_file_system.h"
#include "ppapi/c/ppb_fullscreen.h"
#include "ppapi/c/ppb_graphics_2d.h"
#include "ppapi/c/ppb_graphics_3d.h"
#include "ppapi/c/ppb.h"
#include "ppapi/c/ppb_image_data.h"
#include "ppapi/c/ppb_input_event.h"
#include "ppapi/c/ppb_instance.h"
#include "ppapi/c/ppb_messaging.h"
#include "ppapi/c/ppb_mouse_lock.h"
#include "ppapi/c/ppb_opengles2.h"
#include "ppapi/c/ppb_url_loader.h"
#include "ppapi/c/ppb_url_request_info.h"
#include "ppapi/c/ppb_url_response_info.h"
#include "ppapi/c/ppb_var_array_buffer.h"
#include "ppapi/c/ppb_var.h"
#include "ppapi/c/ppb_view.h"
#include "ppapi/c/ppb_websocket.h"

// --------------------------------------------------------------------------------------------
// Additional (missing?) typedefs
// --------------------------------------------------------------------------------------------
#ifndef __cplusplus
typedef struct PPB_OpenGLES2          PPB_OpenGLES2;
typedef struct PP_Var                 PP_Var;
typedef struct PP_Rect                PP_Rect;
typedef struct PP_Point               PP_Point;
typedef struct PP_Size                PP_Size;
typedef struct PP_FileInfo            PP_FileInfo;
typedef struct PP_CompletionCallback  PP_CompletionCallback;
#endif

#ifdef __cplusplus
extern "C" {
#endif

// --------------------------------------------------------------------------------------------
// These are the functions you must provide to use this API:
// --------------------------------------------------------------------------------------------
PP_Bool NaclHandleInputEvent( PP_Resource input_event );
PP_Bool NaclInstanceCreate( uint32_t argc, const char* argn[], const char* argv[] );
void    NaclInstanceDestroy();
void    NaclDidChangeView( PP_Resource view );
void    NaclDidChangeFocus( PP_Bool has_focus );
PP_Bool NaclHandleDocumentLoad( PP_Resource url_loader );
void    NaclHandleMessage( struct PP_Var message );
void    NaclMouseLockLost();

#ifdef NACL_C_INLINE
// --------------------------------------------------------------------------------------------
// PPB_Audio interface
// --------------------------------------------------------------------------------------------
extern PP_Resource                   NaclAudioCreate( PP_Resource config, PPB_Audio_Callback audio_callback, void* user_data );
extern PP_Bool                       NaclAudioIsAudio( PP_Resource resource );
extern PP_Resource                   NaclAudioGetCurrentConfig( PP_Resource audio );
extern PP_Bool                       NaclAudioStartPlayback( PP_Resource audio );
extern PP_Bool                       NaclAudioStopPlayback( PP_Resource audio );

// --------------------------------------------------------------------------------------------
// PPB_AudioConfig interface
// --------------------------------------------------------------------------------------------
extern PP_Resource                   NaclAudioConfigCreateStereo16Bit( PP_AudioSampleRate sample_rate, uint32_t sample_frame_count );
extern uint32_t                      NaclAudioConfigRecommendSampleFrameCount( PP_AudioSampleRate sample_rate, uint32_t requested_sample_frame_count );
extern PP_Bool                       NaclAudioConfigIsAudioConfig( PP_Resource resource );
extern PP_AudioSampleRate            NaclAudioConfigGetSampleRate( PP_Resource config );
extern uint32_t                      NaclAudioConfigGetSampleFrameCount( PP_Resource config );

// --------------------------------------------------------------------------------------------
// PPB_Core interface
// --------------------------------------------------------------------------------------------
extern void                          NaclCoreAddRefResource( PP_Resource resource );
extern void                          NaclCoreReleaseResource( PP_Resource resource );
extern PP_Time                       NaclCoreGetTime(  );
extern PP_TimeTicks                  NaclCoreGetTimeTicks(  );
extern void                          NaclCoreCallOnMainThread( int32_t delay_in_milliseconds, PP_CompletionCallback callback, int32_t result );
extern PP_Bool                       NaclCoreIsMainThread(  );

// --------------------------------------------------------------------------------------------
// PPB_FileIO interface
// --------------------------------------------------------------------------------------------
extern PP_Resource                   NaclFileIOCreate(  );
extern PP_Bool                       NaclFileIOIsFileIO( PP_Resource resource );
extern int32_t                       NaclFileIOOpen( PP_Resource file_io, PP_Resource file_ref, int32_t open_flags, PP_CompletionCallback callback );
extern int32_t                       NaclFileIOQuery( PP_Resource file_io, struct PP_FileInfo* info, PP_CompletionCallback callback );
extern int32_t                       NaclFileIOTouch( PP_Resource file_io, PP_Time last_access_time, PP_Time last_modified_time, PP_CompletionCallback callback );
extern int32_t                       NaclFileIORead( PP_Resource file_io, int64_t offset, char* buffer, int32_t bytes_to_read, PP_CompletionCallback callback );
extern int32_t                       NaclFileIOWrite( PP_Resource file_io, int64_t offset, const char* buffer, int32_t bytes_to_write, PP_CompletionCallback callback );
extern int32_t                       NaclFileIOSetLength( PP_Resource file_io, int64_t length, PP_CompletionCallback callback );
extern int32_t                       NaclFileIOFlush( PP_Resource file_io, PP_CompletionCallback callback );
extern void                          NaclFileIOClose( PP_Resource file_io );

// --------------------------------------------------------------------------------------------
// PPB_FileRef interface
// --------------------------------------------------------------------------------------------
extern PP_Resource                   NaclFileRefCreate( PP_Resource file_system, const char* path );
extern PP_Bool                       NaclFileRefIsFileRef( PP_Resource resource );
extern PP_FileSystemType             NaclFileRefGetFileSystemType( PP_Resource file_ref );
extern PP_Var                        NaclFileRefGetName( PP_Resource file_ref );
extern PP_Var                        NaclFileRefGetPath( PP_Resource file_ref );
extern PP_Resource                   NaclFileRefGetParent( PP_Resource file_ref );
extern int32_t                       NaclFileRefMakeDirectory( PP_Resource directory_ref, PP_Bool make_ancestors, PP_CompletionCallback callback );
extern int32_t                       NaclFileRefTouch( PP_Resource file_ref, PP_Time last_access_time, PP_Time last_modified_time, PP_CompletionCallback callback );
extern int32_t                       NaclFileRefDelete( PP_Resource file_ref, PP_CompletionCallback callback );
extern int32_t                       NaclFileRefRename( PP_Resource file_ref, PP_Resource new_file_ref, PP_CompletionCallback callback );

// --------------------------------------------------------------------------------------------
// PPB_FileSystem interface
// --------------------------------------------------------------------------------------------
extern PP_Resource                   NaclFileSystemCreate( PP_FileSystemType type );
extern PP_Bool                       NaclFileSystemIsFileSystem( PP_Resource resource );
extern int32_t                       NaclFileSystemOpen( PP_Resource file_system, int64_t expected_size, PP_CompletionCallback callback );
extern PP_FileSystemType             NaclFileSystemGetType( PP_Resource file_system );

// --------------------------------------------------------------------------------------------
// PPB_Fullscreen interface
// --------------------------------------------------------------------------------------------
extern PP_Bool                       NaclFullscreenIsFullscreen(  );
extern PP_Bool                       NaclFullscreenSetFullscreen( PP_Bool fullscreen );
extern PP_Bool                       NaclFullscreenGetScreenSize( struct PP_Size* size );

// --------------------------------------------------------------------------------------------
// PPB_Graphics2D interface
// --------------------------------------------------------------------------------------------
extern PP_Resource                   NaclGraphics2DCreate( const struct PP_Size* size, PP_Bool is_always_opaque );
extern PP_Bool                       NaclGraphics2DIsGraphics2D( PP_Resource resource );
extern PP_Bool                       NaclGraphics2DDescribe( PP_Resource graphics_2d, struct PP_Size* size, PP_Bool* is_always_opqaue );
extern void                          NaclGraphics2DPaintImageData( PP_Resource graphics_2d, PP_Resource image_data, const struct PP_Point* top_left, const struct PP_Rect* src_rect );
extern void                          NaclGraphics2DScroll( PP_Resource graphics_2d, const struct PP_Rect* clip_rect, const struct PP_Point* amount );
extern void                          NaclGraphics2DReplaceContents( PP_Resource graphics_2d, PP_Resource image_data );
extern int32_t                       NaclGraphics2DFlush( PP_Resource graphics_2d, PP_CompletionCallback callback );

// --------------------------------------------------------------------------------------------
// PPB_Graphics3D interface
// --------------------------------------------------------------------------------------------
extern int32_t                       NaclGraphics3DGetAttribMaxValue( PP_Resource instance, int32_t attribute, int32_t* value );
extern PP_Resource                   NaclGraphics3DCreate( PP_Resource share_context, const int32_t attrib_list[] );
extern PP_Bool                       NaclGraphics3DIsGraphics3D( PP_Resource resource );
extern int32_t                       NaclGraphics3DGetAttribs( PP_Resource context, int32_t attrib_list[] );
extern int32_t                       NaclGraphics3DSetAttribs( PP_Resource context, int32_t attrib_list[] );
extern int32_t                       NaclGraphics3DGetError( PP_Resource context );
extern int32_t                       NaclGraphics3DResizeBuffers( PP_Resource context, int32_t width, int32_t height );
extern int32_t                       NaclGraphics3DSwapBuffers( PP_Resource context, PP_CompletionCallback callback );

// --------------------------------------------------------------------------------------------
// PPB_ImageData interface
// --------------------------------------------------------------------------------------------
extern PP_ImageDataFormat            NaclImageDataGetNativeImageDataFormat(  );
extern PP_Bool                       NaclImageDataIsImageDataFormatSupported( PP_ImageDataFormat format );
extern PP_Resource                   NaclImageDataCreate( PP_ImageDataFormat format, const struct PP_Size* size, PP_Bool init_to_zero );
extern PP_Bool                       NaclImageDataIsImageData( PP_Resource image_data );
extern PP_Bool                       NaclImageDataDescribe( PP_Resource image_data, struct PP_ImageDataDesc* desc );
extern void*                         NaclImageDataMap( PP_Resource image_data );
extern void                          NaclImageDataUnmap( PP_Resource image_data );

// --------------------------------------------------------------------------------------------
// PPB_InputEvent interface
// --------------------------------------------------------------------------------------------
extern int32_t                       NaclInputEventRequestInputEvents( uint32_t event_classes );
extern int32_t                       NaclInputEventRequestFilteringInputEvents( uint32_t event_classes );
extern void                          NaclInputEventClearInputEventRequest( uint32_t event_classes );
extern PP_Bool                       NaclInputEventIsInputEvent( PP_Resource resource );
extern PP_InputEvent_Type            NaclInputEventGetType( PP_Resource event );
extern PP_TimeTicks                  NaclInputEventGetTimeStamp( PP_Resource event );
extern uint32_t                      NaclInputEventGetModifiers( PP_Resource event );

// --------------------------------------------------------------------------------------------
// PPB_Instance interface
// --------------------------------------------------------------------------------------------
extern PP_Bool                       NaclInstanceBindGraphics( PP_Resource device );
extern PP_Bool                       NaclInstanceIsFullFrame(  );

// --------------------------------------------------------------------------------------------
// PPB_KeyboardInputEvent interface
// --------------------------------------------------------------------------------------------
extern PP_Resource                   NaclKeyboardInputEventCreate( PP_InputEvent_Type type, PP_TimeTicks time_stamp, uint32_t modifiers, uint32_t key_code, PP_Var character_text );
extern PP_Bool                       NaclKeyboardInputEventIsKeyboardInputEvent( PP_Resource resource );
extern uint32_t                      NaclKeyboardInputEventGetKeyCode( PP_Resource key_event );
extern PP_Var                        NaclKeyboardInputEventGetCharacterText( PP_Resource character_event );

// --------------------------------------------------------------------------------------------
// PPB_Messaging interface
// --------------------------------------------------------------------------------------------
extern void                          NaclMessagingPostMessage( PP_Var message );

// --------------------------------------------------------------------------------------------
// PPB_MouseInputEvent interface
// --------------------------------------------------------------------------------------------
extern PP_Resource                   NaclMouseInputEventCreate( PP_InputEvent_Type type, PP_TimeTicks time_stamp, uint32_t modifiers, PP_InputEvent_MouseButton mouse_button, const struct PP_Point* mouse_position, int32_t click_count, const struct PP_Point* mouse_movement );
extern PP_Bool                       NaclMouseInputEventIsMouseInputEvent( PP_Resource resource );
extern PP_InputEvent_MouseButton     NaclMouseInputEventGetButton( PP_Resource mouse_event );
extern PP_Point                      NaclMouseInputEventGetPosition( PP_Resource mouse_event );
extern int32_t                       NaclMouseInputEventGetClickCount( PP_Resource mouse_event );
extern PP_Point                      NaclMouseInputEventGetMovement( PP_Resource mouse_event );

// --------------------------------------------------------------------------------------------
// PPB_MouseLock interface
// --------------------------------------------------------------------------------------------
extern int32_t                       NaclMouseLockLockMouse( PP_CompletionCallback callback );
extern void                          NaclMouseLockUnlockMouse(  );

// --------------------------------------------------------------------------------------------
// PPB_OpenGLES2 interface
// --------------------------------------------------------------------------------------------
extern void                          NaclOpenGLES2ActiveTexture( PP_Resource context, GLenum texture );
extern void                          NaclOpenGLES2AttachShader( PP_Resource context, GLuint program, GLuint shader );
extern void                          NaclOpenGLES2BindAttribLocation( PP_Resource context, GLuint program, GLuint index, const char* name );
extern void                          NaclOpenGLES2BindBuffer( PP_Resource context, GLenum target, GLuint buffer );
extern void                          NaclOpenGLES2BindFramebuffer( PP_Resource context, GLenum target, GLuint framebuffer );
extern void                          NaclOpenGLES2BindRenderbuffer( PP_Resource context, GLenum target, GLuint renderbuffer );
extern void                          NaclOpenGLES2BindTexture( PP_Resource context, GLenum target, GLuint texture );
extern void                          NaclOpenGLES2BlendColor( PP_Resource context, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );
extern void                          NaclOpenGLES2BlendEquation( PP_Resource context, GLenum mode );
extern void                          NaclOpenGLES2BlendEquationSeparate( PP_Resource context, GLenum modeRGB, GLenum modeAlpha );
extern void                          NaclOpenGLES2BlendFunc( PP_Resource context, GLenum sfactor, GLenum dfactor );
extern void                          NaclOpenGLES2BlendFuncSeparate( PP_Resource context, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha );
extern void                          NaclOpenGLES2BufferData( PP_Resource context, GLenum target, GLsizeiptr size, const void* data, GLenum usage );
extern void                          NaclOpenGLES2BufferSubData( PP_Resource context, GLenum target, GLintptr offset, GLsizeiptr size, const void* data );
extern GLenum                        NaclOpenGLES2CheckFramebufferStatus( PP_Resource context, GLenum target );
extern void                          NaclOpenGLES2Clear( PP_Resource context, GLbitfield mask );
extern void                          NaclOpenGLES2ClearColor( PP_Resource context, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );
extern void                          NaclOpenGLES2ClearDepthf( PP_Resource context, GLclampf depth );
extern void                          NaclOpenGLES2ClearStencil( PP_Resource context, GLint s );
extern void                          NaclOpenGLES2ColorMask( PP_Resource context, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha );
extern void                          NaclOpenGLES2CompileShader( PP_Resource context, GLuint shader );
extern void                          NaclOpenGLES2CompressedTexImage2D( PP_Resource context, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data );
extern void                          NaclOpenGLES2CompressedTexSubImage2D( PP_Resource context, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data );
extern void                          NaclOpenGLES2CopyTexImage2D( PP_Resource context, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border );
extern void                          NaclOpenGLES2CopyTexSubImage2D( PP_Resource context, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height );
extern GLuint                        NaclOpenGLES2CreateProgram( PP_Resource context );
extern GLuint                        NaclOpenGLES2CreateShader( PP_Resource context, GLenum type );
extern void                          NaclOpenGLES2CullFace( PP_Resource context, GLenum mode );
extern void                          NaclOpenGLES2DeleteBuffers( PP_Resource context, GLsizei n, const GLuint* buffers );
extern void                          NaclOpenGLES2DeleteFramebuffers( PP_Resource context, GLsizei n, const GLuint* framebuffers );
extern void                          NaclOpenGLES2DeleteProgram( PP_Resource context, GLuint program );
extern void                          NaclOpenGLES2DeleteRenderbuffers( PP_Resource context, GLsizei n, const GLuint* renderbuffers );
extern void                          NaclOpenGLES2DeleteShader( PP_Resource context, GLuint shader );
extern void                          NaclOpenGLES2DeleteTextures( PP_Resource context, GLsizei n, const GLuint* textures );
extern void                          NaclOpenGLES2DepthFunc( PP_Resource context, GLenum func );
extern void                          NaclOpenGLES2DepthMask( PP_Resource context, GLboolean flag );
extern void                          NaclOpenGLES2DepthRangef( PP_Resource context, GLclampf zNear, GLclampf zFar );
extern void                          NaclOpenGLES2DetachShader( PP_Resource context, GLuint program, GLuint shader );
extern void                          NaclOpenGLES2Disable( PP_Resource context, GLenum cap );
extern void                          NaclOpenGLES2DisableVertexAttribArray( PP_Resource context, GLuint index );
extern void                          NaclOpenGLES2DrawArrays( PP_Resource context, GLenum mode, GLint first, GLsizei count );
extern void                          NaclOpenGLES2DrawElements( PP_Resource context, GLenum mode, GLsizei count, GLenum type, const void* indices );
extern void                          NaclOpenGLES2Enable( PP_Resource context, GLenum cap );
extern void                          NaclOpenGLES2EnableVertexAttribArray( PP_Resource context, GLuint index );
extern void                          NaclOpenGLES2Finish( PP_Resource context );
extern void                          NaclOpenGLES2Flush( PP_Resource context );
extern void                          NaclOpenGLES2FramebufferRenderbuffer( PP_Resource context, GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer );
extern void                          NaclOpenGLES2FramebufferTexture2D( PP_Resource context, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level );
extern void                          NaclOpenGLES2FrontFace( PP_Resource context, GLenum mode );
extern void                          NaclOpenGLES2GenBuffers( PP_Resource context, GLsizei n, GLuint* buffers );
extern void                          NaclOpenGLES2GenerateMipmap( PP_Resource context, GLenum target );
extern void                          NaclOpenGLES2GenFramebuffers( PP_Resource context, GLsizei n, GLuint* framebuffers );
extern void                          NaclOpenGLES2GenRenderbuffers( PP_Resource context, GLsizei n, GLuint* renderbuffers );
extern void                          NaclOpenGLES2GenTextures( PP_Resource context, GLsizei n, GLuint* textures );
extern void                          NaclOpenGLES2GetActiveAttrib( PP_Resource context, GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name );
extern void                          NaclOpenGLES2GetActiveUniform( PP_Resource context, GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name );
extern void                          NaclOpenGLES2GetAttachedShaders( PP_Resource context, GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders );
extern GLint                         NaclOpenGLES2GetAttribLocation( PP_Resource context, GLuint program, const char* name );
extern void                          NaclOpenGLES2GetBooleanv( PP_Resource context, GLenum pname, GLboolean* params );
extern void                          NaclOpenGLES2GetBufferParameteriv( PP_Resource context, GLenum target, GLenum pname, GLint* params );
extern GLenum                        NaclOpenGLES2GetError( PP_Resource context );
extern void                          NaclOpenGLES2GetFloatv( PP_Resource context, GLenum pname, GLfloat* params );
extern void                          NaclOpenGLES2GetFramebufferAttachmentParameteriv( PP_Resource context, GLenum target, GLenum attachment, GLenum pname, GLint* params );
extern void                          NaclOpenGLES2GetIntegerv( PP_Resource context, GLenum pname, GLint* params );
extern void                          NaclOpenGLES2GetProgramiv( PP_Resource context, GLuint program, GLenum pname, GLint* params );
extern void                          NaclOpenGLES2GetProgramInfoLog( PP_Resource context, GLuint program, GLsizei bufsize, GLsizei* length, char* infolog );
extern void                          NaclOpenGLES2GetRenderbufferParameteriv( PP_Resource context, GLenum target, GLenum pname, GLint* params );
extern void                          NaclOpenGLES2GetShaderiv( PP_Resource context, GLuint shader, GLenum pname, GLint* params );
extern void                          NaclOpenGLES2GetShaderInfoLog( PP_Resource context, GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog );
extern void                          NaclOpenGLES2GetShaderPrecisionFormat( PP_Resource context, GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision );
extern void                          NaclOpenGLES2GetShaderSource( PP_Resource context, GLuint shader, GLsizei bufsize, GLsizei* length, char* source );
extern const GLubyte*                NaclOpenGLES2GetString( PP_Resource context, GLenum name );
extern void                          NaclOpenGLES2GetTexParameterfv( PP_Resource context, GLenum target, GLenum pname, GLfloat* params );
extern void                          NaclOpenGLES2GetTexParameteriv( PP_Resource context, GLenum target, GLenum pname, GLint* params );
extern void                          NaclOpenGLES2GetUniformfv( PP_Resource context, GLuint program, GLint location, GLfloat* params );
extern void                          NaclOpenGLES2GetUniformiv( PP_Resource context, GLuint program, GLint location, GLint* params );
extern GLint                         NaclOpenGLES2GetUniformLocation( PP_Resource context, GLuint program, const char* name );
extern void                          NaclOpenGLES2GetVertexAttribfv( PP_Resource context, GLuint index, GLenum pname, GLfloat* params );
extern void                          NaclOpenGLES2GetVertexAttribiv( PP_Resource context, GLuint index, GLenum pname, GLint* params );
extern void                          NaclOpenGLES2GetVertexAttribPointerv( PP_Resource context, GLuint index, GLenum pname, void** pointer );
extern void                          NaclOpenGLES2Hint( PP_Resource context, GLenum target, GLenum mode );
extern GLboolean                     NaclOpenGLES2IsBuffer( PP_Resource context, GLuint buffer );
extern GLboolean                     NaclOpenGLES2IsEnabled( PP_Resource context, GLenum cap );
extern GLboolean                     NaclOpenGLES2IsFramebuffer( PP_Resource context, GLuint framebuffer );
extern GLboolean                     NaclOpenGLES2IsProgram( PP_Resource context, GLuint program );
extern GLboolean                     NaclOpenGLES2IsRenderbuffer( PP_Resource context, GLuint renderbuffer );
extern GLboolean                     NaclOpenGLES2IsShader( PP_Resource context, GLuint shader );
extern GLboolean                     NaclOpenGLES2IsTexture( PP_Resource context, GLuint texture );
extern void                          NaclOpenGLES2LineWidth( PP_Resource context, GLfloat width );
extern void                          NaclOpenGLES2LinkProgram( PP_Resource context, GLuint program );
extern void                          NaclOpenGLES2PixelStorei( PP_Resource context, GLenum pname, GLint param );
extern void                          NaclOpenGLES2PolygonOffset( PP_Resource context, GLfloat factor, GLfloat units );
extern void                          NaclOpenGLES2ReadPixels( PP_Resource context, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels );
extern void                          NaclOpenGLES2ReleaseShaderCompiler( PP_Resource context );
extern void                          NaclOpenGLES2RenderbufferStorage( PP_Resource context, GLenum target, GLenum internalformat, GLsizei width, GLsizei height );
extern void                          NaclOpenGLES2SampleCoverage( PP_Resource context, GLclampf value, GLboolean invert );
extern void                          NaclOpenGLES2Scissor( PP_Resource context, GLint x, GLint y, GLsizei width, GLsizei height );
extern void                          NaclOpenGLES2ShaderBinary( PP_Resource context, GLsizei n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length );
extern void                          NaclOpenGLES2ShaderSource( PP_Resource context, GLuint shader, GLsizei count, const char** str, const GLint* length );
extern void                          NaclOpenGLES2StencilFunc( PP_Resource context, GLenum func, GLint ref, GLuint mask );
extern void                          NaclOpenGLES2StencilFuncSeparate( PP_Resource context, GLenum face, GLenum func, GLint ref, GLuint mask );
extern void                          NaclOpenGLES2StencilMask( PP_Resource context, GLuint mask );
extern void                          NaclOpenGLES2StencilMaskSeparate( PP_Resource context, GLenum face, GLuint mask );
extern void                          NaclOpenGLES2StencilOp( PP_Resource context, GLenum fail, GLenum zfail, GLenum zpass );
extern void                          NaclOpenGLES2StencilOpSeparate( PP_Resource context, GLenum face, GLenum fail, GLenum zfail, GLenum zpass );
extern void                          NaclOpenGLES2TexImage2D( PP_Resource context, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels );
extern void                          NaclOpenGLES2TexParameterf( PP_Resource context, GLenum target, GLenum pname, GLfloat param );
extern void                          NaclOpenGLES2TexParameterfv( PP_Resource context, GLenum target, GLenum pname, const GLfloat* params );
extern void                          NaclOpenGLES2TexParameteri( PP_Resource context, GLenum target, GLenum pname, GLint param );
extern void                          NaclOpenGLES2TexParameteriv( PP_Resource context, GLenum target, GLenum pname, const GLint* params );
extern void                          NaclOpenGLES2TexSubImage2D( PP_Resource context, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels );
extern void                          NaclOpenGLES2Uniform1f( PP_Resource context, GLint location, GLfloat x );
extern void                          NaclOpenGLES2Uniform1fv( PP_Resource context, GLint location, GLsizei count, const GLfloat* v );
extern void                          NaclOpenGLES2Uniform1i( PP_Resource context, GLint location, GLint x );
extern void                          NaclOpenGLES2Uniform1iv( PP_Resource context, GLint location, GLsizei count, const GLint* v );
extern void                          NaclOpenGLES2Uniform2f( PP_Resource context, GLint location, GLfloat x, GLfloat y );
extern void                          NaclOpenGLES2Uniform2fv( PP_Resource context, GLint location, GLsizei count, const GLfloat* v );
extern void                          NaclOpenGLES2Uniform2i( PP_Resource context, GLint location, GLint x, GLint y );
extern void                          NaclOpenGLES2Uniform2iv( PP_Resource context, GLint location, GLsizei count, const GLint* v );
extern void                          NaclOpenGLES2Uniform3f( PP_Resource context, GLint location, GLfloat x, GLfloat y, GLfloat z );
extern void                          NaclOpenGLES2Uniform3fv( PP_Resource context, GLint location, GLsizei count, const GLfloat* v );
extern void                          NaclOpenGLES2Uniform3i( PP_Resource context, GLint location, GLint x, GLint y, GLint z );
extern void                          NaclOpenGLES2Uniform3iv( PP_Resource context, GLint location, GLsizei count, const GLint* v );
extern void                          NaclOpenGLES2Uniform4f( PP_Resource context, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w );
extern void                          NaclOpenGLES2Uniform4fv( PP_Resource context, GLint location, GLsizei count, const GLfloat* v );
extern void                          NaclOpenGLES2Uniform4i( PP_Resource context, GLint location, GLint x, GLint y, GLint z, GLint w );
extern void                          NaclOpenGLES2Uniform4iv( PP_Resource context, GLint location, GLsizei count, const GLint* v );
extern void                          NaclOpenGLES2UniformMatrix2fv( PP_Resource context, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
extern void                          NaclOpenGLES2UniformMatrix3fv( PP_Resource context, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
extern void                          NaclOpenGLES2UniformMatrix4fv( PP_Resource context, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
extern void                          NaclOpenGLES2UseProgram( PP_Resource context, GLuint program );
extern void                          NaclOpenGLES2ValidateProgram( PP_Resource context, GLuint program );
extern void                          NaclOpenGLES2VertexAttrib1f( PP_Resource context, GLuint indx, GLfloat x );
extern void                          NaclOpenGLES2VertexAttrib1fv( PP_Resource context, GLuint indx, const GLfloat* values );
extern void                          NaclOpenGLES2VertexAttrib2f( PP_Resource context, GLuint indx, GLfloat x, GLfloat y );
extern void                          NaclOpenGLES2VertexAttrib2fv( PP_Resource context, GLuint indx, const GLfloat* values );
extern void                          NaclOpenGLES2VertexAttrib3f( PP_Resource context, GLuint indx, GLfloat x, GLfloat y, GLfloat z );
extern void                          NaclOpenGLES2VertexAttrib3fv( PP_Resource context, GLuint indx, const GLfloat* values );
extern void                          NaclOpenGLES2VertexAttrib4f( PP_Resource context, GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w );
extern void                          NaclOpenGLES2VertexAttrib4fv( PP_Resource context, GLuint indx, const GLfloat* values );
extern void                          NaclOpenGLES2VertexAttribPointer( PP_Resource context, GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr );
extern void                          NaclOpenGLES2Viewport( PP_Resource context, GLint x, GLint y, GLsizei width, GLsizei height );

// --------------------------------------------------------------------------------------------
// PPB_URLLoader interface
// --------------------------------------------------------------------------------------------
extern PP_Resource                   NaclURLLoaderCreate(  );
extern PP_Bool                       NaclURLLoaderIsURLLoader( PP_Resource resource );
extern int32_t                       NaclURLLoaderOpen( PP_Resource loader, PP_Resource request_info, PP_CompletionCallback callback );
extern int32_t                       NaclURLLoaderFollowRedirect( PP_Resource loader, PP_CompletionCallback callback );
extern PP_Bool                       NaclURLLoaderGetUploadProgress( PP_Resource loader, int64_t* bytes_sent, int64_t* total_bytes_to_be_sent );
extern PP_Bool                       NaclURLLoaderGetDownloadProgress( PP_Resource loader, int64_t* bytes_received, int64_t* total_bytes_to_be_received );
extern PP_Resource                   NaclURLLoaderGetResponseInfo( PP_Resource loader );
extern int32_t                       NaclURLLoaderReadResponseBody( PP_Resource loader, void* buffer, int32_t bytes_to_read, PP_CompletionCallback callback );
extern int32_t                       NaclURLLoaderFinishStreamingToFile( PP_Resource loader, PP_CompletionCallback callback );
extern void                          NaclURLLoaderClose( PP_Resource loader );

// --------------------------------------------------------------------------------------------
// PPB_URLRequestInfo interface
// --------------------------------------------------------------------------------------------
extern PP_Resource                   NaclURLRequestInfoCreate(  );
extern PP_Bool                       NaclURLRequestInfoIsURLRequestInfo( PP_Resource resource );
extern PP_Bool                       NaclURLRequestInfoSetProperty( PP_Resource request, PP_URLRequestProperty property, PP_Var value );
extern PP_Bool                       NaclURLRequestInfoAppendDataToBody( PP_Resource request, const void* data, uint32_t len );
extern PP_Bool                       NaclURLRequestInfoAppendFileToBody( PP_Resource request, PP_Resource file_ref, int64_t start_offset, int64_t number_of_bytes, PP_Time expected_last_modified_time );

// --------------------------------------------------------------------------------------------
// PPB_URLResponseInfo interface
// --------------------------------------------------------------------------------------------
extern PP_Bool                       NaclURLResponseInfoIsURLResponseInfo( PP_Resource resource );
extern PP_Var                        NaclURLResponseInfoGetProperty( PP_Resource response, PP_URLResponseProperty property );
extern PP_Resource                   NaclURLResponseInfoGetBodyAsFileRef( PP_Resource response );

// --------------------------------------------------------------------------------------------
// PPB_Var interface
// --------------------------------------------------------------------------------------------
extern void                          NaclVarAddRef( PP_Var var );
extern void                          NaclVarRelease( PP_Var var );
extern PP_Var                        NaclVarVarFromUtf8( const char* data, uint32_t len );
extern const char*                   NaclVarVarToUtf8( PP_Var var, uint32_t* len );

// --------------------------------------------------------------------------------------------
// PPB_VarArrayBuffer interface
// --------------------------------------------------------------------------------------------
extern PP_Var                        NaclVarArrayBufferCreate( uint32_t size_in_bytes );
extern PP_Bool                       NaclVarArrayBufferByteLength( PP_Var array, uint32_t* byte_length );
extern void*                         NaclVarArrayBufferMap( PP_Var array );
extern void                          NaclVarArrayBufferUnmap( PP_Var array );

// --------------------------------------------------------------------------------------------
// PPB_View interface
// --------------------------------------------------------------------------------------------
extern PP_Bool                       NaclViewIsView( PP_Resource resource );
extern PP_Bool                       NaclViewGetRect( PP_Resource resource, struct PP_Rect* rect );
extern PP_Bool                       NaclViewIsFullscreen( PP_Resource resource );
extern PP_Bool                       NaclViewIsVisible( PP_Resource resource );
extern PP_Bool                       NaclViewIsPageVisible( PP_Resource resource );
extern PP_Bool                       NaclViewGetClipRect( PP_Resource resource, struct PP_Rect* clip );

// --------------------------------------------------------------------------------------------
// PPB_WebSocket interface
// --------------------------------------------------------------------------------------------
extern PP_Resource                   NaclWebSocketCreate(  );
extern PP_Bool                       NaclWebSocketIsWebSocket( PP_Resource resource );
extern int32_t                       NaclWebSocketConnect( PP_Resource web_socket, PP_Var url, const struct PP_Var protocols[], uint32_t protocol_count, PP_CompletionCallback callback );
extern int32_t                       NaclWebSocketClose( PP_Resource web_socket, uint16_t code, PP_Var reason, PP_CompletionCallback callback );
extern int32_t                       NaclWebSocketReceiveMessage( PP_Resource web_socket, struct PP_Var* message, PP_CompletionCallback callback );
extern int32_t                       NaclWebSocketSendMessage( PP_Resource web_socket, PP_Var message );
extern uint64_t                      NaclWebSocketGetBufferedAmount( PP_Resource web_socket );
extern uint16_t                      NaclWebSocketGetCloseCode( PP_Resource web_socket );
extern PP_Var                        NaclWebSocketGetCloseReason( PP_Resource web_socket );
extern PP_Bool                       NaclWebSocketGetCloseWasClean( PP_Resource web_socket );
extern PP_Var                        NaclWebSocketGetExtensions( PP_Resource web_socket );
extern PP_Var                        NaclWebSocketGetProtocol( PP_Resource web_socket );
extern PP_WebSocketReadyState        NaclWebSocketGetReadyState( PP_Resource web_socket );
extern PP_Var                        NaclWebSocketGetURL( PP_Resource web_socket );

// --------------------------------------------------------------------------------------------
// PPB_WheelInputEvent interface
// --------------------------------------------------------------------------------------------
extern PP_Resource                   NaclWheelInputEventCreate( PP_TimeTicks time_stamp, uint32_t modifiers, const struct PP_FloatPoint* wheel_delta, const struct PP_FloatPoint* wheel_ticks, PP_Bool scroll_by_page );
extern PP_Bool                       NaclWheelInputEventIsWheelInputEvent( PP_Resource resource );
extern struct PP_FloatPoint          NaclWheelInputEventGetDelta( PP_Resource wheel_event );
extern struct PP_FloatPoint          NaclWheelInputEventGetTicks( PP_Resource wheel_event );
extern PP_Bool                       NaclWheelInputEventGetScrollByPage( PP_Resource wheel_event );

#endif // NACL_C_INLINE
// --------------------------------------------------------------------------------------------
// Globals used by single instance interfaces
// --------------------------------------------------------------------------------------------

enum
{
  kNaclInvalidInstance = 0,
};

extern PP_Instance                      g_NaclInstanceId;
extern const PPB_Audio*                 g_NaclAudio;                  // (5) functions
extern const PPB_AudioConfig*           g_NaclAudioConfig;            // (5) functions
extern const PPB_Core*                  g_NaclCore;                   // (6) functions
extern const PPB_FileIO*                g_NaclFileIO;                 // (10) functions
extern const PPB_FileRef*               g_NaclFileRef;                // (10) functions
extern const PPB_FileSystem*            g_NaclFileSystem;             // (4) functions
extern const PPB_Fullscreen*            g_NaclFullscreen;             // (3) functions
extern const PPB_Graphics2D*            g_NaclGraphics2D;             // (7) functions
extern const PPB_Graphics3D*            g_NaclGraphics3D;             // (8) functions
extern const PPB_ImageData*             g_NaclImageData;              // (7) functions
extern const PPB_InputEvent*            g_NaclInputEvent;             // (7) functions
extern const PPB_Instance*              g_NaclInstance;               // (2) functions
extern const PPB_KeyboardInputEvent*    g_NaclKeyboardInputEvent;     // (4) functions
extern const PPB_Messaging*             g_NaclMessaging;              // (1) functions
extern const PPB_MouseInputEvent*       g_NaclMouseInputEvent;        // (6) functions
extern const PPB_MouseLock*             g_NaclMouseLock;              // (2) functions
extern const PPB_OpenGLES2*             g_NaclOpenGLES2;              // (142) functions
extern const PPB_URLLoader*             g_NaclURLLoader;              // (10) functions
extern const PPB_URLRequestInfo*        g_NaclURLRequestInfo;         // (5) functions
extern const PPB_URLResponseInfo*       g_NaclURLResponseInfo;        // (3) functions
extern const PPB_Var*                   g_NaclVar;                    // (4) functions
extern const PPB_VarArrayBuffer*        g_NaclVarArrayBuffer;         // (4) functions
extern const PPB_View*                  g_NaclView;                   // (6) functions
extern const PPB_WebSocket*             g_NaclWebSocket;              // (14) functions
extern const PPB_WheelInputEvent*       g_NaclWheelInputEvent;        // (5) functions

// --------------------------------------------------------------------------------------------
// PPB_Audio inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Resource
NaclAudioCreate( PP_Resource config, PPB_Audio_Callback audio_callback, void* user_data )
{
  return g_NaclAudio->Create(g_NaclInstanceId, config, audio_callback, user_data);
}

inline PP_Bool
NaclAudioIsAudio( PP_Resource resource )
{
  return g_NaclAudio->IsAudio(resource);
}

inline PP_Resource
NaclAudioGetCurrentConfig( PP_Resource audio )
{
  return g_NaclAudio->GetCurrentConfig(audio);
}

inline PP_Bool
NaclAudioStartPlayback( PP_Resource audio )
{
  return g_NaclAudio->StartPlayback(audio);
}

inline PP_Bool
NaclAudioStopPlayback( PP_Resource audio )
{
  return g_NaclAudio->StopPlayback(audio);
}


// --------------------------------------------------------------------------------------------
// PPB_AudioConfig inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Resource
NaclAudioConfigCreateStereo16Bit( PP_AudioSampleRate sample_rate, uint32_t sample_frame_count )
{
  return g_NaclAudioConfig->CreateStereo16Bit(g_NaclInstanceId, sample_rate, sample_frame_count);
}

inline uint32_t
NaclAudioConfigRecommendSampleFrameCount( PP_AudioSampleRate sample_rate, uint32_t requested_sample_frame_count )
{
  return g_NaclAudioConfig->RecommendSampleFrameCount(sample_rate, requested_sample_frame_count);
}

inline PP_Bool
NaclAudioConfigIsAudioConfig( PP_Resource resource )
{
  return g_NaclAudioConfig->IsAudioConfig(resource);
}

inline PP_AudioSampleRate
NaclAudioConfigGetSampleRate( PP_Resource config )
{
  return g_NaclAudioConfig->GetSampleRate(config);
}

inline uint32_t
NaclAudioConfigGetSampleFrameCount( PP_Resource config )
{
  return g_NaclAudioConfig->GetSampleFrameCount(config);
}


// --------------------------------------------------------------------------------------------
// PPB_Core inline definitions
// --------------------------------------------------------------------------------------------
inline void
NaclCoreAddRefResource( PP_Resource resource )
{
  g_NaclCore->AddRefResource(resource);
}

inline void
NaclCoreReleaseResource( PP_Resource resource )
{
  g_NaclCore->ReleaseResource(resource);
}

inline PP_Time
NaclCoreGetTime(  )
{
  return g_NaclCore->GetTime();
}

inline PP_TimeTicks
NaclCoreGetTimeTicks(  )
{
  return g_NaclCore->GetTimeTicks();
}

inline void
NaclCoreCallOnMainThread( int32_t delay_in_milliseconds, PP_CompletionCallback callback, int32_t result )
{
  g_NaclCore->CallOnMainThread(delay_in_milliseconds, callback, result);
}

inline PP_Bool
NaclCoreIsMainThread(  )
{
  return g_NaclCore->IsMainThread();
}


// --------------------------------------------------------------------------------------------
// PPB_FileIO inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Resource
NaclFileIOCreate(  )
{
  return g_NaclFileIO->Create(g_NaclInstanceId);
}

inline PP_Bool
NaclFileIOIsFileIO( PP_Resource resource )
{
  return g_NaclFileIO->IsFileIO(resource);
}

inline int32_t
NaclFileIOOpen( PP_Resource file_io, PP_Resource file_ref, int32_t open_flags, PP_CompletionCallback callback )
{
  return g_NaclFileIO->Open(file_io, file_ref, open_flags, callback);
}

inline int32_t
NaclFileIOQuery( PP_Resource file_io, struct PP_FileInfo* info, PP_CompletionCallback callback )
{
  return g_NaclFileIO->Query(file_io, info, callback);
}

inline int32_t
NaclFileIOTouch( PP_Resource file_io, PP_Time last_access_time, PP_Time last_modified_time, PP_CompletionCallback callback )
{
  return g_NaclFileIO->Touch(file_io, last_access_time, last_modified_time, callback);
}

inline int32_t
NaclFileIORead( PP_Resource file_io, int64_t offset, char* buffer, int32_t bytes_to_read, PP_CompletionCallback callback )
{
  return g_NaclFileIO->Read(file_io, offset, buffer, bytes_to_read, callback);
}

inline int32_t
NaclFileIOWrite( PP_Resource file_io, int64_t offset, const char* buffer, int32_t bytes_to_write, PP_CompletionCallback callback )
{
  return g_NaclFileIO->Write(file_io, offset, buffer, bytes_to_write, callback);
}

inline int32_t
NaclFileIOSetLength( PP_Resource file_io, int64_t length, PP_CompletionCallback callback )
{
  return g_NaclFileIO->SetLength(file_io, length, callback);
}

inline int32_t
NaclFileIOFlush( PP_Resource file_io, PP_CompletionCallback callback )
{
  return g_NaclFileIO->Flush(file_io, callback);
}

inline void
NaclFileIOClose( PP_Resource file_io )
{
  g_NaclFileIO->Close(file_io);
}


// --------------------------------------------------------------------------------------------
// PPB_FileRef inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Resource
NaclFileRefCreate( PP_Resource file_system, const char* path )
{
  return g_NaclFileRef->Create(file_system, path);
}

inline PP_Bool
NaclFileRefIsFileRef( PP_Resource resource )
{
  return g_NaclFileRef->IsFileRef(resource);
}

inline PP_FileSystemType
NaclFileRefGetFileSystemType( PP_Resource file_ref )
{
  return g_NaclFileRef->GetFileSystemType(file_ref);
}

inline PP_Var
NaclFileRefGetName( PP_Resource file_ref )
{
  return g_NaclFileRef->GetName(file_ref);
}

inline PP_Var
NaclFileRefGetPath( PP_Resource file_ref )
{
  return g_NaclFileRef->GetPath(file_ref);
}

inline PP_Resource
NaclFileRefGetParent( PP_Resource file_ref )
{
  return g_NaclFileRef->GetParent(file_ref);
}

inline int32_t
NaclFileRefMakeDirectory( PP_Resource directory_ref, PP_Bool make_ancestors, PP_CompletionCallback callback )
{
  return g_NaclFileRef->MakeDirectory(directory_ref, make_ancestors, callback);
}

inline int32_t
NaclFileRefTouch( PP_Resource file_ref, PP_Time last_access_time, PP_Time last_modified_time, PP_CompletionCallback callback )
{
  return g_NaclFileRef->Touch(file_ref, last_access_time, last_modified_time, callback);
}

inline int32_t
NaclFileRefDelete( PP_Resource file_ref, PP_CompletionCallback callback )
{
  return g_NaclFileRef->Delete(file_ref, callback);
}

inline int32_t
NaclFileRefRename( PP_Resource file_ref, PP_Resource new_file_ref, PP_CompletionCallback callback )
{
  return g_NaclFileRef->Rename(file_ref, new_file_ref, callback);
}


// --------------------------------------------------------------------------------------------
// PPB_FileSystem inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Resource
NaclFileSystemCreate( PP_FileSystemType type )
{
  return g_NaclFileSystem->Create(g_NaclInstanceId, type);
}

inline PP_Bool
NaclFileSystemIsFileSystem( PP_Resource resource )
{
  return g_NaclFileSystem->IsFileSystem(resource);
}

inline int32_t
NaclFileSystemOpen( PP_Resource file_system, int64_t expected_size, PP_CompletionCallback callback )
{
  return g_NaclFileSystem->Open(file_system, expected_size, callback);
}

inline PP_FileSystemType
NaclFileSystemGetType( PP_Resource file_system )
{
  return g_NaclFileSystem->GetType(file_system);
}


// --------------------------------------------------------------------------------------------
// PPB_Fullscreen inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Bool
NaclFullscreenIsFullscreen(  )
{
  return g_NaclFullscreen->IsFullscreen(g_NaclInstanceId);
}

inline PP_Bool
NaclFullscreenSetFullscreen( PP_Bool fullscreen )
{
  return g_NaclFullscreen->SetFullscreen(g_NaclInstanceId, fullscreen);
}

inline PP_Bool
NaclFullscreenGetScreenSize( struct PP_Size* size )
{
  return g_NaclFullscreen->GetScreenSize(g_NaclInstanceId, size);
}


// --------------------------------------------------------------------------------------------
// PPB_Graphics2D inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Resource
NaclGraphics2DCreate( const struct PP_Size* size, PP_Bool is_always_opaque )
{
  return g_NaclGraphics2D->Create(g_NaclInstanceId, size, is_always_opaque);
}

inline PP_Bool
NaclGraphics2DIsGraphics2D( PP_Resource resource )
{
  return g_NaclGraphics2D->IsGraphics2D(resource);
}

inline PP_Bool
NaclGraphics2DDescribe( PP_Resource graphics_2d, struct PP_Size* size, PP_Bool* is_always_opqaue )
{
  return g_NaclGraphics2D->Describe(graphics_2d, size, is_always_opqaue);
}

inline void
NaclGraphics2DPaintImageData( PP_Resource graphics_2d, PP_Resource image_data, const struct PP_Point* top_left, const struct PP_Rect* src_rect )
{
  g_NaclGraphics2D->PaintImageData(graphics_2d, image_data, top_left, src_rect);
}

inline void
NaclGraphics2DScroll( PP_Resource graphics_2d, const struct PP_Rect* clip_rect, const struct PP_Point* amount )
{
  g_NaclGraphics2D->Scroll(graphics_2d, clip_rect, amount);
}

inline void
NaclGraphics2DReplaceContents( PP_Resource graphics_2d, PP_Resource image_data )
{
  g_NaclGraphics2D->ReplaceContents(graphics_2d, image_data);
}

inline int32_t
NaclGraphics2DFlush( PP_Resource graphics_2d, PP_CompletionCallback callback )
{
  return g_NaclGraphics2D->Flush(graphics_2d, callback);
}


// --------------------------------------------------------------------------------------------
// PPB_Graphics3D inline definitions
// --------------------------------------------------------------------------------------------
inline int32_t
NaclGraphics3DGetAttribMaxValue( PP_Resource instance, int32_t attribute, int32_t* value )
{
  return g_NaclGraphics3D->GetAttribMaxValue(instance, attribute, value);
}

inline PP_Resource
NaclGraphics3DCreate( PP_Resource share_context, const int32_t attrib_list[] )
{
  return g_NaclGraphics3D->Create(g_NaclInstanceId, share_context, attrib_list);
}

inline PP_Bool
NaclGraphics3DIsGraphics3D( PP_Resource resource )
{
  return g_NaclGraphics3D->IsGraphics3D(resource);
}

inline int32_t
NaclGraphics3DGetAttribs( PP_Resource context, int32_t attrib_list[] )
{
  return g_NaclGraphics3D->GetAttribs(context, attrib_list);
}

inline int32_t
NaclGraphics3DSetAttribs( PP_Resource context, int32_t attrib_list[] )
{
  return g_NaclGraphics3D->SetAttribs(context, attrib_list);
}

inline int32_t
NaclGraphics3DGetError( PP_Resource context )
{
  return g_NaclGraphics3D->GetError(context);
}

inline int32_t
NaclGraphics3DResizeBuffers( PP_Resource context, int32_t width, int32_t height )
{
  return g_NaclGraphics3D->ResizeBuffers(context, width, height);
}

inline int32_t
NaclGraphics3DSwapBuffers( PP_Resource context, PP_CompletionCallback callback )
{
  return g_NaclGraphics3D->SwapBuffers(context, callback);
}


// --------------------------------------------------------------------------------------------
// PPB_ImageData inline definitions
// --------------------------------------------------------------------------------------------
inline PP_ImageDataFormat
NaclImageDataGetNativeImageDataFormat(  )
{
  return g_NaclImageData->GetNativeImageDataFormat();
}

inline PP_Bool
NaclImageDataIsImageDataFormatSupported( PP_ImageDataFormat format )
{
  return g_NaclImageData->IsImageDataFormatSupported(format);
}

inline PP_Resource
NaclImageDataCreate( PP_ImageDataFormat format, const struct PP_Size* size, PP_Bool init_to_zero )
{
  return g_NaclImageData->Create(g_NaclInstanceId, format, size, init_to_zero);
}

inline PP_Bool
NaclImageDataIsImageData( PP_Resource image_data )
{
  return g_NaclImageData->IsImageData(image_data);
}

inline PP_Bool
NaclImageDataDescribe( PP_Resource image_data, struct PP_ImageDataDesc* desc )
{
  return g_NaclImageData->Describe(image_data, desc);
}

inline void*
NaclImageDataMap( PP_Resource image_data )
{
  return g_NaclImageData->Map(image_data);
}

inline void
NaclImageDataUnmap( PP_Resource image_data )
{
  g_NaclImageData->Unmap(image_data);
}


// --------------------------------------------------------------------------------------------
// PPB_InputEvent inline definitions
// --------------------------------------------------------------------------------------------
inline int32_t
NaclInputEventRequestInputEvents( uint32_t event_classes )
{
  return g_NaclInputEvent->RequestInputEvents(g_NaclInstanceId, event_classes);
}

inline int32_t
NaclInputEventRequestFilteringInputEvents( uint32_t event_classes )
{
  return g_NaclInputEvent->RequestFilteringInputEvents(g_NaclInstanceId, event_classes);
}

inline void
NaclInputEventClearInputEventRequest( uint32_t event_classes )
{
  g_NaclInputEvent->ClearInputEventRequest(g_NaclInstanceId, event_classes);
}

inline PP_Bool
NaclInputEventIsInputEvent( PP_Resource resource )
{
  return g_NaclInputEvent->IsInputEvent(resource);
}

inline PP_InputEvent_Type
NaclInputEventGetType( PP_Resource event )
{
  return g_NaclInputEvent->GetType(event);
}

inline PP_TimeTicks
NaclInputEventGetTimeStamp( PP_Resource event )
{
  return g_NaclInputEvent->GetTimeStamp(event);
}

inline uint32_t
NaclInputEventGetModifiers( PP_Resource event )
{
  return g_NaclInputEvent->GetModifiers(event);
}


// --------------------------------------------------------------------------------------------
// PPB_Instance inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Bool
NaclInstanceBindGraphics( PP_Resource device )
{
  return g_NaclInstance->BindGraphics(g_NaclInstanceId, device);
}

inline PP_Bool
NaclInstanceIsFullFrame(  )
{
  return g_NaclInstance->IsFullFrame(g_NaclInstanceId);
}


// --------------------------------------------------------------------------------------------
// PPB_KeyboardInputEvent inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Resource
NaclKeyboardInputEventCreate( PP_InputEvent_Type type, PP_TimeTicks time_stamp, uint32_t modifiers, uint32_t key_code, PP_Var character_text )
{
  return g_NaclKeyboardInputEvent->Create(g_NaclInstanceId, type, time_stamp, modifiers, key_code, character_text);
}

inline PP_Bool
NaclKeyboardInputEventIsKeyboardInputEvent( PP_Resource resource )
{
  return g_NaclKeyboardInputEvent->IsKeyboardInputEvent(resource);
}

inline uint32_t
NaclKeyboardInputEventGetKeyCode( PP_Resource key_event )
{
  return g_NaclKeyboardInputEvent->GetKeyCode(key_event);
}

inline PP_Var
NaclKeyboardInputEventGetCharacterText( PP_Resource character_event )
{
  return g_NaclKeyboardInputEvent->GetCharacterText(character_event);
}


// --------------------------------------------------------------------------------------------
// PPB_Messaging inline definitions
// --------------------------------------------------------------------------------------------
inline void
NaclMessagingPostMessage( PP_Var message )
{
  g_NaclMessaging->PostMessage(g_NaclInstanceId, message);
}


// --------------------------------------------------------------------------------------------
// PPB_MouseInputEvent inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Resource
NaclMouseInputEventCreate( PP_InputEvent_Type type, PP_TimeTicks time_stamp, uint32_t modifiers, PP_InputEvent_MouseButton mouse_button, const struct PP_Point* mouse_position, int32_t click_count, const struct PP_Point* mouse_movement )
{
  return g_NaclMouseInputEvent->Create(g_NaclInstanceId, type, time_stamp, modifiers, mouse_button, mouse_position, click_count, mouse_movement);
}

inline PP_Bool
NaclMouseInputEventIsMouseInputEvent( PP_Resource resource )
{
  return g_NaclMouseInputEvent->IsMouseInputEvent(resource);
}

inline PP_InputEvent_MouseButton
NaclMouseInputEventGetButton( PP_Resource mouse_event )
{
  return g_NaclMouseInputEvent->GetButton(mouse_event);
}

inline PP_Point
NaclMouseInputEventGetPosition( PP_Resource mouse_event )
{
  return g_NaclMouseInputEvent->GetPosition(mouse_event);
}

inline int32_t
NaclMouseInputEventGetClickCount( PP_Resource mouse_event )
{
  return g_NaclMouseInputEvent->GetClickCount(mouse_event);
}

inline PP_Point
NaclMouseInputEventGetMovement( PP_Resource mouse_event )
{
  return g_NaclMouseInputEvent->GetMovement(mouse_event);
}


// --------------------------------------------------------------------------------------------
// PPB_MouseLock inline definitions
// --------------------------------------------------------------------------------------------
inline int32_t
NaclMouseLockLockMouse( PP_CompletionCallback callback )
{
  return g_NaclMouseLock->LockMouse(g_NaclInstanceId, callback);
}

inline void
NaclMouseLockUnlockMouse(  )
{
  g_NaclMouseLock->UnlockMouse(g_NaclInstanceId);
}


// --------------------------------------------------------------------------------------------
// PPB_OpenGLES2 inline definitions
// --------------------------------------------------------------------------------------------
inline void
NaclOpenGLES2ActiveTexture( PP_Resource context, GLenum texture )
{
  g_NaclOpenGLES2->ActiveTexture(context, texture);
}

inline void
NaclOpenGLES2AttachShader( PP_Resource context, GLuint program, GLuint shader )
{
  g_NaclOpenGLES2->AttachShader(context, program, shader);
}

inline void
NaclOpenGLES2BindAttribLocation( PP_Resource context, GLuint program, GLuint index, const char* name )
{
  g_NaclOpenGLES2->BindAttribLocation(context, program, index, name);
}

inline void
NaclOpenGLES2BindBuffer( PP_Resource context, GLenum target, GLuint buffer )
{
  g_NaclOpenGLES2->BindBuffer(context, target, buffer);
}

inline void
NaclOpenGLES2BindFramebuffer( PP_Resource context, GLenum target, GLuint framebuffer )
{
  g_NaclOpenGLES2->BindFramebuffer(context, target, framebuffer);
}

inline void
NaclOpenGLES2BindRenderbuffer( PP_Resource context, GLenum target, GLuint renderbuffer )
{
  g_NaclOpenGLES2->BindRenderbuffer(context, target, renderbuffer);
}

inline void
NaclOpenGLES2BindTexture( PP_Resource context, GLenum target, GLuint texture )
{
  g_NaclOpenGLES2->BindTexture(context, target, texture);
}

inline void
NaclOpenGLES2BlendColor( PP_Resource context, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha )
{
  g_NaclOpenGLES2->BlendColor(context, red, green, blue, alpha);
}

inline void
NaclOpenGLES2BlendEquation( PP_Resource context, GLenum mode )
{
  g_NaclOpenGLES2->BlendEquation(context, mode);
}

inline void
NaclOpenGLES2BlendEquationSeparate( PP_Resource context, GLenum modeRGB, GLenum modeAlpha )
{
  g_NaclOpenGLES2->BlendEquationSeparate(context, modeRGB, modeAlpha);
}

inline void
NaclOpenGLES2BlendFunc( PP_Resource context, GLenum sfactor, GLenum dfactor )
{
  g_NaclOpenGLES2->BlendFunc(context, sfactor, dfactor);
}

inline void
NaclOpenGLES2BlendFuncSeparate( PP_Resource context, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha )
{
  g_NaclOpenGLES2->BlendFuncSeparate(context, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

inline void
NaclOpenGLES2BufferData( PP_Resource context, GLenum target, GLsizeiptr size, const void* data, GLenum usage )
{
  g_NaclOpenGLES2->BufferData(context, target, size, data, usage);
}

inline void
NaclOpenGLES2BufferSubData( PP_Resource context, GLenum target, GLintptr offset, GLsizeiptr size, const void* data )
{
  g_NaclOpenGLES2->BufferSubData(context, target, offset, size, data);
}

inline GLenum
NaclOpenGLES2CheckFramebufferStatus( PP_Resource context, GLenum target )
{
  return g_NaclOpenGLES2->CheckFramebufferStatus(context, target);
}

inline void
NaclOpenGLES2Clear( PP_Resource context, GLbitfield mask )
{
  g_NaclOpenGLES2->Clear(context, mask);
}

inline void
NaclOpenGLES2ClearColor( PP_Resource context, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha )
{
  g_NaclOpenGLES2->ClearColor(context, red, green, blue, alpha);
}

inline void
NaclOpenGLES2ClearDepthf( PP_Resource context, GLclampf depth )
{
  g_NaclOpenGLES2->ClearDepthf(context, depth);
}

inline void
NaclOpenGLES2ClearStencil( PP_Resource context, GLint s )
{
  g_NaclOpenGLES2->ClearStencil(context, s);
}

inline void
NaclOpenGLES2ColorMask( PP_Resource context, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha )
{
  g_NaclOpenGLES2->ColorMask(context, red, green, blue, alpha);
}

inline void
NaclOpenGLES2CompileShader( PP_Resource context, GLuint shader )
{
  g_NaclOpenGLES2->CompileShader(context, shader);
}

inline void
NaclOpenGLES2CompressedTexImage2D( PP_Resource context, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data )
{
  g_NaclOpenGLES2->CompressedTexImage2D(context, target, level, internalformat, width, height, border, imageSize, data);
}

inline void
NaclOpenGLES2CompressedTexSubImage2D( PP_Resource context, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data )
{
  g_NaclOpenGLES2->CompressedTexSubImage2D(context, target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

inline void
NaclOpenGLES2CopyTexImage2D( PP_Resource context, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border )
{
  g_NaclOpenGLES2->CopyTexImage2D(context, target, level, internalformat, x, y, width, height, border);
}

inline void
NaclOpenGLES2CopyTexSubImage2D( PP_Resource context, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height )
{
  g_NaclOpenGLES2->CopyTexSubImage2D(context, target, level, xoffset, yoffset, x, y, width, height);
}

inline GLuint
NaclOpenGLES2CreateProgram( PP_Resource context )
{
  return g_NaclOpenGLES2->CreateProgram(context);
}

inline GLuint
NaclOpenGLES2CreateShader( PP_Resource context, GLenum type )
{
  return g_NaclOpenGLES2->CreateShader(context, type);
}

inline void
NaclOpenGLES2CullFace( PP_Resource context, GLenum mode )
{
  g_NaclOpenGLES2->CullFace(context, mode);
}

inline void
NaclOpenGLES2DeleteBuffers( PP_Resource context, GLsizei n, const GLuint* buffers )
{
  g_NaclOpenGLES2->DeleteBuffers(context, n, buffers);
}

inline void
NaclOpenGLES2DeleteFramebuffers( PP_Resource context, GLsizei n, const GLuint* framebuffers )
{
  g_NaclOpenGLES2->DeleteFramebuffers(context, n, framebuffers);
}

inline void
NaclOpenGLES2DeleteProgram( PP_Resource context, GLuint program )
{
  g_NaclOpenGLES2->DeleteProgram(context, program);
}

inline void
NaclOpenGLES2DeleteRenderbuffers( PP_Resource context, GLsizei n, const GLuint* renderbuffers )
{
  g_NaclOpenGLES2->DeleteRenderbuffers(context, n, renderbuffers);
}

inline void
NaclOpenGLES2DeleteShader( PP_Resource context, GLuint shader )
{
  g_NaclOpenGLES2->DeleteShader(context, shader);
}

inline void
NaclOpenGLES2DeleteTextures( PP_Resource context, GLsizei n, const GLuint* textures )
{
  g_NaclOpenGLES2->DeleteTextures(context, n, textures);
}

inline void
NaclOpenGLES2DepthFunc( PP_Resource context, GLenum func )
{
  g_NaclOpenGLES2->DepthFunc(context, func);
}

inline void
NaclOpenGLES2DepthMask( PP_Resource context, GLboolean flag )
{
  g_NaclOpenGLES2->DepthMask(context, flag);
}

inline void
NaclOpenGLES2DepthRangef( PP_Resource context, GLclampf zNear, GLclampf zFar )
{
  g_NaclOpenGLES2->DepthRangef(context, zNear, zFar);
}

inline void
NaclOpenGLES2DetachShader( PP_Resource context, GLuint program, GLuint shader )
{
  g_NaclOpenGLES2->DetachShader(context, program, shader);
}

inline void
NaclOpenGLES2Disable( PP_Resource context, GLenum cap )
{
  g_NaclOpenGLES2->Disable(context, cap);
}

inline void
NaclOpenGLES2DisableVertexAttribArray( PP_Resource context, GLuint index )
{
  g_NaclOpenGLES2->DisableVertexAttribArray(context, index);
}

inline void
NaclOpenGLES2DrawArrays( PP_Resource context, GLenum mode, GLint first, GLsizei count )
{
  g_NaclOpenGLES2->DrawArrays(context, mode, first, count);
}

inline void
NaclOpenGLES2DrawElements( PP_Resource context, GLenum mode, GLsizei count, GLenum type, const void* indices )
{
  g_NaclOpenGLES2->DrawElements(context, mode, count, type, indices);
}

inline void
NaclOpenGLES2Enable( PP_Resource context, GLenum cap )
{
  g_NaclOpenGLES2->Enable(context, cap);
}

inline void
NaclOpenGLES2EnableVertexAttribArray( PP_Resource context, GLuint index )
{
  g_NaclOpenGLES2->EnableVertexAttribArray(context, index);
}

inline void
NaclOpenGLES2Finish( PP_Resource context )
{
  g_NaclOpenGLES2->Finish(context);
}

inline void
NaclOpenGLES2Flush( PP_Resource context )
{
  g_NaclOpenGLES2->Flush(context);
}

inline void
NaclOpenGLES2FramebufferRenderbuffer( PP_Resource context, GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer )
{
  g_NaclOpenGLES2->FramebufferRenderbuffer(context, target, attachment, renderbuffertarget, renderbuffer);
}

inline void
NaclOpenGLES2FramebufferTexture2D( PP_Resource context, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level )
{
  g_NaclOpenGLES2->FramebufferTexture2D(context, target, attachment, textarget, texture, level);
}

inline void
NaclOpenGLES2FrontFace( PP_Resource context, GLenum mode )
{
  g_NaclOpenGLES2->FrontFace(context, mode);
}

inline void
NaclOpenGLES2GenBuffers( PP_Resource context, GLsizei n, GLuint* buffers )
{
  g_NaclOpenGLES2->GenBuffers(context, n, buffers);
}

inline void
NaclOpenGLES2GenerateMipmap( PP_Resource context, GLenum target )
{
  g_NaclOpenGLES2->GenerateMipmap(context, target);
}

inline void
NaclOpenGLES2GenFramebuffers( PP_Resource context, GLsizei n, GLuint* framebuffers )
{
  g_NaclOpenGLES2->GenFramebuffers(context, n, framebuffers);
}

inline void
NaclOpenGLES2GenRenderbuffers( PP_Resource context, GLsizei n, GLuint* renderbuffers )
{
  g_NaclOpenGLES2->GenRenderbuffers(context, n, renderbuffers);
}

inline void
NaclOpenGLES2GenTextures( PP_Resource context, GLsizei n, GLuint* textures )
{
  g_NaclOpenGLES2->GenTextures(context, n, textures);
}

inline void
NaclOpenGLES2GetActiveAttrib( PP_Resource context, GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name )
{
  g_NaclOpenGLES2->GetActiveAttrib(context, program, index, bufsize, length, size, type, name);
}

inline void
NaclOpenGLES2GetActiveUniform( PP_Resource context, GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name )
{
  g_NaclOpenGLES2->GetActiveUniform(context, program, index, bufsize, length, size, type, name);
}

inline void
NaclOpenGLES2GetAttachedShaders( PP_Resource context, GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders )
{
  g_NaclOpenGLES2->GetAttachedShaders(context, program, maxcount, count, shaders);
}

inline GLint
NaclOpenGLES2GetAttribLocation( PP_Resource context, GLuint program, const char* name )
{
  return g_NaclOpenGLES2->GetAttribLocation(context, program, name);
}

inline void
NaclOpenGLES2GetBooleanv( PP_Resource context, GLenum pname, GLboolean* params )
{
  g_NaclOpenGLES2->GetBooleanv(context, pname, params);
}

inline void
NaclOpenGLES2GetBufferParameteriv( PP_Resource context, GLenum target, GLenum pname, GLint* params )
{
  g_NaclOpenGLES2->GetBufferParameteriv(context, target, pname, params);
}

inline GLenum
NaclOpenGLES2GetError( PP_Resource context )
{
  return g_NaclOpenGLES2->GetError(context);
}

inline void
NaclOpenGLES2GetFloatv( PP_Resource context, GLenum pname, GLfloat* params )
{
  g_NaclOpenGLES2->GetFloatv(context, pname, params);
}

inline void
NaclOpenGLES2GetFramebufferAttachmentParameteriv( PP_Resource context, GLenum target, GLenum attachment, GLenum pname, GLint* params )
{
  g_NaclOpenGLES2->GetFramebufferAttachmentParameteriv(context, target, attachment, pname, params);
}

inline void
NaclOpenGLES2GetIntegerv( PP_Resource context, GLenum pname, GLint* params )
{
  g_NaclOpenGLES2->GetIntegerv(context, pname, params);
}

inline void
NaclOpenGLES2GetProgramiv( PP_Resource context, GLuint program, GLenum pname, GLint* params )
{
  g_NaclOpenGLES2->GetProgramiv(context, program, pname, params);
}

inline void
NaclOpenGLES2GetProgramInfoLog( PP_Resource context, GLuint program, GLsizei bufsize, GLsizei* length, char* infolog )
{
  g_NaclOpenGLES2->GetProgramInfoLog(context, program, bufsize, length, infolog);
}

inline void
NaclOpenGLES2GetRenderbufferParameteriv( PP_Resource context, GLenum target, GLenum pname, GLint* params )
{
  g_NaclOpenGLES2->GetRenderbufferParameteriv(context, target, pname, params);
}

inline void
NaclOpenGLES2GetShaderiv( PP_Resource context, GLuint shader, GLenum pname, GLint* params )
{
  g_NaclOpenGLES2->GetShaderiv(context, shader, pname, params);
}

inline void
NaclOpenGLES2GetShaderInfoLog( PP_Resource context, GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog )
{
  g_NaclOpenGLES2->GetShaderInfoLog(context, shader, bufsize, length, infolog);
}

inline void
NaclOpenGLES2GetShaderPrecisionFormat( PP_Resource context, GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision )
{
  g_NaclOpenGLES2->GetShaderPrecisionFormat(context, shadertype, precisiontype, range, precision);
}

inline void
NaclOpenGLES2GetShaderSource( PP_Resource context, GLuint shader, GLsizei bufsize, GLsizei* length, char* source )
{
  g_NaclOpenGLES2->GetShaderSource(context, shader, bufsize, length, source);
}

inline const GLubyte*
NaclOpenGLES2GetString( PP_Resource context, GLenum name )
{
  return g_NaclOpenGLES2->GetString(context, name);
}

inline void
NaclOpenGLES2GetTexParameterfv( PP_Resource context, GLenum target, GLenum pname, GLfloat* params )
{
  g_NaclOpenGLES2->GetTexParameterfv(context, target, pname, params);
}

inline void
NaclOpenGLES2GetTexParameteriv( PP_Resource context, GLenum target, GLenum pname, GLint* params )
{
  g_NaclOpenGLES2->GetTexParameteriv(context, target, pname, params);
}

inline void
NaclOpenGLES2GetUniformfv( PP_Resource context, GLuint program, GLint location, GLfloat* params )
{
  g_NaclOpenGLES2->GetUniformfv(context, program, location, params);
}

inline void
NaclOpenGLES2GetUniformiv( PP_Resource context, GLuint program, GLint location, GLint* params )
{
  g_NaclOpenGLES2->GetUniformiv(context, program, location, params);
}

inline GLint
NaclOpenGLES2GetUniformLocation( PP_Resource context, GLuint program, const char* name )
{
  return g_NaclOpenGLES2->GetUniformLocation(context, program, name);
}

inline void
NaclOpenGLES2GetVertexAttribfv( PP_Resource context, GLuint index, GLenum pname, GLfloat* params )
{
  g_NaclOpenGLES2->GetVertexAttribfv(context, index, pname, params);
}

inline void
NaclOpenGLES2GetVertexAttribiv( PP_Resource context, GLuint index, GLenum pname, GLint* params )
{
  g_NaclOpenGLES2->GetVertexAttribiv(context, index, pname, params);
}

inline void
NaclOpenGLES2GetVertexAttribPointerv( PP_Resource context, GLuint index, GLenum pname, void** pointer )
{
  g_NaclOpenGLES2->GetVertexAttribPointerv(context, index, pname, pointer);
}

inline void
NaclOpenGLES2Hint( PP_Resource context, GLenum target, GLenum mode )
{
  g_NaclOpenGLES2->Hint(context, target, mode);
}

inline GLboolean
NaclOpenGLES2IsBuffer( PP_Resource context, GLuint buffer )
{
  return g_NaclOpenGLES2->IsBuffer(context, buffer);
}

inline GLboolean
NaclOpenGLES2IsEnabled( PP_Resource context, GLenum cap )
{
  return g_NaclOpenGLES2->IsEnabled(context, cap);
}

inline GLboolean
NaclOpenGLES2IsFramebuffer( PP_Resource context, GLuint framebuffer )
{
  return g_NaclOpenGLES2->IsFramebuffer(context, framebuffer);
}

inline GLboolean
NaclOpenGLES2IsProgram( PP_Resource context, GLuint program )
{
  return g_NaclOpenGLES2->IsProgram(context, program);
}

inline GLboolean
NaclOpenGLES2IsRenderbuffer( PP_Resource context, GLuint renderbuffer )
{
  return g_NaclOpenGLES2->IsRenderbuffer(context, renderbuffer);
}

inline GLboolean
NaclOpenGLES2IsShader( PP_Resource context, GLuint shader )
{
  return g_NaclOpenGLES2->IsShader(context, shader);
}

inline GLboolean
NaclOpenGLES2IsTexture( PP_Resource context, GLuint texture )
{
  return g_NaclOpenGLES2->IsTexture(context, texture);
}

inline void
NaclOpenGLES2LineWidth( PP_Resource context, GLfloat width )
{
  g_NaclOpenGLES2->LineWidth(context, width);
}

inline void
NaclOpenGLES2LinkProgram( PP_Resource context, GLuint program )
{
  g_NaclOpenGLES2->LinkProgram(context, program);
}

inline void
NaclOpenGLES2PixelStorei( PP_Resource context, GLenum pname, GLint param )
{
  g_NaclOpenGLES2->PixelStorei(context, pname, param);
}

inline void
NaclOpenGLES2PolygonOffset( PP_Resource context, GLfloat factor, GLfloat units )
{
  g_NaclOpenGLES2->PolygonOffset(context, factor, units);
}

inline void
NaclOpenGLES2ReadPixels( PP_Resource context, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels )
{
  g_NaclOpenGLES2->ReadPixels(context, x, y, width, height, format, type, pixels);
}

inline void
NaclOpenGLES2ReleaseShaderCompiler( PP_Resource context )
{
  g_NaclOpenGLES2->ReleaseShaderCompiler(context);
}

inline void
NaclOpenGLES2RenderbufferStorage( PP_Resource context, GLenum target, GLenum internalformat, GLsizei width, GLsizei height )
{
  g_NaclOpenGLES2->RenderbufferStorage(context, target, internalformat, width, height);
}

inline void
NaclOpenGLES2SampleCoverage( PP_Resource context, GLclampf value, GLboolean invert )
{
  g_NaclOpenGLES2->SampleCoverage(context, value, invert);
}

inline void
NaclOpenGLES2Scissor( PP_Resource context, GLint x, GLint y, GLsizei width, GLsizei height )
{
  g_NaclOpenGLES2->Scissor(context, x, y, width, height);
}

inline void
NaclOpenGLES2ShaderBinary( PP_Resource context, GLsizei n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length )
{
  g_NaclOpenGLES2->ShaderBinary(context, n, shaders, binaryformat, binary, length);
}

inline void
NaclOpenGLES2ShaderSource( PP_Resource context, GLuint shader, GLsizei count, const char** str, const GLint* length )
{
  g_NaclOpenGLES2->ShaderSource(context, shader, count, str, length);
}

inline void
NaclOpenGLES2StencilFunc( PP_Resource context, GLenum func, GLint ref, GLuint mask )
{
  g_NaclOpenGLES2->StencilFunc(context, func, ref, mask);
}

inline void
NaclOpenGLES2StencilFuncSeparate( PP_Resource context, GLenum face, GLenum func, GLint ref, GLuint mask )
{
  g_NaclOpenGLES2->StencilFuncSeparate(context, face, func, ref, mask);
}

inline void
NaclOpenGLES2StencilMask( PP_Resource context, GLuint mask )
{
  g_NaclOpenGLES2->StencilMask(context, mask);
}

inline void
NaclOpenGLES2StencilMaskSeparate( PP_Resource context, GLenum face, GLuint mask )
{
  g_NaclOpenGLES2->StencilMaskSeparate(context, face, mask);
}

inline void
NaclOpenGLES2StencilOp( PP_Resource context, GLenum fail, GLenum zfail, GLenum zpass )
{
  g_NaclOpenGLES2->StencilOp(context, fail, zfail, zpass);
}

inline void
NaclOpenGLES2StencilOpSeparate( PP_Resource context, GLenum face, GLenum fail, GLenum zfail, GLenum zpass )
{
  g_NaclOpenGLES2->StencilOpSeparate(context, face, fail, zfail, zpass);
}

inline void
NaclOpenGLES2TexImage2D( PP_Resource context, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels )
{
  g_NaclOpenGLES2->TexImage2D(context, target, level, internalformat, width, height, border, format, type, pixels);
}

inline void
NaclOpenGLES2TexParameterf( PP_Resource context, GLenum target, GLenum pname, GLfloat param )
{
  g_NaclOpenGLES2->TexParameterf(context, target, pname, param);
}

inline void
NaclOpenGLES2TexParameterfv( PP_Resource context, GLenum target, GLenum pname, const GLfloat* params )
{
  g_NaclOpenGLES2->TexParameterfv(context, target, pname, params);
}

inline void
NaclOpenGLES2TexParameteri( PP_Resource context, GLenum target, GLenum pname, GLint param )
{
  g_NaclOpenGLES2->TexParameteri(context, target, pname, param);
}

inline void
NaclOpenGLES2TexParameteriv( PP_Resource context, GLenum target, GLenum pname, const GLint* params )
{
  g_NaclOpenGLES2->TexParameteriv(context, target, pname, params);
}

inline void
NaclOpenGLES2TexSubImage2D( PP_Resource context, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels )
{
  g_NaclOpenGLES2->TexSubImage2D(context, target, level, xoffset, yoffset, width, height, format, type, pixels);
}

inline void
NaclOpenGLES2Uniform1f( PP_Resource context, GLint location, GLfloat x )
{
  g_NaclOpenGLES2->Uniform1f(context, location, x);
}

inline void
NaclOpenGLES2Uniform1fv( PP_Resource context, GLint location, GLsizei count, const GLfloat* v )
{
  g_NaclOpenGLES2->Uniform1fv(context, location, count, v);
}

inline void
NaclOpenGLES2Uniform1i( PP_Resource context, GLint location, GLint x )
{
  g_NaclOpenGLES2->Uniform1i(context, location, x);
}

inline void
NaclOpenGLES2Uniform1iv( PP_Resource context, GLint location, GLsizei count, const GLint* v )
{
  g_NaclOpenGLES2->Uniform1iv(context, location, count, v);
}

inline void
NaclOpenGLES2Uniform2f( PP_Resource context, GLint location, GLfloat x, GLfloat y )
{
  g_NaclOpenGLES2->Uniform2f(context, location, x, y);
}

inline void
NaclOpenGLES2Uniform2fv( PP_Resource context, GLint location, GLsizei count, const GLfloat* v )
{
  g_NaclOpenGLES2->Uniform2fv(context, location, count, v);
}

inline void
NaclOpenGLES2Uniform2i( PP_Resource context, GLint location, GLint x, GLint y )
{
  g_NaclOpenGLES2->Uniform2i(context, location, x, y);
}

inline void
NaclOpenGLES2Uniform2iv( PP_Resource context, GLint location, GLsizei count, const GLint* v )
{
  g_NaclOpenGLES2->Uniform2iv(context, location, count, v);
}

inline void
NaclOpenGLES2Uniform3f( PP_Resource context, GLint location, GLfloat x, GLfloat y, GLfloat z )
{
  g_NaclOpenGLES2->Uniform3f(context, location, x, y, z);
}

inline void
NaclOpenGLES2Uniform3fv( PP_Resource context, GLint location, GLsizei count, const GLfloat* v )
{
  g_NaclOpenGLES2->Uniform3fv(context, location, count, v);
}

inline void
NaclOpenGLES2Uniform3i( PP_Resource context, GLint location, GLint x, GLint y, GLint z )
{
  g_NaclOpenGLES2->Uniform3i(context, location, x, y, z);
}

inline void
NaclOpenGLES2Uniform3iv( PP_Resource context, GLint location, GLsizei count, const GLint* v )
{
  g_NaclOpenGLES2->Uniform3iv(context, location, count, v);
}

inline void
NaclOpenGLES2Uniform4f( PP_Resource context, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
  g_NaclOpenGLES2->Uniform4f(context, location, x, y, z, w);
}

inline void
NaclOpenGLES2Uniform4fv( PP_Resource context, GLint location, GLsizei count, const GLfloat* v )
{
  g_NaclOpenGLES2->Uniform4fv(context, location, count, v);
}

inline void
NaclOpenGLES2Uniform4i( PP_Resource context, GLint location, GLint x, GLint y, GLint z, GLint w )
{
  g_NaclOpenGLES2->Uniform4i(context, location, x, y, z, w);
}

inline void
NaclOpenGLES2Uniform4iv( PP_Resource context, GLint location, GLsizei count, const GLint* v )
{
  g_NaclOpenGLES2->Uniform4iv(context, location, count, v);
}

inline void
NaclOpenGLES2UniformMatrix2fv( PP_Resource context, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
  g_NaclOpenGLES2->UniformMatrix2fv(context, location, count, transpose, value);
}

inline void
NaclOpenGLES2UniformMatrix3fv( PP_Resource context, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
  g_NaclOpenGLES2->UniformMatrix3fv(context, location, count, transpose, value);
}

inline void
NaclOpenGLES2UniformMatrix4fv( PP_Resource context, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value )
{
  g_NaclOpenGLES2->UniformMatrix4fv(context, location, count, transpose, value);
}

inline void
NaclOpenGLES2UseProgram( PP_Resource context, GLuint program )
{
  g_NaclOpenGLES2->UseProgram(context, program);
}

inline void
NaclOpenGLES2ValidateProgram( PP_Resource context, GLuint program )
{
  g_NaclOpenGLES2->ValidateProgram(context, program);
}

inline void
NaclOpenGLES2VertexAttrib1f( PP_Resource context, GLuint indx, GLfloat x )
{
  g_NaclOpenGLES2->VertexAttrib1f(context, indx, x);
}

inline void
NaclOpenGLES2VertexAttrib1fv( PP_Resource context, GLuint indx, const GLfloat* values )
{
  g_NaclOpenGLES2->VertexAttrib1fv(context, indx, values);
}

inline void
NaclOpenGLES2VertexAttrib2f( PP_Resource context, GLuint indx, GLfloat x, GLfloat y )
{
  g_NaclOpenGLES2->VertexAttrib2f(context, indx, x, y);
}

inline void
NaclOpenGLES2VertexAttrib2fv( PP_Resource context, GLuint indx, const GLfloat* values )
{
  g_NaclOpenGLES2->VertexAttrib2fv(context, indx, values);
}

inline void
NaclOpenGLES2VertexAttrib3f( PP_Resource context, GLuint indx, GLfloat x, GLfloat y, GLfloat z )
{
  g_NaclOpenGLES2->VertexAttrib3f(context, indx, x, y, z);
}

inline void
NaclOpenGLES2VertexAttrib3fv( PP_Resource context, GLuint indx, const GLfloat* values )
{
  g_NaclOpenGLES2->VertexAttrib3fv(context, indx, values);
}

inline void
NaclOpenGLES2VertexAttrib4f( PP_Resource context, GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
  g_NaclOpenGLES2->VertexAttrib4f(context, indx, x, y, z, w);
}

inline void
NaclOpenGLES2VertexAttrib4fv( PP_Resource context, GLuint indx, const GLfloat* values )
{
  g_NaclOpenGLES2->VertexAttrib4fv(context, indx, values);
}

inline void
NaclOpenGLES2VertexAttribPointer( PP_Resource context, GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr )
{
  g_NaclOpenGLES2->VertexAttribPointer(context, indx, size, type, normalized, stride, ptr);
}

inline void
NaclOpenGLES2Viewport( PP_Resource context, GLint x, GLint y, GLsizei width, GLsizei height )
{
  g_NaclOpenGLES2->Viewport(context, x, y, width, height);
}


// --------------------------------------------------------------------------------------------
// PPB_URLLoader inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Resource
NaclURLLoaderCreate(  )
{
  return g_NaclURLLoader->Create(g_NaclInstanceId);
}

inline PP_Bool
NaclURLLoaderIsURLLoader( PP_Resource resource )
{
  return g_NaclURLLoader->IsURLLoader(resource);
}

inline int32_t
NaclURLLoaderOpen( PP_Resource loader, PP_Resource request_info, PP_CompletionCallback callback )
{
  return g_NaclURLLoader->Open(loader, request_info, callback);
}

inline int32_t
NaclURLLoaderFollowRedirect( PP_Resource loader, PP_CompletionCallback callback )
{
  return g_NaclURLLoader->FollowRedirect(loader, callback);
}

inline PP_Bool
NaclURLLoaderGetUploadProgress( PP_Resource loader, int64_t* bytes_sent, int64_t* total_bytes_to_be_sent )
{
  return g_NaclURLLoader->GetUploadProgress(loader, bytes_sent, total_bytes_to_be_sent);
}

inline PP_Bool
NaclURLLoaderGetDownloadProgress( PP_Resource loader, int64_t* bytes_received, int64_t* total_bytes_to_be_received )
{
  return g_NaclURLLoader->GetDownloadProgress(loader, bytes_received, total_bytes_to_be_received);
}

inline PP_Resource
NaclURLLoaderGetResponseInfo( PP_Resource loader )
{
  return g_NaclURLLoader->GetResponseInfo(loader);
}

inline int32_t
NaclURLLoaderReadResponseBody( PP_Resource loader, void* buffer, int32_t bytes_to_read, PP_CompletionCallback callback )
{
  return g_NaclURLLoader->ReadResponseBody(loader, buffer, bytes_to_read, callback);
}

inline int32_t
NaclURLLoaderFinishStreamingToFile( PP_Resource loader, PP_CompletionCallback callback )
{
  return g_NaclURLLoader->FinishStreamingToFile(loader, callback);
}

inline void
NaclURLLoaderClose( PP_Resource loader )
{
  g_NaclURLLoader->Close(loader);
}


// --------------------------------------------------------------------------------------------
// PPB_URLRequestInfo inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Resource
NaclURLRequestInfoCreate(  )
{
  return g_NaclURLRequestInfo->Create(g_NaclInstanceId);
}

inline PP_Bool
NaclURLRequestInfoIsURLRequestInfo( PP_Resource resource )
{
  return g_NaclURLRequestInfo->IsURLRequestInfo(resource);
}

inline PP_Bool
NaclURLRequestInfoSetProperty( PP_Resource request, PP_URLRequestProperty property, PP_Var value )
{
  return g_NaclURLRequestInfo->SetProperty(request, property, value);
}

inline PP_Bool
NaclURLRequestInfoAppendDataToBody( PP_Resource request, const void* data, uint32_t len )
{
  return g_NaclURLRequestInfo->AppendDataToBody(request, data, len);
}

inline PP_Bool
NaclURLRequestInfoAppendFileToBody( PP_Resource request, PP_Resource file_ref, int64_t start_offset, int64_t number_of_bytes, PP_Time expected_last_modified_time )
{
  return g_NaclURLRequestInfo->AppendFileToBody(request, file_ref, start_offset, number_of_bytes, expected_last_modified_time);
}


// --------------------------------------------------------------------------------------------
// PPB_URLResponseInfo inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Bool
NaclURLResponseInfoIsURLResponseInfo( PP_Resource resource )
{
  return g_NaclURLResponseInfo->IsURLResponseInfo(resource);
}

inline PP_Var
NaclURLResponseInfoGetProperty( PP_Resource response, PP_URLResponseProperty property )
{
  return g_NaclURLResponseInfo->GetProperty(response, property);
}

inline PP_Resource
NaclURLResponseInfoGetBodyAsFileRef( PP_Resource response )
{
  return g_NaclURLResponseInfo->GetBodyAsFileRef(response);
}


// --------------------------------------------------------------------------------------------
// PPB_Var inline definitions
// --------------------------------------------------------------------------------------------
inline void
NaclVarAddRef( PP_Var var )
{
  g_NaclVar->AddRef(var);
}

inline void
NaclVarRelease( PP_Var var )
{
  g_NaclVar->Release(var);
}

inline PP_Var
NaclVarVarFromUtf8( const char* data, uint32_t len )
{
  return g_NaclVar->VarFromUtf8(data, len);
}

inline const char*
NaclVarVarToUtf8( PP_Var var, uint32_t* len )
{
  return g_NaclVar->VarToUtf8(var, len);
}


// --------------------------------------------------------------------------------------------
// PPB_VarArrayBuffer inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Var
NaclVarArrayBufferCreate( uint32_t size_in_bytes )
{
  return g_NaclVarArrayBuffer->Create(size_in_bytes);
}

inline PP_Bool
NaclVarArrayBufferByteLength( PP_Var array, uint32_t* byte_length )
{
  return g_NaclVarArrayBuffer->ByteLength(array, byte_length);
}

inline void*
NaclVarArrayBufferMap( PP_Var array )
{
  return g_NaclVarArrayBuffer->Map(array);
}

inline void
NaclVarArrayBufferUnmap( PP_Var array )
{
  g_NaclVarArrayBuffer->Unmap(array);
}


// --------------------------------------------------------------------------------------------
// PPB_View inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Bool
NaclViewIsView( PP_Resource resource )
{
  return g_NaclView->IsView(resource);
}

inline PP_Bool
NaclViewGetRect( PP_Resource resource, struct PP_Rect* rect )
{
  return g_NaclView->GetRect(resource, rect);
}

inline PP_Bool
NaclViewIsFullscreen( PP_Resource resource )
{
  return g_NaclView->IsFullscreen(resource);
}

inline PP_Bool
NaclViewIsVisible( PP_Resource resource )
{
  return g_NaclView->IsVisible(resource);
}

inline PP_Bool
NaclViewIsPageVisible( PP_Resource resource )
{
  return g_NaclView->IsPageVisible(resource);
}

inline PP_Bool
NaclViewGetClipRect( PP_Resource resource, struct PP_Rect* clip )
{
  return g_NaclView->GetClipRect(resource, clip);
}


// --------------------------------------------------------------------------------------------
// PPB_WebSocket inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Resource
NaclWebSocketCreate(  )
{
  return g_NaclWebSocket->Create(g_NaclInstanceId);
}

inline PP_Bool
NaclWebSocketIsWebSocket( PP_Resource resource )
{
  return g_NaclWebSocket->IsWebSocket(resource);
}

inline int32_t
NaclWebSocketConnect( PP_Resource web_socket, PP_Var url, const struct PP_Var protocols[], uint32_t protocol_count, PP_CompletionCallback callback )
{
  return g_NaclWebSocket->Connect(web_socket, url, protocols, protocol_count, callback);
}

inline int32_t
NaclWebSocketClose( PP_Resource web_socket, uint16_t code, PP_Var reason, PP_CompletionCallback callback )
{
  return g_NaclWebSocket->Close(web_socket, code, reason, callback);
}

inline int32_t
NaclWebSocketReceiveMessage( PP_Resource web_socket, struct PP_Var* message, PP_CompletionCallback callback )
{
  return g_NaclWebSocket->ReceiveMessage(web_socket, message, callback);
}

inline int32_t
NaclWebSocketSendMessage( PP_Resource web_socket, PP_Var message )
{
  return g_NaclWebSocket->SendMessage(web_socket, message);
}

inline uint64_t
NaclWebSocketGetBufferedAmount( PP_Resource web_socket )
{
  return g_NaclWebSocket->GetBufferedAmount(web_socket);
}

inline uint16_t
NaclWebSocketGetCloseCode( PP_Resource web_socket )
{
  return g_NaclWebSocket->GetCloseCode(web_socket);
}

inline PP_Var
NaclWebSocketGetCloseReason( PP_Resource web_socket )
{
  return g_NaclWebSocket->GetCloseReason(web_socket);
}

inline PP_Bool
NaclWebSocketGetCloseWasClean( PP_Resource web_socket )
{
  return g_NaclWebSocket->GetCloseWasClean(web_socket);
}

inline PP_Var
NaclWebSocketGetExtensions( PP_Resource web_socket )
{
  return g_NaclWebSocket->GetExtensions(web_socket);
}

inline PP_Var
NaclWebSocketGetProtocol( PP_Resource web_socket )
{
  return g_NaclWebSocket->GetProtocol(web_socket);
}

inline PP_WebSocketReadyState
NaclWebSocketGetReadyState( PP_Resource web_socket )
{
  return g_NaclWebSocket->GetReadyState(web_socket);
}

inline PP_Var
NaclWebSocketGetURL( PP_Resource web_socket )
{
  return g_NaclWebSocket->GetURL(web_socket);
}


// --------------------------------------------------------------------------------------------
// PPB_WheelInputEvent inline definitions
// --------------------------------------------------------------------------------------------
inline PP_Resource
NaclWheelInputEventCreate( PP_TimeTicks time_stamp, uint32_t modifiers, const struct PP_FloatPoint* wheel_delta, const struct PP_FloatPoint* wheel_ticks, PP_Bool scroll_by_page )
{
  return g_NaclWheelInputEvent->Create(g_NaclInstanceId, time_stamp, modifiers, wheel_delta, wheel_ticks, scroll_by_page);
}

inline PP_Bool
NaclWheelInputEventIsWheelInputEvent( PP_Resource resource )
{
  return g_NaclWheelInputEvent->IsWheelInputEvent(resource);
}

inline struct PP_FloatPoint
NaclWheelInputEventGetDelta( PP_Resource wheel_event )
{
  return g_NaclWheelInputEvent->GetDelta(wheel_event);
}

inline struct PP_FloatPoint
NaclWheelInputEventGetTicks( PP_Resource wheel_event )
{
  return g_NaclWheelInputEvent->GetTicks(wheel_event);
}

inline PP_Bool
NaclWheelInputEventGetScrollByPage( PP_Resource wheel_event )
{
  return g_NaclWheelInputEvent->GetScrollByPage(wheel_event);
}


#ifdef __cplusplus
} // extern "C"
#endif
