/*
 * Pcb.cpp
 *
 *  Created on: Jul 24, 2018
 *      Author: OS1
 */
#include "Pcb.h"
#include <dos.h>
#include <iostream.h>
#include "BlockQ.h"
extern int GlobalFlag;
extern PCB* running;
extern int ID;
#include "SCHEDULE.H"


PCB::PCB(Thread* myT,Time tslice, StackSize stsz){
	state = PCB::NEW;
	wtoc = new BlockQ();
#ifndef BCC_BLOCK_IGNORE
	asm pushf
	asm cli

	id = ++ID;
	myThread = myT;
	timeSlice = tslice;
	createContext(wrapper,stsz);
	asm sti
	asm popf
#endif
}

void PCB::wait2complete(){
	if(this->state != DONE && this != running && this->state != PCB::NEW){
		asm cli;
		this->wtoc->append(running);
		asm sti;
		dispatch();
	}
}

void PCB::createContext(void (*body)(), StackSize stsz){
	stsz/=sizeof(unsigned);
	st = new unsigned[stsz];
#ifndef BCC_BLOCK_IGNORE
	st[stsz-3] = 0x200;
	st[stsz-4] = FP_SEG(body);
	st[stsz-5] = FP_OFF(body);
	sp = FP_OFF(st + stsz - 14);
	ss = FP_SEG(st + stsz - 14);
	bp = FP_OFF(st + stsz - 14);
#endif
}

void PCB::wrapper(){
	running->myThread->run();
	running->exitThread();
}

void PCB::exitThread(){
	asm cli;
	running->state = PCB::DONE;
	while(wtoc->isEmpty() != 1){
		Scheduler::put(wtoc->take());
	}
	asm sti;
	dispatch();
}
PCB::~PCB(){
	myThread = 0;
	if(st != 0)
		delete [] st;
	while(wtoc->isEmpty() != 1){
		Scheduler::put(wtoc->take());
	}
	if(wtoc)
		delete wtoc;
	wtoc = 0;
}
