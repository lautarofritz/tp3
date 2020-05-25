#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread{
	private:
		std::thread thread;

	public:
		Thread();
		void empezar();
		void unir();
		virtual int operator()() = 0;
		virtual ~Thread();
};

#endif
