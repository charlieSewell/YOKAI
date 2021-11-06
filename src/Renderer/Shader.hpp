#pragma once

#include <GL/glew.h>
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
     * @brief Construct a new Compute Shader
     * @param computePath 
     */
    Shader(const char* computePath);
    /**
     * @brief Binds the Shader for use
     */
    void UseShader() const;
    /**
     * @brief Sets a Bool uniform in the shader
     * @param string& - uniformName
     * @param bool - value
     */
    void SetBool(const std::string &uniformName, bool value) const;
    /**
     * @brief Sets an Int uniform in the shader
     * @param string& - uniformName
     * @param int - value
     */
    void SetInt(const std::string &uniformName, int value) const;
    /**
     * @brief Sets a Float uniform in the shader
     * @param string& - uniformName
     * @param float - value
     */
    void SetFloat(const std::string &uniformName, float value) const;
    /**
     * @brief Sets a 2Iv uniform in the shader
     * @param string& - uniformName
     * @param ivec2& - value
     */
    void SetIvec2(const std::string &name, glm::ivec2 screenSize);
    /**
     * @brief Sets a mat4 uniform in the shader
     * @param string& - uniformName
     * @param mat4& - value
     */
    void SetMat4(const std::string &uniformName, const glm::mat4 &mat) const;
    /**
     * @brief Sets a mat4 vec uniform in the shader
     * @param string& - uniformName
     * @param vector<mat4>& - value
     */
    void SetVecMat4(const std::string &uniformName, const std::vector<glm::mat4> &mat) const;
    /**
     * @brief Sets a vec3 uniform in the shader
     * @param string& - uniformName
     * @param vec3& - value
     */
    void SetVec3(const std::string &uniformName, const glm::vec3 &vec) const;
    /**
     * Returns the shadersID
     * @return unsigned int
     */
    unsigned int GetShaderID(){return m_shaderID;}
  private:
      /**
     * @brief Checks for shader Compiler Errors
     * @param shader 
     * @param type 
     */
    void CheckCompileErrors(GLuint shader, std::string type);
    ///Shaders ID
    unsigned int m_shaderID;
};

