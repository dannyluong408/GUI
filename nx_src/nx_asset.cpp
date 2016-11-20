#include <nx_include/nx_asset.h>
//#include <png.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct NX_ASSET_INTERNAL_CONTAINER {
	uint32_t n_assets, n_pending;
	pthread_mutex_t mtx;

	// path_buffer may only be written/read during mutex lock
	// pwd may be read at any time, but not written.
	char *pwd, *path_buffer;
	// pwd_len and path_buffer_len are measured in bytes.
	uint64_t pwd_len, path_buffer_len;
	struct nx_asset **assets;
	struct nx_asset **pending_load;
	void *pending_ptr;
	
	// Treat zero as unset.
	uint32_t max_png_dimensions;
};
static struct NX_ASSET_INTERNAL_CONTAINER NX_ASSET_INTERNAL;

int nx_init_asset_handler(const char *argv0) {
	NX_ASSET_INTERNAL.pwd = NULL;
	NX_ASSET_INTERNAL.path_buffer = NULL;
	NX_ASSET_INTERNAL.assets = NULL;
	NX_ASSET_INTERNAL.pending_ptr = NULL;
	NX_ASSET_INTERNAL.pending_load = NULL;

	NX_ASSET_INTERNAL.pwd = 0;
	NX_ASSET_INTERNAL.path_buffer_len = 0;
	
	NX_ASSET_INTERNAL.n_assets = 0;
	NX_ASSET_INTERNAL.n_pending = 0;
	
	NX_ASSET_INTERNAL.mtx = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	
	NX_ASSET_INTERNAL.assets = NULL;
	NX_ASSET_INTERNAL.pending_load = NULL;
	NX_ASSET_INTERNAL.pending_ptr = NULL;
	
	NX_ASSET_INTERNAL.max_png_dimensions = 0;

	if (!argv0) return -1;
	
	uint32_t slash_count = 0;
	uint32_t x, last_slash = 0;
	uint32_t arg_len = strlen(argv0);
	if (!arg_len) return -1;
	for (x = 0; x < arg_len; ++x) {
		if (argv0[x] == '\\' || argv0[x] == '/') {
			slash_count++;
			last_slash = x;
		}
	}
	
#ifdef __WIN32
	// On mingw, we get the full path from argv[0]. 
	if (!slash_count) {
		return -1; // can't determine this guy.
	}
	
	NX_ASSET_INTERNAL.pwd = (char*)malloc(last_slash+2); // need space for null-terminator.
	if (!NX_ASSET_INTERNAL.pwd) {
		return -1;
	}
	memcpy(NX_ASSET_INTERNAL.pwd, argv0, last_slash+1);
	NX_ASSET_INTERNAL.pwd[last_slash+1] = 0;
	// Our len is in bytes, not strlen.
	NX_ASSET_INTERNAL.pwd_len = strlen(NX_ASSET_INTERNAL.pwd) + 1;
#elif defined(_POSIX_VERSION)
	// this code is untested
	//#warning "untested code here m8"
	uint64_t current_len = 1000;
	char *ptr = NULL; 
	char *check = NULL;
	while (!check) {
		free(ptr);
		ptr = (char*)malloc(current_len);
		if (!ptr) {
			return -1;
		}
		check = getcwd(ptr, current_len);
		current_len += 500;
	}
	if (slash_count > 1) {
		argv0[last_slash+1] = 0;
		// need to ignore ./ but not ../
		if (strncmp(argv0, "./", 2) == 0) {
			argv0 = &argv0[2]; // please work properly.
		}
		arg_len -= 2;
	} else {
		arg_len = 0;
		argv0 = NULL;
	}
	const int pwd_len = strlen(ptr);
	NX_ASSET_INTERNAL.pwd = (char*)malloc(arg_len + pwd_len + 3);
	if (!NX_ASSET_INTERNAL.pwd) {
		free(ptr);
		return -2;
	}
	memcpy(NX_ASSET_INTERNAL.pwd, ptr, pwd_len);
	NX_ASSET_INTERNAL.pwd[pwd_len] = '/';
	memcpy(&NX_ASSET_INTERNAL.pwd[pwd_len+1], argv0, arg_len);
	NX_ASSET_INTERNAL.pwd[pwd_len + arg_len + 1] = '/';
	NX_ASSET_INTERNAL.pwd[pwd_len + arg_len + 2] = 0;

	NX_ASSET_INTERNAL.pwd_len = pwd_len + arg_len + 3;
	free(ptr);
#else
#error "No valid PWD code"
#endif

	// Our default max path locally is going to be 2048 characters, regardless of system.
	// This will adjust to compensate for extremely long paths.
	// please dont use extremely long paths. it'll cause a warning if you do.
	NX_ASSET_INTERNAL.path_buffer = (char*)malloc(NX_ASSET_INTERNAL.pwd_len + 2048);
	if (!NX_ASSET_INTERNAL.path_buffer) {
		free(NX_ASSET_INTERNAL.pwd);
		NX_ASSET_INTERNAL.pwd = NULL;
		return -3;
	}
	NX_ASSET_INTERNAL.path_buffer_len = NX_ASSET_INTERNAL.pwd_len + 2048;
	return 0;
}

