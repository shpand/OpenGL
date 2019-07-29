#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "Cube.h"
#include "Shader.h"
#include "FpsCounter.h"
#include "samples/Sample.h"
#include "samples/MovingSquareAndCubeSample.h"

int main() {
    GLFWwindow *window = NULL;

    /* start GL context and O/S window using the GLFW helper library */
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    /* start GLEW extension handler */
    glewExperimental = GL_TRUE;
    glewInit();

    /* get version info */
    const GLubyte* graphicsCard = glGetString(GL_RENDERER); /* get renderer string */
    const GLubyte* version = glGetString(GL_VERSION);	 /* version as a string */
    printf("Graphics Card: %s\n", graphicsCard);
    printf("OpenGL version supported %s\n", version);

    /* tell GL to only draw onto a pixel if the shape is closer to the viewer
    than anything already drawn at that pixel */
    glEnable(GL_DEPTH_TEST); /* enable depth-testing */
    /* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
    glDepthFunc(GL_LESS);


    samples::Sample* sample = new samples::MovingSquareAndCubeSample();

    FpsCounter fps(window);
    while (!glfwWindowShouldClose(window)) {
        fps.Update();

        sample->OnUpdate(0.1f);
        sample->OnRender();
        /* update other events like input handling */
        glfwPollEvents();
        /* put the stuff we've been drawing onto the display */
        glfwSwapBuffers(window);
    }

    /* close GL context and any other GLFW resources */
    glfwTerminate();
    return 0;
}
