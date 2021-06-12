#pragma once
#include "Controller/Layer.hpp"
#include "Controller/UIManager.hpp"
/**
 * @class DemoScene
 * @brief A demo Scene for Assignment 1
 */
class DemoScene : public Layer
{
  public:
    /**
     * @brief Initialised the Scene
     */
    void Init() override;
    /**
     * @brief Updates the Scene
     */
    void Update(float frameRate) override;
    /**
     * @brief Draws the Scene
     */
    void Draw() override;
    /**
     * @brief Enables the Scene
     */
    void Enable() override;
    /**
     * @brief Disables the Scene
     */
    void Disable() override;
  private:
    ///Terrain Manager for the scene
    TerrainManager terrainManager = {};
    ///Controls SplashScreen
    //SplashScreen* controlsScreen;
    ///Is this scene active
    bool isEnabled = true;
    /**
     * @brief Registers Menu Buttons
     */
    void registerMenuButtons();

    void registerExit();

    SplashScreen *controlsScreen;
};
