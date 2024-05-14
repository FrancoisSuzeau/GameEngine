/******************************************************************************************************************************************/
// File : StateService.cpp
// Purpose : Implementing service Opengl / SDL  initialisation
/******************************************************************************************************************************************/
#include "StateService.hpp"

namespace Services
{
	StateService::StateService() : m_show_metrics(false), m_show_tools(false), m_exit(false), m_height(0), m_width(0), m_show_app_info(false),
		m_show_style_editor(false), m_show_event(false), m_current_filename(""), m_continued(false), m_projection_perspective_matrix(glm::mat4(1.f)),
		m_show_save_as(false), m_show_confirm(false), m_mouse_clicked(false), m_show_context_menu(false), m_selected_component(nullptr), m_popup_hovered(false),
		m_previous_selected_component_color(1.f), m_pannel_view(Constants::NONE), m_scaling_way(Enums::ScallingWay::EMPTY), m_actualize(false), m_far_plane(100.f), m_near_plane(0.1f),
		sq_texture_id(0), m_texture_id(0), m_projection_ortho_matrix(glm::mat4()), m_fb_type(Enums::FramebufferType::COLORBUFFER)
	{
	}

	void StateService::Init()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			std::shared_ptr<Services::GraphicInitializerService> graph_service_init = container->GetReference<Services::GraphicInitializerService>();
			if (graph_service_init)
			{
				m_width = graph_service_init->GetWidth();
				m_height = graph_service_init->GetHeight();
				graph_service_init.reset();
			}
			else
			{
				SQ_APP_ERROR("Class {} in function {} : Graphic service initializer is not referenced yet", __FILE__, __FUNCTION__);
			}
			
