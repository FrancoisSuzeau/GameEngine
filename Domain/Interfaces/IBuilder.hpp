/******************************************************************************************************************************************/
// File : IBuilder.hpp
// Purpose : An interface for the builder pattern
/******************************************************************************************************************************************/
#ifndef IBUILDER_H
#define IBUILDER_H

namespace Builders {
    class IBuilder {
    public:
        virtual ~IBuilder() {}
        virtual void ProducePartA() const = 0;
    };
}
#endif