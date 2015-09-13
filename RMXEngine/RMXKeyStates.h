//
//  RMXKeyStates.h
//  AiCubo
//
//  Created by Max Bilbow on 13/09/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef RMXKeyStates_h
#define RMXKeyStates_h

#include <stdio.h>

#endif /* RMXKeyStates_h */


/*************************************************************************
 * RMX API tokens
 *************************************************************************/

/*! @name RMX version macros
 *  @{ */
/*! @brief The major version number of the RMX library.
 *
 *  This is incremented when the API is changed in non-compatible ways.
 *  @ingroup init
 */
#define RMX_VERSION_MAJOR          3
/*! @brief The minor version number of the RMX library.
 *
 *  This is incremented when features are added to the API but it remains
 *  backward-compatible.
 *  @ingroup init
 */
#define RMX_VERSION_MINOR          1
/*! @brief The revision number of the RMX library.
 *
 *  This is incremented when a bug fix release is made that does not contain any
 *  API changes.
 *  @ingroup init
 */
#define RMX_VERSION_REVISION       1
/*! @} */

/*! @name Key and button actions
 *  @{ */
/*! @brief The key or mouse button was released.
 *
 *  The key or mouse button was released.
 *
 *  @ingroup input
 */
#define RMX_RELEASE                0
/*! @brief The key or mouse button was pressed.
 *
 *  The key or mouse button was pressed.
 *
 *  @ingroup input
 */
#define RMX_PRESS                  1
/*! @brief The key was held down until it repeated.
 *
 *  The key was held down until it repeated.
 *
 *  @ingroup input
 */
#define RMX_REPEAT                 2
/*! @} */

/*! @defgroup keys Keyboard keys
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  These key codes are inspired by the _USB HID Usage Tables v1.12_ (p. 53-60),
 *  but re-arranged to map to 7-bit ASCII for printable keys (function keys are
 *  put in the 256+ range).
 *
 *  The naming of the key codes follow these rules:
 *   - The US keyboard layout is used
 *   - Names of printable alpha-numeric characters are used (e.g. "A", "R",
 *     "3", etc.)
 *   - For non-alphanumeric characters, Unicode:ish names are used (e.g.
 *     "COMMA", "LEFT_SQUARE_BRACKET", etc.). Note that some names do not
 *     correspond to the Unicode standard (usually for brevity)
 *   - Keys that lack a clear US mapping are named "WORLD_x"
 *   - For non-printable keys, custom names are used (e.g. "F4",
 *     "BACKSPACE", etc.)
 *
 *  @ingroup input
 *  @{
 */

/* The unknown key */
#define RMX_KEY_UNKNOWN            -1

