#ifndef __Singleton_H__
#define __Singleton_H__

#include <mutex>
#include <cassert>

namespace audio_alarm {

	template<typename T>
	struct has_no_destroy
	{
		template <typename C> static char test(decltype(&C::no_destroy));
		template <typename C> static int32_t test(...);
		const static bool value = sizeof(test<T>(0)) == 1;
	};

	template<typename T>
	class Singleton
	{
	public:
		Singleton() = delete;
		~Singleton() = delete;
		Singleton(const Singleton<T>&) = delete;
		Singleton<T>& operator = (const Singleton<T>&) = delete;

	public:
		static T& instance()
		{
			std::call_once(ponce_, &Singleton::init);
			assert(value_ != NULL);
			return *value_;
		}

	private:
		static void init()
		{
			value_ = new T();
			if (!has_no_destroy<T>::value)
			{
				::atexit(destroy);
			}
		}

		static void destroy()
		{
			typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
			T_must_be_complete_type dummy; (void)dummy;

			delete value_;
			value_ = NULL;
		}

	private:
		static std::once_flag ponce_;
		static T* value_;
	};

	template<typename T>
	std::once_flag Singleton<T>::ponce_;

	template<typename T>
	T* Singleton<T>::value_ = NULL;
}

#endif 
