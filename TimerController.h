/****************************/
/* Author:  MIECIELICA YANN */
/* Date:    17/09/2017 20:16*/
/* P-Name:  Timer           */
/****************************/

#include <Arduino.h>
#include <functional>
#include <vector>
#include "Timer.h"

#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#define MAX_THREADS 100

class TimerController: public Timer {

protected:
	// std::vector<Timer*>      m_timers;
	Timer* 									 m_timers[MAX_THREADS];
	int                      m_cached_size;

public:
	TimerController();

	// run() Method is overrided
	void run();

	// Adds a thread in the first available slot (remove first)
	// Returns if the Thread could be added or not
	bool add(Timer *timer);

	// remove the thread (given the Thread* or ThreadID)
	void remove(int id);
	void remove(Timer *timer);

	// Removes all threads
	void clear();

	// Return the quantity of Threads
	int size();
};

#endif
