/******************************************************************************************************************************************/
// File : ModifySceneCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "ModifySceneCommand.hpp"

namespace Commands
{
	ModifySceneCommand::ModifySceneCommand(Enums::SceneModifier const scene_modifier, Enums::RendererType component_type) : m_scene_modifier(scene_modifier), m_component_type(component_type),
		m_component_to_copy(nullptr), m_skybox_name(Constants::NONE)
	{
		this->GetServices();
	}

	ModifySceneCommand::ModifySceneCommand(Enums::SceneModifier const scene_modifier) : m_scene_modifier(scene_modifier), m_component_type(Enums::RendererType::NONE),
		m_component_to_copy(nullptr), m_skybox_name(Constants::NONE)
	{
		this->GetServices();
	}

	ModifySceneCommand::ModifySceneCommand(Enums::SceneModifier const scene_modifier, std::string const skybox_name) : m_scene_modifier(scene_modifier), m_component_type(Enums::RendererType::NONE),
		m_component_to_copy(nullptr), m_skybox_name(skybox_name)
	{
		this->GetServices();
	}

	ModifySceneCommand::ModifySceneCommand(Enums::SceneModifier const scene_modifier, std::shared_ptr<Component::IComponent> component_to_copy) : m_scene_modifier(scene_modifier), 
		m_component_type(Enums::RendererType::NONE), m_component_to_copy(component_to_copy), m_skybox_name(Constants::NONE)
	{
		this->GetServices();
	}

