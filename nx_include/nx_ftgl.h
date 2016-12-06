#ifndef __NX_FTGL_H
#define __NX_FTGL_H

// Workaround for GLES2 quirky pixel format support
#define NX_FTGL_PIXEL_FMT GL_RED

#include <GL/glew.h>

#if defined(_WIN32)
	#include <gl/gl.h>
#elif defined(__gnu_linux__)
	#include <GL/gl.h>
#elif defined(__ANDROID__)
	#include <GLES2/gl2.h>
	#undef NX_FTGL_PIXEL_FMT
	#define NX_FTGL_PIXEL_FMT GL_LUMINANCE
#elif defined(__APPLE__)
	#include "TargetConditionals.h"
	#if defined(TARGET_OS_IPHONE)
		#include <OpenGLES/ES2/gl.h>
		#undef NX_FTGL_PIXEL_FMT
		#define NX_FTGL_PIXEL_FMT GL_LUMINANCE
	#elif defined(TARGET_OS_MAC)
		#include <OpenGL/gl.h>
	#endif
#endif

#include <ft2build.h>
#include FT_FREETYPE_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

struct nx_ftgl_vec2f {
	GLfloat x,y;
};

struct nx_ftgl_vec4f {
	GLfloat r,g,b,a;
};

struct nx_ftgl_vec2i {
	int32_t x,y;
};

union nx_ftgl_ucs4 {
	uint32_t code;
	unsigned char byte[4];
};

struct nx_ftgl_spatial_node {
	struct nx_ftgl_vec2i pos, dimensions;
};

struct nx_ftgl_spatial_directory {
	uint32_t n_children;
	struct nx_ftgl_spatial_node **child;
};

struct nx_ftgl_glyph {
	struct nx_ftgl_vec2i dimensions, bearing;
	struct nx_ftgl_vec2f tex_position, tex_dimensions;
	GLuint advance;
	union nx_ftgl_ucs4 charcode;
	uint16_t size;
	uint64_t last_used;
	struct nx_ftgl_glyph *next;
};

struct nx_ftgl_face {
	FT_Face FTface;
	struct nx_ftgl_glyph *glyphs;
};

// Generate vec2i
struct nx_ftgl_vec2i nx_ftgl_vec2i(const int32_t x, const int32_t y);

int nx_ftgl_init();
void nx_ftgl_exit();

void nx_ftgl_set_fallbackfont(const uint32_t new_fallback_face_id);
void nx_ftgl_setshader2D(const GLuint id);

int nx_ftgl_genbuffer(const uint32_t size);
void nx_ftgl_deletebuffer();
int nx_ftgl_loadfont(const char *path);

int nx_ftgl_buffertext(const unsigned char *text, const uint32_t face_id, const uint16_t size);

int nx_ftgl_rendertext(const unsigned char *text, const uint32_t face_id, const uint16_t size, const struct nx_ftgl_vec2i viewport, const struct nx_ftgl_vec2i position, const struct nx_ftgl_vec4f color);
int nx_ftgl_rendertext_center_at_x(const unsigned char *text, const uint32_t face_id, const uint16_t size, const struct nx_ftgl_vec2i viewport, const struct nx_ftgl_vec2i position, const struct nx_ftgl_vec4f color);

#endif /* __NX_FTGL_H */