/******************************************************************************************************************************************/
// File : StateService.cpp
// Purpose : Implementing service Opengl / SDL  initialisation
/******************************************************************************************************************************************/
#include "StateService.hpp"

namespace Services
{
	StateService::StateService() : m_show_metrics(false), m_show_tools(false), m_exit(false), m_height(0), m_width(0), m_show_app_info(false),
		m_show_style_editor(false), m_show_event(false), m_current_filename(""), m_continued(false), m_projection_matrix(glm::mat4(1.f)),
		m_show_save_as(false), m_show_confirm(false), m_mouse_clicked(false), m_show_context_menu(false), m_selected_component(nullptr), m_popup_hovered(false), m_previous_selected_component_color(1.f)
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
			
			m_projection_matrix = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 100.0f);
		}
		
	}

	void StateService::DeInit()
	{

		this->CleanRenderers();
		m_selected_component = nullptr;
		this->CleanConfig();
		
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
		return m_show_save_as || m_show_confirm || m_show_app_info || m_show_event || m_show_metrics || m_show_style_editor || m_show_tools || m_show_context_menu || m_popup_hovered;
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

	std::string StateService::getFileName() const
	{
		return m_current_filename;
	}

	std::shared_ptr<Services::ConfigEntity> StateService::getConfigs() const
	{
		return m_configs;
	}

	void StateService::setConfigs(std::shared_ptr<Services::ConfigEntity> configs)
	{
		this->CleanConfig();
		m_configs = configs;
	}

	std::vector<std::shared_ptr<Component::IComponent>> StateService::getComponents() const
	{
		return m_components;
	}

	void StateService::setComponents(std::vector<std::shared_ptr<Component::IComponent>> const components)
	{
		this->CleanRenderers();

		m_components = components;
	}

	void StateService::setSelectedComponent()
	{
		this->unSelectComponent();
		auto result = std::find_if(m_components.begin(), m_components.end(), [](const std::shared_ptr<Component::IComponent> selectable_component) {return selectable_component->GetSelected() == true; });
		
		if (result != m_components.end())
		{
			m_selected_component = *result;
			m_previous_selected_component_color = m_selected_component->GetBackgroundColor();
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
		if (new_component)
		{
			m_components.push_back(new_component);
		}
	}

	void StateService::deleteComponent()
	{
		this->unSelectComponent();
		auto to_remove = std::remove_if(m_components.begin(), m_components.end(), [](const std::shared_ptr<Component::IComponent> selectable_component) {return selectable_component->GetSelected() == true; });
		m_components.erase(to_remove, m_components.end());
	}
	
	
	glm::mat4 StateService::GetProjectionMatrix() const
	{
		return m_projection_matrix;
	}
	
	void StateService::CleanRenderers()
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
	void StateService::CleanConfig()
	{
		if (m_configs)
		{
			m_configs.reset();
		}
	}
}




