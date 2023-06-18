/******************************************************************************************************************************************/
// File : GUIEngine.cpp
// Purpose : Implementing the GUI engine
/******************************************************************************************************************************************/
#include "GUIEngine.hpp"

using namespace Engines;
static bool show_app_metrics = false;
static bool show_app_stack_tool = false;
static bool show_app_style_editor = false;
static bool show_app_about = false;

GUIEngine::~GUIEngine()
{
}

void GUIEngine::Construct()
{
	IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
	std::shared_ptr<Services::ImGUIServiceInitializer> imgui_service_init = container->make<Services::ImGUIServiceInitializer>();
	m_state_service = container->make<Services::StateService>();
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

void GUIEngine::Render()
{
	if (show_app_metrics) { ImGui::ShowMetricsWindow(&show_app_metrics); }
	if (show_app_stack_tool) { ImGui::ShowStackToolWindow(&show_app_stack_tool); }
	if (show_app_about) { ImGui::ShowAboutWindow(&show_app_about); }
	if (show_app_style_editor)
	{
		ImGui::Begin("Dear ImGui Style Editor", &show_app_style_editor);
		ImGui::ShowStyleEditor();
		ImGui::End();
	}
	this->RenderMainMenuBar();
}

void GUIEngine::RenderMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			RenderMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			RenderMenuEdit();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools"))
		{
			RenderMenuTools();
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void GUIEngine::RenderMenuFile()
{
	if (ImGui::MenuItem("New")) {}
	if (ImGui::MenuItem("Open", "Ctrl+O")) {}
	if (ImGui::BeginMenu("Open Recent"))
	{
		ImGui::MenuItem("NewFile");
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem("Save", "Ctrl+S")) {}
	if (ImGui::MenuItem("Save As..")) {}

	ImGui::Separator();

	if (ImGui::MenuItem("Quit", "Alt+F4"))
	{
		std::shared_ptr<Commands::ExitCommand> exit_command = std::shared_ptr<Commands::ExitCommand>(new Commands::ExitCommand(m_state_service));
		exit_command->Execute();
	}
}

void GUIEngine::RenderMenuEdit() 
{
	if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
	if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
	ImGui::Separator();
	if (ImGui::MenuItem("Cut", "CTRL+X")) {}
	if (ImGui::MenuItem("Copy", "CTRL+C")) {}
	if (ImGui::MenuItem("Paste", "CTRL+V")) {}
}

void GUIEngine::RenderMenuTools()
{
	ImGui::MenuItem("Metrics/Debugger", NULL, &show_app_metrics);
	ImGui::MenuItem("Stack Tool", NULL, &show_app_stack_tool);
	ImGui::MenuItem("Style Editor", NULL, &show_app_style_editor);
	ImGui::MenuItem("About Dear ImGui", NULL, &show_app_about);
}
