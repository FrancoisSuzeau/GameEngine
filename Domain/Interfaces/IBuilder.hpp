/******************************************************************************************************************************************/
// File : IBuilder.hpp
// Purpose : An interface for the builder pattern
/******************************************************************************************************************************************/
#ifndef IBUILDER_H
#define IBUILDER_H

#include "IService.hpp"
#include "IEngine.hpp"
#include "IViewModel.hpp"
#include <memory>
#include <string>

namespace Builders {
    class IBuilder {
    public:
        virtual ~IBuilder() {}
        virtual void Produce() = 0;
        virtual void Build(std::string service_name, std::shared_ptr<Services::IService> service_initializer) = 0;
        virtual void Build(std::shared_ptr<Engines::IEngine> engine) = 0;
        virtual void Build(std::string view_model_name, std::shared_ptr<ViewModels::IViewModel> view_model) = 0;
        virtual void OnBuilderEnd() = 0;
    };
}
#endif