#version 100

attribute vec4 vertex;
varying vec2 TexCoords;

void main() {
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
} 