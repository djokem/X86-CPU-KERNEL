/*
 * Thread.h
 *
 *  Created on: Jul 24, 2018
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_
typedef unsigned int Time;
typedef unsigned long StackSize;

const StackSize defaultStackSize = 4096;
const Time defaultTimeSlice = 2; // default = 2*55ms


class PCB;
class Thread {
public:
	void start();
	void waitToComplete();
	virtual ~Thread();
	static void sleep(Time timeToSleep);
protected:

	friend class PCB;
	Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {}

private:
	PCB* myPCB;

};
 void dispatch ();

#endif /* THREAD_H_ */
