#ifndef __NX_ASSET_H
#define __NX_ASSET_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>

#ifdef ASSET_USE_GL
#include <QtOpenGL>
#include <QImage>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif

#ifdef __WIN32
	#include <io.h>
	#include <fcntl.h>
	#include <Share.h>
	#include <sys/stat.h>
#elif defined(_POSIX_VERSION)
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
#else
	#error "No valid file IO system setup for this platform."
#endif

#include <nx_include/nx_error.h>
#include <nx_include/nx_timing.h>

#define NX_RGB 3
#define NX_RGBA 4

#ifdef __cplusplus
extern "C" {
#endif


enum {
	NX_NO_FORMAT = 0, // Signifies deleted or otherwise unusable
	NX_IMG = 1,
	NX_IMG_PERSIST = 2, // Do not upload this img as a texture when complete.
	NX_TEXTURE = 4, // Completely uploaded textures only. Switched by GL thread.
	NX_MODEL = 8, 
	NX_MODEL_EXT = 16, // Extended model format.
	NX_GPU_MODEL = 32, // Completely uploaded models only. Switched by GL thread.
	
	NX_SKYBOX = 128, // NYI
	
	//NX_OPUS = 256,
	NX_COLLISION_TABLE = 512,
	// As far as I'm concerned, this can be used for misc binary files as well.
	NX_TEXT_FILE = 1024,
};

enum {
	NX_REQUIRED_START = 0,
	NX_REQUIRED_GAMEPLAY = 1,
	NX_NON_ESSENTIAL_ASSET = 100,
};

enum {
	NX_ASSET_INITIALIZED,
	NX_ASSET_LOADED,
	NX_ASSET_FAILED_INVALID_FILE,
	NX_ASSET_FAILED_INVALID_DATA, // Incorrect type or invalid data
	NX_ASSET_FAILED_MISC
};
#ifdef ASSET_USE_GL
struct nx_material_uniform {
	float diffuse[4];
	float ambient[4];
	float specular[4];
	float emissive[4];
	float shininess;
	int tex_count;
};

// NYI
struct nx_asset_skybox {
	struct nx_asset *files;
};

struct nx_asset_mesh {
	float *buffer;
	// either ushort or uint, check data_type
	void *faces;
	uint32_t n_verts, n_uvs, n_normals, n_faces;
	struct nx_asset *texture;
	
	GLuint vao, vbo, ebo, mat_buffer;
	//uint32_t vao_offset;
	GLenum data_type;
	struct nx_material_uniform material;
};

struct nx_asset_model {
	struct nx_asset_mesh *mesh;
	uint32_t n_meshes;
};

struct nx_asset_gpu_mesh {
	GLuint vao, vbo, ebo, matb;
	uint32_t n_faces;
	GLenum data_type;
	// we assume there's no UVs if there's no texture. or so we should.
	struct nx_asset *texture;
};

struct nx_asset_gpu_model {
	struct nx_asset_gpu_mesh *mesh;
	uint32_t n_meshes;
};

#endif // ASSET_USE_GL
/*
struct nx_asset_img {
	uint32_t w, h;
	unsigned char *data;
	uint8_t colorspace;
	uint32_t texture_id;
	// byte position
	uint64_t position;
};
*/

struct nx_asset_texture {
	// not even sure why we need w/h anymore tbh.
	uint32_t w, h;
	uint32_t texture_id;
};

struct nx_asset {
	char *file;
	void *data;
	uint64_t length;
	sig_atomic_t type;
	uint8_t status, priority;
	pthread_mutex_t mtx;
};

struct nx_asset *nx_new_asset(const char *filename, const uint32_t type, const uint8_t priority);
// pthread friendly asset loading
void *nx_load_asset(void *input);
// NYI
//void nx_delete_asset(struct nx_asset *asset);

int nx_init_asset_handler(const char *argv0);
// NYI
void nx_free_asset_handler();

struct nx_asset *get_pending_asset(const uint8_t restrict_priority);
struct nx_asset *enumerate_assets(const uint32_t restrict_type);
uint32_t nx_asset_count_pending(const uint8_t restrict_priority);

// Translates a relative path to work from anywhere on the system. nx_init_asset_handler() must have returned successfully before this works.
// The output of this function must be free()'d.
char *nx_asset_translate_path(const char *relative_path);
// Returns the contents of @path or NULL on error. If a value is passed to output_length, the length is returned on success.
char *nx_asset_read_text(const char *path, uint64_t *output_length);

void nx_asset_wait_change(struct nx_asset *asset);

#ifdef __cplusplus
}
#endif

#endif /* __NX_ASSET_H */
