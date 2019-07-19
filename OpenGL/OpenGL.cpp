#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "Cube.h"
#include "Asserter.h"
#include "Shader.h"

#include "vendor/glm/glm.hpp";
#include "vendor/glm/gtc/matrix_transform.hpp";
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Renderer.h"

int main() {
    GLFWwindow *window = NULL;

    Cube* cube = new Cube(0.5, 0.5, 0, 0.5, 0.5, 0.5);
    std::vector<GLfloat> points = cube->GetPoints();
    std::vector<unsigned int> indices = cube->GetIndicies();

    Cube* cube2 = new Cube(-0.5, -0.5, 0, 0.5, 1, 0.5);
    std::vector<GLfloat> points2 = cube2->GetPoints();
    std::vector<unsigned int> indices2 = cube2->GetIndicies();

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

    /* a vertex buffer object (VBO) is created here. this stores an array of
    data on the graphics adapter's memory. in our case - the vertex points */
    const int pointsSizeInBytes = points.size() * sizeof(GLfloat);
    const VertexBuffer vb(&points[0], pointsSizeInBytes);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    //layout.Push<float>(2);//layout for texture coordinates
    VertexArray va;
    va.AddBuffer(vb, layout);
    //binding of indices must happen right after vb and va has been bound.
    IndexBuffer ib(&indices[0], indices.size());

    //Prepare 2nd cube-----------------------------------------------------------
    const int pointsSizeInBytes2 = points2.size() * sizeof(GLfloat);
    VertexBuffer vb2(&points2[0], pointsSizeInBytes2);

    VertexBufferLayout layout2;
    layout2.Push<float>(3);
    //layout.Push<float>(2);//layout for texture coordinates
    VertexArray va2;
    va2.AddBuffer(vb2, layout2);

    IndexBuffer ib2(&indices2[0], indices2.size());
    //End of preparing 2nd cube---------------------------------------------------


    /* here we copy the shader strings into GL shaders, and compile them. we
    then create an executable shader 'program' and attach both of the compiled
            shaders. we link this, which matches the outputs of the vertex shader to
    the inputs of the fragment shader, etc. and it is then ready to use */

    Shader shader("Basic.shader");
    shader.Bind();

    /* this loop clears the drawing surface, then draws the geometry described
            by the VAO onto the drawing surface. we 'poll events' to see if the window
    was closed, etc. finally, we 'swap the buffers' which displays our drawing
            surface onto the view area. we use a double-buffering system which means
            that we have a 'currently displayed' surface, and 'currently being drawn'
            surface. hence the 'swap' idea. in a single-buffering system we would see
            stuff being drawn one-after-the-other */

    Renderer renderer;
    glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, 0, 0));//it's essentially a camera that we move


    float offsetX = 0;
    float rotateDegree = 0;
    float mover = 0.0002;
    while (!glfwWindowShouldClose(window)) {
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

        renderer.Draw(va, ib, shader);
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
