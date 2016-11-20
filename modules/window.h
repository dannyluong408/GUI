#ifndef __MODULES_WINDOW_H
#define __MODULES_WINDOW_H

#include <stdint.h>
#include <signal.h>
#include <pthread.h>
#include <nx_include/nx_error.h>
#undef Sucess // X macro conflicts with Eigen
#include <nanogui/nanogui.h>
#include <GLFW/glfw3.h>

enum window_flags {
	NX_FULLSCREEN = 1,
	NX_WINDOWED = 2,
	NX_BORDERLESS = 4
};

struct window_ctx {
	int32_t res_x, res_y;
	uint32_t flags;
	
	GLFWwindow *glfw_window;
	nanogui::Screen *nanogui_screen;
	nanogui::FormHelper *gui;
	volatile sig_atomic_t polling_ready;
};

int mylescraft_init_window(window_ctx *ctx, const uint32_t flags, const int32_t x, const int32_t y);









#endif // __MODULES_WINDOW_H