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

uniform vec4 color_mod;
uniform uint player_id;

in vec2 UV;
in vec3 normal;

out vec4 output_color;
out uint id_output;

uniform sampler2D bound_texture;

void main() {
	vec4 color;
	vec4 ambient_color;
	vec3 light_direction;
	vec3 object_normal;
	float intensity;
	
	object_normal = normalize(normal);
	
	vec3 camera_dir = normalize(vec3(0.0,0.0,0.0));
	
	light_direction = normalize(vec3(1.0,1.0,1.0));
	intensity = max(dot(light_direction,object_normal),0.0);

	if (texCount == 0) {
		color = vec4(0.0,1.0,0.0,1.0) * diffuse;
		ambient_color = ambient;
	} else {
		color = texture(bound_texture,UV);
		ambient_color = color * 0.3;
	}
	output_color = (color * intensity) + ambient_color * 0.6;
	output_color.a = 1.f;
	output_color = output_color * color_mod;
	id_output = player_id;
}