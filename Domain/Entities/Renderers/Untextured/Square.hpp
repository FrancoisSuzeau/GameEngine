/******************************************************************************************************************************************/
// File : Square.hpp
// Purpose : An interface for the Square renderer
/******************************************************************************************************************************************/
#ifndef SQUARE_H
#define SQUARE_H

#include "../../../Interfaces/IRenderer.hpp"

namespace Renderers {

	

	class Square : public IRenderer
	{
	public:
		
		Square();
		~Square();

		void Construct() override;
		void Clean() override;


	protected:
		void Attach();
		void Load();
		std::vector<unsigned int> m_indices;
		unsigned int m_bytes_indices_size;

	private:
		typedef IRenderer base;


	};
}

#endif