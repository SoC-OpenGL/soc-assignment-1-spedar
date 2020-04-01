#version 400

layout (location = 0) in vec2 vp;
layout (location = 1) in float aColor;

out vec3 ourColor;

void main () 
{
  gl_Position = vec4 (vp,0.0, 1.0);
  ourColor = vec3 (aColor, aColor, aColor) ;
}
