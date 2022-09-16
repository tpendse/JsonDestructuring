#pragma once

#include <memory>

namespace JsonDestructure
{
	template<typename T>
	class ISystemList
	{
	public:
		virtual ~ISystemList() { /* Must remain empty */ }

		virtual void Add(T* item) = 0;

		virtual int Count() = 0;

		virtual std::shared_ptr<T> operator[](unsigned int index) const = 0;
		
		virtual bool Valid() = 0;
	};
}