char *nx_asset_translate_path(const char *relative_path) {
	const uint32_t len = strlen(relative_path);
	char *out = (char*)malloc(len + NX_ASSET_INTERNAL.pwd_len);
	if (!out) return NULL;
	memcpy((void*)out, (void*)NX_ASSET_INTERNAL.pwd, NX_ASSET_INTERNAL.pwd_len);
	memcpy((void*)&out[NX_ASSET_INTERNAL.pwd_len-1], (void*)relative_path, len+1);
	return out;
}
// unused?
void nx_asset_set_png_maxd(const uint32_t maxd) {
	pthread_mutex_lock(&NX_ASSET_INTERNAL.mtx);
	NX_ASSET_INTERNAL.max_png_dimensions = maxd;
	pthread_mutex_unlock(&NX_ASSET_INTERNAL.mtx);
}

struct nx_asset *get_pending_asset(const uint8_t restrict_priority) {
	struct nx_asset *out = NULL;
	pthread_mutex_lock(&NX_ASSET_INTERNAL.mtx);
	if (NX_ASSET_INTERNAL.n_pending) {
		if (NX_ASSET_INTERNAL.pending_load[0]->priority <= restrict_priority) {
			out = NX_ASSET_INTERNAL.pending_load[0];
			if (NX_ASSET_INTERNAL.n_pending > 1) {
				NX_ASSET_INTERNAL.pending_load = &NX_ASSET_INTERNAL.pending_load[1];
			} else {
				NX_ASSET_INTERNAL.pending_load = NULL;
			}
			NX_ASSET_INTERNAL.n_pending--;
		} 
	} 
	pthread_mutex_unlock(&NX_ASSET_INTERNAL.mtx);
	return out;
}

struct nx_asset *nx_new_asset(const char *filename, const uint32_t type, const uint8_t priority) {
	assert(type);
	assert(filename);
	if (!filename) return NULL;
	const size_t len = strlen(filename);
	assert(len); // this isn't necessarily required. it's just good to know about.
	if (!len) return NULL;
	
	if (len > 2048) {
		nx_log_msg("nx_new_asset: File \"%s\" path is extremely long and may cause problems.",3,filename);
	}
	pthread_mutex_lock(&NX_ASSET_INTERNAL.mtx);
	
	char *absolute_path = NX_ASSET_INTERNAL.path_buffer;
	// The null terminator is already counted in pwd_len.
	if (len + NX_ASSET_INTERNAL.pwd_len > NX_ASSET_INTERNAL.path_buffer_len) {
		char *ptr = (char*)malloc(len + NX_ASSET_INTERNAL.pwd_len);
		if (ptr) {
			free(NX_ASSET_INTERNAL.path_buffer);
			NX_ASSET_INTERNAL.path_buffer = ptr;
			NX_ASSET_INTERNAL.path_buffer_len = len + NX_ASSET_INTERNAL.pwd_len;
		} else {
			nx_log_msg("nx_new_asset: Failed to allocate %u bytes for new path buffer.",2,len + NX_ASSET_INTERNAL.pwd_len);
			return NULL;
		}
	}
	snprintf(absolute_path, NX_ASSET_INTERNAL.path_buffer_len, "%s%s", NX_ASSET_INTERNAL.pwd, filename);
	uint32_t x;
	// search for duplicates
	uint32_t compare = 0;
	// We don't want to search for NX_IMG_PERSIST duplicates because they're used in very specific ways.
	if (type == NX_IMG) compare = NX_IMG | NX_TEXTURE;
	else if (type == NX_MODEL) compare = NX_MODEL | NX_GPU_MODEL;
	if (compare) {
		for (x = 0; x < NX_ASSET_INTERNAL.n_assets; ++x) {
			// filenames can't be changed and aren't added to the journal before they're allocated.
			// we shouldn't have to lock anything here.
			if (strcmp(NX_ASSET_INTERNAL.assets[x]->file, absolute_path) == 0) {
				// check for compatible type
				if (NX_ASSET_INTERNAL.assets[x]->type & compare) {
					pthread_mutex_unlock(&NX_ASSET_INTERNAL.mtx);
					return NX_ASSET_INTERNAL.assets[x];
				}
			}
		}
	}
	
