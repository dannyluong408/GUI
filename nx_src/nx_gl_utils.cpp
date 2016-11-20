#include <nx_gl_utils.h>

#include <QImage>

#ifdef __cplusplus
extern "C" {
#endif

static GLuint create_shader(char *source, const GLenum type, const char free_data) {
	if (!source) {
		nx_log_msg("create_shader: Invalid (empty) source provided.",2);
	}
	GLint shader_id = glCreateShader(type);
	if (!shader_id) {
		nx_log_msg("create_shader: Failed to create GL shader.",2);
		return 0;
	}
	// heh
	glShaderSource(shader_id, 1, (const GLchar**)&source, NULL);
	glCompileShader(shader_id);
	
	GLint status;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
	if (free_data) free(source);
	if (status != GL_TRUE) {
		char error_buffer[2000];
		glGetShaderInfoLog(shader_id, sizeof(error_buffer)-1, NULL, error_buffer);
		error_buffer[sizeof(error_buffer)-1] = 0;
		nx_log_msg("create_shader: Shader %s failed to compile. Error log:\n%s",2,error_buffer);
		return 0;
	}
	return shader_id;
}
// not currently used
/*
static GLuint read_create_shader(const char *path, const GLenum type) {
	char *true_path = nx_asset_translate_path(path);
	//char *source = read_shader(true_path);
	char *source = nx_asset_read_text(true_path, NULL);
	free(true_path);
	if (!source) {
		nx_log_msg("read_create_shader: Failed to read file %s.",2,path);
		return 0;
	}
	// We want to free the source when we're done with it.
	return create_shader(source, type, 1);
}
*/
// not currently used
/*
GLuint nx_gen_program(const char *geometry_path, const char *vertex_path, const char *fragment_path) {
	GLuint geometry_shader = 0, vertex_shader = 0, fragment_shader = 0;
	if (geometry_path) {
		geometry_shader = read_create_shader(geometry_path, GL_GEOMETRY_SHADER);
		if (!geometry_shader) return 0;
	}
	vertex_shader = read_create_shader(vertex_path, GL_VERTEX_SHADER);
	if (!vertex_shader) {
		if (geometry_shader) glDeleteShader(geometry_shader);
		nx_log_msg("Failed to compile vertex shader %s.",1,vertex_path);
		return 0;
	}
	fragment_shader = read_create_shader(fragment_path, GL_FRAGMENT_SHADER);
	if (!fragment_shader) {
		if (geometry_shader) glDeleteShader(geometry_shader);
		glDeleteShader(vertex_shader);
		nx_log_msg("Failed to compile fragment shader %s.",1,fragment_path);
		return 0;
	}
	GLuint program = glCreateProgram();
	if (geometry_shader) glAttachShader(program, geometry_shader);
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	
	if (geometry_shader) glDeleteShader(geometry_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		char error_buffer[10000];
		glGetProgramInfoLog(program, sizeof(error_buffer)-1, NULL, error_buffer);
		nx_log_msg("Shader program failed to link.",1);
		nx_log_msg("Output log: %s",2,error_buffer);
		glDeleteProgram(program);
		return 0;
	}
	if (geometry_path) nx_log_msg("Successfully built program (%s / %s / %s).",8,geometry_path,vertex_path,fragment_path);
	else nx_log_msg("Successfully built program (%s / %s).",8,vertex_path,fragment_path);
	return program;
}
*/
GLuint nx_gen_program_from_memory(char *geometry_src, char *vertex_src, char *fragment_src, const char *id_str) {
	GLuint geometry_shader = 0, vertex_shader = 0, fragment_shader = 0;
	if (geometry_src) {
		geometry_shader = create_shader(geometry_src, GL_GEOMETRY_SHADER, 0);
		if (!geometry_shader) {
			nx_log_msg("Failed to compile geometry shader for shader %s.",1,id_str);
			return 0;
		}
	}
	vertex_shader = create_shader(vertex_src, GL_VERTEX_SHADER, 0);
	if (!vertex_shader) {
		if (geometry_shader) glDeleteShader(geometry_shader);
		nx_log_msg("Failed to compile vertex shader for shader %s.",1,id_str);
		return 0;
	}
	fragment_shader = create_shader(fragment_src, GL_FRAGMENT_SHADER, 0);
	if (!fragment_shader) {
		if (geometry_shader) glDeleteShader(geometry_shader);
		glDeleteShader(vertex_shader);
		nx_log_msg("Failed to compile fragment shader for shader %s.",1,id_str);
		return 0;
	}
	GLuint program = glCreateProgram();
	if (geometry_shader) glAttachShader(program, geometry_shader);
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	
	if (geometry_shader) glDeleteShader(geometry_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		char error_buffer[10000];
		glGetProgramInfoLog(program, sizeof(error_buffer)-1, NULL, error_buffer);
		nx_log_msg("Shader program failed to link.",1);
		nx_log_msg("Output log: %s",2,error_buffer);
		glDeleteProgram(program);
		return 0;
	}
	nx_log_msg("Successfully built %s.",8,id_str);
	return program;
}



void GL_draw_model(struct nx_asset_gpu_model *model, struct nx_gl_context *context) {
	uint32_t x;
	for (x = 0; x < model->n_meshes; ++x) {
		// make sure we're really done loading.
		if (model->mesh[x].texture) {
			if (model->mesh[x].texture->type == NX_TEXTURE) {
				struct nx_asset_texture *tex = (struct nx_asset_texture*)model->mesh[x].texture->data;
				//glBindBufferBase(GL_UNIFORM_BUFFER, 0, model->mesh[x].matb);
				glBindBufferRange(GL_UNIFORM_BUFFER, 0, model->mesh[x].matb, 0, sizeof(struct nx_material_uniform));
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex->texture_id);
				glUniform1i(context->texture_uni_pos, 0);
				
				glBindVertexArray(model->mesh[x].vao);
				glDrawElements(GL_TRIANGLES, model->mesh[x].n_faces * 3, model->mesh[x].data_type, (void*)0);
			}
		} else {
			glBindBufferRange(GL_UNIFORM_BUFFER, 0, model->mesh[x].matb, 0, sizeof(struct nx_material_uniform));
			
			glBindVertexArray(model->mesh[x].vao);
			glDrawElements(GL_TRIANGLES, model->mesh[x].n_faces * 3, model->mesh[x].data_type, (void*)0);
		}
	}
}

