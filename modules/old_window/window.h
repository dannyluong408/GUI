#ifndef __MODULES_WINDOW_H
#define __MODULES_WINDOW_H

struct renderer_ctx;

#include <modules/window.h>
#include <modules/renderer.h>

int init_SDL(struct renderer_ctx *ctx);
int init_GL(struct renderer_ctx *ctx);

#endif // __MODULES_WINDOW_H