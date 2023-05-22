/******************************************************************************************************************************************/
// File : IService.hpp
// Purpose : An interface for Opengl / SDL / Json initialisation service
/******************************************************************************************************************************************/
#ifndef ISERVICE_H
#define ISERVICE_H



namespace Services {

	class IService {

	public :
		virtual bool Init() = 0;
		virtual void DeInit() = 0;
		

	protected :
		virtual void ShowError(std::string error_message) = 0;
		bool init_succeded;
		std::string title;
	};
}

#endif