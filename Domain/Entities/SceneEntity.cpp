/******************************************************************************************************************************************/
// File : SceneEntity.cpp
// Purpose : Implementing the SceneEntity 
/******************************************************************************************************************************************/
#include "SceneEntity.hpp"

namespace Services {

	SceneEntity::SceneEntity() : m_selected_skybox("")
	{

	}

	SceneEntity::~SceneEntity()
	{

	}

	std::vector<std::shared_ptr<Component::IComponent>> SceneEntity::GetSceneComponents() const
	{
		return m_components;
	}

	void SceneEntity::SetSceneComponents(std::vector<std::shared_ptr<Component::IComponent>> const components)
	{
		m_components = components;
	}

	void SceneEntity::AddComponent(std::shared_ptr<Component::IComponent> const new_component)
	{
		if (new_component)
		{
			m_components.push_back(new_component);
		}
	}

	void SceneEntity::DeleteComponents()
	{
		for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = m_components.begin(); it != m_components.end(); it++)
		{
			if (it[0])
			{
				it[0]->Clean();
				it[0].reset();
			}
		}
		m_components.clear();
	}

	void SceneEntity::DeleteComponent()
	{
		auto to_remove = std::remove_if(m_components.begin(), m_components.end(), [](const std::shared_ptr<Component::IComponent> selectable_component) {return selectable_component->GetSelected() == true; });
		m_components.erase(to_remove, m_components.end());
	}

	std::string const SceneEntity::GetSelectedSkybox()
	{
		return m_selected_skybox;
	}

	void SceneEntity::SetSelectedSkybox(std::string const selected_skybox)
	{
		m_selected_skybox = selected_skybox;
	}



}