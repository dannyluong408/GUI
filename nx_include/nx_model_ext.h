#ifndef __NX_MODEL_EXT_H
#define __NX_MODEL_EXT_H
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <nx_error.h>

/*
	nx_model_ext: 
	Extended model format for animation with additional render options such as outputting particles at certain points.
*/

struct nx_model_ext_ref {
	char *name;
	struct vec3f pos;
};

struct nx_model_ext {
	char *model_file;
	struct nx_model_ext_ref *ref_points;
	uint32_t n_ref_points;
};


#endif // __NX_MODEL_EXT_H