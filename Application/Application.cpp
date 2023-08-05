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
        m_view_model_builder = std::make_unique<Builders::ViewModelBuilder>();
        this->SetAllService();
        this->SetAllEngine();
    }

    void Application::SetAllService()
    {
        this->SetServiceBuilder<Services::GraphicInitializerService>();
        this->SetServiceBuilder<Services::AudioInitializerService>();
        this->SetServiceBuilder<Services::ImGUIServiceInitializer>();
        this->SetServiceBuilder<Services::StateService>();
        this->SetServiceBuilder<Services::JsonLoaderService>();
        this->SetServiceBuilder<Services::ShaderLoaderService>();
        this->SetServiceBuilder<Services::ShaderService>();
    }

    void Application::SetAllEngine()
    {
        this->SetEngineBuilder<Engines::GUIEngine>();
        this->SetEngineBuilder<Engines::SceneEngine>();
        this->SetEngineBuilder<Engines::MainEngine>();
    }

    void Application::Run()
    {
        this->StartAllBuilder();
        std::shared_ptr<Engines::MainEngine> main_engine = IoC::Container::Container::GetInstanceContainer()->make<Engines::MainEngine>();
        main_engine->MainLoop();
    }

    void Application::Shutdown()
    {
        main_engine.reset();
        this->EndAllBuilder();
        SQ_APP_INFO("Squeamish shutdown");
        Logger::Log::Shutdown();
    }

    void Application::EndAllBuilder()
    {
        m_service_builder->OnBuilderEnd();
        m_engine_builder->OnBuilderEnd();
        m_view_model_builder->OnBuilderEnd();

        m_service_builder.reset();
        m_engine_builder.reset();
        m_view_model_builder.reset();
    }

    void Application::StartAllBuilder()
    {
        std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
        ioc_module->StartBuilder(m_service_builder.get());
        ioc_module->StartBuilder(m_engine_builder.get());
        ioc_module->StartBuilder(m_view_model_builder.get());
        ioc_module.reset();
    }
}