/*
 * Thread.cpp
 *
 *  Created on: Jul 24, 2018
 *      Author: OS1
 */
#include "Thread.h"
#include "SCHEDULE.H"
#include "Timer.h"
#include "Pcb.h"
#include "QUEUE.H"
#include <iostream.h>
extern int req4consw;
extern int GlobalFlag;
extern Time timeToSleep;
extern int ID;
extern PCB* running;
extern Queue* sleepQueue;
Thread::Thread(StackSize stackSize, Time timeSlice):myPCB(new PCB(this,timeSlice,stackSize)){
}

Thread::~Thread(){
	if(myPCB)
		delete myPCB;
}

void Thread::start(){

#ifndef BCC_BLOCK_IGNORE
	asm cli
	myPCB->state = PCB::READY;
	Scheduler::put(myPCB);
	asm sti
#endif
}

void Thread::waitToComplete(){
	myPCB->wait2complete();
}

void dispatch(){
	asm pushf;
	asm cli;

	req4consw = 1;
	asm int 08h
	//timer();

	//asm sti;

	asm popf;
}

void Thread::sleep(Time time){
	if(time){
		sleepQueue->append(running,time);
		dispatch();
	}
}
