// Include standard headers
#include <cstdio>
#include <cstdlib>
using namespace std;

// Include GLEW and GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//GLM library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

// Project headers
#include <ShaderProgram.h>
#include <Window.h>

mat4 projection, view, model, mvp;
vec3 cameraPosition(0, 0, 10);

void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mode) {

    if (action != GLFW_PRESS) return;

    if (key == GLFW_KEY_Q) cameraPosition.x++;
    if (key == GLFW_KEY_W) cameraPosition.x--;
    if (key == GLFW_KEY_A) cameraPosition.y++;
    if (key == GLFW_KEY_S) cameraPosition.y--;
    if (key == GLFW_KEY_Z) cameraPosition.z++;
    if (key == GLFW_KEY_X) cameraPosition.z--;
    view = lookAt(cameraPosition, vec3(0,0,0), vec3(0,1,0));
    mvp = projection * view * model;
}

/* Cube vertex data */
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

/* UV data for the cube */
static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

int main( void ) {
	   
    Window window = Window("Dungeon Warrior", 1000, 600);
    glfwSetKeyCallback(window.getWindow(), keyCallback);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    //Load shaders
    ShaderProgram simpleShader("assets/shaders/SimpleVertexShader.txt", "assets/shaders/SimpleFragmentShader.txt");

    //Setup glm stuff
    projection = perspective(radians(45.0f), 4.0f/3.0f, 0.1f, 100.0f);
    view = lookAt(cameraPosition, vec3(0,0,0), vec3(0, 1, 0));
    model = mat4(1.0f);
    mvp = projection * view * model;

    GLuint matrixID = glGetUniformLocation(simpleShader.getProgramID(), "mvp");

    GLuint vertexArrayId, vertexBuffer, colorBuffer;
    glGenVertexArrays(1, &vertexArrayId);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &colorBuffer);

    glBindVertexArray(vertexArrayId);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

	while (!window.isClosed()) {
        window.clear();

		// Draw the triangles
        simpleShader.bind();

        //Set the uniform mvp matrix
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]); 

        glBindVertexArray(vertexArrayId);
        glDrawArrays(GL_TRIANGLES, 0, 12*3);
        glBindVertexArray(0);
        simpleShader.unbind();

        window.update();
    }

	return 0;
}
