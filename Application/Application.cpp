/******************************************************************************************************************************************/
// File : Application.cpp
// Purpose : Implementing the Application
/******************************************************************************************************************************************/
#include "Application.hpp"

namespace Starting
{
    void Application::Initialize()
    {
        Logger::Log::InitAllLogger();
        SQ_APP_INFO("Squeamish v{}.{}", 0, 1);
        m_service_builder = std::make_unique<Builders::ServiceBuilder>();
        m_engine_builder = std::make_unique<Builders::EngineBuilder>();
        m_view_model_builder = std::make_shared<Builders::ViewModelBuilder>();
        this->SetAllService();
        this->SetAllEngine();
    }

    void Application::SetAllService()
    {
        this->SetServiceBuilder<Services::GraphicInitializerService>();
        this->SetServiceBuilder<Services::AudioInitializerService>();
        this->SetServiceBuilder<Services::ImGUIServiceInitializer>();
        this->SetServiceBuilder<Services::JsonLoaderService>();
        this->SetServiceBuilder<Services::ShaderLoaderService>();
        this->SetServiceBuilder<Services::ShaderService>();
        this->SetServiceBuilder<Services::FramebufferService>();
        this->SetServiceBuilder<Services::TextureLoaderService>();
        this->SetServiceBuilder<Services::CameraService>();
        this->SetServiceBuilder<Services::StateService>();
        this->SetServiceBuilder<Services::LoaderService>();
        this->SetServiceBuilder<Services::MouseInputService>();
        this->SetServiceBuilder<Services::KeyboardInputService>();
    }

    void Application::SetAllEngine()
    {
        this->SetEngineBuilder<Engines::GUIEngine>();
        this->SetEngineBuilder<Engines::SceneEngine>();
        this->SetEngineBuilder<Engines::MainEngine>();
    }

    void Application::ShutAllService()
    {
        this->DeleteReference<Services::GraphicInitializerService>();
        this->DeleteReference<Services::AudioInitializerService>();
        this->DeleteReference<Services::ImGUIServiceInitializer>();
        this->DeleteReference<Services::JsonLoaderService>();
        this->DeleteReference<Services::ShaderLoaderService>();
        this->DeleteReference<Services::ShaderService>();
        this->DeleteReference<Services::FramebufferService>();
        this->DeleteReference<Services::TextureLoaderService>();
        this->DeleteReference<Services::CameraService>();
        this->DeleteReference<Services::StateService>();
        this->DeleteReference<Services::LoaderService>();
        this->DeleteReference<Services::MouseInputService>();
        this->DeleteReference<Services::KeyboardInputService>();
    }

    void Application::ShutAllEngine()
    {
        this->DeleteReference<Engines::GUIEngine>();
        this->DeleteReference<Engines::SceneEngine>();
        this->DeleteReference<Engines::MainEngine>();
    }

    void Application::Run()
    {
        this->StartAllBuilder();
        main_engine = IoC::Container::Container::GetInstanceContainer()->GetReference<Engines::MainEngine>();
        if (!main_engine)
        { 
            SQ_APP_ERROR("Class {} in function {} : Main engine is not referenced yet", __FILE__, __FUNCTION__);
        }
        else
        {
            main_engine->StartScreen(m_view_model_builder);
            main_engine->MainLoop(m_view_model_builder);
        }
    }

    void Application::Shutdown()
    {

        if (main_engine)
        {
            main_engine.reset();
        }
        this->EndAllBuilder();
        this->ShutAllEngine();
        this->ShutAllService();
        SQ_APP_INFO("Squeamish shutdown");
        Logger::Log::Shutdown();
    }

    void Application::EndAllBuilder()
    {

        if (m_service_builder)
        {
            m_service_builder->OnBuilderEnd();
            m_service_builder.reset();
        }
        if (m_engine_builder)
        {
            m_engine_builder->OnBuilderEnd();
            m_engine_builder.reset();
        }
        if (m_view_model_builder)
        {
            m_view_model_builder->OnBuilderEnd();
            m_view_model_builder.reset();
        }
    }

    void Application::StartAllBuilder()
    {
        std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
        if (ioc_module)
        {
            ioc_module->StartBuilder(m_service_builder.get());
            ioc_module->StartBuilder(m_engine_builder.get());
            ioc_module->StartBuilder(m_view_model_builder.get());
            ioc_module.reset();
        }
    }
}