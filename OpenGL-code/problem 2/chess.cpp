#include "gl_framework.hpp"
#include "shader_util.hpp"
#include<cmath>
#include<iostream>

float points[81*18];

float startx = -0.8, inc = 0.2, color=0.0;

void genpoint(float* points){
  int k=0;
  for (int i=0; i<8; i++){
    float starty = -0.8;
    for (int j=0; j<8; j++){
      points[k] = startx  ;
      points[k+1] = starty  ;
      points[k+2] = color ;

      points[k+3] = startx  ;
      points[k+4] = starty + inc ;
      points[k+5] = color ;

      points[k+6] = startx+inc;
      points[k+7] = starty;
      points[k+8] =  color;

      points[k+9] =  startx;
      points[k+10] = starty+inc;
      points[k+11] =  color;

      points[k+12] = startx+inc;
      points[k+13] = starty;
      points[k+14] =  color;


      points[k+15] = startx+inc;
      points[k+16] = starty+inc;
      points[k+17] =  color;
      k+=18;
      starty+=inc;
      if(color==0.0) color = 1.0;
      else color = 0.0;
    }
    if(color == 0.0)color =1.0;
    else color = 0.0;
    startx+= inc;
  } 
}


GLuint shaderProgram;
GLuint vbo, vao ;

void initShadersGL(void)
{
  std::string vertex_shader_file("vs.glsl");
  std::string fragment_shader_file("fs.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  
}

void initVertexBufferGL(void)
{
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glGenBuffers (1, &vbo);

  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glBufferData (GL_ARRAY_BUFFER, sizeof (points), points, GL_STATIC_DRAW);


  glEnableVertexAttribArray (0);
  glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
 
  glEnableVertexAttribArray(1) ;
  glVertexAttribPointer (1, 1, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(2*sizeof(float)) );

}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  glUseProgram(shaderProgram);

  glBindVertexArray (vao);

  glDrawArrays(GL_TRIANGLES, 0, 64*6);
}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW wkow
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a wkowed mode wkow and its OpenGL context
  window = glfwCreateWindow(640, 640, "chess", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the wkow's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  genpoint(points);
  csX75::initGL();
  initShadersGL();
  initVertexBufferGL();

  // Loop until the user closes the wkow
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
 
  glfwTerminate();
  return 0;
}
