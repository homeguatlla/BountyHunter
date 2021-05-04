#pragma once

#include "ISubscriber.h"
#include <memory>

namespace utils
{
	namespace subscriber
	{
		template<class T>
		class IPublisher
		{		
		public:
			virtual ~IPublisher() = default;
			virtual bool Subscribe(ISubscriber<T>* subscriber) = 0;
			virtual bool UnSubscribe(ISubscriber<T>* subscriber) = 0;
			virtual void NotifyAll(std::shared_ptr<T> event) = 0;
		};
	}
}