			m_projection_perspective_matrix = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, m_near_plane, m_far_plane);
			m_projection_ortho_matrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, m_near_plane, m_far_plane);
			
			m_runtime_service = container->GetReference<RunTimeService>();
			if (!m_runtime_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Runtime service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
		
	}

	void StateService::DeInit()
	{

		this->CleanScene();
		m_selected_component = nullptr;
		this->CleanConfig();
		if (m_scene_grid)
		{
			m_scene_grid->Clean();
			m_scene_grid.reset();
		}

		if (m_runtime_service)
		{
			m_runtime_service->DeleteTexture(m_texture_id);
			m_runtime_service->DeleteTexture(sq_texture_id);
		}
		
		for (std::map<std::string, unsigned int>::iterator it = m_available_textures.begin(); it != m_available_textures.end(); it++)
		{
			if (m_runtime_service)
			{
				m_runtime_service->DeleteTexture(it->second);
			}
		}
		m_available_textures.clear();
		for (std::map<std::string, unsigned int>::iterator it = m_available_skybox.begin(); it != m_available_skybox.end(); it++)
		{
			if (m_runtime_service)
			{
				m_runtime_service->DeleteTexture(it->second);
			}
		}
		m_available_skybox.clear();
	}

	bool StateService::getExit() const
	{
		return m_exit;
	}

	void StateService::setExit(bool const new_val)
	{
		m_exit = new_val;
	}

	int StateService::getWidth() const
	{
		return m_width;
	}

	int StateService::getHeight() const
	{
		return m_height;
	}

	bool StateService::getShowMetrics() const
	{
		return m_show_metrics;
	}

	void StateService::setShowMetrics(bool const new_val)
	{
		m_show_metrics = new_val;
	}
	bool StateService::getShowTools() const
	{
		return m_show_tools;
	}
	void StateService::setShowTools(bool const new_val)
	{
		m_show_tools = new_val;
	}

	bool StateService::getShowInfos() const
	{
		return m_show_app_info;
	}
	void StateService::setShowInfos(bool const new_val)
	{
		m_show_app_info = new_val;
	}
	bool StateService::getShowStyleEditor() const
	{
		return m_show_style_editor;
	}
	void StateService::setShowStyleEditor(bool const new_val)
	{
		m_show_style_editor = new_val;
	}
	void StateService::setShowEvent(bool const new_val)
	{
		m_show_event = new_val;
	}
	bool StateService::getShowEvent() const
	{
		return m_show_event;
	}

	void StateService::setFileName(std::string const new_val)
	{
		m_current_filename = new_val;
	}

	bool StateService::getGuiOpen() const
	{
		return m_show_save_as || m_show_confirm || m_show_app_info || m_show_event || m_show_metrics || m_show_style_editor || m_show_tools || m_show_context_menu || m_popup_hovered || m_pannel_view != Constants::NONE;
	}

	bool StateService::getContinued() const
	{
		return m_continued;
	}

	void StateService::setContinued(bool const new_val)
	{
		m_continued = new_val;
	}

	void StateService::setShowSaveAs(bool const new_val)
	{
		m_show_save_as = new_val;
	}

	bool StateService::getShowSaveAs() const
	{
		return m_show_save_as;
	}

	bool StateService::getShowConfirm() const
	{
		return m_show_confirm;
	}

	void StateService::setShowConfirm(bool const new_val)
	{
		m_show_confirm = new_val;
	}

	void StateService::setConfirmMessage(std::string const new_val)
	{
		m_confirm_message = new_val;
	}

	std::string StateService::getConfirmMessage() const
	{
		return m_confirm_message;
	}

	void StateService::setMouseClicked(bool const new_val)
	{
		m_mouse_clicked = new_val;
	}

	bool StateService::getMouseClicked() const
	{
		return m_mouse_clicked;
	}

	void StateService::setShowContextMenu(bool const new_val)
	{
		m_show_context_menu = new_val;
	}

	bool StateService::getShowContextMenu() const
	{
		return m_show_context_menu;
	}

	std::shared_ptr<Component::IComponent> StateService::getSelectedComponent() const
	{
		return m_selected_component;
	}

	int StateService::GetTotalRessources() const
	{
		return (int)this->m_configs->GetAvailableSkybox().size() + (int)m_configs->GetAvailableTextures().size();
	}

	std::string StateService::getFileName() const
	{
		return m_current_filename;
	}

	std::shared_ptr<Services::ConfigEntity> StateService::getConfigs() const
	{
		return m_configs;
	}

	std::shared_ptr<Services::SceneEntity> StateService::GetScene() const
	{
		return m_scene;
	}

	void StateService::SetScene(std::shared_ptr<Services::SceneEntity> scene)
	{
		m_scene = scene;
	}

	void StateService::setConfigs(std::shared_ptr<Services::ConfigEntity> configs)
	{
		this->CleanConfig();
		m_configs = configs;
	}

	void StateService::setSelectedComponent()
	{
		this->unSelectComponent();
		if (m_scene)
		{
			std::vector<std::shared_ptr<Component::IComponent>> components = m_scene->GetSceneComponents();
			auto result = std::find_if(components.begin(), components.end(), [](const std::shared_ptr<Component::IComponent> selectable_component) {return selectable_component->GetSelected() == true; });

			if (result != components.end())
			{
				m_selected_component = *result;
				m_previous_selected_component_color = m_selected_component->GetBackgroundColor();
			}
		}
		
	}

	void StateService::unSelectComponent()
	{
		m_selected_component = nullptr;
	}

	void StateService::setPopupHovered(bool const new_val)
	{
		m_popup_hovered = new_val;
	}

	bool StateService::getPopupHovered() const
	{
		return m_popup_hovered;
	}

	glm::vec4 StateService::getRefColor() const
	{
		return m_previous_selected_component_color;
	}

	void StateService::addComponent(std::shared_ptr<Component::IComponent> new_component)
	{
		if (new_component && m_scene)
		{
			m_scene->AddComponent(new_component);
		}
	}

	void StateService::deleteComponent()
	{
		this->unSelectComponent();
		if (m_scene)
		{
			m_scene->DeleteComponent();
		}
	}
	
	
	glm::mat4 StateService::GetPerspectiveProjectionMatrix() const
	{
		return m_projection_perspective_matrix;
	}

	glm::mat4 StateService::GetOrthoProjectionMatrix() const
	{
		return m_projection_ortho_matrix;
	}

	void StateService::setConfigPannel(std::string const new_val)
	{
		m_pannel_view = new_val;
	}

	std::string StateService::getConfigPannel() const
	{
		return m_pannel_view;
	}

	void StateService::setScalingWay(Enums::ScallingWay const new_scroll_dir)
	{
		m_scaling_way = new_scroll_dir;
	}

	Enums::ScallingWay StateService::getScalingWay() const
	{
		return m_scaling_way;
	}

	void StateService::setGridRenderer(std::shared_ptr<Renderers::Grid> grid_renderer)
	{
		m_scene_grid = grid_renderer;
	}

	std::shared_ptr<Renderers::Grid> StateService::getGridRenderer() const
	{
		return m_scene_grid;
	}

	bool StateService::getActualize() const
	{
		return m_actualize;
	}

	void StateService::setActualize(bool const new_val)
	{
		m_actualize = new_val;
	}

	void StateService::setSelectedSkyboxTextureId(unsigned int const texture_id)
	{
		m_texture_id = texture_id;
	}

	void StateService::SetSqueamishTextureId(unsigned int const texture_id)
	{
		sq_texture_id = texture_id;
	}

	unsigned int StateService::GetSqueamishTextureId() const
	{
		return sq_texture_id;
	}

	unsigned int StateService::getSelectedSkyboxTextureId() const
	{
		return m_texture_id;
	}

	std::map<std::string, unsigned int> StateService::getAvailableSkybox() const
	{
		return m_available_skybox;
	}

	void StateService::addAvailableSkybox(std::string map_id, unsigned int texture_id)
	{
		if (m_available_skybox.contains(map_id))
		{
			if (m_available_skybox.at(map_id) != 0 && m_runtime_service)
			{
				m_runtime_service->DeleteTexture(m_available_skybox.at(map_id));
			}
			m_available_skybox[map_id] = texture_id;

		}
		else
		{
			m_available_skybox.insert_or_assign(map_id, texture_id);
		}
	}

	void StateService::addAvailableTextures(std::string map_id, unsigned int texture_id)
	{
		if (m_available_textures.contains(map_id))
		{
			if (m_available_textures.at(map_id) != 0 && m_runtime_service)
			{
				m_runtime_service->DeleteTexture(m_available_textures.at(map_id));
			}
			m_available_textures[map_id] = texture_id;
		}
		else
		{
			m_available_textures.insert_or_assign(map_id, texture_id);
		}
	}

	void StateService::setPass(Enums::FramebufferType fb_type)
	{
		m_fb_type = fb_type;
	}

	Enums::FramebufferType StateService::getPass() const
	{
		return m_fb_type;
	}

	float StateService::getFarPlane() const
	{
		return m_far_plane;
	}

	float StateService::getNearPlane() const
	{
		return m_near_plane;
	}

	std::map<std::string, unsigned int> StateService::GetAvailableTextures() const
	{
		return m_available_textures;
	}
	
	void StateService::CleanScene()
	{
		if (this->m_scene)
		{
			this->m_scene->DeleteComponents();
		}
		/*for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = m_components.begin(); it != m_components.end(); it++)
		{
			if (it[0])
			{
				it[0]->Clean();
				it[0].reset();
			}
		}
		m_components.clear();*/
	}
	void StateService::CleanConfig()
	{
		if (this->m_configs)
		{
			this->m_configs.reset();
		}
	}
}




