#include "Scene.hpp"

void Scene::Reset()
{
    YOKAI_PARSE::SaveScene("content/"+m_sceneName+".json", m_objectManager, m_lightManager);
    m_objectManager.Clear();
    m_lightManager.Clear();
}
void Scene::SaveScene()
{
    YOKAI_PARSE::SaveScene("content/"+m_sceneName+".json", m_objectManager, m_lightManager);
}
void Scene::LoadScene()
{
    YOKAI_PARSE::LoadScene("content/"+m_sceneName+".json", m_objectManager, m_lightManager);
}
void Scene::SetSceneName(std::string sceneName)
{
    m_sceneName = sceneName;
}
std::string Scene:: GetSceneName()
{
    return m_sceneName;
}