#version 400 core

in vec3 Color;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main()
{
    FragColor = vec4(Color, 1.0f);
}