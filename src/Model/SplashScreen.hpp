//
// Created by Charlie Sewell on 7/04/2021.
//

#pragma once

#include "Renderer/Renderer.hpp"
/**
 * @class SplashScreen
 * @brief Class that creates Splash screens for rendering
 */
class SplashScreen {
  public:
    /**
     * @brief Constructor for SplashScreen
     * @param string - texturePath
     */
    SplashScreen(const std::string& texturePath);
    /**
     * @brief Draws splash screen
     */
    void Draw();
    /**
     * @brief Sets the texture for the splash screen
     * @param string - texturePath
     */
    void SetTexture(const std::string& texturePath);
    /**
     * @brief Sets up splash screen panel mesh
     */
    void SetupPanel(float left, float right, float top, float bottom);
    /**
     * @brief Sets the splash screen as active
     */
    void SetActive(bool a);
    /**
     * @brief Returns whether the splash screen is active
     * @return bool
     */
    bool GetActive() const;
  private:
    ///shared_ptr to splash screen panel
    std::shared_ptr<VertexArrayBuffer> m_vao;
    ///shared_ptr to splash screen texture
    int m_texture = -1;
    ///is splash screen active
    bool m_active = false;
};