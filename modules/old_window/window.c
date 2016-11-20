#include <modules/window.h>
#include <modules/renderer.h>

int init_SDL(struct renderer_ctx *ctx) {
	int window_settings = SDL_WINDOW_OPENGL;
	/*
	if (game->settings.window_fullscreen) window_settings |= SDL_WINDOW_MAXIMIZED;
	if (game->settings.window_borderless) window_settings |= SDL_WINDOW_BORDERLESS;
	else window_settings |= SDL_WINDOW_RESIZABLE;
	*/
	window_settings |= SDL_WINDOW_RESIZABLE;
	
	
	
	ctx->window = SDL_CreateWindow("gamer game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, window_settings);
	if (ctx->window == NULL) {
		nx_log_msg("Failed to create window: %s.",1,SDL_GetError());
		return -1;
	}
	SDL_SetWindowMinimumSize(ctx->window, 640, 480);
	// filter all this shit
	
	SDL_EventState(SDL_JOYAXISMOTION, SDL_IGNORE);
	SDL_EventState(SDL_JOYBALLMOTION, SDL_IGNORE);
	SDL_EventState(SDL_JOYHATMOTION, SDL_IGNORE);
	SDL_EventState(SDL_JOYBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_JOYBUTTONUP, SDL_IGNORE);
	SDL_EventState(SDL_JOYDEVICEADDED, SDL_IGNORE);
	SDL_EventState(SDL_JOYDEVICEREMOVED, SDL_IGNORE);
	
	SDL_EventState(SDL_CONTROLLERAXISMOTION, SDL_IGNORE);
	SDL_EventState(SDL_CONTROLLERBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_CONTROLLERBUTTONUP, SDL_IGNORE);
	SDL_EventState(SDL_CONTROLLERDEVICEADDED, SDL_IGNORE);
	SDL_EventState(SDL_CONTROLLERDEVICEREMOVED, SDL_IGNORE);
	SDL_EventState(SDL_CONTROLLERDEVICEREMAPPED, SDL_IGNORE);
	
	return 0;
}

int init_GL(struct renderer_ctx *ctx) {
	// Define our attributes before creating a context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	
	ctx->gl_context = SDL_GL_CreateContext(ctx->window);
	if (!ctx->gl_context) {
		nx_log_msg("Failed to create GL context: %s.",1,SDL_GetError());
		return -2;
	}
	
	SDL_GetWindowSize(ctx->window, &ctx->window_x, &ctx->window_y);
	glewExperimental = GL_TRUE;
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		nx_log_msg("Glew failed to initialize: %s.",1,glewGetErrorString(glew_status));
		return -3;
	}
	if (!glewIsSupported("GL_VERSION_3_0")) {
		nx_log_msg("GPU doesn't support GL version 3.0. Please make sure your drivers are up-to-date.",1);
		return -4;
	}
	
	// this shit literally doesnt work how its documented god damn im so mad
	//if (SDL_GL_SetSwapInterval(1)) {
	//	log_error("vsync not supported on this system\n",&game->error,2);
	//}
	

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	//glBlendFunc(GL_ONE, GL_ONE);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	printf("Vendor: %s\n", glGetString (GL_VENDOR));
	printf("Renderer: %s\n", glGetString (GL_RENDERER));
	printf("Version: %s\n", glGetString (GL_VERSION));
	printf("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
	int tex_size; glGetIntegerv(GL_MAX_TEXTURE_SIZE, &tex_size);
	printf("GL max_texture_size: %i\n",tex_size);
	
	if (tex_size < 2048) {
		nx_log_msg("OpenGL max texture size is %i which is TOO SMALL. We may run into serious problems!",2,tex_size);
	}
	
	//SDL_GetMouseState(&game->mouse.mouse_position.x, &game->mouse.mouse_position.y);
	
	SDL_ShowCursor(SDL_DISABLE);
	return 0;
}