#version 330 core

layout (location = 0) in vec3 aPos;

uniform float ourX;
uniform float ourColor;
uniform float ourY;
uniform float colorR;
uniform float colorG;
uniform float colorB;

out vec4 vertexColor;

void main()
{
   gl_Position = vec4(aPos.x+ourX,aPos.y+ourY,aPos.z, 1.0f);
   vertexColor = vec4(colorR,colorG,colorB,0.0f);
}