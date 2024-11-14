/******************************************************************************************************************************************/
// File : SceneViewModel.cpp
// Purpose : Implementing the GUI view model
/******************************************************************************************************************************************/

#include "SceneViewModel.hpp"

namespace ViewModels
{
	SceneViewModel::~SceneViewModel()
	{
		if (m_canvas)
		{
			m_canvas->Clean();
			m_canvas.reset();
		}

		if (m_shader_service)
		{
			m_shader_service.reset();
		}

		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_framebuffer_service)
		{
			m_framebuffer_service.reset();
		}

		if (m_camera_service)
		{
			m_camera_service.reset();
		}

		if (m_runtime_service)
		{
			m_runtime_service.reset();
		}

		for (std::map<Enums::RendererType, std::unique_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
		{
			if (it->second)
			{
				it->second->Clean();
				it->second.reset();
			}
		}
		m_renderers.clear();

		for (std::map<Enums::RendererType, std::shared_ptr<Component::IComponent>>::iterator it = m_components.begin(); it != m_components.end(); it++)
		{
			if (it->second)
			{
				it->second->Clean();
				it->second.reset();
			}
		}
		m_components.clear();
	}
	void SceneViewModel::Construct()
	{
		m_grid_size = 300;
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
				
			}
			else
			{
				m_state_service->setScalingWay(Enums::ScallingWay::Up);
			}
			
