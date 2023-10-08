/******************************************************************************************************************************************/
// File : ViewModelBuilder.cpp
// Purpose : Implementing the engine builder
/******************************************************************************************************************************************/
#include "ViewModelBuilder.hpp"

namespace Builders
{
	ViewModelBuilder::~ViewModelBuilder()
	{
	}

	void ViewModelBuilder::Produce()
	{
		for (std::map<std::string, std::shared_ptr<ViewModels::IViewModel>>::iterator it = m_view_models.begin(); it != m_view_models.end(); ++it)
		{
			if (it->second)
			{
				it->second->Construct();
			}
		}
	}
	
	void ViewModelBuilder::Build(std::string view_model_name, std::shared_ptr<ViewModels::IViewModel> view_model)
	{
		if (view_model && !m_view_models.contains(view_model_name))
		{
			m_view_models.insert_or_assign(view_model_name, view_model);
		}
	}

	void ViewModelBuilder::OnBuilderEnd()
	{
		for (std::map<std::string, std::shared_ptr<ViewModels::IViewModel>>::iterator it = m_view_models.begin(); it != m_view_models.end(); ++it)
		{
			if (it->second)
			{
				it->second.reset();
			}
		}
	}
	std::shared_ptr<ViewModels::IViewModel> ViewModelBuilder::GetViewModel(std::string const view_model_name)
	{
		if (m_view_models.contains(view_model_name))
		{
			return m_view_models.at(view_model_name);
		}

		return nullptr;
	}
}


