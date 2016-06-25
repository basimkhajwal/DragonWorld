#include <cstdio>
#include <Window.h>

Window::Window(const char* title, int width, int height) {

    /* Set state variables*/
    this->windowTitle = title;
    this->width = width;
    this->height = height;

    /* Initally loaded is false until all checks have been passed*/
    this->loaded = false;

    /* Initliase window */
	// Initialise GLFW
    printf("WINDOW:\tLoading GLFW...\n");
	if( !glfwInit() ) {
        printf("WINDOW:\tERROR: failed to initialize GLFW\n" );
		getchar();
		return;
	}

    /* Initialise window constraints */
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
    printf("WINDOW:\tCreating window sized\n");
	window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
	if (window == NULL){
        printf("WINDOW:\tERROR: Failed to open GLFW window\n");
		getchar();
		return;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
    printf("WINDOW:\tInitialising GLEW...\n");
    glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("WINDOW:\tERROR: Failed to initialize GLEW\n");
		getchar();
		return;
	}

    printf("WINDOW:\tWindow loaded successfully\n");
    loaded = true;
}

Window::~Window() {
    printf("WINDOW:\tTerminating window\n");
    glfwTerminate();
}

void Window::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

bool Window::isClosed() const {
    return !loaded
        || glfwWindowShouldClose(window) == 1
        || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;    
}