	struct nx_asset *asset = (struct nx_asset*)malloc(sizeof(struct nx_asset));
	if (!asset) {
		pthread_mutex_unlock(&NX_ASSET_INTERNAL.mtx);
		return NULL;
	}
	const uint32_t absolute_len = strlen(absolute_path);
	char *ptr = (char*)malloc(absolute_len+1);
	if (!ptr) {
		pthread_mutex_unlock(&NX_ASSET_INTERNAL.mtx);
		free(asset);
		return NULL;
	}
	memcpy((void*)ptr, (void*)absolute_path, absolute_len+1);
	asset->data = NULL;
	asset->length = 0;
	asset->type = type;
	asset->status = NX_ASSET_INITIALIZED;
	asset->file = ptr;
	asset->priority = priority;
	asset->mtx = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

	struct nx_asset **new_asset_list = (struct nx_asset **)malloc(sizeof(struct nx_asset*) * (NX_ASSET_INTERNAL.n_assets + 1));
	struct nx_asset **new_pending_list = (struct nx_asset **)malloc(sizeof(struct nx_asset*) * (NX_ASSET_INTERNAL.n_pending + 1));
	memcpy(new_asset_list, NX_ASSET_INTERNAL.assets, sizeof(struct nx_asset*) * NX_ASSET_INTERNAL.n_assets);
	new_asset_list[NX_ASSET_INTERNAL.n_assets] = asset;
	free(NX_ASSET_INTERNAL.assets);
	NX_ASSET_INTERNAL.assets = new_asset_list;
	NX_ASSET_INTERNAL.n_assets++;
	
	
	uint32_t at = NX_ASSET_INTERNAL.n_pending;
	for (x = 0; x < NX_ASSET_INTERNAL.n_pending; ++x) {
		if (asset->priority <= NX_ASSET_INTERNAL.pending_load[x]->priority) {
			at = x;
			x = NX_ASSET_INTERNAL.n_pending;
		}
	}
	memcpy((void*)new_pending_list, (void*)NX_ASSET_INTERNAL.pending_load, sizeof(struct nx_asset*) * at);
	memcpy((void*)&new_pending_list[at+1], (void*)&NX_ASSET_INTERNAL.pending_load[at], sizeof(struct nx_asset*) * (NX_ASSET_INTERNAL.n_pending - at));
	new_pending_list[at] = asset;
	free(NX_ASSET_INTERNAL.pending_ptr);
	NX_ASSET_INTERNAL.pending_load = new_pending_list;
	NX_ASSET_INTERNAL.pending_ptr = (void*)new_pending_list;
	NX_ASSET_INTERNAL.n_pending++;
	pthread_mutex_unlock(&NX_ASSET_INTERNAL.mtx);
	
	return asset;
}

#ifdef ASSET_USE_GL
static void set_4f(float *ptr, float a, float b, float c, float d) {
	ptr[0] = a;
	ptr[1] = b;
	ptr[2] = c;
	ptr[3] = d;
}

static void color4_4f(aiColor4D *input, float *ptr) {
	ptr[0] = input->r;
	ptr[1] = input->g;
	ptr[2] = input->b;
	ptr[3] = input->a;
}

