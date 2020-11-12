/*
 * Semaphore.cpp
 *
 *  Created on: Jul 25, 2018
 *      Author: OS1
 */

#include "BlockQ.h"
#include "Semaphor.h"
#include "SCHEDULE.H"
#include "Pcb.h"
#include <iostream.h>

extern PCB* running;
extern int GlobalFlag;
class KernelSem{
public:

	int val;
	KernelSem(int value);
	int Wait(int toBlock);
	void Signal();
	inline int getVal(){
		return val;
	}
private:
	BlockQ* blockQueue;
};



KernelSem::KernelSem(int value){
	val = value;
	blockQueue = new BlockQ();
}
int KernelSem::Wait(int toBlock){
	if(toBlock != 0){
		--val;
		if(val < 0){
			blockQueue->append(running);
			GlobalFlag = 3;
			dispatch();
			return 1;
		}
		return 0;
	}
	else{
		if(val <= 0){
			return -1;
		}
		else
			--val;
		return 0;
	}
}
void KernelSem::Signal(){
	++val;
	if(val<=0){
		PCB* pom = blockQueue->take();
		if(pom){
			Scheduler::put(pom);
		}
	}
}




Semaphore::Semaphore(int init):myImpl(new KernelSem(init)){}

Semaphore::~Semaphore(){
	if(myImpl)
		delete myImpl;
}

int Semaphore::wait(int toBlock){
	int k = -2;
#ifndef BCC_BLOCK_IGNORE
	asm cli
	k = myImpl->Wait(toBlock);
	asm sti
#endif
	return k;
}

void Semaphore::signal(){
#ifndef BCC_BLOCK_IGNORE
	asm cli
	myImpl->Signal();
	asm sti
#endif
}

int Semaphore::val() const{
	return myImpl->getVal();
}




