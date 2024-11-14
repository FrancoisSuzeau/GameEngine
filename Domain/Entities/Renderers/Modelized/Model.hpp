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
		Model(Model& other);
		~Model();

		void Construct() override;
		void Clean() override;

		void Draw(size_t index) override;
		void Draw(size_t index, std::vector<unsigned int> light_textures_ids) override;
		std::vector<Texturate> GetMeshTextures(size_t index) const override;
		size_t GetNbMeshes() const override;


	protected:
		void Load() override;

	private:
		void Attach();

		std::vector<std::unique_ptr<Mesh>> m_meshes;

		typedef IRenderer base;

	};
}

#endif