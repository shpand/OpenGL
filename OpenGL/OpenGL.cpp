#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "Cube.h"
#include "Shader.h"

#include "glm/glm.hpp";
#include "glm/gtc/matrix_transform.hpp";
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
#include "Square.h"
#include "FpsCounter.h"
#include "CubeRenderer.h"
#include "samples/Sample.h"
#include "samples/MovingSquareAndCubeSample.h"

int main() {
    GLFWwindow *window = NULL;

    Square* square = new Square(-0.5, -0.5, 0.5, 1);
    std::vector<GLfloat> points2 = square->GetPoints();
    std::vector<unsigned int> indices2 = square->GetIndicies();

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

    //Prepare 2nd cube-----------------------------------------------------------
    const int pointsSizeInBytes2 = points2.size() * sizeof(GLfloat);
    VertexBuffer vb2(&points2[0], pointsSizeInBytes2);

    VertexBufferLayout layout2;
    layout2.Push<float>(2);
    layout2.Push<float>(2);//layout for texture coordinates
    VertexArray va2;
    va2.AddBuffer(vb2, layout2);

    IndexBuffer ib2(&indices2[0], indices2.size());
    //End of preparing 2nd cube---------------------------------------------------


    /* here we copy the shader strings into GL shaders, and compile them. we
    then create an executable shader 'program' and attach both of the compiled
            shaders. we link this, which matches the outputs of the vertex shader to
    the inputs of the fragment shader, etc. and it is then ready to use */

    Shader shader("Basic.shader");
    //Shader shader("color.shader");
    shader.Bind();

    Texture texture("resources/textures/cube.png");
    const int textureSlot = 0;
    texture.Bind(textureSlot);
    shader.SetUniform1i("u_Texture", textureSlot);

    /* this loop clears the drawing surface, then draws the geometry described
            by the VAO onto the drawing surface. we 'poll events' to see if the window
    was closed, etc. finally, we 'swap the buffers' which displays our drawing
            surface onto the view area. we use a double-buffering system which means
            that we have a 'currently displayed' surface, and 'currently being drawn'
            surface. hence the 'swap' idea. in a single-buffering system we would see
            stuff being drawn one-after-the-other */

    CubeRenderer cubeRenderer(glm::vec3(0.5, 0.5, 0), glm::vec3(0.5, 0.5, 0.5), &shader);

    Renderer renderer;
    glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, 0, 0));//it's essentially a camera that we move


    samples::Sample* sample = new samples::MovingSquareAndCubeSample();
    sample->OnUpdate(0.1f);
    sample->OnRender();

    float offsetX = 0;
    float rotateDegree = 0;
    float mover = 0.0004;
    FpsCounter fps(window);
    while (!glfwWindowShouldClose(window)) {
        fps.Update();

        offsetX += mover;
        rotateDegree += mover;
        if(offsetX > 1)
        {
            offsetX = 1;
            mover = -mover;
        }
        else if (offsetX < -1)
        {
            offsetX = -1;
            mover = -mover;
        }
        glm::vec3 translationX(offsetX, 0, 0);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translationX);//objects transformation
        model = glm::rotate(model, glm::radians(rotateDegree * 90), glm::vec3(1.f, 1.f, 1.f));
        glm::mat4 modelViewProjection = projection * viewMatrix * model;
        shader.SetUniformMat4f("u_MVP", modelViewProjection);


        /* wipe the drawing surface clear */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.2, 1);

        cubeRenderer.Draw();
        renderer.Draw(va2, ib2, shader);

        /* update other events like input handling */
        glfwPollEvents();
        /* put the stuff we've been drawing onto the display */
        glfwSwapBuffers(window);
    }

    /* close GL context and any other GLFW resources */
    glfwTerminate();
    return 0;
}
