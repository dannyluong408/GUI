#include <modules/input.h>

int nx_cursor_pos_callback(const double x, const double y) {
	renderer_ctx *context = game_state.get_renderer_context();
	
	pthread_mutex_lock(&context->mtx);
	if (!context->window.nanogui_screen->cursorPosCallbackEvent(x,y)) {
		// cursor stuff
	}
	pthread_mutex_unlock(&context->mtx);
	return 0;
}
int nx_mouse_callback(const int button, const int action, const int modifiers) {
	renderer_ctx *context = game_state.get_renderer_context();
	
	pthread_mutex_lock(&context->mtx);
	if (!context->window.nanogui_screen->mouseButtonCallbackEvent(button, action, modifiers)) {
		// code stuff
	}
	pthread_mutex_unlock(&context->mtx);
	return 0;
}
int nx_key_callback(const int key, const int scancode, const int action, const int mods) {
	renderer_ctx *context = game_state.get_renderer_context();
	
	pthread_mutex_lock(&context->mtx);
	if (!context->window.nanogui_screen->keyCallbackEvent(key, scancode, action, mods)) {
		// do stuff here
	}
	pthread_mutex_unlock(&context->mtx);
	return 0;
}

int nx_char_callback(const unsigned int codepoint) {
	renderer_ctx *context = game_state.get_renderer_context();
	
	pthread_mutex_lock(&context->mtx);
	context->window.nanogui_screen->charCallbackEvent(codepoint);
	pthread_mutex_unlock(&context->mtx);
	
	return 0;
}

// do i even want this.
int nx_drop_callback(const int count, const char **filenames) {
	renderer_ctx *context = game_state.get_renderer_context();
	
	pthread_mutex_lock(&context->mtx);
	context->window.nanogui_screen->dropCallbackEvent(count, filenames);
	puts("file drop not fully supported");
	pthread_mutex_unlock(&context->mtx);

	return 0;
}

int nx_scroll_callback(const double x, const double y) {
	renderer_ctx *context = game_state.get_renderer_context();
	
	pthread_mutex_lock(&context->mtx);
	if (!context->window.nanogui_screen->scrollCallbackEvent(x, y)) {
		// scroll handler goes here.
	}
	pthread_mutex_unlock(&context->mtx);
	return 0;
}
int nx_framebuffer_callback(const int width, const int height) {
	renderer_ctx *context = game_state.get_renderer_context();
	
	pthread_mutex_lock(&context->mtx);
	context->window.nanogui_screen->resizeCallbackEvent(width, height);
	context->window.res_x = width;
	context->window.res_y = height;
	pthread_mutex_unlock(&context->mtx);
	
	return 0;
}

void read_input() {
	while (!game_state.quit()) {
		glfwPollEvents();
		nx_usleep(game_state.get_sleep_int());
	}
}