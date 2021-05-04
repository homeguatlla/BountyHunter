#pragma once
#include <memory>

namespace utils
{
	namespace subscriber
	{
		template<class T>
		class ISubscriber
		{		
		public:
			virtual void OnNotification(std::shared_ptr<T> stimulus) = 0;
		};
	}
}
