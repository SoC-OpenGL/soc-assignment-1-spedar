#version 400

out vec4 frag_colour;
in vec3 ourColor ;

void main () 
{

  gl_FragColor = vec4 (ourColor, 1.0) ;
  
}