/* Printable keys */
#define RMX_KEY_SPACE              32
#define RMX_KEY_APOSTROPHE         39  /* ' */
#define RMX_KEY_COMMA              44  /* , */
#define RMX_KEY_MINUS              45  /* - */
#define RMX_KEY_PERIOD             46  /* . */
#define RMX_KEY_SLASH              47  /* / */
#define RMX_KEY_0                  48
#define RMX_KEY_1                  49
#define RMX_KEY_2                  50
#define RMX_KEY_3                  51
#define RMX_KEY_4                  52
#define RMX_KEY_5                  53
#define RMX_KEY_6                  54
#define RMX_KEY_7                  55
#define RMX_KEY_8                  56
#define RMX_KEY_9                  57
#define RMX_KEY_SEMICOLON          59  /* ; */
#define RMX_KEY_EQUAL              61  /* = */
#define RMX_KEY_A                  65
#define RMX_KEY_B                  66
#define RMX_KEY_C                  67
#define RMX_KEY_D                  68
#define RMX_KEY_E                  69
#define RMX_KEY_F                  70
#define RMX_KEY_G                  71
#define RMX_KEY_H                  72
#define RMX_KEY_I                  73
#define RMX_KEY_J                  74
#define RMX_KEY_K                  75
#define RMX_KEY_L                  76
#define RMX_KEY_M                  77
#define RMX_KEY_N                  78
#define RMX_KEY_O                  79
#define RMX_KEY_P                  80
#define RMX_KEY_Q                  81
#define RMX_KEY_R                  82
#define RMX_KEY_S                  83
#define RMX_KEY_T                  84
#define RMX_KEY_U                  85
#define RMX_KEY_V                  86
#define RMX_KEY_W                  87
#define RMX_KEY_X                  88
#define RMX_KEY_Y                  89
#define RMX_KEY_Z                  90
#define RMX_KEY_LEFT_BRACKET       91  /* [ */
#define RMX_KEY_BACKSLASH          92  /* \ */
#define RMX_KEY_RIGHT_BRACKET      93  /* ] */
#define RMX_KEY_GRAVE_ACCENT       96  /* ` */
#define RMX_KEY_WORLD_1            161 /* non-US #1 */
#define RMX_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define RMX_KEY_ESCAPE             256
#define RMX_KEY_ENTER              257
#define RMX_KEY_TAB                258
#define RMX_KEY_BACKSPACE          259
#define RMX_KEY_INSERT             260
#define RMX_KEY_DELETE             261
#define RMX_KEY_RIGHT              262
#define RMX_KEY_LEFT               263
#define RMX_KEY_DOWN               264
#define RMX_KEY_UP                 265
#define RMX_KEY_PAGE_UP            266
#define RMX_KEY_PAGE_DOWN          267
#define RMX_KEY_HOME               268
#define RMX_KEY_END                269
#define RMX_KEY_CAPS_LOCK          280
#define RMX_KEY_SCROLL_LOCK        281
#define RMX_KEY_NUM_LOCK           282
#define RMX_KEY_PRINT_SCREEN       283
#define RMX_KEY_PAUSE              284
#define RMX_KEY_F1                 290
#define RMX_KEY_F2                 291
#define RMX_KEY_F3                 292
#define RMX_KEY_F4                 293
#define RMX_KEY_F5                 294
#define RMX_KEY_F6                 295
#define RMX_KEY_F7                 296
#define RMX_KEY_F8                 297
#define RMX_KEY_F9                 298
#define RMX_KEY_F10                299
#define RMX_KEY_F11                300
#define RMX_KEY_F12                301
#define RMX_KEY_F13                302
#define RMX_KEY_F14                303
#define RMX_KEY_F15                304
#define RMX_KEY_F16                305
#define RMX_KEY_F17                306
#define RMX_KEY_F18                307
#define RMX_KEY_F19                308
#define RMX_KEY_F20                309
#define RMX_KEY_F21                310
#define RMX_KEY_F22                311
#define RMX_KEY_F23                312
#define RMX_KEY_F24                313
#define RMX_KEY_F25                314
#define RMX_KEY_KP_0               320
#define RMX_KEY_KP_1               321
#define RMX_KEY_KP_2               322
#define RMX_KEY_KP_3               323
#define RMX_KEY_KP_4               324
#define RMX_KEY_KP_5               325
#define RMX_KEY_KP_6               326
#define RMX_KEY_KP_7               327
#define RMX_KEY_KP_8               328
#define RMX_KEY_KP_9               329
#define RMX_KEY_KP_DECIMAL         330
#define RMX_KEY_KP_DIVIDE          331
#define RMX_KEY_KP_MULTIPLY        332
#define RMX_KEY_KP_SUBTRACT        333
#define RMX_KEY_KP_ADD             334
#define RMX_KEY_KP_ENTER           335
#define RMX_KEY_KP_EQUAL           336
#define RMX_KEY_LEFT_SHIFT         340
#define RMX_KEY_LEFT_CONTROL       341
#define RMX_KEY_LEFT_ALT           342
#define RMX_KEY_LEFT_SUPER         343
#define RMX_KEY_RIGHT_SHIFT        344
#define RMX_KEY_RIGHT_CONTROL      345
#define RMX_KEY_RIGHT_ALT          346
#define RMX_KEY_RIGHT_SUPER        347
#define RMX_KEY_MENU               348
#define RMX_KEY_LAST               RMX_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

