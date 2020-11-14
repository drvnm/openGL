#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "shader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
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
       -0.5f, -0.5f, //links onder
        0.5f, -0.5f, //rechts onder
        0.5f,  0.5f, //rechts boven
       -0.5f,  0.5f  //links boven
        
    };
    unsigned int indices[] = {
        0,1,2,
        2,3,0 
    };
    //maak een buffer 

    unsigned int VAO;
    glCall(glGenVertexArrays(1, &VAO)); //maak vertex array
    glCall(glBindVertexArray(VAO)); // bind vertex array
   
    //Vertex Buffer
    VertexBuffer vb(positions, 4 * 2 * sizeof(float)); 
    
    IndexBuffer ib(indices, 6);
    //Index buffer
    unsigned int ibo;
   
    //vertel hoe data naar shader gaat
    glCall(glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE, 2* sizeof(float),(const void*) 0));
    glCall(glEnableVertexAttribArray(0));

    Shader myShader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
    myShader.use(); 

    int location = glGetUniformLocation(myShader.ID, "u_Color"); //krijg locatie van de color variable
    glCall(glUniform4f(location, 0.F, 0.3F, 0.8f, 1.0F)); //zet de value
    float r = 0.05f; 
    float increment = 0.05f; 

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        glCall(glUniform4f(location, r, 0.3F, 0.8f, 1.0F)); //zet de value
        glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));   /* Swap front and back buffers */
        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f; 
        r += increment; 
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}