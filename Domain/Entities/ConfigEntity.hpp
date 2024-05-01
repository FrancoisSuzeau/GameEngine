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
#include <map>


namespace Services {



	class ConfigEntity 
	{
	public:
		ConfigEntity();
		~ConfigEntity();

		void AddCreatedScene(std::string const created_scene);
		void SetCreatedScene(std::vector<std::string> const created_scenes);
		std::vector<std::string> GetCreatedScenes() const;
		float GetGridScalingTrigger() const;
		void SetGridScalingTrigger(float const grid_scaling_trigger);
		void SetGridSpacingRatio(int const grid_scaling_ratio);
		int GetGridSpacingRatio() const;
		void SetRenderGrid(bool const render_grid);
		bool GetRenderGrid() const;
		int GetBloomStrength() const;
		void SetBloomStrength(int const new_val);
		bool GetBloom() const;
		void SetBloom(bool const bloom);
		void SetRenderDebug(bool const debug);
		bool GetRenderDebug() const;
		std::string GetSelectedSkybox() const;
		unsigned int GetSelectedSkyboxId() const;
		void SetSelectedSkybox(std::string const selected_skybox);
		void SetSelectedSkybox(unsigned int const selected_skybox);
		void SetAvailableSkybox(std::vector<std::string> available_skybox);
		void SetAvailableSkybox(std::string const map_id, unsigned int const texture_id);
		std::vector<std::string> GetAvailableSkybox();
		void SetRenderSkybox(bool const render_skybox);
		bool GetRenderSkybox() const;

		
	private:
		
		std::vector<std::string> m_created_scenes;
		float m_grid_scaling_trigger;
		int m_grid_spacing_ratio;
		bool m_render_grid;
		int m_bloom_strength;
		bool m_active_bloom;
		bool m_render_debug;
		std::pair<std::string, unsigned int> m_selected_skybox;
		std::map<std::string, unsigned int> m_available_skybox;
		bool m_render_skybox;

	};
}

#endif