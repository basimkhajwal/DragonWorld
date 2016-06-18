#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

/*
 * Utility class to manage a vertex and fragment shader
 * by providing loading and usage abstractions
 * */
class ShaderProgram {

    /*
     * Load the specified source as the shader type
     * */
    GLuint loadShader(const char* source, GLenum type);

    /*
     * Read the whole file into memory as a
     * std::string
     * */
    string readFile(const char* source);

    GLuint programID, fragmentID, vertexID;

public:

    /*
     * Load the file paths into memory and initialise
     * the ShaderProgram
     * */
    ShaderProgram(const char* vertexFile, const char* fragmentFile);

    /*
     * Unbind, dispose and free the memory of this shader
     * */
    ~ShaderProgram();

    void bind();
    void unbind();
};
