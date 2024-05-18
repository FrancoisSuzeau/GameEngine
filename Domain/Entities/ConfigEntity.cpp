/******************************************************************************************************************************************/
// File : ConfigEntity.cpp
// Purpose : Implementing the ConfigEntity 
/******************************************************************************************************************************************/
#include "ConfigEntity.hpp"

namespace Services {

	ConfigEntity::ConfigEntity() : m_grid_spacing_ratio(4), m_grid_scaling_trigger(5.f), m_render_grid(true), m_bloom_strength(20), m_active_bloom(true), m_render_debug(false), 
		 m_render_skybox(false), m_active_depth(true)
	{
		m_available_skybox =
		{
			"calm_lake",
			"space"
		};

		m_available_textures =
		{
			"container",
			"brique",
			"wall",
			"earth",
			"calisto",
			"cloud",
			"enceladus",
			"europa",
			"ganymede",
			"io",
			"jupiter",
			"mars",
			"mercury",
			"mimas",
			"moon",
			"neptune",
			"saturn",
			"ring1",
			"sun",
			"titan1",
			"titan2",
			"uranus",
			"ring2",
			"venus1",
			"venus2"
		};
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

	void ConfigEntity::SetAvailableSkybox(std::vector<std::string> available_skybox)
	{
		m_available_skybox = available_skybox;
	}

	void ConfigEntity::SetAvailableTextures(std::vector<std::string> available_texure)
	{
		m_available_textures = available_texure;
	}

	std::vector<std::string> ConfigEntity::GetAvailableTextures()
	{
		return m_available_textures;
	}

	std::vector<std::string> ConfigEntity::GetAvailableSkybox()
	{
		return m_available_skybox;
	}

	void ConfigEntity::SetRenderSkybox(bool const render_skybox)
	{
		m_render_skybox = render_skybox;
	}

	bool ConfigEntity::GetRenderSkybox() const
	{
		return m_render_skybox;
	}

	bool ConfigEntity::GetDepth() const
	{
		return m_active_depth;
	}

	void ConfigEntity::SetDepth(bool const depth)
	{
		m_active_depth = depth;
	}

	void ConfigEntity::SetToDefault()
	{
		m_grid_spacing_ratio = 4;
		m_grid_scaling_trigger = 5.f;
		m_render_grid = true;
		m_bloom_strength = 20;
		m_active_bloom = true;
		m_render_debug = false;
		m_render_skybox = false;
		m_active_depth = true;
	}



}