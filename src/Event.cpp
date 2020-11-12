/*
 * Event.cpp
 *
 *  Created on: Aug 11, 2018
 *      Author: OS1
 */
// Zabranjuje prekide
#define lock asm cli
// Dozvoljava prekide
#define unlock asm sti
#include "Event.h"
#include "KernelEv.h"
#include <iostream.h>
KernelEv* Event::getMyImpl(){
	return myImpl;
}

Event::Event(IVTNo ivtNo){
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
	myImpl = new KernelEv(ivtNo);
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal() {
	myImpl->signal();
}

Event::~Event(){
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
	delete myImpl;
	myImpl = 0; //
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}
