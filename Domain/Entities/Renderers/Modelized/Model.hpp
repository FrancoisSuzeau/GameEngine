/******************************************************************************************************************************************/
// File : Model.hpp
// Purpose : An interface for the Model renderer
/******************************************************************************************************************************************/
#ifndef MODEL_H
#define MODEL_H

#include "../../Interfaces/IRenderer.hpp"

namespace Renderers {

	class Model : public IRenderer
	{
	public:

		Model();
		~Model();

		void Construct() override;
		void Clean() override;


	protected:
		void Load() override;

	private:
		void Attach();

		typedef IRenderer base;

	};
}

#endif