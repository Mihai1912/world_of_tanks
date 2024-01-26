#version 330

// TODO: get values from fragment shader
in vec2 frag_coord;
in vec3 frag_color;
in vec3 frag_normal;
in vec3 frag_position;
in float frag_health;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO: write pixel out color
	vec3 colorInFunctionOfHealth = frag_color + vec3((frag_health * 20)/255.f);
	   
	out_color = vec4(colorInFunctionOfHealth, 1);
}