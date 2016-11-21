#version 100
precision highp float;
varying vec2 TexCoords;
uniform sampler2D text;

void main() {
	gl_FragColor = texture2D(text, TexCoords);
} 