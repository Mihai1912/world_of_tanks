#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_color;
layout(location = 2) in vec2 v_coord;
layout(location = 1) in vec3 v_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 Color;
uniform float health;

// TODO: output values to fragment shader
out vec2 frag_coord;
out vec3 frag_normal;
out vec3 frag_color;
out vec3 frag_position;
out float frag_health;

void main()
{
	// TODO: send output to fragment shader
	
	frag_position = v_position;
	frag_color = Color;
	frag_normal = v_normal;
	frag_coord = v_coord;
	frag_health = health;

	// v_position = v_position + glm::vec3( cos(health + 87) , sin(health - 3) , 0.0f);
	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(v_position + vec3(-health/2 * sin(health - 3), 0.0f , health/2 * sin(health - 3)), 1.0);
}