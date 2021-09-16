#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
/**
 * @class Shader
 * @brief class used for createing GLSL shaders
 */
class Shader 
{
  public:
    /**
     * @brief Constructor for a shader
     * @param const char* - vertexPath
     * @param const char* - fragmentPath
     */
    Shader(const char* vertexPath, const char* fragmentPath);
    /**
     * @brief Binds the Shader for use
     */
    void useShader() const;
    /**
     * @brief Sets a Bool uniform in the shader
     * @param string& - uniformName
     * @param bool - value
     */
    void setBool(const std::string &uniformName, bool value) const;
    /**
     * @brief Sets an Int uniform in the shader
     * @param string& - uniformName
     * @param int - value
     */
    void setInt(const std::string &uniformName, int value) const;
    /**
     * @brief Sets a Float uniform in the shader
     * @param string& - uniformName
     * @param float - value
     */
    void setFloat(const std::string &uniformName, float value) const;
    /**
     * @brief Sets a mat4 uniform in the shader
     * @param string& - uniformName
     * @param mat4& - value
     */
    void setMat4(const std::string &uniformName, const glm::mat4 &mat) const;
    /**
     * @brief Sets a mat4 vec uniform in the shader
     * @param string& - uniformName
     * @param vector<mat4>& - value
     */
    void setVecMat4(const std::string &uniformName, const std::vector<glm::mat4> &mat) const;
    /**
     * @brief Sets a vec3 uniform in the shader
     * @param string& - uniformName
     * @param vec3& - value
     */
    void setVec3(const std::string &uniformName, const glm::vec3 &vec) const;

    /**
     * Returns the shadersID
     * @return unsigned int
     */
    unsigned int getShaderID(){return shaderID;}

  private:
    ///Shaders ID
    unsigned int shaderID;
};

