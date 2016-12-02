#include <nx_ftgl.h>

typedef struct NX_FTGL_INTERNAL_DATA {
	GLuint texture, vertex_buffer, shader, color_uni_location;
	FT_Library library;
	struct nx_ftgl_face *face;
	struct nx_ftgl_spatial_directory directory;
	uint32_t current_face, texture_size, buffer_size, batch_size, fallback_face;
	uint64_t relative_time;
	uint8_t error;
	float *batch;
} NX_FTGL_INTERNAL_DATA;
NX_FTGL_INTERNAL_DATA internal;

int nx_ftgl_init() {
	internal.current_face = 0;
	internal.buffer_size = 0;
	internal.error = 0;
	internal.face = NULL;
	internal.texture = 0;
	internal.vertex_buffer = 0;
	internal.relative_time = 0;
	internal.shader = 0;
	internal.batch_size = 0;
	internal.batch = NULL;
	internal.color_uni_location = 0;
	internal.fallback_face = 0;
	return FT_Init_FreeType(&internal.library);
}

struct nx_ftgl_vec2i nx_ftgl_vec2i(const int32_t x, const int32_t y) {
	struct nx_ftgl_vec2i output;
	output.x = x;
	output.y = y;
	return output;
}

void nx_ftgl_set_fallbackfont(const uint32_t new_fallback_face_id) {
	internal.fallback_face = new_fallback_face_id;
}

void nx_ftgl_setshader2D(const GLuint id) {
	internal.shader = id;
	internal.color_uni_location = glGetUniformLocation(internal.shader, "textColor");
}

static struct nx_ftgl_glyph *nx_ftgl_search(const uint32_t face_id, const union nx_ftgl_ucs4 character, const uint16_t size) {
	struct nx_ftgl_glyph *current = internal.face[face_id].glyphs;
	while (current) {
		if (current->charcode.code == character.code && current->size == size) return current;
		current = current->next;
	}
	return NULL;
}