			m_canvas = std::make_unique<Views::Canvas>(shared_from_this());
			if (m_canvas)
			{
				m_canvas->ConstructRenderer();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Canvas component is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_shader_service = container->GetReference<Services::ShaderService>();
			if (!m_shader_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_framebuffer_service = container->GetReference<Services::FramebufferService>();
			if (!m_framebuffer_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Framebuffer service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_runtime_service = container->GetReference<Services::RunTimeService>();
			if (!m_runtime_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Runtime service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_camera_service = container->GetReference<Services::CameraService>();
			if (!m_camera_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Camera service is not referenced yet", __FILE__, __FUNCTION__);
			}
			else
			{
				m_current_cam_pos = m_camera_service->GetPos();
			}

			m_loader_service = container->GetReference<Services::LoaderService>();
			if (!m_loader_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Loader service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_physic_service = container->GetReference<Services::PhysicsService>();
			if (!m_physic_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Physic service is not referenced yet", __FILE__, __FUNCTION__);
			}
			

			

			m_components.insert_or_assign(Enums::RendererType::SKYBOX, std::make_shared<Component::TexturedComponent>(glm::vec3(0.f), glm::vec3(0.f), Enums::RendererType::SKYBOX, Constants::NONE));
			m_components.insert_or_assign(Enums::RendererType::MODEL, std::make_shared<Component::TexturedComponent>(glm::vec3(0.f), glm::vec3(4.f), Enums::RendererType::MODEL, Constants::NONE));
			m_components.insert_or_assign(Enums::RendererType::GRID, std::make_shared<Component::ComponentBase>(glm::vec3(0.f), glm::vec3(20.f), Enums::RendererType::GRID, glm::vec4(1.f, 1.f, 1.f, 0.75f)));
			m_components.insert_or_assign(Enums::RendererType::AXIS, std::make_shared<Component::ComponentBase>(glm::vec3(0.f), glm::vec3(1.f), Enums::RendererType::AXIS, glm::vec4(1.f, 0.f, 0.f, 1.f)));
			m_components.insert_or_assign(Enums::RendererType::SUBBGRID, std::make_shared<Component::ComponentBase>(glm::vec3(0.f), glm::vec3(20.f), Enums::RendererType::SUBBGRID, glm::vec4(0.5f, 0.5f, 0.5f, 0.75f)));
			m_components.insert_or_assign(Enums::RendererType::SUBGRID2, std::make_shared<Component::ComponentBase>(glm::vec3(0.f), glm::vec3(20.f), Enums::RendererType::SUBGRID2, glm::vec4(0.5f, 0.5f, 0.5f, 0.75f)));
			m_components.insert_or_assign(Enums::RendererType::SPHERE_X, std::make_shared<Component::ComponentBase>(glm::vec3(0.f), glm::vec3(20.f), Enums::RendererType::SPHERE_X, glm::vec4(1.f, 0.f, 0.f, 1.f)));
			m_components.insert_or_assign(Enums::RendererType::SPHERE_Y, std::make_shared<Component::ComponentBase>(glm::vec3(0.f), glm::vec3(20.f), Enums::RendererType::SPHERE_Y, glm::vec4(0.f, 1.f, 0.f, 1.f)));
			m_components.insert_or_assign(Enums::RendererType::SPHERE_Z, std::make_shared<Component::ComponentBase>(glm::vec3(0.f), glm::vec3(20.f), Enums::RendererType::SPHERE_Z, glm::vec4(0.f, 0.f, 1.f, 1.f)));

			m_renderers.insert_or_assign(Enums::RendererType::SKYBOX, std::make_unique<Renderers::Skybox>());
			if (m_state_service && m_state_service->getConfigs())
			{
				m_state_service->setGridRenderer(std::make_shared<Renderers::Grid>(m_grid_size, (float)m_state_service->getConfigs()->GetGridSpacingRatio()));
				m_state_service->setActualize(true);
				this->AddCommand(std::make_unique<Commands::ActualizeCommand>());
				this->OnCommand();
			}
			for (std::map<Enums::RendererType, std::unique_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
			{
				if (it->second)
				{
					it->second->Construct();
				}
			}

			m_current_relative_distance_from_cam = 40.f;

			m_state_service->setAxisRenderer(std::make_shared<Renderers::Axis>());
			m_state_service->SetSphereRenderer(std::make_shared<Renderers::Sphere>(1.f, 70, 70));
		}
	}

	void SceneViewModel::RenderComponents()
	{
		if (m_state_service && m_state_service->GetScene())
		{
			if (m_canvas)
			{
				m_canvas->Render(m_state_service->GetScene()->GetSceneComponents());
			}
		}
	}
	void SceneViewModel::ManageScene()
	{
		if (m_state_service && m_state_service->GetScene())
		{
			std::vector<std::shared_ptr<Component::IComponent>> components = m_state_service->GetScene()->GetSceneComponents();
			if (m_canvas)
			{
				m_canvas->DragComponents(components);
				m_canvas->TransformComponents(components);
			}
		}

		if (m_camera_service)
		{
			glm::vec3 cam_pos = m_camera_service->GetPos();
			this->ManageGridPosition(cam_pos);
			this->ManageGridScaling(cam_pos);
			this->ManageCameraCapture();
			this->ManageAxix();
			this->ManageSphereAxis();
			this->TransformSceneElements();
		}
		
	}

	void SceneViewModel::RenderSceneElements(Enums::RendererType element)
	{

		if (m_shader_service && m_runtime_service && m_components.contains(element) && m_components.at(element) && m_state_service && m_state_service->getConfigs())
		{

			switch (element)
			{
			case Enums::RendererType::GRID:
				if (m_state_service->getGridRenderer() && m_state_service->getConfigs()->GetRenderGrid())
				{
					std::string shader_name = Constants::GRID_SHADER;
					m_shader_service->BindShaderProgram(shader_name);
					Component::Transformer::PutIntoShader(m_components.at(element), m_shader_service, shader_name);
					m_state_service->getGridRenderer()->Draw();
					m_shader_service->UnbindShaderProgram();
				}
				break;
			case::Enums::RendererType::SUBGRID2:
			case Enums::RendererType::SUBBGRID:
				if (m_state_service->getGridRenderer() && m_state_service->getConfigs()->GetRenderGrid())
				{
					std::string shader_name = Constants::GRID_SHADER;
					m_shader_service->BindShaderProgram(shader_name);
					Component::Transformer::PutIntoShader(m_components.at(element), m_shader_service, shader_name);
					m_state_service->getGridRenderer()->Draw();
					m_shader_service->UnbindShaderProgram();
				}
				break;
			case Enums::RendererType::SKYBOX:
				if (m_renderers.contains(Enums::RendererType::SKYBOX) && m_renderers.at(Enums::RendererType::SKYBOX) && m_state_service->getSelectedSkyboxTextureId() != 0)
				{
					m_runtime_service->LequalDepth();
					m_shader_service->BindShaderProgram(Constants::SKYBOX_SHADER);
					Component::Transformer::PutIntoShader(m_components.at(element), m_shader_service, Constants::SKYBOX_SHADER);
					m_renderers.at(element)->Draw(m_state_service->getSelectedSkyboxTextureId());
					m_shader_service->UnbindShaderProgram();
					m_runtime_service->LessDepth();
				}
				break;
			case Enums::RendererType::MODEL:
				{
					std::string shader_name = Constants::CAMERA_SHADER;
					std::shared_ptr<Renderers::Model> camera_model = m_state_service->getCameraModelRenderer();
					if (camera_model)
					{
						m_shader_service->BindShaderProgram(shader_name);
						Component::Transformer::PutIntoShader(m_components.at(element), m_shader_service, shader_name);
						for (size_t i = 0; i < camera_model->GetNbMeshes(); i++)
						{
							Component::Transformer::PutIntoShader(camera_model->GetMeshTextures(i), m_shader_service, shader_name);
							camera_model->Draw(i);
								
						}
						m_shader_service->UnbindShaderProgram();
					}
				}
				break;
			case Enums::RendererType::AXIS:
			{
				std::shared_ptr<Renderers::Axis> line_renderer = m_state_service->getAxisRenderer();
				if (line_renderer)
				{
					std::string shader_name = Constants::LINE_SHADER;
					m_shader_service->BindShaderProgram(shader_name);
					Component::Transformer::PutIntoShader(m_components.at(element), m_shader_service, shader_name);
					line_renderer->Draw();
					m_shader_service->UnbindShaderProgram();
				}
			}
				break;

			case Enums::RendererType::SPHERE_X:
			case Enums::RendererType::SPHERE_Y:
			case Enums::RendererType::SPHERE_Z:
			{
				std::shared_ptr<Renderers::Sphere> sphere_renderer = m_state_service->getSphereRenderer();
				if (sphere_renderer)
				{
					std::string shader_name = Constants::UNTEXTURED_SHADER;
					m_shader_service->BindShaderProgram(shader_name);
					Component::Transformer::PutIntoShader(m_components.at(element), m_shader_service, shader_name);
					sphere_renderer->Draw();
					m_shader_service->UnbindShaderProgram();
				}
			}
			break;
			case Enums::RendererType::TRIANGLE:
			case Enums::RendererType::SPHERE:
			case Enums::RendererType::SPHERE_TEXTURED:
			case Enums::RendererType::SQUARE:
			case Enums::RendererType::SQUARE_TEXTURED:
			case Enums::RendererType::TRIANGLE_TEXTURED:
			case Enums::RendererType::CUBE_TEXTURED:
			case Enums::RendererType::CUBE:
			case Enums::RendererType::NONE:
			default:
				break;
			}
		}
	}

	void SceneViewModel::LoadModel(const int index)
	{
		if (m_canvas && m_loader_service && m_state_service && m_state_service->getConfigs())
		{
			std::vector<std::string> available_models = m_state_service->getConfigs()->GetAvailableModels();
			if (index >= 0 && index < available_models.size())
			{
				std::string name = available_models[index];
				std::unique_ptr<Renderers::Model> model = m_loader_service->LoadModel(name + "/" + name);
				if (name == "camera")
				{
					std::shared_ptr<Renderers::Model> camera_model = std::make_shared<Renderers::Model>(*model);
					m_state_service->setCameraModelRenderer(camera_model);
				}
				m_canvas->AddModelRenderer(std::move(model), name);
			}

		}
	}
	
	void SceneViewModel::TransformSceneElements()
	{
		for (std::map<Enums::RendererType, std::shared_ptr<Component::IComponent>>::iterator it = m_components.begin(); it != m_components.end(); it++)
		{
			if (it->second)
			{
				Component::Transformer::ReinitModelMat(it->second);

				Component::Transformer::Move(it->second);

				Component::Transformer::Rotate(it->second, Enums::OrientationAngle::YAXIS);
				Component::Transformer::Rotate(it->second, Enums::OrientationAngle::ZAXIS);
				Component::Transformer::Rotate(it->second, Enums::OrientationAngle::XAXIS);

				Component::Transformer::Resize(it->second);
			}
		}
	}
	void SceneViewModel::ManageGridScaling(glm::vec3 const cam_pos)
	{
		if (m_components.contains(Enums::RendererType::GRID) && m_components.at(Enums::RendererType::GRID) && m_camera_service && m_state_service->getGridRenderer()
			&& m_state_service && m_state_service->getConfigs() && m_state_service->getConfigs()->GetRenderGrid() &&
			m_components.contains(Enums::RendererType::SUBBGRID) && m_components.at(Enums::RendererType::SUBBGRID) &&
			m_components.contains(Enums::RendererType::SUBGRID2) && m_components.at(Enums::RendererType::SUBGRID2))
		{
			
			float relative_dist = glm::length(cam_pos - m_components.at(Enums::RendererType::GRID)->GetPosition());
			if (std::abs(relative_dist - m_current_relative_distance_from_cam) >= m_state_service->getConfigs()->GetGridScalingTrigger())
			{
				glm::vec3 actual_size = m_components.at(Enums::RendererType::GRID)->GetSize();
				glm::vec3 actual_size2 = m_components.at(Enums::RendererType::SUBBGRID)->GetSize();
				glm::vec3 actual_size3 = m_components.at(Enums::RendererType::SUBGRID2)->GetSize();
				switch (m_state_service->getScalingWay())
				{
				case Enums::ScallingWay::Up:
					actual_size *= 2;
					actual_size2 *= 2;
					actual_size3 *= 2;
					break;
				case Enums::ScallingWay::Bottom:
					actual_size /= 2;
					actual_size2 /= 2;
					actual_size3 /= 2;
					break;
				case Enums::ScallingWay::EMPTY:
				default:
					break;
				}

				m_components.at(Enums::RendererType::GRID)->SetSize(actual_size);
				m_components.at(Enums::RendererType::SUBBGRID)->SetSize(actual_size2);
				m_components.at(Enums::RendererType::SUBGRID2)->SetSize(actual_size3);
				m_current_relative_distance_from_cam = relative_dist;
			}
		}
	}
	void SceneViewModel::ManageGridPosition(glm::vec3 const cam_pos)
	{
		if (m_components.contains(Enums::RendererType::GRID) && m_components.at(Enums::RendererType::GRID) && m_camera_service && m_state_service->getGridRenderer()
			&& m_state_service && m_state_service->getConfigs() && m_state_service->getConfigs()->GetRenderGrid() &&
			m_components.contains(Enums::RendererType::SUBBGRID) && m_components.at(Enums::RendererType::SUBBGRID) &&
			m_components.contains(Enums::RendererType::SUBGRID2) && m_components.at(Enums::RendererType::SUBGRID2))
		{
			float x = cam_pos.x - ((float)m_grid_size / 2.f);
			float z = cam_pos.z - ((float)m_grid_size / 2.f);
			float offset_x = (((float)(m_state_service->getConfigs()->GetGridSpacingRatio()) * m_components.at(Enums::RendererType::GRID)->GetSize().x / 10.f) / 3.f);
			float offset_z = (((float)(m_state_service->getConfigs()->GetGridSpacingRatio()) * m_components.at(Enums::RendererType::GRID)->GetSize().z / 10.f) / 3.f);

			m_components.at(Enums::RendererType::GRID)->SetPosition(glm::vec3(x, -1.f, z));
			m_components.at(Enums::RendererType::SUBBGRID)->SetPosition(glm::vec3(x + offset_x, -1.f, z + offset_z));
			m_components.at(Enums::RendererType::SUBGRID2)->SetPosition(glm::vec3(x + offset_x * 2, -1.f, z + offset_z * 2));

		}
	}
	void SceneViewModel::ManageAxix()
	{
		if (m_components.contains(Enums::RendererType::AXIS) && m_components.at(Enums::RendererType::AXIS))
		{
			m_components.at(Enums::RendererType::AXIS)->SetPosition(glm::vec3(0.1f, 0.2f, -2.f));
			m_components.at(Enums::RendererType::AXIS)->SetAngle1(0.f);
			m_components.at(Enums::RendererType::AXIS)->SetAngle2(0.f);
			m_components.at(Enums::RendererType::AXIS)->SetAngle3(90.f);
			m_components.at(Enums::RendererType::AXIS)->SetSize(glm::vec3(0.6f, 0.7f, 0.7f));

		}
	}
	void SceneViewModel::ManageSphereAxis()
	{
		if (m_camera_service && m_physic_service)
		{
			glm::vec3 cam_pos = m_camera_service->GetPos();
			glm::vec3 camera_speed = m_physic_service->CalculateCameraSpeed(cam_pos, m_current_cam_pos);
			if (m_components.contains(Enums::RendererType::SPHERE_X) && m_components.at(Enums::RendererType::SPHERE_X))
			{
				m_components.at(Enums::RendererType::SPHERE_X)->SetPosition(glm::vec3(-0.5f, -0.3f, -2.f));
				m_components.at(Enums::RendererType::SPHERE_X)->SetAngle1(0.f);
				m_components.at(Enums::RendererType::SPHERE_X)->SetAngle2(0.f);
				m_components.at(Enums::RendererType::SPHERE_X)->SetAngle3(0.f);
				m_components.at(Enums::RendererType::SPHERE_X)->SetSize(glm::vec3(0.05f));
				if (std::abs(camera_speed.x) > std::abs(camera_speed.y) && std::abs(camera_speed.x) > std::abs(camera_speed.z))
				{
					m_components.at(Enums::RendererType::SPHERE_X)->SetBackgroundColor(glm::vec4(1.f, 0.f, 0.f, 1.f));
					m_components.at(Enums::RendererType::SPHERE_X)->SetIsALigthSource(false);
					m_current_cam_pos = cam_pos;
				}
				else
				{
					m_components.at(Enums::RendererType::SPHERE_X)->SetBackgroundColor(glm::vec4(0.f));
				}

			}

			if (m_components.contains(Enums::RendererType::SPHERE_Y) && m_components.at(Enums::RendererType::SPHERE_Y))
			{
				m_components.at(Enums::RendererType::SPHERE_Y)->SetPosition(glm::vec3(0.6f, 0.62f, -2.f));
				m_components.at(Enums::RendererType::SPHERE_Y)->SetAngle1(0.f);
				m_components.at(Enums::RendererType::SPHERE_Y)->SetAngle2(0.f);
				m_components.at(Enums::RendererType::SPHERE_Y)->SetAngle3(0.f);
				m_components.at(Enums::RendererType::SPHERE_Y)->SetSize(glm::vec3(0.05f));
				if (std::abs(camera_speed.y) > std::abs(camera_speed.z) && std::abs(camera_speed.y) > std::abs(camera_speed.x))
				{
					m_components.at(Enums::RendererType::SPHERE_Y)->SetBackgroundColor(glm::vec4(0.f, 1.f, 0.f, 1.f));
					m_current_cam_pos = cam_pos;
				}
				else
				{
					m_components.at(Enums::RendererType::SPHERE_Y)->SetBackgroundColor(glm::vec4(0.f));
				}

			}

			if (m_components.contains(Enums::RendererType::SPHERE_Z) && m_components.at(Enums::RendererType::SPHERE_Z))
			{
				m_components.at(Enums::RendererType::SPHERE_Z)->SetPosition(glm::vec3(1.26f, -0.65f, -2.f));
				m_components.at(Enums::RendererType::SPHERE_Z)->SetAngle1(0.f);
				m_components.at(Enums::RendererType::SPHERE_Z)->SetAngle2(0.f);
				m_components.at(Enums::RendererType::SPHERE_Z)->SetAngle3(0.f);
				m_components.at(Enums::RendererType::SPHERE_Z)->SetSize(glm::vec3(0.05f));
				if (std::abs(camera_speed.z) > std::abs(camera_speed.x) && std::abs(camera_speed.z) > std::abs(camera_speed.x))
				{
					m_components.at(Enums::RendererType::SPHERE_Z)->SetBackgroundColor(glm::vec4(0.f, 0.f, 1.f, 1.f));
					m_current_cam_pos = cam_pos;
				}
				else
				{
					m_components.at(Enums::RendererType::SPHERE_Z)->SetBackgroundColor(glm::vec4(0.f));
				}

			}
		}
	}
	void SceneViewModel::ManageCameraCapture()
	{
		if (m_components.contains(Enums::RendererType::MODEL) && m_components.at(Enums::RendererType::MODEL) && m_camera_service)
		{
			m_components.at(Enums::RendererType::MODEL)->SetPosition(glm::vec3(0.f, -0.4f, -3.f));
			m_components.at(Enums::RendererType::MODEL)->SetSize(glm::vec3(8.f));
			m_components.at(Enums::RendererType::MODEL)->SetAngle1(0.f);
			m_components.at(Enums::RendererType::MODEL)->SetAngle2(m_camera_service->GetYaw() + 180.f);
			m_components.at(Enums::RendererType::MODEL)->SetAngle3(m_camera_service->GetPitch());
		}
	}
}

