#include <modules/window.h>

static void mylescraft_glfw_error_wrapper(int errcode, const char *errstr) {
	// TODO: use errcode to determine how problematic the error is.
	
	
	// since nx_log_msg is thread-safe, this should be fine as a callback.
	nx_log_msg("glfw error: %s",2,errstr); 
	// i really dont like this callback method tbh.
}

int mylescraft_init_window(window_ctx *ctx, const uint32_t flags, const int32_t x, const int32_t y) {
	glfwSetErrorCallback(&mylescraft_glfw_error_wrapper);
	if (!glfwInit()) {
		nx_log_msg("Failed to start video & input handling subsystem.",1);
		return -1;
	}
	glfwSetTime(0);
	
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	// We're using fb multisampling.
	glfwWindowHint(GLFW_SAMPLES, 0);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	
	ctx->glfw_window = glfwCreateWindow(x, y, "mylescraft", glfwGetPrimaryMonitor(), NULL);
	if (!ctx->glfw_window) {
		nx_log_msg("Failed to create window.",1);
		return -2;
	}
	glfwGetWindowSize(ctx->glfw_window, &ctx->res_x, &ctx->res_y);
	//glfwSetWindowMonitor(ctx->window, glfwGetPrimaryMonitor(),
	
	return 0;
}