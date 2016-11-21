#version 100
attribute vec4 pos;

uniform float z_index;
varying vec2 TexCoords;

void main() {
	gl_Position = vec4(pos.xy, -z_index, 1.0);
    TexCoords = pos.zw;
}