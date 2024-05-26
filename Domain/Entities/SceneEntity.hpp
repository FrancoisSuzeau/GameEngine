/******************************************************************************************************************************************/
// File : SceneEntity.hpp
// Purpose : A definity for the SceneEntity 
/******************************************************************************************************************************************/
#ifndef SceneEntity_H
#define SceneEntity_H

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <map>
#include "../Interfaces/IComponent.hpp"


namespace Services {



	class SceneEntity
	{
	public:
		SceneEntity();
		~SceneEntity();

		std::vector<std::shared_ptr<Component::IComponent>> GetSceneComponents();
		void SetSceneComponents(std::vector<std::shared_ptr<Component::IComponent>> const components);
		void AddComponent(std::shared_ptr<Component::IComponent> const new_component);
		void DeleteComponents();
		void DeleteComponent();

		std::string const GetSelectedSkybox();
		void SetSelectedSkybox(std::string const selected_skybox);
		
		
	private:

		std::vector<std::shared_ptr<Component::IComponent>> m_components;
		std::string m_selected_skybox;
	};
}

#endif