//
// Created by Charlie Sewell on 9/03/2021.
//
#include "OpenGLDataTypes.hpp"

#include <memory>
#include "Renderer/OpenGL/FileIO.hpp"
#include <spdlog/spdlog.h>

OpenGLTexture::OpenGLTexture(const std::string path)
{
    std::string filename = std::string(path);
    glGenTextures(1, &m_textureID);
    int width, height, nrComponents;
    unsigned char *data = TextureFromFile(filename,width,height,nrComponents,0);
    if (data)
    {
        GLenum format = 0;
        try{
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

        }
        catch (std::exception& e) {
            
            SPDLOG_ERROR(e.what());
        }

        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE,data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
        FreeTextureData(data);
        SPDLOG_INFO("Texture Loaded: "+  path);
    }
    else
    {
        SPDLOG_ERROR("Texture failed to load at path: "+  path);
        FreeTextureData(data);
    }
}

OpenGLTexture::~OpenGLTexture()
{
    glDeleteTextures(1,&m_textureID);
}

void OpenGLTexture::Bind(size_t slot) 
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

}

void OpenGLTexture::UnBind(size_t slot) 
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D,0);
}
int OpenGLTexture::GetID()
{
    return m_textureID;
}

OpenGLVertexBuffer::OpenGLVertexBuffer(std::vector<Vertex> &vertices)
{
    glGenBuffers(1,&m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER,m_vboID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1,&m_vboID);
}

void OpenGLVertexBuffer::Bind() 
{
    glBindBuffer(GL_ARRAY_BUFFER,m_vboID);
}

void OpenGLVertexBuffer::UnBind() 
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

OpenGLIndexBuffer::OpenGLIndexBuffer(std::vector<unsigned int> &indices)
{
    glGenBuffers(1,&m_ibID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1,&m_ibID);
}

void OpenGLIndexBuffer::Bind() 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibID);
}

void OpenGLIndexBuffer::UnBind() 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

OpenGLVertexArrayBuffer::OpenGLVertexArrayBuffer(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    glGenVertexArrays(1,&m_vaoID);
    glBindVertexArray(m_vaoID);
    m_vertexBuffer = std::make_shared<OpenGLVertexBuffer>(vertices);
    m_indexBuffer = std::make_shared<OpenGLIndexBuffer>(indices);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (0));
    // vertex normals pointer setup
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normal));
    // vertex coords pointer setup
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, textureCoords));
    // Tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tangent));
	// Bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, biTangent));
    // bone pointer setup
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (GLvoid*) offsetof(Vertex, boneIDs));
    //bone weight setup
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, boneWeights));
    
    glBindVertexArray(0);
}

OpenGLVertexArrayBuffer::~OpenGLVertexArrayBuffer()
{
    glDeleteVertexArrays(1, &m_vaoID);
}

void OpenGLVertexArrayBuffer::Bind() 
{
    glBindVertexArray(m_vaoID);
}

void OpenGLVertexArrayBuffer::UnBind() 
{
    glBindVertexArray(0);
}