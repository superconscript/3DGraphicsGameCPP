#version 330 core
out vec4 FragColor;
in vec4 passedColor1;
uniform vec4 passedColor;

void main()
{
	FragColor = passedColor1;
}