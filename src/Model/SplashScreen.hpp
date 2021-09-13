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
     * @brief Draws Splash Screen
     */
     /**
      * @brief Draws splash screen
      */
    void draw();
    /**
     * @brief Sets the texture for the splash screen
     * @param string - texturePath
     */
    void setTexture(const std::string& texturePath);

    /**
     * @brief Sets up splash screen panel mesh
     */

    void setupPanel(float left, float right, float top, float bottom);

    /**
     * @brief Sets the splash screen as active
     */
    void setActive(bool a);
    /**
     * @brief Sets the splash screen as inactive
     */
    /**
     * @brief Returns whether the splash screen is active
     * @return bool
     */
    bool getActive() const;

  private:
    ///shared_ptr to splash screen panel
    std::shared_ptr<VertexArrayBuffer> vao;
    ///shared_ptr to splash screen texture
    int texture = -1;
    ///is splash screen active
    bool active = false;
};