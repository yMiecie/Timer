/****************************/
/* Author:  MIECIELICA YANN */
/* Date:    17/09/2017 20:16*/
/* P-Name:  Timer           */
/****************************/

#include "TimerController.h"

TimerController::TimerController()
 : Timer::Timer(0, [](Timer *timer) { }, false), m_cached_size(0) {

    clear();

		name = "ThreadController ";
		name = name + id;
}

/*
	ThreadController run() (cool stuf)
*/
void TimerController::run(){

  // Run this thread before
  if(m_handler != NULL)
    m_handler(this);

  unsigned long time = millis();
  int checks = 0;
  for(int i = 0; i < MAX_THREADS && checks <= m_cached_size; i++){
    // Object exists? Is enabled? Timeout exceeded?
    if(m_timers[i]){
      checks++;
      if(m_timers[i]->shouldRun(time)){
        m_timers[i]->run();
      }
    }
  }

  // ThreadController extends Thread, so we should flag as runned thread
  runned();

	// Run this thread before
	/*if(m_handler != NULL)
		m_handler(this);

	unsigned long time = millis();
  for(int i(0); i<m_timers.size(); ++i)
  {
			if(m_timers[i]->shouldRun(time)){
				m_timers[i]->run();
			}
	}

	// ThreadController extends Thread, so we should flag as runned thread
	runned();*/
}


/*
	List controller (boring part)
*/
bool TimerController::add(Timer *timer){

    // Check if the Thread already exists on the array
    for(int i = 0; i < MAX_THREADS; i++){
      if(m_timers[i] != NULL && m_timers[i]->id == timer->id)
        return true;
    }

    // Find an empty slot
    for(int i = 0; i < MAX_THREADS; i++){
      if(!m_timers[i]){
        // Found a empty slot, now add Thread
        m_timers[i] = timer;
        m_cached_size++;
        return true;
      }
    }

    // Array is full
    return false;

	// Check if the Thread already exists on the array
  /*for(int i(0); i<m_timers.size(); ++i)
  {
		if(m_timers[i]->id == timer->id)
			return true;
	}

  // Add
  m_timers.push_back(timer);

	return false;*/
}

void TimerController::remove(int id){

  // Find Threads with the id, and removes
	for(int i = 0; i < MAX_THREADS; i++){
		if(m_timers[i]->id == id){
			m_timers[i] = NULL;
			m_cached_size--;
			return;
		}
	}

  /*std::vector<Timer*>::iterator it;

  for( it=m_timers.begin() ; it < m_timers.end(); ) {
      if ( (*it)->id == id) {
        Serial.printf("[TimerController::remove] Timer will be erase: %i - %s\n", (*it)->id, (*it)->name.c_str());
        it = m_timers.erase(it);
      } else {
        ++it;
      }
  }*/
}

void TimerController::remove(Timer *timer){
	remove(timer->id);
}

void TimerController::clear(){

  for(int i = 0; i < MAX_THREADS; i++){
		m_timers[i] = NULL;
	}
	m_cached_size = 0;

  /*std::vector<Timer*>::iterator it;

  for( it=m_timers.begin() ; it < m_timers.end(); ) {
    it = m_timers.erase(it);
  }*/
}

int TimerController::size(){

  int size = 0;
  for(int i = 0; i < MAX_THREADS; i++){
    if(m_timers[i])
      size++;
  }
  m_cached_size = size;

  return m_cached_size;

	//return m_timers.size();
}
