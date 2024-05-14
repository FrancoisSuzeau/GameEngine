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
#include <map>
#include "../Interfaces/IComponent.hpp"


namespace Services {



	class SceneEntity
	{
	public:
		SceneEntity();
		~SceneEntity();

		std::vector<std::shared_ptr<Component::IComponent>> GetSceneComponents() const;
		void SetSceneComponents(std::vector<std::shared_ptr<Component::IComponent>> const components);
		void AddComponent(std::shared_ptr<Component::IComponent> const new_component);
		void DeleteComponents();
		void DeleteComponent();
		
	private:

		std::vector<std::shared_ptr<Component::IComponent>> m_components;
	};
}

#endif