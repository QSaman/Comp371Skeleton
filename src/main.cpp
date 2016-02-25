/* Include glew.h before glfw3.h */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 600

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Each GLFWWindow encapsulate both window details and OpenGL context */
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    /* It is important to call glewInit after glfwMakeContextCurrent*/
    glewInit();
    /* After glewInit(), it is safe to use OpenGL API */
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    //GLFW game loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}
