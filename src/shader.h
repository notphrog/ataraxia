#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader 
{
public:

    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        try {
            // open the files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);

            std::stringstream vShaderstream, fShaderStream;
            // read file buffer contents into streams
            vShaderstream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // vlose the files handlers
            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderstream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e) {
            std::cout << "error, shader file not successfully read :(" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // compile the shaders!
        unsigned int vertex, fragment;


        // vert shader creation
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        //frag shader creation
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // the shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        // cleanup!
        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }

    // use the shader
    void use() {
        glUseProgram(ID);
    }

    // utinility form functions
    void setBool (const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt (const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    void setFloat (const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }
    void setVec4(const std::string &name, float r, float g, float b, float a) const {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), r, g, b, a);
    }
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    

    private:
        void checkCompileErrors(unsigned int shader, std::string type) {
            int success;
            char infoLog[1024]; // need double 512 because were doing the frag and the vert
            
            if (type != "PROGRAM") {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "error with shader compilation of type: " << type << "\n" << infoLog << "\n -- --------------- --" << std::endl;
                }
            }
            else {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success) {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "error with program linking of type: " << type << "\n" << infoLog << "\n -- --------------- --" << std::endl;
                }
            }
        }


};
#endif
