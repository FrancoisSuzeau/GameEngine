/******************************************************************************************************************************************/
// File : Canvas.hpp
// Purpose : The canvas view of the scene
/******************************************************************************************************************************************/
#ifndef CANVAS_H
#define CANVAS_H

#include "IView.hpp"

namespace Views
{
	class Canvas : public IView
	{
	public:
		Canvas();
		void Render() override;
	};
}

#endif