void GL_upload_asset(struct nx_asset **input_asset, struct nx_gl_context *context) {
	if (!*input_asset) {
		*input_asset = enumerate_assets(NX_IMG | NX_MODEL | NX_SKYBOX);
		if (!*input_asset) return;
	}
	struct nx_asset *asset = *input_asset;
	// assume pcie x4 @ 4.0GB/s
	// ~60mb allowable per frame @ 60 fps. adjust accordingly.
	// may want to update with time target. we can always run this again if we have free time.
	// using up to 20mb per update to be conservative. not that any textures will exceed that.
	const uint32_t block_size = 20 * 1024 * 1024;
	
	pthread_mutex_lock(&asset->mtx);
	// Need to double-check after we lock since enumerate_assets doesn't do this for us.
	if (!((*input_asset)->status == NX_ASSET_LOADED && ((*input_asset)->type == NX_IMG || (*input_asset)->type == NX_MODEL))) {
		*input_asset = NULL;
		pthread_mutex_unlock(&asset->mtx);
		return;
	}
	if (asset->type == NX_IMG) {
	/*
		struct nx_asset_img *img = (struct nx_asset_img*)asset->data;
		const GLint format = (img->colorspace == NX_RGB) ? GL_RGB : GL_RGBA;
		const uint32_t image_size = img->w * img->h * img->colorspace;
		if (!img->texture_id) {
			glGenTextures(1, &img->texture_id);
			glBindTexture(GL_TEXTURE_2D, img->texture_id);
			// internalFormat may cause problems with our shaders.
			// we'll run into problems if we have any GL_PIXEL_UNPACK_BUFFER buffers bound.
			if (image_size < block_size) {
				glTexImage2D(GL_TEXTURE_2D, 0, format, img->w, img->h, 0, format, GL_UNSIGNED_BYTE, (void*)img->data);
				img->position = image_size;
			} else {
				glTexImage2D(GL_TEXTURE_2D, 0, format, img->w, img->h, 0, format, GL_UNSIGNED_BYTE, NULL);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		if (img->position < image_size) {
			// bytes remaining
			const uint32_t rem = (image_size - img->position < block_size) ? image_size - img->position : block_size;
			uint32_t n_rows = 0;
			// figure out how many rows we're uploading
			while (img->position + (n_rows * img->w * img->colorspace) < rem) {
				n_rows++;
			}
			const uint32_t at_h = img->position / img->colorspace / img->w;
			const uint64_t n_bytes = (n_rows * img->w * img->colorspace);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, at_h, img->w, n_rows, format, GL_UNSIGNED_BYTE, (void*)&img->data[img->position]);
			img->position += n_bytes;
		} 
		if (img->position == image_size) {
			glGenerateMipmap(GL_TEXTURE_2D);
			struct nx_asset_texture *new_tex = malloc(sizeof(struct nx_asset_texture));
			new_tex->w = img->w;
			new_tex->h = img->h;
			new_tex->texture_id = img->texture_id;
			
			free(img->data);
			free(asset->data);
			asset->data = (void*)new_tex;
			asset->length = sizeof(struct nx_asset_texture);
			asset->type = NX_TEXTURE;
			nx_log_msg("Uploaded texture %s to GPU.",10,asset->file);
		} else {
			// We aren't done here, come back another time to finish.
			pthread_mutex_unlock(&asset->mtx);
			return; 
		}
		*/
		QImage *ptr = (QImage)asset->data;
		// TODO: scale this image according to our texture quality rules here!!
		
		struct nx_asset_texture tex;
		tex.w = ptr->width();
		tex.h = ptr->height(); 
		// we already converted from previous format to one of these.
		const GLint format = (ptr->format() == QImage::Format_RGB32) ? GL_RGB : GL_RGBA;
		glGenTextures(1, &tex.texture_id);
		glBindTexture(GL_TEXTURE_2D, tex.texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, tex.w, tex.h, 0, format, GL_UNSIGNED_BYTE, (void*)ptr->constBits());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		struct nx_asset_texture *new_tex = malloc(sizeof(struct nx_asset_texture));
		memcpy(new_tex, &tex, sizeof(tex));
		delete(ptr);
		asset->data = (void*)new_tex;
		nx_log_msg("Uploaded texture %s to GPU.",10,asset->file);
	} else if (asset->type == NX_MODEL) {
		struct nx_asset_model *model = (struct nx_asset_model*)asset->data;
		uint32_t x;
		for (x = 0; x < model->n_meshes; ++x) {
			glGenVertexArrays(1, &model->mesh[x].vao);
			glBindVertexArray(model->mesh[x].vao);
			glGenBuffers(1, &model->mesh[x].ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->mesh[x].ebo);
			const uint8_t size = (model->mesh[x].data_type == GL_UNSIGNED_SHORT) ? sizeof(unsigned short) : sizeof(unsigned int);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * model->mesh[x].n_faces * 3, model->mesh[x].faces, GL_STATIC_DRAW);
			
			glGenBuffers(1, &model->mesh[x].vbo);
			glBindBuffer(GL_ARRAY_BUFFER, model->mesh[x].vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (model->mesh[x].n_verts * 3 + model->mesh[x].n_uvs * 2 + model->mesh[x].n_normals * 3), model->mesh[x].buffer, GL_STATIC_DRAW);
			
			// these are buffered in order of verts, normals, uvs.
			// our importer settings generate normals if they're not present. UVs are technically optional.
			glEnableVertexAttribArray(context->vertex_pos);
			glVertexAttribPointer(context->vertex_pos, 3, GL_FLOAT, 0, 0, (void*)0);
			
			glEnableVertexAttribArray(context->normal_pos);
			glVertexAttribPointer(context->normal_pos, 3, GL_FLOAT, 0, 0, (void*)(sizeof(float) * model->mesh[x].n_verts * 3));
			
			if (model->mesh[x].n_uvs) {
				glEnableVertexAttribArray(context->uv_pos);
				glVertexAttribPointer(context->uv_pos, 2, GL_FLOAT, 0, 0, (void*)(sizeof(float) * (model->mesh[x].n_verts * 3 + model->mesh[x].n_normals * 3)));
			} else {
				glDisableVertexAttribArray(context->uv_pos);
			}
			
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER,0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
			
			glGenBuffers(1, &model->mesh[x].mat_buffer);
			glBindBuffer(GL_UNIFORM_BUFFER, model->mesh[x].mat_buffer);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(struct nx_material_uniform), &model->mesh[x].material, GL_STATIC_DRAW);
		} 
		struct nx_asset_gpu_model *new_model = malloc(sizeof(struct nx_asset_gpu_model));
		new_model->n_meshes = model->n_meshes;
		new_model->mesh = malloc(sizeof(struct nx_asset_gpu_mesh) * model->n_meshes);
		for (x = 0; x < model->n_meshes; ++x) {
			new_model->mesh[x].vao = model->mesh[x].vao;
			new_model->mesh[x].ebo = model->mesh[x].ebo;
			new_model->mesh[x].vbo = model->mesh[x].vbo;
			new_model->mesh[x].matb = model->mesh[x].mat_buffer;
			new_model->mesh[x].n_faces = model->mesh[x].n_faces;
			new_model->mesh[x].data_type = model->mesh[x].data_type;
			new_model->mesh[x].texture = model->mesh[x].texture;
			free(model->mesh[x].faces);
			free(model->mesh[x].buffer);
		}
		free(model->mesh);
		free(asset->data);
		asset->type = NX_GPU_MODEL;
		asset->length = sizeof(struct nx_asset_gpu_model);
		asset->data = (void*)new_model;
		nx_log_msg("Uploaded model %s to GPU.",10,asset->file);
	} else if (asset->type == NX_SKYBOX) {
		// ?
	}
	pthread_mutex_unlock(&asset->mtx);
	*input_asset = enumerate_assets(NX_IMG | NX_MODEL);
}

int nx_check_viewport() {

	return 1;
}
/*
// Approximate a view frustum as a circle and determine if the object lies within it.
int nx_check_viewport_fast(const struct nx_circle object, const struct nx_circle viewport) {
	const float x = viewport.x - object.x;
	const float y = viewport.y - object.y;
	const float r = viewport.r + object.r;
	return x * x + y * y <= r * r;
}*/

#ifdef __cplusplus
} // extern "C"
#endif