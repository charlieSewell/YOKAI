#pragma once

#include <functional>
#include <map>
#include <glm/glm.hpp>

//TODO CONNOR: KILL

enum class NoReturnEvent
{
	moveForward,
	moveBackward,
	moveLeft,
	moveRight,
	jump,
	moveDown,
	increaseSpeed,
	xyLook,
    closePressed,
    closeReleased,
	togglePhysicsPressed,
	togglePhysicsReleased,
	toggleWireFramePressed,
	toggleWireFrameReleased,
    toggleMenuPressed,
    toggleMenuReleased,
    mouseClicked,
    mouseReleased,
	mouse2Clicked,
	mouse2Released,
    reloadPressed,
    reloadReleased,
	sprintPressed,
	sprintReleased,
	meleePressed,
	meleeReleased,
    pausePressed,
    pauseReleased,
    ExitPressed
};

enum class ReturnMat4Event
{
    getViewMatrix,
    getPerspective
};

enum class ReturnVec3Event
{
	getPlayerPosition
};

enum class ReturnIntEvent
{
	getPlayerColliderID
};

/**
 * @class EMS
 * @brief Singleton Class Defining The Event Management System
 */
class EMS
{
  public:
    /**
     * @brief Gets the instance of the EMS
     * @return EMS&
     */
    static EMS& getInstance();

    ///Deleted copy constructor
	EMS(EMS const&)			 = delete;

    ///Deleted = operator
	void operator=(EMS const&) = delete;

    /**
     * @brief Adds an input Event callback
     * @param InputEvent - event
     * @param function<void()> - func
     */
	void add(NoReturnEvent event, std::function<void()> func);

    /**
     * @brief Adds a Render Event callback
     * @param RenderEvent - event
     * @param function<mat4()> - func
     */
    void add(ReturnMat4Event event, std::function<glm::mat4()> func);

    /**
     * @brief Adds a Render Event callback
     * @param InputEvent - event
     * @param function<void(double x, double y)> - func
     */
	void add(NoReturnEvent event, std::function<void(double x, double)> func);

	/**
	 * @brief Adds a Event callback
	 * @param InputEvent - event
	 * @param function<glm::vec3()> - func
	 */
	void add(ReturnVec3Event event, std::function<glm::vec3()> func);

	/**
	 * @brief Adds a Event callback
	 * @param InputEvent - event
	 * @param function<glm::vec3()> - func
	 */
	void add(ReturnIntEvent event, std::function<int()> func);

    /**
     * @brief Fires an Input Event
     * @param InputEvent - event
     */
	void fire(NoReturnEvent event);

    /**
     * @brief Fires a Render Event
     * @param RenderEvent - event
     * @return mat4
     */
    glm::mat4 fire(ReturnMat4Event event);

    /**
     * @brief Fires non returning event with Data
     * @param InputEvent event
     * @param double - x
     * @param double - y
     */
	void fire(NoReturnEvent event, double x, double y);

	/**
	 * @brief Fires a Render Event
	 * @param RenderEvent - event
	 * @return mat4
	 */
	glm::vec3 fire(ReturnVec3Event event);

	int fire(ReturnIntEvent event);

  private:
      ///Privatised constructor of EMS
	  EMS() {}

      ///Multimap storing input events against their function pointers
	  std::multimap<NoReturnEvent, std::function<void()>> m_NoReturnEventList;

      ///Function pointer for mouse Look
	  std::function<void(double, double)> m_xyLook;

      ///Function pointer for View Matrix
      std::function<glm::mat4(void)> m_viewMatrix;

      ///Function pointer for Perspective matrix
      std::function<glm::mat4(void)> m_perspective;
      ///Function pointer for player position
	  std::function<glm::vec3(void)> m_playerPosition;
	  ///Function pointer for player collider
	  std::function<int(void)> m_playerColliderID;
};
