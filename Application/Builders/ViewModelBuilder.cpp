/******************************************************************************************************************************************/
// File : ViewModelBuilder.cpp
// Purpose : Implementing the engine builder
/******************************************************************************************************************************************/
#include "ViewModelBuilder.hpp"
std::vector<std::shared_ptr<ViewModels::IViewModel>> Builders::ViewModelBuilder::m_view_models;
namespace Builders
{
	ViewModelBuilder::~ViewModelBuilder()
	{
	}

	void ViewModelBuilder::Produce()
	{
		for (std::vector<std::shared_ptr<ViewModels::IViewModel>>::iterator it = m_view_models.begin(); it != m_view_models.end(); ++it)
		{
			if (it[0])
			{
				it[0]->Construct();
			}
		}
	}

	void ViewModelBuilder::Build(std::string service_name, std::shared_ptr<Services::IService> service_initializer)
	{
	}
	void ViewModelBuilder::Build(std::shared_ptr<ViewModels::IViewModel> view_model)
	{
		if (view_model)
		{
			m_view_models.push_back(view_model);
		}
	}
	void ViewModelBuilder::Build(std::shared_ptr<Engines::IEngine> engine)
	{

	}

	void ViewModelBuilder::OnBuilderEnd()
	{
		for (std::vector<std::shared_ptr<ViewModels::IViewModel>>::iterator it = m_view_models.begin(); it != m_view_models.end(); ++it)
		{
			if (it[0])
			{
				it[0]->DeConstruct();
				it->reset();
			}
		}
	}
}


