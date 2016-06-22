#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
    
    GLFWwindow* window;  
    const char* windowTitle;
    int width, height;
    bool loaded;

public:

    Window(const char* windowTitle, int width, int height);
    ~Window();

    void clear() const;
    void update();

    bool isClosed() const;

    int getWidth() const { return width; };
    int getHeight() const { return height; }
    GLFWwindow* getWindow() const { return window; }
};