static int nx_load_model(struct nx_asset_model *output, struct nx_asset *asset, const char *file) {	
	assert(asset);
	assert(output);
	assert(file);
	struct aiScene *scene =  (struct aiScene*)aiImportFile(file, aiProcessPreset_TargetRealtime_Quality | aiProcess_FlipUVs | aiProcess_Triangulate);
	if (!scene) {
		nx_log_msg("nx_load_model: Failed to import file %s. Error: %s.",2,file,aiGetErrorString());
		return -1;
	}
	if (!scene->mNumMeshes) {
		nx_log_msg("nx_load_model: File %s has no valid meshes.",2,file);
		aiReleaseImport(scene);
		return -1;
	}
	struct nx_asset_mesh *mesh_list = (struct nx_asset_mesh*)malloc(sizeof(struct nx_asset_mesh) * scene->mNumMeshes);
	if (!mesh_list) {
		nx_log_msg("nx_load_model: Failed to allocate memory for %s mesh list.",2,file);
		aiReleaseImport(scene);
		return -1;
	}
	if (scene->mNumAnimations) {
		nx_log_msg("Model %s has %u animations.",2,file,scene->mNumAnimations);
	}
	
	uint32_t x, y;
	for (x = 0; x < scene->mNumMeshes; ++x) {
		float *verts = NULL;
		float *uvs = NULL;
		float *normals = NULL;
		mesh_list[x].faces = NULL;
		mesh_list[x].buffer = NULL;
		mesh_list[x].texture = NULL;
		mesh_list[x].vao = 0;
		mesh_list[x].vbo = 0;
		mesh_list[x].ebo = 0;
		mesh_list[x].mat_buffer = 0;
		mesh_list[x].n_verts = 0;
		mesh_list[x].n_uvs = 0;
		mesh_list[x].n_normals = 0;
		// dont know what to do with material tbh
		// prob doesnt matter
		
		const struct aiMesh *mesh = scene->mMeshes[x];
		if (mesh->mNumVertices) {
			verts = (float*)malloc(sizeof(float) * mesh->mNumVertices * 3);
			mesh_list[x].n_verts = mesh->mNumVertices;
			if (!verts) {
				nx_log_msg("nx_load_model: Failed to allocate memory for %s mesh vertices.",2,file);
				aiReleaseImport(scene);
				goto destroy_error;
			}
			memcpy(verts, mesh->mVertices, sizeof(float) * 3 * mesh->mNumVertices);
		} else {
			nx_log_msg("nx_load_model: Model %s has no vertices in mesh %u.",2,file,x);
			aiReleaseImport(scene);
			goto destroy_error;
		}
		// "The array contains normalized vectors, NULL if not present. The array is mNumVertices in size."
		// it shouldn't be possible for this to have no normals. these are auto-generated if not present.
		assert(mesh->mNormals);
		normals = (float*)malloc(sizeof(float) * mesh->mNumVertices * 3);
		mesh_list[x].n_normals = mesh->mNumVertices;
		if (!normals) {
			nx_log_msg("nx_load_model: Failed to allocate memory for %s mesh normals.",2,file);
			aiReleaseImport(scene);
			free(verts);
			goto destroy_error;
		}
		memcpy((void*)normals, (void*)mesh->mNormals, sizeof(float) * 3 * mesh->mNumVertices);
		
		// "A mesh may contain 0 to AI_MAX_NUMBER_OF_TEXTURECOORDS per vertex. NULL if not present. The array is mNumVertices in size."
		if (mesh->mTextureCoords) {
			uvs = (float*)malloc(sizeof(float) * mesh->mNumVertices * 2);
			mesh_list[x].n_uvs = mesh->mNumVertices;
			if (!uvs) {
				nx_log_msg("nx_load_model: Failed to allocate %u bytes for %s mesh uvs.",2,sizeof(float) * mesh->mNumVertices * 2, file);
				aiReleaseImport(scene);
				free(verts);
				free(normals);
				goto destroy_error;
			}
			const uint32_t d = mesh->mNumVertices;
			for (y = 0; y < d; ++y) {
				uvs[y*2] = mesh->mTextureCoords[0][y].x;
				uvs[y*2+1] = mesh->mTextureCoords[0][y].y;
			}
		} else {
			mesh_list[x].n_uvs = 0;
		}
		uint8_t size;
		if (mesh_list[x].n_verts >= UINT16_MAX) {
			mesh_list[x].data_type = GL_UNSIGNED_INT;
			size = sizeof(unsigned int);
		} else {
			mesh_list[x].data_type = GL_UNSIGNED_SHORT;
			size = sizeof(unsigned short);
		}
		
		if (mesh->mNumBones) {
			nx_log_msg("File %s has %u bones.",2,file,mesh->mNumBones);
		}
		
		mesh_list[x].n_faces = mesh->mNumFaces;
		mesh_list[x].faces = (void*)malloc(size * mesh->mNumFaces * 3);
		if (!mesh_list[x].faces) {
			nx_log_msg("nx_load_model: Failed to allocate memory for %s mesh indices.",2,file);
			aiReleaseImport(scene);
			free(verts);
			free(uvs);
			free(normals);
			goto destroy_error;
		}
		if (size == sizeof(unsigned int)) {
			unsigned int *ptr = (unsigned int*)mesh_list[x].faces;
			for (y = 0; y < mesh->mNumFaces; ++y) {
				const struct aiFace *face = &mesh->mFaces[y];
				ptr[y*3] = face->mIndices[0];
				ptr[y*3+1] = face->mIndices[1];
				ptr[y*3+2] = face->mIndices[2];
			}
		} else {
			unsigned short *ptr = (unsigned short*)mesh_list[x].faces;
			for (y = 0; y < mesh->mNumFaces; ++y) {
				const struct aiFace *face = &mesh->mFaces[y];
				ptr[y*3] = face->mIndices[0];
				ptr[y*3+1] = face->mIndices[1];
				ptr[y*3+2] = face->mIndices[2];
			}
		}
		const uint32_t len = sizeof(float)*(mesh_list[x].n_verts * 3 + mesh_list[x].n_uvs * 2 + mesh_list[x].n_normals * 3);
		mesh_list[x].buffer = (float*)malloc(len);
		if (!mesh_list[x].buffer) {
			nx_log_msg("nx_load_model: Failed to allocate %u bytes for %s VAO buffer.",2,len,file);
			aiReleaseImport(scene);
			free(verts);
			free(uvs);
			free(normals);
			free(mesh_list[x].faces);
			goto destroy_error;
		}
		// what a pain in the ass
		memcpy((void*)mesh_list[x].buffer, (void*)verts, sizeof(float) * mesh_list[x].n_verts * 3);
		memcpy((void*)&mesh_list[x].buffer[mesh_list[x].n_verts*3], (void*)normals, sizeof(float) * mesh_list[x].n_normals * 3);
		memcpy((void*)&mesh_list[x].buffer[mesh_list[x].n_verts*3 + mesh_list[x].n_normals*3], (void*)uvs, sizeof(float) * mesh_list[x].n_uvs * 2);
		// done with these
		free(verts);
		free(normals);
		free(uvs);
		
		struct aiMaterial *mtl = scene->mMaterials[mesh->mMaterialIndex];
		struct aiString texture_path;
		struct nx_material_uniform material;
		material.tex_count = 0;
		mesh_list[x].texture = NULL;
		// If the mesh doesn't have UVs, ignore any texture we might find anyway.
		if (mesh_list[x].n_uvs) {
			if (aiGetMaterialTexture(mtl, aiTextureType_DIFFUSE, 0, &texture_path, 0,0,0,0,0,0) == AI_SUCCESS) {
				// "." as far as I can tell refers to just a blank texture.
				if (strcmp(texture_path.data, ".") != 0) {
					char *texture_true_path = texture_path.data;
					// Check if the texture path points to a simple filename (abc.png) or a relative path from the game directory.
					const uint32_t texture_path_len = strlen(texture_path.data);
					uint8_t texture_path_is_model_relative = 1;
					for (y = 0; y < texture_path_len; ++y) {
						if (texture_path.data[y] == '/' || texture_path.data[y] == '\\') {
							texture_path_is_model_relative = 0;
							y = texture_path_len;
						}
					}
					if (texture_path_is_model_relative) {
						const uint32_t file_strlen = strlen(file);
						y = 0; 
						while (file[y] == NX_ASSET_INTERNAL.pwd[y]) {
							y++;
						}
						const uint32_t end = y;
						uint32_t last_slash = 0;
						//y = 0;
						while (y < file_strlen) {
							if (file[y] == '/' || file[y] == '\\') last_slash = y+1;
							y++;
						}
						// This shouldn't be possible. The asset loader automatically generates absolute paths for these files.
						if (last_slash < end) {
							nx_log_msg("nx_load_model: Couldn't generate a proper path for material %s in file %s.",2,texture_path.data,file);
							aiReleaseImport(scene);
							goto destroy_error;
						}
						// add null terminator and slash
						texture_true_path = (char*)malloc(last_slash - end + texture_path_len + 2);
						if (!texture_true_path) {
							nx_log_msg("nx_load_model: Error allocating %u bytes for texture path.",2,last_slash - end + texture_path_len + 2);
							aiReleaseImport(scene);
							goto destroy_error;
						}
						memcpy(texture_true_path, &file[end], (last_slash - end));
						memcpy(&texture_true_path[last_slash-end], texture_path.data, texture_path_len+1);
					}
					mesh_list[x].texture = nx_new_asset(texture_true_path, NX_IMG, asset->priority);
					if (!mesh_list[x].texture) {
						nx_log_msg("nx_load_model: Failed to init texture asset %s.",2,texture_path.data);
						// We don't need to throw away the model for this. need to find an error texture or something.
					} else {
						material.tex_count = 1;
						nx_log_msg("nx_load_model: Added texture %s to queue.",5,texture_true_path);
					}
					if (texture_path_is_model_relative) {
						free(texture_true_path);
					}
				} else {
					nx_log_msg("nx_load_model: File %s has UVs but no texture associated with it. This may fail to display properly.",2,file);
				}
			} else {
				nx_log_msg("nx_load_model: Failed to load material info for model %s.",2,file);
			}
		}
		float c[4];
        aiColor4D color;
		set_4f(c,0.8f,0.8f,0.8f,1.0f);
		if (aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &color) == AI_SUCCESS) {
			color4_4f(&color, c);
		}
		memcpy((void*)material.diffuse, (void*)c, sizeof(c));
		
		set_4f(c,0.0f,0.0f,0.0f,1.0f);
		if (aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &color) == AI_SUCCESS) {
			color4_4f(&color, c);
		}
		memcpy((void*)material.specular, (void*)c, sizeof(c));
		
		set_4f(c,0.0f,0.0f,0.0f,1.0f);
		if (aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &color) == AI_SUCCESS) {
			color4_4f(&color, c);
		}
		memcpy((void*)material.emissive, (void*)c, sizeof(c));
		
		float shininess = 0.0f;
		aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, NULL);
		material.shininess = shininess;
		
		mesh_list[x].material = material;
	}
	output->n_meshes = scene->mNumMeshes;
	output->mesh = mesh_list;
	aiReleaseImport(scene);
	return 0;
	
	destroy_error:
	;
	// clean up the previous meshes if one fails to load.
	const uint32_t at = x;
	for (x = 0; x < at; ++x) {
		free(mesh_list[x].faces);
		free(mesh_list[x].buffer);
	}
	free(mesh_list);
	return -1;
}
#endif // ASSET_USE_GL

