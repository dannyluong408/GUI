#include <modules/renderer.h>

int init_render_ctx(renderer_ctx *ctx) {
	memset(ctx, 0, sizeof(renderer_ctx));
	ctx->initial_loading_screen = nx_new_asset("resources/ui/loading.png", NX_PNG, 0);
	
	ctx->general_vs = nx_new_asset("resources/shaders/330_core/low/general_low.vert", NX_TEXT_FILE, 0);
	ctx->general_fs = nx_new_asset("resources/shaders/330_core/low/general_low.frag", NX_TEXT_FILE, 0);

	ctx->mtx = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	
	//return !(ctx->gui_vs && ctx->gui_fs && ctx->text_vs && ctx->text_fs && ctx->general_vs && ctx->general_fs);
	if (!(ctx->general_vs && ctx->general_fs)) {
		nx_log_msg("Failed to init general shaders.",1);
		return -1;
	}
	return 0;
}
/*
static int resize_frame(struct renderer_ctx *ctx, const uint32_t new_x, const uint32_t new_y) {
	if (ctx->frame_buffer) {
		glDeleteFramebuffers(1, &ctx->frame_buffer);
		ctx->frame_buffer = 0;
	}
	glGenFramebuffers(1, &ctx->frame_buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, ctx->frame_buffer);
	if (ctx->depth_texture) {
		glDeleteTextures(1, &ctx->depth_texture);
		ctx->depth_texture = 0;
	}
	glGenTextures(1, &ctx->depth_texture);
	glBindTexture(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, new_x, new_y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ctx->depth_texture, 0);
	
	return (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE);
}*/

void *start_renderer_gl33(void *input) {
	renderer_ctx *context = game_state.get_renderer_context();
	glfwMakeContextCurrent(context->window.glfw_window); // wew
	
	glfwGetFramebufferSize(context->window.glfw_window, &context->window.res_x, &context->window.res_y);
	
	nx_timer frame_timer, fps_timer;
	nx_init_timer(&frame_timer,30);
	nx_init_timer(&fps_timer,200);
	glViewport(0, 0, context->window.res_x, context->window.res_y);
	// This doesn't work on any driver I've ever tried it on.
	glfwSwapInterval(0);
	glClearColor(0.13f, 0.27f, 0.75f, 1.0f);

	context->window.nanogui_screen = new (std::nothrow) nanogui::Screen();
	if (!context->window.nanogui_screen) {
		nx_log_msg("Failed to initialize GUI.",1);
		return NULL;
	}
	context->window.nanogui_screen->initialize(context->window.glfw_window, false);
	context->window.gui = new (std::nothrow) nanogui::FormHelper(context->window.nanogui_screen);
	
	glfwSetCursorPosCallback(context->window.glfw_window, 
		[](GLFWwindow *, double x, double y) {
			nx_cursor_pos_callback(x, y);
		}
	);
	glfwSetMouseButtonCallback(context->window.glfw_window,
		[](GLFWwindow *, int button, int action, int modifiers) {
			nx_mouse_callback(button, action, modifiers);
		}
	);
	glfwSetKeyCallback(context->window.glfw_window,
		[](GLFWwindow *, int key, int scancode, int action, int mods) {
			nx_key_callback(key, scancode, action, mods);
		}
	);
	glfwSetCharCallback(context->window.glfw_window,
		[](GLFWwindow*, unsigned int codepoint) {
			nx_char_callback(codepoint);
		}
	);
	/*
	glfwSetDropCallback(context->window.glfw_window,
		[](GLFWwindow *, int count, const char **filenames) {
			nx_drop_callback(count, filenames);
		}
	);
	*/
	glfwSetScrollCallback(context->window.glfw_window,
		[&](GLFWwindow *, double x, double y) {
			nx_scroll_callback(x,y);
		}
	);
	glfwSetFramebufferSizeCallback(context->window.glfw_window,
		[](GLFWwindow *, int width, int height) {
			//context->window.nanogui_screen->resizeCallbackEvent(width, height);
			nx_framebuffer_callback(width, height);
		}
	);
	context->window.nanogui_screen->setVisible(1);
	context->window.nanogui_screen->performLayout();
	// Ready to poll on main thread.
	context->window.polling_ready = 1;
	
	
	struct nx_asset *next_asset = NULL;
	
	nx_asset_wait_change(context->general_vs);
	nx_asset_wait_change(context->general_fs);
	context->general_shader = nx_gen_program_from_memory(NULL, (char*)context->general_vs->data, (char*)context->general_fs->data, "General 3D shader");
	if (!context->general_shader) {
		return NULL;
	}
	// necessary?
	//glUseProgram(context->general_shader);
	glBindFragDataLocation(context->general_shader, 0, "outputc");
	context->attribs.vertex_pos = glGetAttribLocation(context->general_shader, "vertex_modelspace");
	context->attribs.uv_pos = glGetAttribLocation(context->general_shader, "vertexUV");
	context->attribs.normal_pos = glGetAttribLocation(context->general_shader, "object_normal");
	context->attribs.texture_uni_pos = glGetUniformLocation(context->general_shader, "bound_texture");
	context->attribs.mvp_uni_pos = glGetUniformLocation(context->general_shader, "MVP");
	

	do {
		GL_upload_asset(&next_asset, &context->attribs);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// do render stuff
		
		
		
		
		
		
		
		glfwSwapBuffers(context->window.glfw_window);
		
		// Block until new command comes.
		game_state.renderer_block();
	} while (!game_state.quit());
	
	
	
	
	
	
	
	return NULL;
}