static int nx_ftgl_add(const uint32_t face_id, const union nx_ftgl_ucs4 character, const uint16_t size) {
	const FT_GlyphSlot slot = internal.face[face_id].FTface->glyph;
	if (internal.texture) {
		struct nx_ftgl_spatial_node *ptr;
		struct nx_ftgl_vec2i corner = nx_ftgl_vec2i(0, 0), dimensions;
		uint32_t x;
		for (x = 0; x < internal.directory.n_children; ++x) {
			ptr = internal.directory.child[x];
			corner = ptr->pos;
			dimensions = ptr->dimensions;
			// 1 pixel buffer on each side. this is not added to the recorded bitmap size.
			// May want to change this to only pad when x/y != 0/max
			if (ptr->dimensions.x >= slot->bitmap.width + 2 && ptr->dimensions.y >= slot->bitmap.rows + 2) {	
				char ptr_used = 0;
				// Split the node, reusing ptr's storage for one split.
				if (dimensions.x != slot->bitmap.width + 2) {
					ptr->pos.x = corner.x + (slot->bitmap.width + 2);
					ptr->pos.y = corner.y;
					ptr->dimensions.x = dimensions.x - (slot->bitmap.width + 2);
					ptr->dimensions.y = slot->bitmap.rows + 2;
					ptr_used = 1;
				} 				
				if (dimensions.y != slot->bitmap.rows + 2) {
					if (ptr_used) {
						ptr = malloc(sizeof(struct nx_ftgl_spatial_node));
						if (!ptr) {
							// fug
						}
					}
					ptr->pos.x = corner.x;
					ptr->pos.y = corner.y + slot->bitmap.rows + 2;
					ptr->dimensions.x = dimensions.x;
					ptr->dimensions.y = dimensions.y - (slot->bitmap.rows + 2);
					if (ptr_used) {
						struct nx_ftgl_spatial_node **ptr_directory = malloc(sizeof(struct nx_ftgl_spatial_node*)*(internal.directory.n_children+1));
						memcpy(ptr_directory, internal.directory.child, sizeof(struct nx_ftgl_spatial_node*)*(internal.directory.n_children));
						ptr_directory[internal.directory.n_children] = ptr;
						free(internal.directory.child);
						internal.directory.child = ptr_directory;
						internal.directory.n_children++;
					}
					ptr_used = 1;
				} 
				
				if (!ptr_used) {
					free(internal.directory.child[x]);
					if (x + 1 != internal.directory.n_children) {
						internal.directory.n_children--; 
						internal.directory.child[x] = internal.directory.child[internal.directory.n_children];
					} else {
						internal.directory.n_children--;
					}
					// don't bother resizing the directory. it's 1 node at most.
				}
				x = UINT32_MAX-1;
				
			} 
		}
		
		glBindTexture(GL_TEXTURE_2D, internal.texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, corner.x + 1, corner.y + 1, slot->bitmap.width, slot->bitmap.rows, NX_FTGL_PIXEL_FMT, GL_UNSIGNED_BYTE, slot->bitmap.buffer);

		struct nx_ftgl_glyph *glyph_data = malloc(sizeof(struct nx_ftgl_glyph));
		if (!glyph_data) {
			internal.error = 1;
			return -1;
		}
		
		glyph_data->last_used = internal.relative_time;
		internal.relative_time++;
		glyph_data->charcode = character;
		glyph_data->size = size;
		glyph_data->tex_position.x = (corner.x + 1) / (float)internal.texture_size;
		glyph_data->tex_position.y = (corner.y + 1) / (float)internal.texture_size;
		glyph_data->tex_dimensions.x = slot->bitmap.width / (float)internal.texture_size;
		glyph_data->tex_dimensions.y = slot->bitmap.rows / (float)internal.texture_size;
		glyph_data->dimensions.x = slot->bitmap.width;
		glyph_data->dimensions.y = slot->bitmap.rows;
		glyph_data->bearing.x = slot->bitmap_left;
		glyph_data->bearing.y = slot->bitmap_top;
		glyph_data->advance = slot->advance.x;
		// This will be necessary only if we plan to deal with vertical text.
		//glyph_data->advance.y = slot->advance.y;
		glyph_data->next = NULL;
		
		struct nx_ftgl_glyph *current = internal.face[face_id].glyphs;
		// insert new entry
		if (!current) {
			internal.face[face_id].glyphs = glyph_data;
		} else {
			while (current->next) {
				current = current->next;
			}
			current->next = glyph_data;
		}	
	} else {
		internal.error = 5;
		return -1;
	}
	return 0;
}
void nx_ftgl_deletebuffer() {
	if (internal.texture) {
		glDeleteTextures(1, &internal.texture);
		internal.texture = 0;
	}
	if (internal.vertex_buffer) {
		glDeleteBuffers(1, &internal.vertex_buffer);
		internal.vertex_buffer = 0;
	}
}
void nx_ftgl_exit() {
	nx_ftgl_deletebuffer();
	int x;
	for (x = 0; x < internal.current_face; ++x) {
		struct nx_ftgl_glyph *g = internal.face[x].glyphs;
		if (g) {
			while (g->next) {
				struct nx_ftgl_glyph *next = g->next;
				free(g);
				g = next;
			}
			free(g);
		}
	}
	for (x = 0; x < internal.directory.n_children; ++x) {
		free(internal.directory.child[x]);
	}
	free(internal.directory.child);
	free(internal.batch);
}

