/*
 * Pcb.h
 *
 *  Created on: Jul 24, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "Thread.h"
#include "BlockQ.h"
class BlockQ;
class PCB{
public:
	static int NEW, READY, BLOCKED, StartThrad, DONE, IDLE, SLEEP;
	int state;
	Thread * myThread;
	Time timeSlice;

	unsigned* st;
	unsigned ss;
	unsigned sp;
	unsigned bp;
	PCB(Time t, int st){
		state = st;
		timeSlice = t;
	}

	PCB(Thread* myT, Time tslice, StackSize stsz);
	void createContext(void (*body)(), StackSize stsz);
	static void wrapper();
	void exitThread();
	void wait2complete();
	int getID(){
		return id;
	}
	~PCB();
private:
	friend class BlockQ;
	int id;
	BlockQ* wtoc;
};


#endif /* PCB_H_ */
