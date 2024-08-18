/******************************************************************************************************************************************/
// File : Model.hpp
// Purpose : An interface for the Model renderer
/******************************************************************************************************************************************/
#ifndef MODEL_H
#define MODEL_H

#include "../../../Interfaces/IRenderer.hpp"
#include "Mesh.hpp"

namespace Renderers {

	class Model : public IRenderer
	{
	public:

		Model(std::vector<std::unique_ptr<Mesh>> meshes);
		~Model();

		void Construct() override;
		void Clean() override;


	protected:
		void Load() override;

	private:
		void Attach();

		std::vector<std::unique_ptr<Mesh>> m_meshes;

		typedef IRenderer base;

	};
}

#endif