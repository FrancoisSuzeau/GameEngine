/******************************************************************************************************************************************/
// File : IEngine.hpp
// Purpose : the interface engine 
/******************************************************************************************************************************************/
#ifndef IENGINE_H
#define IENGINE_H

namespace Engines {


	class IEngine
	{
	public:
		virtual ~IEngine() {}
		virtual void Construct() = 0;

	protected:

		virtual void InitFrame() = 0;
		virtual void EndFrame() = 0;
	};
}
#endif