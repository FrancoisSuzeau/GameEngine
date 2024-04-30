/******************************************************************************************************************************************/
// File : ConfigEntity.cpp
// Purpose : Implementing the ConfigEntity 
/******************************************************************************************************************************************/
#include "ConfigEntity.hpp"

namespace Services {

	ConfigEntity::ConfigEntity() : m_grid_spacing_ratio(2), m_grid_scaling_trigger(5.f), m_render_grid(true), m_bloom_strength(0), m_active_bloom(false), m_render_debug(false), m_selected_skybox(std::make_pair("calm_lake", 0))
	{

	}

	ConfigEntity::~ConfigEntity()
	{
		m_created_scenes.clear();
	}

	void ConfigEntity::AddCreatedScene(std::string const created_scene)
	{
		if (std::find(m_created_scenes.begin(), m_created_scenes.end(), created_scene) == m_created_scenes.end())
		{
			m_created_scenes.push_back(created_scene);
		}
	}

	void ConfigEntity::SetCreatedScene(std::vector<std::string> const created_scenes)
	{
		m_created_scenes = created_scenes;
	}

	std::vector<std::string> ConfigEntity::GetCreatedScenes() const
	{
		return m_created_scenes;
	}

	float ConfigEntity::GetGridScalingTrigger() const
	{
		return m_grid_scaling_trigger;
	}

	void ConfigEntity::SetGridScalingTrigger(float const grid_scaling_trigger)
	{
		m_grid_scaling_trigger = grid_scaling_trigger;
	}

	void ConfigEntity::SetGridSpacingRatio(int const grid_scaling_ratio)
	{
		m_grid_spacing_ratio = grid_scaling_ratio;
	}

	int ConfigEntity::GetGridSpacingRatio() const
	{
		return m_grid_spacing_ratio;
	}

	void ConfigEntity::SetRenderGrid(bool const render_grid)
	{
		m_render_grid = render_grid;
	}

	bool ConfigEntity::GetRenderGrid() const
	{
		return m_render_grid;
	}

	int ConfigEntity::GetBloomStrength() const
	{
		return m_bloom_strength;
	}

	void ConfigEntity::SetBloomStrength(int const new_val)
	{
		m_bloom_strength = new_val;
	}

	bool ConfigEntity::GetBloom() const
	{
		return m_active_bloom;
	}

	void ConfigEntity::SetBloom(bool const bloom)
	{
		m_active_bloom = bloom;
	}

	void ConfigEntity::SetRenderDebug(bool const debug)
	{
		m_render_debug = debug;
	}

	bool ConfigEntity::GetRenderDebug() const
	{
		return m_render_debug;
	}

	std::string ConfigEntity::GetSelectedSkybox() const
	{
		return m_selected_skybox.first;
	}

	unsigned int ConfigEntity::GetSelectedSkyboxId() const
	{
		return m_selected_skybox.second;
	}

	void ConfigEntity::SetSelectedSkybox(std::string const selected_skybox)
	{
		m_selected_skybox.first = selected_skybox;
	}

	void ConfigEntity::SetSelectedSkybox(unsigned int const selected_skybox)
	{
		m_selected_skybox.second = selected_skybox;
	}



}