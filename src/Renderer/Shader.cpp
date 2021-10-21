//
// Created by Charlie Sewell on 13/01/2021.
//

#include "Shader.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <spdlog/spdlog.h>
Shader::Shader(const char *vertexPath, const char *fragmentPath) 
{
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    try
    {
        std::stringstream vertexShaderSS;
        std::stringstream fragmentShaderSS;
        std::ifstream vertexShaderFile;
        std::ifstream fragmentShaderFile;
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);

        vertexShaderSS << vertexShaderFile.rdbuf();
        fragmentShaderSS << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();
        vertexShaderSource = vertexShaderSS.str();
        fragmentShaderSource = fragmentShaderSS.str();

    }
    catch(std::ifstream::failure& e)
    {
        std::string error("File failed to read: ");
        error.append(e.what());
        SPDLOG_ERROR(error);
    }

    const char* vertexShaderCode = vertexShaderSource.c_str();
    const char* fragmentShaderCode = fragmentShaderSource.c_str();
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::string error("Vertex shader compilation failed: ");
        error.append(infoLog);
        SPDLOG_ERROR(error);
    }
    //create fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::string error("Fragment shader compilation failed: ");
        error.append(infoLog);
        SPDLOG_ERROR(error);
    }
    //create shader program
    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderID, 512, nullptr, infoLog);
        std::string error("ERROR::SHADER::PROGRAM::LINKING_FAILED: ");
        error.append(infoLog);
        SPDLOG_ERROR(error);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
Shader::Shader(const GLchar* computePath) {
	std::string computeCode;
	std::ifstream computeShaderFile;

	// Ensure that ifstream objects can throw exceptions
	computeShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// Open file
		computeShaderFile.open(computePath);
		std::stringstream cShaderStream;

		// Read file;s buffer contents into streams
		cShaderStream << computeShaderFile.rdbuf();

		// close file handlers
		computeShaderFile.close();

		// Convert stream to string
		computeCode = cShaderStream.str();
	}
	catch (std::ifstream::failure e) {
        std::string error("Failed to read file: ");
        error.append(e.what());
        SPDLOG_ERROR(error);
	}

	// Then compile shader
	const GLchar* computeShaderCode = computeCode.c_str();

	GLuint compute;

	// Compute shader
	compute = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(compute, 1, &computeShaderCode, NULL);
	glCompileShader(compute);
	CheckCompileErrors(compute, "COMPUTE");

	// Create the shader program
	shaderID = glCreateProgram();
	glAttachShader(shaderID, compute);

	glLinkProgram(shaderID);
	CheckCompileErrors(shaderID, "PROGRAM");

	// No longer need the shaders, delete them
	glDeleteShader(compute);
}
void Shader::useShader() const
{
    glUseProgram(shaderID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}
void Shader::setIvec2(const std::string &name, glm::ivec2 screenSize)
{
    glUniform2iv(glGetUniformLocation(shaderID, name.c_str()), 1, &screenSize[0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat)const 
{
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setVecMat4(const std::string &name, const std::vector<glm::mat4> &mat) const
{
    if (!mat.empty()) {
        glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), mat.size(), GL_FALSE, glm::value_ptr(mat[0]));
    }
}
void Shader::setVec3(const std::string &name, const glm::vec3 &vec) const 
{
    glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &vec[0]);
}
void Shader::CheckCompileErrors(GLuint shader, std::string type) {
	GLint success;
	GLchar infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::string error("| ERROR::::SHADER-COMPILATION-ERROR of type: " + type + " | " + infoLog);
            SPDLOG_INFO(error);
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::string error("| ERROR::::PROGRAM-LINKING-ERROR of type: " + type + " | " + infoLog);
            SPDLOG_INFO(error);
		}
	}
}