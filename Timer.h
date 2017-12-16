/****************************/
/* Author:  MIECIELICA YANN */
/* Date:    17/09/2017 20:16*/
/* P-Name:  Timer           */
/****************************/
#include <Arduino.h>
#include <functional>

#ifndef TIMER_H
#define TIMER_H

class Timer{
protected:
	// Desired interval between runs
	unsigned long m_interval;

	// Last runned time in Ms
	unsigned long m_last_run;

	// Scheduled run in Ms (MUST BE CACHED)
	unsigned long m_cached_next_run;

  bool m_repeats;

  bool m_wasRunned;

	/*
		IMPORTANT! Run after all calls to run()
		Updates last_run and cache next run.
		NOTE: This MUST be called if extending
		this class and implementing run() method
	*/
	void runned(unsigned long time);

	// Default is to mark it runned "now"
	void runned() { runned(millis()); }

	// Callback for run() if not implemented
  std::function< void (Timer*)> m_handler = [](Timer *timer) { };

public:

	// If the current Thread is enabled or not
	bool enabled;

	// ID of the Thread (initialized from memory adr.)
	int id;

  // Thread Name (used for better UI).
  String name;

  Timer(unsigned long interval, std::function< void (Timer*)> handler, bool repeats);

	// Set the desired interval for calls, and update _cached_next_run
	virtual void setInterval(unsigned long interval);

	// Should be run once
	virtual void setRepeats(bool repeats);

	// Return if the Thread should be runned or not
	virtual bool shouldRun(unsigned long time);

	// Default is to check whether it should run "now"
	bool shouldRun() { return shouldRun(millis()); }

	// Callback set
	void setHandler(std::function< void (Timer*)>);

	// Runs Thread
	virtual void run();
};

#endif