	ModifySceneCommand::~ModifySceneCommand()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_camera_service)
		{
			m_camera_service.reset();
		}

		if (m_loader_service)
		{
			m_loader_service.reset();
		}

		if (m_component_to_copy)
		{
			m_component_to_copy.reset();
		}
	}

	void ModifySceneCommand::Execute()
	{
		if (m_state_service)
		{
			switch (m_scene_modifier)
			{
			case Enums::SceneModifier::ADDCOMPONENT:
				this->AddComponentToScene();
				break;
			case Enums::SceneModifier::DELETECOMPONENT:
				m_state_service->deleteComponent();
				SQ_APP_TRACE("Component deleted !");
				break;
			case Enums::SceneModifier::COPYCOMPONENT:
				this->CopyComponent();
				break;
			case Enums::SceneModifier::CHANGESKYBOX:
				m_state_service->GetScene()->SetSelectedSkybox(m_skybox_name);
				m_state_service->SetSelectedSkyboxTextureId();
				SQ_APP_TRACE("Skybox changed");
				break;
			default:
				break;
			}
		}
	}
	void ModifySceneCommand::PostAddingComponentToScene(std::shared_ptr<Component::IComponent> new_component_to_make)
	{
		if (m_state_service && m_camera_service)
		{
			glm::vec3 position = m_camera_service->GetPos() + m_camera_service->GetTarget();

			if (m_component_to_copy)
			{
				m_component_to_copy->SetSelected(false);
			}
			new_component_to_make->SetPosition(position);
			new_component_to_make->SetSelected(true);
			m_state_service->addComponent(new_component_to_make);
			m_state_service->setSelectedComponent();
			new_component_to_make.reset();
		}
	}
	void ModifySceneCommand::AddComponentToScene()
	{
		if (m_camera_service)
		{
			glm::vec3 position = m_camera_service->GetPos() + m_camera_service->GetTarget();
			switch (m_component_type)
			{
			case Enums::RendererType::TRIANGLE:
				this->PostAddingComponentToScene(std::make_shared<Component::ComponentBase>(position, glm::vec3(0.2f), m_component_type, glm::vec4(0.f, 0.f, 0.f, 1.f)));
				SQ_APP_TRACE("New triangle added");
				break;
			case Enums::RendererType::SPHERE:
				this->PostAddingComponentToScene(std::make_shared<Component::ComponentBase>(position, glm::vec3(0.2f), m_component_type, glm::vec4(0.f, 0.f, 0.f, 1.f)));
				SQ_APP_TRACE("New sphere added");
				break;

			case Enums::RendererType::CUBE:
				this->PostAddingComponentToScene(std::make_shared<Component::ComponentBase>(position, glm::vec3(0.2f), m_component_type, glm::vec4(0.f, 0.f, 0.f, 1.f)));
				SQ_APP_TRACE("New cube added");
				break;
			case Enums::RendererType::SQUARE:
				this->PostAddingComponentToScene(std::make_shared<Component::ComponentBase>(position, glm::vec3(0.2f), m_component_type, glm::vec4(0.f, 0.f, 0.f, 1.f)));
				SQ_APP_TRACE("New square added");
				break;
			case Enums::RendererType::CUBE_TEXTURED:
			{
				std::shared_ptr<Component::TexturedComponent> component = std::make_shared<Component::TexturedComponent>(position, glm::vec3(0.2f), m_component_type, Constants::NONE);
				m_loader_service->LoadTexture(component, component->GetTextureName());
				this->PostAddingComponentToScene(component);
				SQ_APP_TRACE("New textured cube added");
			}
			break;
			case Enums::RendererType::SQUARE_TEXTURED:
			{
				std::shared_ptr<Component::TexturedComponent> component = std::make_shared<Component::TexturedComponent>(position, glm::vec3(0.2f), m_component_type, Constants::NONE);
				m_loader_service->LoadTexture(component, component->GetTextureName());
				this->PostAddingComponentToScene(component);
				SQ_APP_TRACE("New textured square added");
			}
			break;
			case Enums::RendererType::TRIANGLE_TEXTURED:
			{
				std::shared_ptr<Component::TexturedComponent> component = std::make_shared<Component::TexturedComponent>(position, glm::vec3(0.2f), m_component_type, Constants::NONE);
				m_loader_service->LoadTexture(component, component->GetTextureName());
				this->PostAddingComponentToScene(component);
				SQ_APP_TRACE("New textured triangle added");
			}
			break;
			case Enums::RendererType::SPHERE_TEXTURED:
			{
				std::shared_ptr<Component::TexturedComponent> component = std::make_shared<Component::TexturedComponent>(position, glm::vec3(0.2f), m_component_type, Constants::NONE);
				m_loader_service->LoadTexture(component, component->GetTextureName());
				this->PostAddingComponentToScene(component);
				SQ_APP_TRACE("New textured sphere added");
			}
			break;
			case Enums::RendererType::SKYBOX:
			case Enums::RendererType::GRID:
				SQ_APP_TRACE("This component type cannot be added to the scene");
				break;
			case Enums::RendererType::NONE:
			default:
				SQ_APP_TRACE("Component type not known. Cannot add it");
				break;
			}
		}
	}
	void ModifySceneCommand::CopyComponent()
	{
		if (m_component_to_copy)
		{
			switch (m_component_to_copy->GetType())
			{
			case Enums::RendererType::TRIANGLE:
			case Enums::RendererType::SQUARE:
			case Enums::RendererType::CUBE:
			case Enums::RendererType::SPHERE:
				this->PostAddingComponentToScene(std::make_shared<Component::ComponentBase>(*std::dynamic_pointer_cast<Component::ComponentBase>(m_component_to_copy)));
				SQ_APP_TRACE("Component copied !");
				break;
			case Enums::RendererType::CUBE_TEXTURED:
			case Enums::RendererType::SQUARE_TEXTURED:
			case Enums::RendererType::TRIANGLE_TEXTURED:
			case Enums::RendererType::SPHERE_TEXTURED:
				this->PostAddingComponentToScene(std::make_shared<Component::TexturedComponent>(*std::dynamic_pointer_cast<Component::TexturedComponent>(m_component_to_copy)));
				SQ_APP_TRACE("Component copied !");
				break;
			case Enums::RendererType::SKYBOX:
			case Enums::RendererType::GRID:
			case Enums::RendererType::NONE:
			default:
				break;
			}

		}
	}
	void ModifySceneCommand::GetServices()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_camera_service = container->GetReference<Services::CameraService>();
			if (!m_camera_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Camera service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_loader_service = container->GetReference<Services::LoaderService>();
			if (!m_loader_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Loader service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}
}