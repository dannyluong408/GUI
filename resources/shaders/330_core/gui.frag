#version 330 core
in vec2 TexCoords;
out vec4 c;
uniform sampler2D text;

void main() {
	c = texture(text, TexCoords);
}