#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 inColor;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 passedColor1;
void main()
{
	gl_Position = projection * view * transform * vec4(aPos, 1.0f);
	passedColor1 = vec4(clamp(aPos.y / 10, 0.2f,1.0f), clamp(aPos.y / 10, 0.2f,1.0f), clamp(aPos.y / 10, 0.0f, 0.5f), 1.0f);
}