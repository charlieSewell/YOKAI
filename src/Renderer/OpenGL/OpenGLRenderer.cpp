//
// Created by charl on 1/03/2021.
//
#pragma once
#include "OpenGLRenderer.hpp"
#include "Engine/TextureManager.hpp"
#include <glm/gtx/string_cast.hpp>
void OpenGLRenderer::Init() 
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SPDLOG_ERROR("Failed to initialize GLEW");
        return;
    }
    glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

    SCREEN_SIZE.x = 1920;
    SCREEN_SIZE.y = 1080;

	workGroupsX = (SCREEN_SIZE.x + (SCREEN_SIZE.x % 16)) / 16;
	workGroupsY = (SCREEN_SIZE.y + (SCREEN_SIZE.y % 16)) / 16;

	depthShader = new Shader("content/Shaders/depth.vert", "content/Shaders/depth.frag");
	lightAccumulationShader = new Shader("content/Shaders/light_accumulation.vert", "content/Shaders/light_accumulation.frag");
	lightCullingShader = new Shader("content/Shaders/light_culling.comp");
	hdr = new Shader("content/Shaders/hdr.vert", "content/Shaders/hdr.frag");
    
	glm::mat4 perspective = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 300.0f);
	depthShader->useShader();
	depthShader->setMat4("projection",perspective);

	lightCullingShader->useShader();
    lightCullingShader->setInt("lightCount",NUM_LIGHTS);
	lightCullingShader->setMat4("projection",perspective);
	//lightCullingShader->setIvec2("screenSize",SCREEN_SIZE);
    glUniform2iv(glGetUniformLocation(lightCullingShader->getShaderID(), "screenSize"), 1, &SCREEN_SIZE[0]);

    lightAccumulationShader->useShader();
    lightAccumulationShader->setInt("numberOfTilesX", workGroupsX);
	lightAccumulationShader->setMat4("projection",perspective);
	lightAccumulationShader->setInt("numberOfLights",NUM_LIGHTS);

    SPDLOG_INFO("OpenGL version: {}",glGetString(GL_VERSION));
	SPDLOG_INFO("GLSL version: {}",glGetString(GL_SHADING_LANGUAGE_VERSION));
	SPDLOG_INFO("Vendor: {}",glGetString(GL_VENDOR));
	SPDLOG_INFO("Renderer: {}", glGetString(GL_RENDERER));
    if (!GLEW_VERSION_4_5) 
    {
		SPDLOG_ERROR("OpenGL version be >= 4.5");
       // throw std::runtime_error("OpenGL 4.5 API is not available.");
	}
    // Define work group sizes in x and y direction based off screen size and tile size (in pixels)
	workGroupsX = (SCREEN_SIZE.x + (SCREEN_SIZE.x % 16)) / 16;
	workGroupsY = (SCREEN_SIZE.y + (SCREEN_SIZE.y % 16)) / 16;
	size_t numberOfTiles = workGroupsX * workGroupsY;
	// Generate our shader storage buffers
	glGenBuffers(1, &lightBuffer);
	glGenBuffers(1, &visibleLightIndicesBuffer);

	// Bind light buffer
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, lightBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_LIGHTS * sizeof(PointLight), NULL, GL_DYNAMIC_DRAW);

	// Bind visible light indices buffer
    
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, visibleLightIndicesBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, numberOfTiles * sizeof(VisibleIndex) * NUM_LIGHTS, NULL, GL_DYNAMIC_DRAW);


	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    
    std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, lightBuffer);
	PointLight *pointLights = (PointLight*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE);

	for (int i = 0; i < NUM_LIGHTS; i++) {
		PointLight &light = pointLights[i];
		light.position = glm::vec4(RandomPosition(dis, gen), 1.0f);
		light.color = glm::vec4(1.0f + dis(gen), 1.0f + dis(gen), 1.0f + dis(gen), 1.0f);
		light.paddingAndRadius = glm::vec4(glm::vec3(0.0f), 30.0f);
	}

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	SetupDepthMap();
    SetupHDRBuffer();
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
    SPDLOG_INFO("Renderer Initialised: Using OpenGL");

}
glm::vec3 OpenGLRenderer::RandomPosition(std::uniform_real_distribution<> dis, std::mt19937 gen) {
	glm::vec3 position = glm::vec3(0.0);
	for (int i = 0; i < 3; i++) {
		float min = LIGHT_MIN_BOUNDS[i];
		float max = LIGHT_MAX_BOUNDS[i];
		position[i] = (GLfloat)dis(gen) * (max - min) + min;
	}

	return position;
}
void OpenGLRenderer::DeInit() 
{
    ImGui_ImplOpenGL3_Shutdown();
}
void OpenGLRenderer::DrawQuad() 
{
	if (quadVAO == 0) 
    {
		GLfloat quadVertices[] = {
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};

		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
void OpenGLRenderer::SetupDepthMap()
{
    glGenFramebuffers(1, &depthMapFBO);

	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCREEN_SIZE.x, SCREEN_SIZE.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void OpenGLRenderer::SetupHDRBuffer()
{
    // Create a floating point HDR frame buffer and a floating point color buffer (as a texture)
	
	glGenFramebuffers(1, &hdrFBO);

	
	glGenTextures(1, &colorBuffer);
	glBindTexture(GL_TEXTURE_2D, colorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCREEN_SIZE.x, SCREEN_SIZE.y, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// It will also need a depth component as a render buffer, attached to the hdrFBO
	
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_SIZE.x, SCREEN_SIZE.y);

	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void OpenGLRenderer::Clear() 
{
    glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
void OpenGLRenderer::UpdateLights() {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, lightBuffer);
	PointLight *pointLights = (PointLight*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE);

	for (int i = 0; i < NUM_LIGHTS; i++) {
		PointLight &light = pointLights[i];
		float min = LIGHT_MIN_BOUNDS[1];
		float max = LIGHT_MAX_BOUNDS[1];

		light.position.y = fmod((light.position.y + (-4.5f * 0.1) - min + max), max) + min;
	}

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}


void OpenGLRenderer::ToggleWireFrame() 
{
    if(isWireFrame)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        isWireFrame = false;
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        isWireFrame = true;
    }
}

void OpenGLRenderer::DrawArrays(VertexArrayBuffer& VAO, size_t indicesSize)
{
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);

}
void OpenGLRenderer::DrawScene()
{
    glm::mat4 view = EMS::getInstance().fire(ReturnMat4Event::getViewMatrix);
    glm::mat4 inverseview = glm::inverse(view);
    glm::vec3 viewpos = glm::vec3(inverseview[3].x,inverseview[3].y,inverseview[3].z);
    UpdateLights();
	depthShader->useShader();
    depthShader->setMat4("view",view);

    //DEPTH PASS
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	for(auto& drawItem : drawQueue)
    {
        depthShader->setMat4("model",drawItem.transform);
        DrawMesh(depthShader,drawItem.mesh);
    }
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    lightCullingShader->useShader();
    lightCullingShader->setMat4("view",view);
	lightCullingShader->setInt("depthMap", 4);
    // Bind depth map texture to texture location 4 (which will not be used by any model texture)
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, lightBuffer);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, visibleLightIndicesBuffer);   

    // Dispatch the compute shader, using the workgroup values calculated earlier
	glDispatchCompute(workGroupsX, workGroupsY, 1);
    
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	// Unbind the depth map
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, 0);
	
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	lightAccumulationShader->useShader();
    lightAccumulationShader->setMat4("view",view);
	lightAccumulationShader->setVec3("viewPosition",viewpos);

    for(auto& drawItem : drawQueue)
    {
        lightAccumulationShader->setMat4("model",drawItem.transform);
        DrawMesh(lightAccumulationShader,drawItem.mesh);
    }
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Weirdly, moving this call drops performance into the floor
	hdr->useShader();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorBuffer);
    hdr->setFloat("exposure", 1.0f);
	DrawQuad();
		
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, 0);
	
    drawQueue.clear();
}
void OpenGLRenderer::DrawGui() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void OpenGLRenderer::SetDepthTesting(bool isEnabled)
{
    if(isEnabled)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
        {
        glDisable(GL_DEPTH_TEST);
    }
}
 const void OpenGLRenderer::DrawMesh(Shader* shader,Mesh* mesh)
 {
     unsigned int diffuseNr = 1;
     unsigned int specularNr = 1;
     unsigned int normalNumber = 1;
	 unsigned int heightNumber = 1;
     auto& textures = mesh->getTextures();
     for(int i = 0; i < textures.size(); i++)
     {
         TextureManager::getInstance().getTexture(textures[i].texture)->Bind(i);
         std::string number;
         std::string name = textures[i].type;
         if(name == "texture_diffuse")
             number = std::to_string(diffuseNr++);
         else if(name == "texture_specular")
             number = std::to_string(specularNr++);
         else if(name == "texture_normal")
             number = std::to_string(normalNumber++);
         else if(name == "texture_height")
             number = std::to_string(heightNumber++);
        shader->setInt((name + number).c_str(), i);
     }

     DrawArrays(*mesh->GetVAO(),mesh->getIndices()->size());

    // Reset to defaults
	for (size_t i = 0; i < textures.size(); i++) {
		TextureManager::getInstance().getTexture(textures[i].texture)->UnBind(i);
	}
     
}
void OpenGLRenderer::SubmitDraw(DrawItem drawItem)
{
    drawQueue.push_back(drawItem);
}