#include <GL/glew.h>

#include "vld.h" //Don't remove!! Its Visual Leak Debugger to search memory leaks

#include <cstdio>
#include "Shader.h"
#include "utils/FpsCounter.h"
#include "samples/Sample3d.h"
#include "samples/WorldEditor.h"

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

    window = glfwCreateWindow(1920, 1080, "Hello Triangle", NULL, NULL);
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


    //samples::Sample* sample = new samples::MovingSquareAndCubeSample();
    //samples::Sample* sample = new samples::Sample3d();
    samples::Sample* sample = new samples::WorldEditor();

    FpsCounter fps(window);
    double lastTime = 0;
    while (!glfwWindowShouldClose(window)) {
        const double time = glfwGetTime();
        const double deltaTime = time - lastTime;
        lastTime = time;

        fps.Update();

        sample->OnUpdate(deltaTime, window);
        sample->OnRender();
        /* update other events like input handling */
        glfwPollEvents();
        /* put the stuff we've been drawing onto the display */
        glfwSwapBuffers(window);
    }

    delete sample;

    /* close GL context and any other GLFW resources */
    glfwTerminate();
    return 0;
}
