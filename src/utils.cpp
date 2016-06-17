#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <utils.h>

using namespace std;

GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath) {
    
    //Create the shaders
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    string vertexShaderCode = "";
    ifstream vertexShaderStream(vertexFilePath, ios::in);
    if (vertexShaderStream.is_open()) {
        for (string line; getline(vertexShaderStream, line);) {
            vertexShaderCode += line + "\n";
        }
    } else {
        cout << "Vertex shader " << vertexFilePath << " not found" << endl;
        getchar();
        return 0;
    }
        
    string fragmentShaderCode = "";
    ifstream fragmentShaderStream(fragmentFilePath, ios::in);
    if (fragmentShaderStream.is_open()) {
        for (string line; getline(fragmentShaderStream, line);) {
            fragmentShaderCode += line + "\n";
        }
    } else {
        cout << "Fragment shader " << fragmentFilePath << " not found" << endl;
        getchar();
        return 0;
    }
    
    int infoLogLength;

    //Compile the shaders
    cout << "Compiling vertex shader " << vertexFilePath << ":"<< endl;
    char const* vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderID);

    //Check vertex shader
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> vertexErrorMsg(infoLogLength+1);
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexErrorMsg[0]);
        printf("%s\n", &vertexErrorMsg[0]);
    }

    //Compile the fragment shader
    cout << "Compiling fragment shader " << fragmentFilePath << ":"<< endl;
    char const* fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderID);

    //Check fragment shader
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> fragmentErrorMsg(infoLogLength+1);
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentErrorMsg[0]);
        printf("%s\n", &fragmentErrorMsg[0]);
    }

    //Link the program
    cout << "Linking program" << endl;
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    //Check the program
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> programErrorMsg(infoLogLength+1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMsg[0]);
        printf("%s\n", &programErrorMsg[0]);
    }
    //Cleanup
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}
