/******************************************************************************************************************************************/
// File : EngineBuilder.cpp
// Purpose : Implementing the engine builder
/******************************************************************************************************************************************/
#include "EngineBuilder.hpp"

using namespace Builders;

EngineBuilder::~EngineBuilder()
{
}

void EngineBuilder::Produce()
{
	for (std::vector<std::shared_ptr<Engines::IEngine>>::iterator it = m_engine.begin(); it != m_engine.end(); ++it)
	{
		it[0]->Construct();
	}
}

void EngineBuilder::Build(std::string service_name, std::shared_ptr<Services::IService> service_initializer)
{
}

void EngineBuilder::Build(std::shared_ptr<Engines::IEngine> engine)
{
	m_engine.push_back(engine);
}

void EngineBuilder::OnBuilderEnd()
{
	for (std::vector<std::shared_ptr<Engines::IEngine>>::iterator it = m_engine.begin(); it != m_engine.end(); ++it)
	{
		it->reset();
	}
}
