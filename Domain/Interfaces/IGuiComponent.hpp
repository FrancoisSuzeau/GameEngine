/******************************************************************************************************************************************/
// File : IGuiComponent.hpp
// Purpose : the interface engine 
/******************************************************************************************************************************************/
#ifndef IGUICOMPONENT_H
#define IGUICOMPONENT_H

#include <iostream>
#include <functional>

namespace Views {

	class IGuiComponent
	{
	public:
		virtual ~IGuiComponent() {}
		void SetParent(IGuiComponent* parent) {
			this->m_parent = std::shared_ptr<IGuiComponent>(parent);
		}

		IGuiComponent* GetParent() const {
			return this->m_parent.get();
		}

		virtual void Add(std::shared_ptr<IGuiComponent> component) {};
		virtual void Remove(std::shared_ptr<IGuiComponent>) {};
		virtual bool IsComposite() const {
			return false;
		}

		virtual void Render(bool show = true) = 0;

	protected:
		std::shared_ptr<IGuiComponent> m_parent;

	};
	
}
#endif