/******************************************************************************************************************************************/
// File : IoCModule.hpp
// Purpose : An ioc module to connect to all services and then inject necessary data
/******************************************************************************************************************************************/
#ifndef IOCMODULE
#define IOCMODULE
#include "Container/Container.hpp"
#include "IBuilder.hpp"
#include "../Logger/Logger.hpp"

namespace IoC {

	class IocModule
	{
	public:
		IocModule();
		~IocModule();

		template<typename T>
		void LoadService(Builders::IBuilder *builder)
		{
			auto type = std::type_index(typeid(T));

			IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
			if (builder && container)
			{
				container->registerType<T>([]() {
					return new T();
					});

				auto service = container->make<T>();

				builder->Build(type.name(), service);
				SQ_SHARED_TRACE("IoC module : {} loaded", type.name());
			}
		}
		template<typename T>
		void LoadEngine(Builders::IBuilder* builder)
		{
			auto type = std::type_index(typeid(T));
			IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
			if (builder && container)
			{
				container->registerType<T>([]() {
					return new T();
					});
				auto engine = container->make<T>();

				builder->Build(engine);
				SQ_SHARED_TRACE("IoC module : {} loaded", type.name());
			}
		}

		template<typename T>
		void AddView()
		{
			auto type = std::type_index(typeid(T));
			IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
			if (container)
			{
				container->registerType<T>([]() {
					return new T();
					});
				SQ_SHARED_TRACE("IoC module : {} loaded", type.name());
			}
		}

		template<typename T>
		void AddViewModel(Builders::IBuilder* builder)
		{
			auto type = std::type_index(typeid(T));
			IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
			if (builder && container)
			{
				container->registerType<T>([]() {
					return new T();
					});
				auto view_model = container->make<T>();
				builder->Build(Constants::GUIVIEWMODEL, view_model);
				SQ_SHARED_TRACE("IoC module : {} loaded", type.name());
			}
		}

		void StartBuilder(Builders::IBuilder* builder);

	private:

	};
}

#endif