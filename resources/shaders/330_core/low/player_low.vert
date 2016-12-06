#version 330 core

precision highp float;

in vec3 vertex_modelspace;
in vec2 vertexUV;
in vec3 object_normal;

uniform mat4 MVP;

uniform vec4 player_color;

out vec2 UV;
out vec3 normal;

void main(){
    gl_Position = MVP * vec4(vertex_modelspace,1);
	UV = vertexUV;
	normal = object_normal;
}