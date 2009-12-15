#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>

class Mutex
{
	public:
		class Lock 
		{
			public:
				Lock(Mutex& mutex) : _mutex(mutex)
				{
					pthread_mutex_lock(&_mutex._ptmutex);
				}

				~Lock()
				{
					pthread_mutex_unlock(&_mutex._ptmutex);
				}

			protected:
				Mutex& _mutex;
		};

		friend class Lock;

		Mutex()
		{
			pthread_mutex_init(&_ptmutex, 0);
		}

		~Mutex()
		{
			pthread_mutex_destroy(&_ptmutex);
		}

	protected:
		pthread_mutex_t _ptmutex;
};

#endif

