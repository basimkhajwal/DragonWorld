// Include standard headers
#include <cstdio>
#include <cstdlib>

// Include GLEW and GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Project headers
#include <utils.h>
using namespace std;

GLFWwindow* window;

int main( void ) {
	// Initialise GLFW
	if( !glfwInit() ) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

    /* Initialise window constraints */
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(800,600, "Dragon World", NULL, NULL);
	if (window == NULL){
		fprintf( stderr, "Failed to open GLFW window\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
    glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

    //Load shaders
    GLuint programID = LoadShaders("../src/shaders/SimpleVertexShader.txt", "../src/shaders/SimpleFragmentShader.txt");

    GLfloat triangleVBOData[] = {
        -0.9f, -0.5f, 0.0f,
        -0.0f, -0.5f, 0.0f,
        -0.45f, 0.5f, 0.0f
    };

    GLuint vertexArrayId, vertexBuffer;
    glGenVertexArrays(1, &vertexArrayId);
    glGenBuffers(1, &vertexBuffer);

    //Bind buffer
    glBindVertexArray(vertexArrayId);

    // Load triangle buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVBOData), triangleVBOData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	do{
		// Clear the screen.
        glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
		glClear( GL_COLOR_BUFFER_BIT);

		// Draw nothing
        glUseProgram(programID);
        glBindVertexArray(vertexArrayId);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
