#version 100
precision highp float;
varying vec2 TexCoords;

uniform sampler2D text;
uniform vec4 textColor;

void main() {
	gl_FragColor = textColor * vec4(1.0, 1.0, 1.0, texture2D(text, TexCoords).r);
} 