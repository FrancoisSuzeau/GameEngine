/******************************************************************************************************************************************/
// File : IService.hpp
// Purpose : A service interface
/******************************************************************************************************************************************/
#ifndef ISERVICE_H
#define ISERVICE_H

namespace Services {

	class IService
	{
	public:
		virtual ~IService() {}
		virtual void Init() = 0;
		virtual void DeInit() = 0;
	};
}

#endif