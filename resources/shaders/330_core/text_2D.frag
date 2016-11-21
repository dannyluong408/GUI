#version 330 core
in vec2 TexCoords;
out vec4 c;
uniform sampler2D text;
uniform vec4 textColor;

void main() {
	c = textColor * vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
} 