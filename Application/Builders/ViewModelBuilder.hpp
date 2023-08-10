/******************************************************************************************************************************************/
// File : ViewModelBuilder.hpp
// Purpose : A builder for view model
/******************************************************************************************************************************************/
#ifndef VIEWMODELBUILDER_H
#define VIEWMODELBUILDER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>

#include "IBuilder.hpp"
#include "Container/Container.hpp"

namespace Builders {

	class ViewModelBuilder : public IBuilder
	{
	public:
		~ViewModelBuilder() override;
		void Produce() override;
		void Build(std::string service_name, std::shared_ptr<Services::IService> service_initializer) override;
		void Build(std::shared_ptr<Engines::IEngine> engine) override;
		void Build(std::string view_model_name, std::shared_ptr<ViewModels::IViewModel> view_model) override;
		void OnBuilderEnd() override;
		std::shared_ptr<ViewModels::IViewModel> GetViewModel(std::string const view_model_name);
	private:
		std::map<std::string, std::shared_ptr<ViewModels::IViewModel>> m_view_models;
	};
}

#endif