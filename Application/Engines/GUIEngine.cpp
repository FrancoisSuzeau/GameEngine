/******************************************************************************************************************************************/
// File : GUIEngine.cpp
// Purpose : Implementing the GUI engine
/******************************************************************************************************************************************/
#include "GUIEngine.hpp"

namespace Engines
{
	GUIEngine::~GUIEngine()
	{
	}

	void GUIEngine::Construct()
	{
		std::shared_ptr<Services::ImGUIServiceInitializer> imgui_service_init = IoC::Container::Container::GetInstanceContainer()->make<Services::ImGUIServiceInitializer>();
		m_io = imgui_service_init->GetIO();

		imgui_service_init.reset();
	}

	void GUIEngine::InitFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void GUIEngine::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUIEngine::RenderGuiComponents()
	{
		for (auto view_models : Builders::ViewModelBuilder::m_view_models)
		{
			view_models.get()->RenderViews(Constants::SIMPLECPT);
		}
	}

	void GUIEngine::RenderMainMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			for (auto view_models : Builders::ViewModelBuilder::m_view_models)
			{
				view_models.get()->RenderViews(Constants::MENUSCPT);
			}

			ImGui::EndMainMenuBar();
		}
	}
}



