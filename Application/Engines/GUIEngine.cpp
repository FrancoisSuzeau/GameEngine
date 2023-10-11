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
		std::shared_ptr<Services::ImGUIServiceInitializer> imgui_service_init = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::ImGUIServiceInitializer>();
		if (imgui_service_init)
		{
			m_io = imgui_service_init->GetIO();
			imgui_service_init.reset();
		}
		else
		{
			SQ_APP_ERROR("ImGUI service initializer is not referenced yet");
		}
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

	void GUIEngine::RenderGuiComponents(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		if (view_model_builder)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::GUIVIEWMODEL);

			if (view_model)
			{
				view_model->RenderViews(Constants::SIMPLECPT);
			}
		}

	}

	void GUIEngine::RenderMainMenuBar(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (view_model_builder)
			{
				std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::GUIVIEWMODEL);

				if (view_model)
				{
					view_model->RenderViews(Constants::MENUSCPT);
				}
			}

			ImGui::EndMainMenuBar();
		}
	}
}