int nx_ftgl_genbuffer(const uint32_t size) {
	if (internal.texture) {
		nx_ftgl_deletebuffer();
	}
	glGenTextures(1, &internal.texture);
	glBindTexture(GL_TEXTURE_2D, internal.texture);
	glTexImage2D(GL_TEXTURE_2D, 0, NX_FTGL_PIXEL_FMT, size, size, 0, NX_FTGL_PIXEL_FMT, GL_UNSIGNED_BYTE, 0);
	// linear filtering results in strange artifacts along the outer border of the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	internal.texture_size = size;
	
	struct nx_ftgl_spatial_node **container = malloc(sizeof(struct nx_ftgl_spatial_node*));
	if (!container) {
		internal.error = 1;
		return -1;
	}
	struct nx_ftgl_spatial_node *node = malloc(sizeof(struct nx_ftgl_spatial_node));
	if (!node) {
		free(container);
		internal.error = 1;
		return -2;
	}
	
	glUseProgram(internal.shader);

	internal.buffer_size = 0;
	glGenBuffers(1, &internal.vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, internal.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	
	internal.directory.n_children = 1;
	internal.directory.child = container;
	internal.directory.child[0] = node;
	node->pos.x = 0;
	node->pos.y = 0;
	node->dimensions.x = size;
	node->dimensions.y = size;
	return 0;
}

int nx_ftgl_loadfont(const char *path) {
	struct nx_ftgl_face *ptr = malloc(sizeof(struct nx_ftgl_face)*(internal.current_face+1));
	if (!ptr) {
		internal.error = 1;
		return -1;
	}
	const int error = FT_New_Face(internal.library, path, 0, &ptr[internal.current_face].FTface);
	if (error == FT_Err_Unknown_File_Format) {
		free(ptr);
		internal.error = 2;
		return -2;
	} else if (error) {
		free(ptr);
		internal.error = 3;
		return -3;
	}
	ptr[internal.current_face].glyphs = NULL;
	memcpy(ptr,internal.face,sizeof(struct nx_ftgl_face)*(internal.current_face));
	internal.current_face++;
	free(internal.face);
	internal.face = ptr;
	return internal.current_face-1;
}

static size_t nx_ftgl_ucs4_clen(const unsigned char input) {
	static const char trailing_byte_index[256] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3, 4,4,4,4,4,4,4,4,5,5,5,5,6,6,6,6
	};
	return trailing_byte_index[input];
}

// Returns UTF-8 string length 
size_t nx_ftgl_ustrlen(const unsigned char *string) {
	if (!string) return 0;
	size_t at = 0, length = 0;
	const size_t byte_length = strlen((char*)string);
	while (at < byte_length) {
		at += nx_ftgl_ucs4_clen(string[at]);
		length++;
	}
	return length;
}

union nx_ftgl_ucs4 nx_ftgl_getc(const unsigned char *input, const uint32_t position) {
	union nx_ftgl_ucs4 c; c.code = 0;
	if (input) {
		const size_t length = nx_ftgl_ucs4_clen(input[position]);
		static const uint32_t utf8_offsets[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL, 0x03C82080UL, 0xFA082080UL, 0x82082080UL };
		uint32_t pos = position;
		switch (length) {
			case 6: c.code += input[pos]; c.code <<= 6; pos++;
			case 5: c.code += input[pos]; c.code <<= 6; pos++;
			case 4: c.code += input[pos]; c.code <<= 6; pos++;
			case 3: c.code += input[pos]; c.code <<= 6; pos++;
			case 2: c.code += input[pos]; c.code <<= 6; pos++;
			case 1: c.code += input[pos]; 
		}
		c.code -= utf8_offsets[length-1];
	}
	return c;
}

// Called intrinsically through nx_ftgl_buffertext
static int nx_ftgl_bufferchar(const union nx_ftgl_ucs4 character, const uint32_t face_id, const uint16_t size) {
	if (face_id >= internal.current_face) return -1; 
	if (character.code >= ' ') {
		if (!nx_ftgl_search(face_id, character, size)) {
			const uint32_t code = FT_Get_Char_Index(internal.face[face_id].FTface, character.code);
			if (code) {
				FT_Load_Glyph(internal.face[face_id].FTface, code, FT_LOAD_RENDER);
				const int error = nx_ftgl_add(face_id, character, size);
				if (error) {
					printf("NXFTGL: Error buffering char %lu\n",(long unsigned int)face_id);
					return -2;
				}
			} else {
				internal.error = 4;
				printf("NXFTGL: Unknown character code %u.\n",character.code);
				return -2;
			}
		}
	} 
	return 0;
}

