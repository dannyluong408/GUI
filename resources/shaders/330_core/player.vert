#version 330 core

precision highp float;

in vec3 vertex_modelspace;
in vec2 vertexUV;
in vec3 object_normal;
in ivec4 bone_ids;
in vec4 bone_weights;

// need to add bones too

uniform mat4 MVP;
uniform vec4 color_mod;
uniform uint player_id;

out vec2 UV;
out vec3 normal;

void main(){
    gl_Position = MVP * vec4(vertex_modelspace,1);
	UV = vertexUV;
	normal = object_normal;
}