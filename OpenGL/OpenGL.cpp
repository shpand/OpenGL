#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "Cube.h"
#include "Asserter.h"
#include "Shader.h"

#include "vendor/glm/glm.hpp";
#include "vendor/glm/gtc/matrix_transform.hpp";

int main() {
    GLFWwindow *window = NULL;
    const GLubyte *renderer;
    const GLubyte *version;
    GLuint vao, vao2;
    GLuint vbo, vbo2;
    GLuint ib, ib2;

    Cube* cube = new Cube(0.5, 0.5, 0, 0.5, 0.5, 0.5);
    std::vector<GLfloat> points = cube->GetPoints();
    std::vector<int> indices = cube->GetIndicies();

    Cube* cube2 = new Cube(-0.5, -0.5, 0, 0.5, 1, 0.5);
    std::vector<GLfloat> points2 = cube2->GetPoints();
    std::vector<int> indices2 = cube2->GetIndicies();

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
    renderer = glGetString(GL_RENDERER); /* get renderer string */
    version = glGetString(GL_VERSION);	 /* version as a string */
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    /* tell GL to only draw onto a pixel if the shape is closer to the viewer
    than anything already drawn at that pixel */
    glEnable(GL_DEPTH_TEST); /* enable depth-testing */
    /* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
    glDepthFunc(GL_LESS);

    /* a vertex buffer object (VBO) is created here. this stores an array of
    data on the graphics adapter's memory. in our case - the vertex points */
    const int pointsSizeInBytes = points.size() * sizeof(GLfloat);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, pointsSizeInBytes, &points[0], GL_STATIC_DRAW);

    /* the vertex array object (VAO) is a little descriptor that defines which
    data from vertex buffer objects should be used as input variables to vertex
    shaders. in our case - use our only VBO, and say 'every three floats is a
    variable' */
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    /* "attribute #0 should be enabled when this vao is bound" */
    glEnableVertexAttribArray(0);
    /* this VBO is already bound, but it's a good habit to explicitly specify which
    VBO's data the following vertex attribute pointer refers to */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    /* "attribute #0 is created from every 3 variables in the above buffer, of type
    float (i.e. make me vec3s)" */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    const int indicesSizeInBytes = indices.size() * sizeof(int);
    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSizeInBytes, &indices[0], GL_STATIC_DRAW);


    //Prepare 2nd cube-----------------------------------------------------------
    const int pointsSizeInBytes2 = points2.size() * sizeof(GLfloat);
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, pointsSizeInBytes2, &points2[0], GL_STATIC_DRAW);

    GLCall(glGenVertexArrays(1, &vao2));
    GLCall(glBindVertexArray(vao2));
    /* "attribute #0 should be enabled when this vao is bound" */
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo2));
    /* "attribute #0 is created from every 3 variables in the above buffer, of type
    float (i.e. make me vec3s)" */
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));

    const int indicesSizeInBytes2 = indices2.size() * sizeof(int);
    GLCall(glGenBuffers(1, &ib2));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib2));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSizeInBytes2, &indices2[0], GL_STATIC_DRAW));
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
        glBindVertexArray(vao);
        /* draw points 0-3 from the currently bound VAO with current in-use shader */
        //glDrawArrays(GL_TRIANGLES, 0, sizeof(points) / sizeof(*points));
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        GLCall(glBindVertexArray(vao2));
        GLCall(glDrawElements(GL_TRIANGLES, indices2.size(), GL_UNSIGNED_INT, nullptr));

        /* update other events like input handling */
        glfwPollEvents();
        /* put the stuff we've been drawing onto the display */
        glfwSwapBuffers(window);
    }

    /* close GL context and any other GLFW resources */
    glfwTerminate();
    return 0;
}