char *nx_asset_read_text(const char *path, uint64_t *output_length) {
	#ifdef __WIN32
	int fd;
	_sopen_s(&fd, path, _O_RDONLY, _SH_DENYRW, _S_IREAD);
	if (fd == -1) {
		nx_log_msg("nx_asset_read_text: Failed to open text file %s. %s.",2,path,nx_log_strerror());
		nx_log_strerror_finish();
		return NULL;
	}
	#if __x86_64__
	int64_t len = _filelengthi64(fd);
	#else
	int32_t len = _filelength(fd);
	#endif
	if (len == -1) {
		_close(fd);
		nx_log_msg("nx_asset_read_text: Couldn't find %s length.",2,path,nx_log_strerror());
		nx_log_strerror_finish();
		return NULL;
	}
	if (!len) {
		nx_log_msg("nx_asset_read_text: File %s is empty.",2,path);
		_close(fd);
		return NULL;
	}
	// We'll be applying our own null-terminator to the end of this.
	char *source = (char*)malloc(len+1);
	const int read_len = read(fd, source, len);
	source[read_len] = 0;
	#ifdef DEBUG
	if (read_len != len) {
		nx_log_msg("nx_asset_read_text: File %s read len isn't the same as _filelength len. This is probably from using DOS EOL. Consider converting to UNIX EOL.",3,path);
	}
	if (_close(fd)) {
		nx_log_msg("nx_asset_read_text: Failed to _close %s. %s.",3,path,nx_log_strerror());
		nx_log_strerror_finish();
	}
	#else
	// We can't do anything about this if it's happening on a live system anyway. Basically just have to ignore it.
	_close(fd);
	#endif
	if (output_length) *output_length = read_len;
	// This is still fine though.
	return source;
	#elif defined(_POSIX_VERSION) && _POSIX_C_SOURCE >= 200112L
	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		nx_log_msg("nx_asset_read_text: Failed to open text file %s. %s.",2,path,nx_log_strerror());
		nx_log_strerror_finish();
		return NULL;
	}
	struct stat buf;
	if ((fstat(fd, &buf) != 0)) {
		nx_log_msg("nx_asset_read_text: Couldn't read %s stat information. %s.",2,path,nx_log_strerror());
		nx_log_strerror_finish();
		close(fd);
		return NULL;
	}
	if (!S_ISREG(buf.st_mode)) {
		nx_log_msg("nx_asset_read_text: File %s is not a regular file.",2,path);
		close(fd);
		return NULL;
	}
	const uint64_t len = buf.st_size;
	if (!len) {
		nx_log_msg("nx_asset_read_text: File %s is empty.",2,path);
		close(fd);
		return NULL;
	}
	char *source = (char*)malloc(len+1);
	const uint64_t read_len = read(fd, source, len);
	#ifdef DEBUG
	if (read_len != len) {
		nx_log_msg("nx_asset_read_text: File %s read len isn't the same as fstat len.",3,path);
	}
	#endif
	if (output_length) *output_length = len;
	close(fd);
	return source;
	
	#else
		#error "No valid file reading function"
	#endif
}
/*
static int nx_load_png(struct nx_asset_img *output, const char *filename, FILE *f) {
	assert(f);
	assert(filename);
	assert(output);
	uint8_t header[8] = { 0 };
	const size_t n_read = fread(header, 8, 1, f);
	if (n_read != 8 || png_sig_cmp(header, 0, 8)) {
		nx_log_msg("nx_load_png: File %s is not a valid PNG file.",2,filename);
		return 1;
	}
	png_structp png_struct_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_struct_ptr) {
		nx_log_msg("nx_load_png: Error initializing png_structp.",2);
		return 1;
	}
	png_infop png_info_ptr = png_create_info_struct(png_struct_ptr);
	if (!png_info_ptr) {
		nx_log_msg("nx_load_png: Error initializing png_infop.",2);
		png_destroy_read_struct(&png_struct_ptr, NULL, NULL);
		return 2;
	}
	if (setjmp(png_jmpbuf(png_struct_ptr))) {
		nx_log_msg("nx_load_png: setjmp error.",2);
		png_destroy_read_struct(&png_struct_ptr, &png_info_ptr, NULL);
		return 3;
	}
	png_init_io(png_struct_ptr, f);
	png_set_sig_bytes(png_struct_ptr, 8);
	png_read_info(png_struct_ptr, png_info_ptr);
	
	output->w = png_get_image_width(png_struct_ptr, png_info_ptr);
	output->h = png_get_image_height(png_struct_ptr, png_info_ptr);
	unsigned char color = png_get_color_type(png_struct_ptr, png_info_ptr);
	if (color != PNG_COLOR_TYPE_RGB && color != PNG_COLOR_TYPE_RGB_ALPHA) {
		nx_log_msg("nx_load_png: Invalid colorspace read in file %s.",2,filename);
		png_destroy_read_struct(&png_struct_ptr, &png_info_ptr, NULL);
		return 4;
	}
	unsigned char bit_depth = png_get_bit_depth(png_struct_ptr, png_info_ptr);
	const uint8_t bytes_per_pixel = (color == PNG_COLOR_TYPE_RGB) ? 3 : 4 * (bit_depth / 8);
	png_set_interlace_handling(png_struct_ptr);
	png_read_update_info(png_struct_ptr, png_info_ptr);
	
	if (setjmp(png_jmpbuf(png_struct_ptr))) {
		nx_log_msg("nx_load_png: setjmp2 error.",2);
		png_destroy_read_struct(&png_struct_ptr, &png_info_ptr, NULL);
		return 5;
	}
	unsigned char *data = malloc(output->w * output->h * bytes_per_pixel);
	unsigned char **row_ptrs = malloc(output->h * sizeof(unsigned char*));
	if (!data || !row_ptrs) {
		free(data);
		free(row_ptrs);
		png_destroy_read_struct(&png_struct_ptr, &png_info_ptr, NULL);
		nx_log_msg("nx_load_png: %s.",2,nx_log_strerror());
		nx_log_strerror_finish();
		return 6;
	}
	
	
	uint32_t x;
	for (x = 0; x < output->h; ++x) {
		row_ptrs[x] = &data[bytes_per_pixel * output->w * x];
	}
	png_read_image(png_struct_ptr, row_ptrs);
	free(row_ptrs);
	
	output->colorspace = (color == PNG_COLOR_TYPE_RGB) ? NX_RGB : NX_RGBA;
	
	// Make sure we're using 8 bit color depth. If not, convert.
	if (bit_depth == 16) {
		const int n_bytes = output->w * output->h * output->colorspace;
		unsigned char *true_data = malloc(n_bytes);
		for (x = 0; x < n_bytes; ++x) {
			true_data[x] = *((uint16_t*)(&data[2*x])) >> 8;
		}
		free(data);
		data = true_data;
	}
	output->data = data;
	
	// cleanup
	png_destroy_read_struct(&png_struct_ptr, &png_info_ptr, NULL);
	
	
	// apply post-processing effects.
	pthread_mutex_lock(&NX_ASSET_INTERNAL.mtx);
	//const uint32_t max_dimensions = NX_ASSET_INTERNAL.max_png_dimensions;
	pthread_mutex_unlock(&NX_ASSET_INTERNAL.mtx);
	
	// ..............
	
	return 0;
}
*/

