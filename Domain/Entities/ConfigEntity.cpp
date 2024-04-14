/******************************************************************************************************************************************/
// File : ConfigEntity.cpp
// Purpose : Implementing the ConfigEntity 
/******************************************************************************************************************************************/
#include "ConfigEntity.hpp"

namespace Services {

	ConfigEntity::ConfigEntity() : m_grid_scaling_ratio(4), m_grid_scaling_trigger(25.f), m_render_grid(false)
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

	void ConfigEntity::SetGridScalingRatio(int const grid_scaling_ratio)
	{
		m_grid_scaling_ratio = grid_scaling_ratio;
	}

	int ConfigEntity::GetGridScalingRatio() const
	{
		return m_grid_scaling_ratio;
	}

	void ConfigEntity::SetRenderGrid(bool const render_grid)
	{
		m_render_grid = render_grid;
	}

	bool ConfigEntity::GetRenderGrid() const
	{
		return m_render_grid;
	}

}