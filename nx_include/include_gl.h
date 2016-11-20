#pragma once
#define GLEW_STATIC
#if defined(_WIN32)
	#include <GL/glew.h>
	#include <GL/gl.h>
#elif defined(__gnu_linux__)
	#include <GL/glew.h>
	#include <GL/gl.h>
#elif defined(__ANDROID__)
	#undef NX_FTGL_PIXEL_FMT
	#define NX_FTGL_PIXEL_FMT GL_LUMINANCE
	#include <GLES2/gl2.h>
#elif defined(__APPLE__)
	#include "TargetConditionals.h"
	#if defined(TARGET_OS_IPHONE)
		#undef NX_FTGL_PIXEL_FMT
		#define NX_FTGL_PIXEL_FMT GL_LUMINANCE
		#include <OpenGLES/ES2/gl.h>
	#elif defined(TARGET_OS_MAC)
		#include <OpenGL/gl.h>
	#endif
#endif