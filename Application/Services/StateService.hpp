/******************************************************************************************************************************************/
// File : StateService.hpp
// Purpose : A service initialising Opengl / SDL
/******************************************************************************************************************************************/
#ifndef STATESERVICE_H
#define STATESERVICE_H

#include <iostream>
#include "Container/Container.hpp"
#include "GraphicInitializerService.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <algorithm>

#include "IService.hpp"
#include "Renderers/Untextured/Grid.hpp"
#include "RunTimeService.hpp"

#include "IComponent.hpp"
#include "ConfigEntity.hpp"
#include "SceneEntity.hpp"
#include "Enums/EngineEnum.hpp"

#include "TextureLoaderService/TextureLoaderService.hpp"

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
		int GetTotalRessources() const;

		std::string getFileName() const;
		std::shared_ptr<Services::ConfigEntity> getConfigs() const;
		std::shared_ptr<Services::SceneEntity> GetScene() const;
		void SetScene(std::shared_ptr<Services::SceneEntity> scene);
		void setConfigs(std::shared_ptr<Services::ConfigEntity> configs);
		void setSelectedComponent();
		void unSelectComponent();
		void setPopupHovered(bool const new_val);
		bool getPopupHovered() const;
		glm::vec4 getRefColor() const;
		void addComponent(std::shared_ptr<Component::IComponent> new_component);
		void deleteComponent();

		glm::mat4 GetPerspectiveProjectionMatrix() const;
		glm::mat4 GetOrthoProjectionMatrix() const;

		void setConfigPannel(std::string const new_val);
		std::string getConfigPannel() const;

		void setScalingWay(Enums::ScallingWay const new_scroll_dir);
		Enums::ScallingWay getScalingWay() const;

		void setGridRenderer(std::shared_ptr<Renderers::Grid> grid_renderer);
		std::shared_ptr<Renderers::Grid> getGridRenderer() const;

		bool getActualize() const;
		void setActualize(bool const new_val);

		void SetSelectedSkyboxTextureId();
		void SetSqueamishTextureId(unsigned int const texture_id);
		unsigned int GetSqueamishTextureId() const;
		unsigned int getSelectedSkyboxTextureId() const;
		std::map<std::string, unsigned int> getAvailableSkybox() const;
		void AddAvailableSkyboxChoice(std::string map_id, unsigned int texture_id);
		void AddSkyboxCubeTex(std::string map_id, unsigned int texture_id);
		void addAvailableTextures(std::string map_id, unsigned int texture_id);

		
		
		float getFarPlane() const;
		float getNearPlane() const;
		
		std::map<std::string, unsigned int> GetAvailableTextures() const;
		

	private:

		void CleanScene();
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
		bool m_actualize;
		float m_near_plane;
		float m_far_plane;
		glm::vec4 m_previous_selected_component_color;
		glm::mat4 m_projection_perspective_matrix;
		glm::mat4 m_projection_ortho_matrix;
		std::string m_current_filename;
		bool m_continued;
		std::shared_ptr<Services::ConfigEntity> m_configs;
		std::shared_ptr<Services::SceneEntity> m_scene;
		std::string  m_confirm_message;
		std::shared_ptr<Component::IComponent> m_selected_component;
		std::string m_pannel_view;
		Enums::ScallingWay m_scaling_way;
		std::shared_ptr<Renderers::Grid> m_scene_grid;
		std::shared_ptr<RunTimeService> m_runtime_service;
		std::map<std::string, unsigned int> m_available_skybox_choices;
		std::map<std::string, unsigned int> m_skybox_cube_texture;
		std::map<std::string, unsigned int> m_available_textures;
		unsigned int m_texture_id;
		
		unsigned int sq_texture_id;

	};
}

#endif