void nx_load_asset(void *input) {
	assert(input);
	struct nx_asset *asset = (struct nx_asset*)input;
	pthread_mutex_lock(&asset->mtx);
	assert(asset->file);
	switch (asset->type) {
		case NX_IMG:
        case NX_IMG_PERSIST:{
                ;
                QImage img(asset->file);
                if (img.isNull()) {
                    asset->status = NX_ASSET_FAILED_INVALID_FILE;
                    pthread_mutex_unlock(&asset->mtx);
                    return;
                }
                QImage *ptr;
                if (img.hasAlphaChannel()) {
                    ptr = new QImage(img.convertToFormat(QImage::Format_ARGB32));
                } else {
                    ptr = new QImage(img.convertToFormat(QImage::Format_RGB32));
                }
                if (!ptr || ptr->isNull()) {
                    asset->status = NX_ASSET_FAILED_INVALID_FILE;
                    pthread_mutex_unlock(&asset->mtx);
                    return;
                }
                asset->data = (void*)ptr;
                asset->length = sizeof(QImage);

                /*
                if (img.isNull()) {
                    asset->status = NX_ASSET_FAILED_INVALID_FILE;
                    pthread_mutex_unlock(&asset->mtx);
                    return;
                }

                // translate to nx_asset_image
                const unsigned char *pixeldata = img.constBits();
                struct nx_asset_img image;
                image.data = malloc(img.byteCount());
                if (!image.data) {
                    asset->status = NX_ASSET_FAILED_INVALID_FILE;
                    pthread_mutex_unlock(&asset->mtx);
                    nx_log_msg("nx_load_asset: Failed to allocate memory for pixel buffer.",2);
                    return;
                }
                memcpy(image.data, pixeldata, img.byteCount());
                image.w = img.width();
                image.h = img.height();
                image.colorspace = NX_RGBA;

                image.texture_id = 0;
                image.position = 0;

                asset->data = malloc(sizeof(image));
                memcpy(asset->data, &image, sizeof(image));
                asset->length = sizeof(image); // don't count the pixel data length here.
                */


                asset->status = NX_ASSET_LOADED;
                nx_log_msg("nx_load_asset: Successfully read IMG %s.",5,asset->file);
                break;
                break;
        }
        case NX_TEXT_FILE:{
            ;
			uint64_t len = 0;
			char *text_file = nx_asset_read_text(asset->file, &len);
			if (!text_file || !len) {
				asset->status = NX_ASSET_FAILED_INVALID_FILE;
				pthread_mutex_unlock(&asset->mtx);
				return;
			}
			asset->data = (void*)text_file;
			asset->length = len;
			asset->status = NX_ASSET_LOADED;
			break;
        }
		#ifdef ASSET_USE_GL
        case NX_MODEL:{
            ;
			struct nx_asset_model model;
			if (nx_load_model(&model, asset, asset->file)) {
				asset->status = NX_ASSET_FAILED_INVALID_DATA;
				pthread_mutex_unlock(&asset->mtx);
				return;
			}
			asset->data = malloc(sizeof(model));
			memcpy(asset->data, (void*)&model, sizeof(model));
			asset->length = sizeof(model);
			asset->status = NX_ASSET_LOADED;
			nx_log_msg("nx_load_asset: Successfully read model %s.",5,asset->file);
			break;
        }
		#endif // ASSET_USE_GL
	}
	pthread_mutex_unlock(&asset->mtx);
}

