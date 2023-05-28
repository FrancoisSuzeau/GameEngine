/******************************************************************************************************************************************/
// File : IBuilder.hpp
// Purpose : An interface for the builder pattern
/******************************************************************************************************************************************/
#ifndef IBUILDER_H
#define IBUILDER_H

#include "IService.hpp"

namespace Builders {
    class IBuilder {
    public:
        virtual ~IBuilder() {}
        virtual void Produce() = 0;
        virtual void Build(std::string service_name, std::shared_ptr<Services::IService> service_initializer) = 0;
        virtual void OnServicesEnd() = 0;
    };
}
#endif