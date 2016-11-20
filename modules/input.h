#ifndef __MODULES_INPUT_H
#define __MODULES_INPUT_H

#include <modules/game_state.h>

int nx_cursor_pos_callback(const double x, const double y);
int nx_mouse_callback(const int button, const int action, const int modifiers);
int nx_key_callback(const int key, const int scancode, const int action, const int mods);
int nx_char_callback(const unsigned int codepoint);
// do i even want this
int nx_drop_callback(const int count, const char **filenames);
int nx_scroll_callback(const double x, const double y);
int nx_framebuffer_callback(const int width, const int height);

void read_input();

#endif // __MODULES_INPUT_H