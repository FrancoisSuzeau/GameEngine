/******************************************************************************************************************************************/
// File : StateService.hpp
// Purpose : A service initialising Opengl / SDL
/******************************************************************************************************************************************/
#ifndef STATESERVICE_H
#define STATESERVICE_H

#include <iostream>
#include "Container/Container.hpp"
#include "GraphicInitializerService.hpp"
#include "CameraService.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <algorithm>

#include "IService.hpp"
#include "IRenderer.hpp"
#include "IEngine.hpp"
#include "Container/Container.hpp"
#include "../Services/ImGUIServiceInitalizer.hpp"
#include <ExternalServices.hpp>


namespace Services {

	class StateService : public IService
	{

	public:
		StateService();
		void Init() override;
		void DeInit() override;

		bool getExit() const;
		void setExit(bool const new_val);
		int getWidth() const;
		int getHeight() const;
		bool getShowMetrics() const;
		void setShowMetrics(bool const new_val);
		bool getShowTools() const;
		void setShowTools(bool const new_val);
		bool getShowInfos() const;
		void setShowInfos(bool const new_val);
		bool getShowStyleEditor() const;
		void setShowStyleEditor(bool const new_val);
		void setShowEvent(bool const new_val);
		bool getShowEvent() const;
		void setFileName(std::string const new_val);
		bool getGuiOpen() const;
		bool getContinued() const;
		void setContinued(bool const new_val);
		void setShowSaveAs(bool const new_val);
		bool getShowSaveAs() const;
		bool getShowConfirm() const;
		void setShowConfirm(bool const new_val);
		void setConfirmMessage(std::string const new_val);
		std::string getConfirmMessage() const;
		void setMouseClicked(bool const new_val);
		bool getMouseClicked() const;
		void setShowContextMenu(bool const new_val);
		bool getShowContextMenu() const;
		std::shared_ptr<Component::IComponent> getSelectedComponent() const;

		std::string getFileName() const;
		std::shared_ptr<Services::ConfigEntity> getConfigs() const;
		void setConfigs(std::shared_ptr<Services::ConfigEntity> configs);
		std::vector<std::shared_ptr<Component::IComponent>> getComponents() const;
		void setComponents(std::vector<std::shared_ptr<Component::IComponent>> const components);
		void setSelectedComponent();
		void unSelectComponent();
		void setPopupHovered(bool const new_val);
		bool getPopupHovered() const;
		glm::vec4 getRefColor() const;
		void addComponent(std::shared_ptr<Component::IComponent> new_component);
		void deleteComponent();

		glm::mat4 GetProjectionMatrix() const;

		void setConfigPannel(std::string const new_val);
		std::string getConfigPannel() const;

		void setScrollDir(Enums::ScrollDir const new_scroll_dir);
		Enums::ScrollDir getScrollDir() const;

		void setGridRenderer(std::shared_ptr<Renderers::Grid> grid_renderer);
		std::shared_ptr<Renderers::Grid> getGridRenderer() const;
		

	private:

		void CleanComponents();
		void CleanConfig();
		int m_width;
		int m_height;
		bool m_exit;
		bool m_show_metrics;
		bool m_show_tools;
		bool m_show_app_info;
		bool m_show_style_editor;
		bool m_show_event;
		bool m_show_save_as;
		bool m_show_confirm;
		bool m_mouse_clicked;
		bool m_show_context_menu;
		bool m_popup_hovered;
		glm::vec4 m_previous_selected_component_color;
		glm::mat4 m_projection_matrix;
		std::string m_current_filename;
		bool m_continued;
		std::shared_ptr<Services::ConfigEntity> m_configs;
		std::vector<std::shared_ptr<Component::IComponent>> m_components;
		std::string  m_confirm_message;
		std::shared_ptr<Component::IComponent> m_selected_component;
		std::string m_pannel_view;
		Enums::ScrollDir m_scroll_dir;
		std::shared_ptr<Renderers::Grid> m_scene_grid;

	};
}

#endif