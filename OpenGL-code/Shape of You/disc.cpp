#include "gl_framework.hpp"
#include "shader_util.hpp"
#include<cmath>
#include<iostream>
using namespace std ;
const int nvertices = 50 ;
                                                                /*update here */
float points[200] ;// no of vertices times 2(x,y)* 2(ring) ... (x4)
unsigned int ind[300]; // no of vertives times*6                  
int m = nvertices*4, n = nvertices*6 ;
void genpoint(float* points, unsigned int* ind ){
  for (int i = 0; i<(m); i = i+4){                              
    points[i]   = 0.0 * cos(2*M_PI/nvertices*i/4) ;
    points[i+1] = 0.0 * sin(2*M_PI/nvertices*i/4) ;
    points[i+2] = 0.5 * cos(2*M_PI/nvertices*i/4) ;
    points[i+3] = 0.5 * sin(2*M_PI/nvertices*i/4) ;
  }
  unsigned int o = 0, k = nvertices*2;
  for (int i = 0; i<n ; i=i+6){                                  
    ind[i] = o; ind[i+1]=o+1; ind[i+2]=(o+2)%k;
    ind[i+3] = o+1; ind[i+4]=(o+2)%k; ind[i+5]=(o+3)%k;
    o+=2;
  }
}

// float points[] = {
//     0.0f,  0.5f,  0.0f,
//     0.5f, -0.5f,  0.0f,
//     -0.5f, -0.5f,  0.0f
//   };

GLuint shaderProgram;
GLuint vbo, vao, EBO;

void initShadersGL(void)
{
  std::string vertex_shader_file("simple_vs.glsl");
  std::string fragment_shader_file("simple_fs.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  
}

void initVertexBufferGL(void)
{
  //Ask GL for a Vertex Attribute Object (vao)
  glGenVertexArrays (1, &vao);
  //Set it as the current array to be used by binding it
  glBindVertexArray (vao);
  //Ask GL for a Vertex Buffer Object (vbo)
  glGenBuffers (1, &vbo);
  glGenBuffers (1, &EBO);
  //Set it as the current buffer to be used by binding it
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  //Copy the points into the current buffer - 9 float values, start pointer and static data
  glBufferData (GL_ARRAY_BUFFER,  sizeof (points), points, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);

  //Enable the vertex attribute
  glEnableVertexAttribArray (0);
  //This the layout of our first vertex buffer
  //"0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats 
  glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
  glBindVertexArray(0) ;
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderProgram);

  glBindVertexArray (vao);

  // Draw points 0-3 from the currently bound VAO with current in-use shader
  //glDrawArrays(GL_LINES, 0, 16);

  glDrawElements(GL_TRIANGLES, n, GL_UNSIGNED_INT,0);
}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
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

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(640, 640, "Any Disc", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
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
  genpoint(points, ind);
  csX75::initGL();
  initShadersGL();
  initVertexBufferGL();

  // Loop until the user closes the window
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

