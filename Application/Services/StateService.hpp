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
		void setRenderLine(bool const new_val);
		bool getRenderLine() const;
		std::string getConfirmMessage() const;

		std::string getFileName() const;
		std::shared_ptr<Services::ConfigEntity> getConfigs() const;
		void setConfigs(std::shared_ptr<Services::ConfigEntity> configs);
		std::vector<std::shared_ptr<Renderers::IRenderer>> getRenderers() const;
		void setRenderers(std::vector<std::shared_ptr<Renderers::IRenderer>> const renderers);

		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix() const;
		void RefreshProjectionMatrix();


	private:

		void CleanRenderers();
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
		bool m_render_line;
		glm::mat4 m_projection_matrix;
		glm::mat4 m_view;
		std::shared_ptr<Services::CameraService> m_camera_services;
		std::string m_current_filename;
		bool m_continued;
		std::shared_ptr<Services::ConfigEntity> m_configs;
		std::vector<std::shared_ptr<Renderers::IRenderer>> m_renderers;
		std::string  m_confirm_message;

	};
}

#endif