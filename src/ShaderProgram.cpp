#include <vector>
#include <fstream>
#include <cstdio>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ShaderProgram.h>

using namespace std;

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) {

    this->vertexID = this->loadShader(vertexFile, GL_VERTEX_SHADER);
    this->fragmentID = this->loadShader(fragmentFile, GL_FRAGMENT_SHADER);
    
    if (this->vertexID == 0 || this->fragmentID == 0) {
        printf("Could not load program\n");
        return;
    }

    printf("Creating and linking program....\n");
    this->programID = glCreateProgram();
    glAttachShader(this->programID, this->vertexID);
    glAttachShader(this->programID, this->fragmentID);
    glLinkProgram(this->programID);
    
    GLint infoLogLength;
    glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> errorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programID, 512, NULL, &errorMessage[0]);    
        printf("Error linking program:\n%s\n", &errorMessage[0]);
        return;
    }

    //Cleanup
    glDetachShader(this->programID, this->vertexID);
    glDetachShader(this->programID, this->fragmentID);
    glDeleteShader(this->vertexID);
    glDeleteShader(this->fragmentID);
}

ShaderProgram::~ShaderProgram() {
    this->unbind();
    glDeleteProgram(this->programID);
}

void ShaderProgram::bind()   {  glUseProgram(this->programID); }
void ShaderProgram::unbind() {  glUseProgram(0);               }

GLuint ShaderProgram::loadShader(const char* source, GLenum shaderType) {
    string shaderFile = this->readFile(source);

    if (shaderFile == "") {
        printf("Could not load shader\n");
        return 0;
    }

    GLuint shaderID = glCreateShader(shaderType);
    
    printf("Compiling shader %s....\n", source);
    char const* sourcePointer = shaderFile.c_str();
    glShaderSource(shaderID, 1, &sourcePointer, NULL);
    glCompileShader(shaderID);

    int infoLogLength;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
        vector<char> errorMessage(infoLogLength + 1);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &errorMessage[0]);
        printf("Error compiling shader %s\n%s\n", source, &errorMessage[0]);
        return 0;
    }

    return shaderID;
}

string ShaderProgram::readFile(const char* source) {
    string contents = "";
    ifstream fin(source, ios::in);

    if (!fin.is_open()) {
        printf("Error reading file %s\n", source);
        return "";
    }

    for (string line; getline(fin, line);) {
        contents += line + "\n";
    }

    return contents;
}
