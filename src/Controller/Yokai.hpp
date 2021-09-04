#pragma once

#include "View/Renderer/Renderer.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "View/Window.hpp"
#include "Model/SplashScreen.hpp"
#include "Controller/Layer.hpp"
#include <spdlog/spdlog.h>
#include "Export.hpp"

//workaround to allow vector of layer pointers
class Layer;
/**
 * @class Yokai
 * @brief A class which ties together all game engine components
 */
class YOKAI_API Yokai 
{
public:
    /**
     * @brief Returns an instance of the engine
     * @return Yokai&
     */
    static Yokai& getInstance();
    /**
     * @brief Initialises the engine
     */
    void Init();
    /**
     * @brief Runs the engine loop
     */
    void Run();
    ///renderer used by engine
    Renderer renderer = {};
    ///window used by the engine
    Window window = {};
    /**
     * @brief Set is Running
     * @param s
     */
    void setIsRunning(bool s);
    /**
     * @brief Gets a layer Pointer
     * @return Layer*
     */
    std::vector<std::shared_ptr<Layer>> getLayer();
    /**
     * @brief Sets active lauer
     * @param a
     */
    void setActiveLayer(int a);
    /**
     * Sets the paused state
     * @param p
     */
    void setIsPaused(bool p);
    /**
     * Return true if engine paused
     * @return bool
     */
    bool getIsPaused() const;

	void addScene(std::shared_ptr<Layer> scene);

private:
    //Singleton pattern requires that all constructors,destructors and copy constructors be private
    /**
     * @brief Registers Engine close event with EMS
     */
    void registerClose();

    /**
     * @brief Privatised Default Constructor
     */
    Yokai() = default;
    /**
     * @brief Privatised Default Destructor
     */
    ~Yokai() = default;
    /**
     * @brief Deleted Copy Constructor
     */
    Yokai(const Yokai&) = delete;

    void InitialiseLogger();
    /**
     * @brief Privatised assign operator
     */
    Yokai& operator =(const Yokai&);
    ///Is engine Running
    bool isRunning = true;
    ///Vector of Scene layers
    std::vector<std::shared_ptr<Layer>> layers;
    ///is paused
    bool isPaused;
    ///active layer
    int activeLayer;
    ///Log sinks for Engine class
    std::vector<spdlog::sink_ptr> sinks;

};