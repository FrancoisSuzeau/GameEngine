/******************************************************************************************************************************************/
// File : ConfigEntity.hpp
// Purpose : A definity for the ConfigEntity 
/******************************************************************************************************************************************/
#ifndef CONFIGENTITY_H
#define CONFIGENTITY_H

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

namespace Services {



	class ConfigEntity 
	{
	public:
		ConfigEntity();
		~ConfigEntity();

		void AddCreatedScene(std::string const created_scene);
		void SetCreatedScene(std::vector<std::string> const created_scenes);
		std::vector<std::string> GetCreatedScenes() const;

		
	private:
		
		std::vector<std::string> m_created_scenes;


	};
}

#endif