#version 330 core

layout(location = 0) in vec3 vertex_pos;
uniform mat4 depth_MVP;
void main() {
	gl_Position = depth_MVP * vec4(vertex_pos, 1);
}