/*! @brief If this bit is set one or more Shift keys were held down.
 */
#define RMX_MOD_SHIFT           0x0001
/*! @brief If this bit is set one or more Control keys were held down.
 */
#define RMX_MOD_CONTROL         0x0002
/*! @brief If this bit is set one or more Alt keys were held down.
 */
#define RMX_MOD_ALT             0x0004
/*! @brief If this bit is set one or more Super keys were held down.
 */
#define RMX_MOD_SUPER           0x0008

/*! @} */

/*! @defgroup buttons Mouse buttons
 *
 *  See [mouse button input](@ref input_mouse_button) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define RMX_MOUSE_BUTTON_1         0
#define RMX_MOUSE_BUTTON_2         1
#define RMX_MOUSE_BUTTON_3         2
#define RMX_MOUSE_BUTTON_4         3
#define RMX_MOUSE_BUTTON_5         4
#define RMX_MOUSE_BUTTON_6         5
#define RMX_MOUSE_BUTTON_7         6
#define RMX_MOUSE_BUTTON_8         7
#define RMX_MOUSE_BUTTON_LAST      RMX_MOUSE_BUTTON_8
#define RMX_MOUSE_BUTTON_LEFT      RMX_MOUSE_BUTTON_1
#define RMX_MOUSE_BUTTON_RIGHT     RMX_MOUSE_BUTTON_2
#define RMX_MOUSE_BUTTON_MIDDLE    RMX_MOUSE_BUTTON_3
/*! @} */

/*! @defgroup joysticks Joysticks
 *
 *  See [joystick input](@ref joystick) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define RMX_JOYSTICK_1             0
#define RMX_JOYSTICK_2             1
#define RMX_JOYSTICK_3             2
#define RMX_JOYSTICK_4             3
#define RMX_JOYSTICK_5             4
#define RMX_JOYSTICK_6             5
#define RMX_JOYSTICK_7             6
#define RMX_JOYSTICK_8             7
#define RMX_JOYSTICK_9             8
#define RMX_JOYSTICK_10            9
#define RMX_JOYSTICK_11            10
#define RMX_JOYSTICK_12            11
#define RMX_JOYSTICK_13            12
#define RMX_JOYSTICK_14            13
#define RMX_JOYSTICK_15            14
#define RMX_JOYSTICK_16            15
#define RMX_JOYSTICK_LAST          RMX_JOYSTICK_16
/*! @} */

/*! @defgroup errors Error codes
 *
 *  See [error handling](@ref error_handling) for how these are used.
 *
 *  @ingroup init
 *  @{ */
/*! @brief RMX has not been initialized.
 *
 *  This occurs if a RMX function was called that may not be called unless the
 *  library is [initialized](@ref intro_init).
 *
 *  @par Analysis
 *  Application programmer error.  Initialize RMX before calling any function
 *  that requires initialization.
 */
#define RMX_NOT_INITIALIZED        0x00010001
/*! @brief No context is current for this thread.
 *
 *  This occurs if a RMX function was called that needs and operates on the
 *  current OpenGL or OpenGL ES context but no context is current on the calling
 *  thread.  One such function is @ref RMXSwapInterval.
 *
 *  @par Analysis
 *  Application programmer error.  Ensure a context is current before calling
 *  functions that require a current context.
 */
#define RMX_NO_CURRENT_CONTEXT     0x00010002
/*! @brief One of the arguments to the function was an invalid enum value.
 *
 *  One of the arguments to the function was an invalid enum value, for example
 *  requesting [RMX_RED_BITS](@ref window_hints_fb) with @ref
 *  RMXGetWindowAttrib.
 *
 *  @par Analysis
 *  Application programmer error.  Fix the offending call.
 */
