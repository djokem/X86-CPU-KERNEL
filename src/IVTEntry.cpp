/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 11, 2018
 *      Author: OS1
 */
#include <dos.h>
#include <iostream.h>
#include <stdlib.h>
#include "IVTEntry.h"
#include "KernelEv.h"

IVTEntry** IVTEntry::IVTable = new IVTEntry*[256];

// Zabranjuje prekide
#define lock asm cli
// Dozvoljava prekide
#define unlock asm sti


IVTEntry::IVTEntry(IVTNo no, InterruptRoutine newIR){
	this->ivtNo = no;
	IVTable[this->ivtNo] = this;
	this->oldIR = 0;
	this->myKernelEv = 0;

#ifndef BCC_BLOCK_IGNORE
	asm cli;

	this->oldIR = getvect(this->ivtNo);
	setvect(this->ivtNo, newIR);

	asm sti;
#endif
}

void IVTEntry::callOldIR(){
	oldIR();
}

void IVTEntry::signal(){
	myKernelEv->signal();
}

IVTEntry* IVTEntry::getIVTable(){
	return *IVTable;
}
IVTEntry::~IVTEntry(){
#ifndef BCC_BLOCK_IGNORE
	asm cli;

	setvect(this->ivtNo, this->oldIR);

	asm sti;

#endif
	this->myKernelEv = 0;
	this->oldIR = 0;
}
