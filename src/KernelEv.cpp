/*
 * KernelEv.cpp
 *
 *  Created on: Aug 11, 2018
 *      Author: OS1
 */


#include <iostream.h>
#include "KernelEv.h"
#include "IVTEntry.h"
#include "SCHEDULE.H"
#include "PCB.h"
extern int GlobalFlag;
extern PCB* running;
KernelEv::KernelEv(IVTNo ivtNo){

	if((unsigned int)ivtNo <= (unsigned int)256){
		if(IVTEntry::IVTable[ivtNo]){
			blocked = 0;
			value = 0;
			this->owner = running;
			this->ivtNo = ivtNo;
			IVTEntry::IVTable[ivtNo]->myKernelEv = this;
		}
	}
}

void KernelEv::wait(){
	if(this->owner != running){
		return;
	}
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
	if(this->value == 0){
		running->state = PCB::BLOCKED;
		blocked = running;
		GlobalFlag = 3;
		dispatch();
	}
	else{
		this->value = 0;
		GlobalFlag = 1;
	}
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}
void KernelEv::signal(){
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
	if(this->blocked == 0)
		value = 1;
	else{
		blocked->state = PCB::READY;
		Scheduler::put(blocked);
		blocked = 0;
	}
	GlobalFlag = 1;
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}


IVTNo KernelEv::getIVTentryNo(){
	return ivtNo;
}

KernelEv::~KernelEv(){
	if(blocked){
		Scheduler::put(this->blocked);
		this->blocked = 0;
	}
	delete IVTEntry::IVTable[ivtNo];

	IVTEntry::IVTable[ivtNo] = 0;
}
