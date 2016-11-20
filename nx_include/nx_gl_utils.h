#include <nx_error.h>
#include <include_gl.h>
#include <nx_asset.h>
#include <assert.h>
#include <pthread.h>

struct nx_gl_context {
	GLuint vertex_pos, uv_pos, normal_pos;
	GLuint texture_uni_pos, mvp_uni_pos;
};

#ifdef __cplusplus
extern "C" {
#endif

GLuint nx_gen_program(const char *geometry_path, const char *vertex_path, const char *fragment_path);
void GL_upload_asset(struct nx_asset **input_asset, struct nx_gl_context *context);
void GL_draw_model(struct nx_asset_gpu_model *model, struct nx_gl_context *context);
GLuint nx_gen_program_from_memory(char *geometry_src, char *vertex_src, char *fragment_src, const char *id_str);

#ifdef __cplusplus
}
#endif