#ifndef __MODULES_RENDERER_H
#define __MODULES_RENDERER_H

#include <nx_gl_utils.h>
#include <nx_asset.h>
#include <nx_error.h>
#include <nx_ftgl.h>
#include <nx_timing.h>
#include <nx_profiling.h>

#include <pthread.h>
#include <stdint.h>
#include <string.h>

#include <modules/game_state.h>
#include <modules/window.h>
#include <nanogui/nanogui.h>
#include <modules/input.h>

//#include <map/types.h>

struct Game_state;

enum {
	NX_NO_RENDERER = 0,
	NX_GL33,
	// unimplemented types
	NX_GL40,
	NX_GL45_ARB,
	NX_VK1
};

struct render_buffer {
	float camera_x, camera_y;
	float pos_x, pos_y, pos_z;
	// more stuff goes here!
};

struct renderer_limits {
	int max_texture_size; // GL_MAX_TEXTURE_SIZE
	int max_viewport_dims[2]; // GL_MAX_VIEWPORT_DIMS
};

struct renderer_ctx {
	// Non-shared state. No modifying from outside the render thread.
	struct nx_asset *initial_loading_screen;
	struct nx_asset *general_vs, *general_fs;
	
		//*gui_vs, *gui_fs, *text_fs, *text_vs;
	GLuint general_shader;// gui_shader, text_shader;
	GLuint depth_texture, frame_buffer;
	
	struct nx_gl_context attribs;
	
	// Shared state with other threads.
	pthread_mutex_t mtx;
	// Window sizes
	uint8_t msaa_level;
	
	window_ctx window;
	
	struct render_buffer *current, *next;
	
	// idk what to do with this
	void *feedback;
};

void *start_renderer_gl33(void *input);
int init_render_ctx(renderer_ctx *ctx);


#endif // __MODULES_RENDERER_H
