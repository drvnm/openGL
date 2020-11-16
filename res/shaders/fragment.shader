#version 330 core

layout(location = 0)out vec4 color;
uniform vec4 u_Color; 
void main()
{
    color = vec4(1.0f,0.5f,1.0f,1.0f);
};