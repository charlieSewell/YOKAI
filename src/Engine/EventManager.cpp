//EventManager.cpp

#include "EventManager.hpp"

EMS& EMS::getInstance() 
{
	static EMS instance;
	return instance;

}

void EMS::add(NoReturnEvent event, std::function<void()> func)
{
	m_NoReturnEventList.insert(std::pair<NoReturnEvent, std::function<void()>>(event, func));
}

void EMS::add(NoReturnEvent event, std::function<void(double, double)> func)
{
	if(event == NoReturnEvent::xyLook)
		m_xyLook = func;
}

void EMS::add(ReturnMat4Event event, std::function<glm::mat4()> func)
{
	if (event == ReturnMat4Event::getViewMatrix)
		m_viewMatrix = func;
	if (event == ReturnMat4Event::getPerspective)
		m_perspective = func;
}

void EMS::add(ReturnVec3Event event, std::function<glm::vec3()> func)
{
	if (event == ReturnVec3Event::getPlayerPosition)
		m_playerPosition = func;
}

void EMS::add(ReturnIntEvent event, std::function<int()> func)
{
	if (event == ReturnIntEvent::getPlayerColliderID)
		m_playerColliderID = func;
}

void EMS::fire(NoReturnEvent event) 
{
	//TODO CONNOR: do exception handling / logging after rewrite
	if (!m_NoReturnEventList.empty())
	{
		for (std::multimap<NoReturnEvent, std::function<void()>>::iterator itr = m_NoReturnEventList.begin(); itr != m_NoReturnEventList.end(); ++itr)
		{
			if (itr->first == event)
				(itr->second)();
		}
	}
}

void EMS::fire(NoReturnEvent event, double x, double y)
{
	//TODO CONNOR: do exception handling / logging after rewrite
	if (m_xyLook)
	{
		if (event == NoReturnEvent::xyLook)
			m_xyLook(x, y);
	}
}

glm::mat4 EMS::fire(ReturnMat4Event event)
{
    if (event == ReturnMat4Event::getViewMatrix)
        return m_viewMatrix();
    if (event == ReturnMat4Event::getPerspective)
        return m_perspective();
    return glm::mat4(1.0);
}

glm::vec3 EMS::fire(ReturnVec3Event event)
{
	if (event == ReturnVec3Event::getPlayerPosition)
		return m_playerPosition();

	return glm::vec3(-1,-1,-1);
}

int EMS::fire(ReturnIntEvent event)
{
	if (event == ReturnIntEvent::getPlayerColliderID)
		return m_playerColliderID();

	return -1;
}