int nx_ftgl_buffertext(const unsigned char *text, const uint32_t face_id, const uint16_t size) {
	// Quick check for valid face id
	if (face_id >= internal.current_face) return -1;
	const size_t length = nx_ftgl_ustrlen(text);
	size_t x, position;
	
	FT_Set_Char_Size(internal.face[face_id].FTface, size * 64, 0, 100, 0 ); 
	FT_Select_Charmap(internal.face[face_id].FTface, ft_encoding_unicode);
	for (x = 0, position = 0; x < length; ++x) {
		union nx_ftgl_ucs4 character = nx_ftgl_getc(text,position);
		nx_ftgl_bufferchar(character, face_id, size);
		position += nx_ftgl_ucs4_clen(text[position]);
	}
	return 0;
}

int nx_ftgl_rendertext(const unsigned char *text, const uint32_t face_id, const uint16_t size, const struct nx_ftgl_vec2i viewport, const struct nx_ftgl_vec2i position, const struct nx_ftgl_vec4f color) {
	if (!text) return 0;
	glUseProgram(internal.shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, internal.texture);
	glBindBuffer(GL_ARRAY_BUFFER, internal.vertex_buffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	
	glUniform4f(internal.color_uni_location, color.r, color.g, color.b, color.a);	
	
	const size_t length = nx_ftgl_ustrlen(text);
	if (length == 0) return 0;
	struct nx_ftgl_vec2i offset = position, res = viewport;
	res.x /= 2;
	res.y /= 2;

	int entry_count = 0;
	if (internal.batch_size < length) {
		free(internal.batch);
		internal.batch = malloc(sizeof(float) * 24 * length);
		if (!internal.batch) {
			internal.batch_size = 0;
			internal.error = 1;
			return -1;
		}
		internal.batch_size = length;
	}
	size_t x, byte;
	for (x = 0, byte = 0; x < length; ++x) {
		union nx_ftgl_ucs4 character = nx_ftgl_getc(text,byte);
		const int byte_advance = nx_ftgl_ucs4_clen(text[byte]);
		if (character.code == '\n') { 
			offset.x = position.x;
			offset.y -= size * 2;
		} else {
			struct nx_ftgl_glyph *ptr;
			uint32_t using_face = face_id;
			renderchar:
			ptr = nx_ftgl_search(using_face, character, size);
			if (!ptr) {
				FT_Select_Charmap(internal.face[using_face].FTface, ft_encoding_unicode);
				const uint32_t code = FT_Get_Char_Index(internal.face[using_face].FTface, character.code);
				if (code) {
					FT_Load_Glyph(internal.face[using_face].FTface, code, FT_LOAD_RENDER);
					unsigned char buffer[8];
					memcpy(buffer, &text[byte], byte_advance);
					buffer[byte_advance] = '\0';
					const int error = nx_ftgl_buffertext(buffer, using_face, size);
					if (error) {
						puts("NXFTGL: nx_ftgl_buffertext error.");
					} else {
						ptr = nx_ftgl_search(using_face, character, size);
					}
				} else {
					if (using_face != internal.fallback_face) {
						using_face = internal.fallback_face;
					} else {
						// No glyph for this code is available, use '?' instead.
						character = nx_ftgl_getc((unsigned char*)"?",0);
						using_face = face_id;
					}
					goto renderchar;
				}
			}
			if (ptr) {
				struct nx_ftgl_vec2f left, right;
				
				left.x = (offset.x + ptr->bearing.x - res.x) / (float)res.x;
				left.y = (offset.y + ptr->dimensions.y - (ptr->dimensions.y - ptr->bearing.y) - res.y) / (float)res.y;
				
				right.x = (offset.x + ptr->dimensions.x + ptr->bearing.x - res.x) / (float)res.x;
				right.y = (offset.y - (ptr->dimensions.y - ptr->bearing.y) - res.y) / (float)res.y;

				struct nx_ftgl_vec2f tleft, tright;
				tleft.x = ptr->tex_position.x;
				tleft.y = ptr->tex_position.y;
				tright.x = ptr->tex_position.x + ptr->tex_dimensions.x;
				tright.y = ptr->tex_position.y + ptr->tex_dimensions.y;
				
				// CCW winding order
				const GLfloat data[24] = {
					right.x, right.y, tright.x, tright.y,
					right.x, left.y, tright.x, tleft.y,
					left.x, left.y, tleft.x, tleft.y,
					
					left.x, left.y, tleft.x, tleft.y,
					left.x, right.y, tleft.x, tright.y,
					right.x, right.y, tright.x, tright.y
				};
				memcpy(&internal.batch[entry_count*24], data, sizeof(data));			
				offset.x += (ptr->advance/64);
				entry_count++;
			}
		}
		byte += byte_advance;
	}
	if (entry_count > internal.buffer_size) {
		glBufferData(GL_ARRAY_BUFFER, entry_count * 24 * sizeof(float), (void*)internal.batch, GL_DYNAMIC_DRAW);
		internal.buffer_size = entry_count;
	} else {
		glBufferSubData(GL_ARRAY_BUFFER, 0, entry_count * 24 * sizeof(float), (void*)internal.batch);
	}
	glDrawArrays(GL_TRIANGLES, 0, entry_count * 6);
	glDisableVertexAttribArray(0);
	return offset.x - position.x;
}

int nx_ftgl_rendertext_center_at_x(const unsigned char *text, const uint32_t face_id, const uint16_t size, const struct nx_ftgl_vec2i viewport, const struct nx_ftgl_vec2i position, const struct nx_ftgl_vec4f color) {
	// Get total length of the string in chars and pixels
	const size_t length_bytes = nx_ftgl_ustrlen(text);
	if (length_bytes == 0) return 0;
	size_t byte, length_pixels = 0;
	for (byte = 0; byte < length_bytes;) {
		union nx_ftgl_ucs4 character = nx_ftgl_getc(text,byte);
		const int byte_advance = nx_ftgl_ucs4_clen(text[byte]);
		struct nx_ftgl_glyph *ptr;
		uint32_t using_face = face_id;
		bufferchar:
		ptr = nx_ftgl_search(using_face, character, size);
		if (!ptr) {
			FT_Select_Charmap(internal.face[using_face].FTface, ft_encoding_unicode);
			const uint32_t code = FT_Get_Char_Index(internal.face[using_face].FTface, character.code);
			if (code) {
				FT_Load_Glyph(internal.face[using_face].FTface, code, FT_LOAD_RENDER);
				unsigned char buffer[8];
				memcpy(buffer, &text[byte], byte_advance);
				buffer[byte_advance] = '\0';
				const int error = nx_ftgl_buffertext(buffer, using_face, size);
				if (error) {
					puts("NXFTGL: nx_ftgl_buffertext_center_at_x error.");
				} else {
					ptr = nx_ftgl_search(using_face, character, size);
				}
			} else {
				if (using_face != internal.fallback_face) {
					using_face = internal.fallback_face;
				} else {
					character = nx_ftgl_getc((unsigned char*)"?",0);
					using_face = face_id;
				}
				goto bufferchar;
			}
		}
		// Don't want to get caught here.
		if (byte_advance == 0) {
			return 0;
		}
		byte += byte_advance;
		length_pixels += (ptr->advance/64);
	}
	struct nx_ftgl_vec2i new_position = position;
	new_position.x -= (length_pixels / 2);
	return nx_ftgl_rendertext(text, face_id, size, viewport, new_position, color);
}