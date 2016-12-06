#version 330 core

precision highp float;

layout (std140) uniform Material {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	vec4 emissive;
	float shininess;
	int texCount;
};


in vec2 UV;
in vec3 normal;

out vec4 outputc;
uniform sampler2D bound_texture;
uniform mat4 MVP;

void main() {
	vec4 color;
	vec4 ambient_color;
	vec3 light_direction;
	vec3 object_normal;
	float intensity;
	
	light_direction = normalize(vec3(1.0,1.0,1.0));
	
	object_normal = normalize(normal);
	intensity = max(dot(light_direction,object_normal),0.0);

	if (texCount == 0) {
		color = vec4(0.0,1.0,0.0,1.0) * diffuse;
		ambient_color = ambient;
	} else {
		color = texture(bound_texture,UV);
		ambient_color = color * 0.3;
	}
	outputc = (color * intensity) + ambient_color * 0.6;
	outputc.a = 1.0;
}