#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "shader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include <vector>
int main()
{
    GLFWwindow* window;

    /* Initialize the library */

    if (!glfwInit())

        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // zet major opengl version naar 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // zet minor opengl version naar 3 (3.3 in totaal dus)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //zet de profile naar core
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); 
    std::cout << glGetString(GL_VERSION) << std::endl; 

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }
    /* Loop until the user closes the window */


    //vertex data
    float positions[] = {
       -0.5f, -0.5f, 0.0f, 0.0f, //links onder
        0.5f, -0.5f, 1.0f, 0.0f, //rechts onder
        0.5f,  0.5f, 1.0f, 1.0f,//rechts boven
       -0.5f,  0.5f, 0.0f, 1.0f//links boven
        
    };
    unsigned int indices[] = {
        0,1,2,
        2,3,0 
    };


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    //vertex array
    VertexArray va;
    //Vertex Buffer
    VertexBuffer vb(positions, 4 * 4 * sizeof(float)); 
    VertexBufferLayout layout; 

    layout.Push<float>(2); 
    layout.Push<float>(2);

    va.AddBuffer(vb, layout);
    IndexBuffer ib(indices, 6);
    //Index buffer

    Shader myShader("res/shaders/vertex.shader", "res/shaders/fragment.shader");

    Renderer renderer;
    Texture texture("res/textures/hp.png");
    texture.Bind();
    myShader.setUniform1i("u_Texture", 0);
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        renderer.Clear(); 
        myShader.use();
        myShader.setUniform4f("u_Color", 1.0f, 0.6f, 0.3f, 1.0f);
        
        renderer.Draw(va, ib, myShader);
       
       
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}