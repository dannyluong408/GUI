#version 330 core
precision highp float;
layout (location = 0) in vec4 pos;

uniform float z_index;

out vec2 TexCoords;

void main() {
	gl_Position = vec4(pos.xy, -z_index, 1.0);
    TexCoords = pos.zw;
}