#define RMX_INVALID_ENUM           0x00010003
/*! @brief One of the arguments to the function was an invalid value.
 *
 *  One of the arguments to the function was an invalid value, for example
 *  requesting a non-existent OpenGL or OpenGL ES version like 2.7.
 *
 *  Requesting a valid but unavailable OpenGL or OpenGL ES version will instead
 *  result in a @ref RMX_VERSION_UNAVAILABLE error.
 *
 *  @par Analysis
 *  Application programmer error.  Fix the offending call.
 */
#define RMX_INVALID_VALUE          0x00010004
/*! @brief A memory allocation failed.
 *
 *  A memory allocation failed.
 *
 *  @par Analysis
 *  A bug in RMX or the underlying operating system.  Report the bug to our
 *  [issue tracker](https://github.com/RMX/RMX/issues).
 */
#define RMX_OUT_OF_MEMORY          0x00010005
/*! @brief RMX could not find support for the requested client API on the
 *  system.
 *
 *  RMX could not find support for the requested client API on the system.  If
 *  emitted by functions other than @ref RMXCreateWindow, no supported client
 *  API was found.
 *
 *  @par Analysis
 *  The installed graphics driver does not support the requested client API, or
 *  does not support it via the chosen context creation backend.  Below are
 *  a few examples.
 *
 *  @par
 *  Some pre-installed Windows graphics drivers do not support OpenGL.  AMD only
 *  supports OpenGL ES via EGL, while Nvidia and Intel only supports it via
 *  a WGL or GLX extension.  OS X does not provide OpenGL ES at all.  The Mesa
 *  EGL, OpenGL and OpenGL ES libraries do not interface with the Nvidia binary
 *  driver.
 */
#define RMX_API_UNAVAILABLE        0x00010006
/*! @brief The requested OpenGL or OpenGL ES version is not available.
 *
 *  The requested OpenGL or OpenGL ES version (including any requested context
 *  or framebuffer hints) is not available on this machine.
 *
 *  @par Analysis
 *  The machine does not support your requirements.  If your application is
 *  sufficiently flexible, downgrade your requirements and try again.
 *  Otherwise, inform the user that their machine does not match your
 *  requirements.
 *
 *  @par
 *  Future invalid OpenGL and OpenGL ES versions, for example OpenGL 4.8 if 5.0
 *  comes out before the 4.x series gets that far, also fail with this error and
 *  not @ref RMX_INVALID_VALUE, because RMX cannot know what future versions
 *  will exist.
 */
#define RMX_VERSION_UNAVAILABLE    0x00010007
/*! @brief A platform-specific error occurred that does not match any of the
 *  more specific categories.
 *
 *  A platform-specific error occurred that does not match any of the more
 *  specific categories.
 *
 *  @par Analysis
 *  A bug or configuration error in RMX, the underlying operating system or
 *  its drivers, or a lack of required resources.  Report the issue to our
 *  [issue tracker](https://github.com/RMX/RMX/issues).
 */
#define RMX_PLATFORM_ERROR         0x00010008
/*! @brief The requested format is not supported or available.
 *
 *  If emitted during window creation, the requested pixel format is not
 *  supported.
 *
 *  If emitted when querying the clipboard, the contents of the clipboard could
 *  not be converted to the requested format.
 *
 *  @par Analysis
 *  If emitted during window creation, one or more
 *  [hard constraints](@ref window_hints_hard) did not match any of the
 *  available pixel formats.  If your application is sufficiently flexible,
 *  downgrade your requirements and try again.  Otherwise, inform the user that
 *  their machine does not match your requirements.
 *
 *  @par
 *  If emitted when querying the clipboard, ignore the error or report it to
 *  the user, as appropriate.
 */
#define RMX_FORMAT_UNAVAILABLE     0x00010009
/*! @} */

#define RMX_FOCUSED                0x00020001
#define RMX_ICONIFIED              0x00020002
#define RMX_RESIZABLE              0x00020003
#define RMX_VISIBLE                0x00020004
#define RMX_DECORATED              0x00020005
#define RMX_AUTO_ICONIFY           0x00020006
#define RMX_FLOATING               0x00020007

