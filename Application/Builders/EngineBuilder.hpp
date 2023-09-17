/******************************************************************************************************************************************/
// File : EngineBuilder.hpp
// Purpose : A builder for engines
/******************************************************************************************************************************************/
#ifndef ENGINEBUILDER_H
#define ENGINEBUILDER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "IBuilder.hpp"
#include "Container/Container.hpp"

namespace Builders {

	class EngineBuilder : public IBuilder
	{
	public:
		~EngineBuilder() override;
		void Produce() override;
		void Build(std::shared_ptr<Engines::IEngine> engine) override;
		void OnBuilderEnd() override;

	private:

		std::vector<std::shared_ptr<Engines::IEngine>> m_engine;
	};
}

#endif