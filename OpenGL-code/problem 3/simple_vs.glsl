#version 400

layout (location = 0) in vec2 vp;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord ;

void main () 
{
  gl_Position = vec4 (vp, 0.0, 1.0);
  TexCoord = aTexCoord;
}