void nx_asset_wait_change(struct nx_asset *asset) {
	while (asset->status == NX_ASSET_INITIALIZED) {
		nx_usleep(1000);
	}
}

// needs to be updated to modify the asset journal
/*
void nx_delete_asset(struct nx_asset *asset) {
	// Don't delete data we're not allowed to delete.
	if (asset->status != NX_ASSET_LOADED_LINKED) {
		switch (asset->type) {
			case NX_IMG:
				;
				struct nx_asset_img *ptr = (struct nx_asset_img*)asset->data;
				free(ptr->data);
				break;
			case NX_ARCHIVE:
				
				break;
			case NX_TEXT_FILE:
				// covered
				break;
			case NX_TEXTURE:
				// this is hard. Do we call from GL thread or what?
				break;
		}
		free(asset->data);
	}
	free(asset->file);
	pthread_mutex_destroy(&asset->mtx);
	asset->file = NULL;
	asset->data = NULL;
	asset->length = 0;
	asset->type = NX_NO_FORMAT;
	asset->status = NX_ASSET_INITIALIZED;
}
*/

struct nx_asset *enumerate_assets(const uint32_t restrict_type) {
	struct nx_asset *out = NULL;
	uint32_t count = 0;
	pthread_mutex_lock(&NX_ASSET_INTERNAL.mtx);
	while (count < NX_ASSET_INTERNAL.n_assets) {
		// Double check the type after this returns.
		if (NX_ASSET_INTERNAL.assets[count]->type & restrict_type && NX_ASSET_INTERNAL.assets[count]->status == NX_ASSET_LOADED) {
			out = NX_ASSET_INTERNAL.assets[count];
			count = NX_ASSET_INTERNAL.n_assets;
		} 
		count++;
	}
	pthread_mutex_unlock(&NX_ASSET_INTERNAL.mtx);
	return out;
}

uint32_t nx_asset_count_pending(const uint8_t restrict_priority) {
	uint32_t count = 0;
	pthread_mutex_lock(&NX_ASSET_INTERNAL.mtx);
	while (count < NX_ASSET_INTERNAL.n_pending && NX_ASSET_INTERNAL.pending_load[count]->priority <= restrict_priority) {
		count++;
	}
	pthread_mutex_unlock(&NX_ASSET_INTERNAL.mtx);
	return count;
}

void nx_free_asset_handler() {
	
}

#ifdef __cplusplus
}
#endif