#define RMX_RED_BITS               0x00021001
#define RMX_GREEN_BITS             0x00021002
#define RMX_BLUE_BITS              0x00021003
#define RMX_ALPHA_BITS             0x00021004
#define RMX_DEPTH_BITS             0x00021005
#define RMX_STENCIL_BITS           0x00021006
#define RMX_ACCUM_RED_BITS         0x00021007
#define RMX_ACCUM_GREEN_BITS       0x00021008
#define RMX_ACCUM_BLUE_BITS        0x00021009
#define RMX_ACCUM_ALPHA_BITS       0x0002100A
#define RMX_AUX_BUFFERS            0x0002100B
#define RMX_STEREO                 0x0002100C
#define RMX_SAMPLES                0x0002100D
#define RMX_SRGB_CAPABLE           0x0002100E
#define RMX_REFRESH_RATE           0x0002100F
#define RMX_DOUBLEBUFFER           0x00021010

#define RMX_CLIENT_API             0x00022001
#define RMX_CONTEXT_VERSION_MAJOR  0x00022002
#define RMX_CONTEXT_VERSION_MINOR  0x00022003
#define RMX_CONTEXT_REVISION       0x00022004
#define RMX_CONTEXT_ROBUSTNESS     0x00022005
#define RMX_OPENGL_FORWARD_COMPAT  0x00022006
#define RMX_OPENGL_DEBUG_CONTEXT   0x00022007
#define RMX_OPENGL_PROFILE         0x00022008
#define RMX_CONTEXT_RELEASE_BEHAVIOR 0x00022009

#define RMX_OPENGL_API             0x00030001
#define RMX_OPENGL_ES_API          0x00030002

#define RMX_NO_ROBUSTNESS                   0
#define RMX_NO_RESET_NOTIFICATION  0x00031001
#define RMX_LOSE_CONTEXT_ON_RESET  0x00031002

#define RMX_OPENGL_ANY_PROFILE              0
#define RMX_OPENGL_CORE_PROFILE    0x00032001
#define RMX_OPENGL_COMPAT_PROFILE  0x00032002

#define RMX_CURSOR                 0x00033001
#define RMX_STICKY_KEYS            0x00033002
#define RMX_STICKY_MOUSE_BUTTONS   0x00033003

#define RMX_CURSOR_NORMAL          0x00034001
#define RMX_CURSOR_HIDDEN          0x00034002
#define RMX_CURSOR_DISABLED        0x00034003

#define RMX_ANY_RELEASE_BEHAVIOR            0
#define RMX_RELEASE_BEHAVIOR_FLUSH 0x00035001
#define RMX_RELEASE_BEHAVIOR_NONE  0x00035002

/*! @defgroup shapes Standard cursor shapes
 *
 *  See [standard cursor creation](@ref cursor_standard) for how these are used.
 *
 *  @ingroup input
 *  @{ */

/*! @brief The regular arrow cursor shape.
 *
 *  The regular arrow cursor.
 */
#define RMX_ARROW_CURSOR           0x00036001
/*! @brief The text input I-beam cursor shape.
 *
 *  The text input I-beam cursor shape.
 */
#define RMX_IBEAM_CURSOR           0x00036002
/*! @brief The crosshair shape.
 *
 *  The crosshair shape.
 */
#define RMX_CROSSHAIR_CURSOR       0x00036003
/*! @brief The hand shape.
 *
 *  The hand shape.
 */
#define RMX_HAND_CURSOR            0x00036004
/*! @brief The horizontal resize arrow shape.
 *
 *  The horizontal resize arrow shape.
 */
#define RMX_HRESIZE_CURSOR         0x00036005
/*! @brief The vertical resize arrow shape.
 *
 *  The vertical resize arrow shape.
 */
#define RMX_VRESIZE_CURSOR         0x00036006
/*! @} */

#define RMX_CONNECTED              0x00040001
#define RMX_DISCONNECTED           0x00040002

#define RMX_DONT_CARE              -1

