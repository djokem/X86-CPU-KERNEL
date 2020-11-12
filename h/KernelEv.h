/*
 * KernelEv.h
 *
 *  Created on: Aug 11, 2018
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

class Thread;
class PCB;
class KernelSem;
#include "Event.h"
class KernelEv{
private:
	IVTNo ivtNo;
	PCB* owner;
	PCB* blocked;
	int value;
public:
	KernelEv (IVTNo ivtNo);
	~KernelEv();
	IVTNo getIVTentryNo();
protected:
	friend class IVTEntry;
	friend class Event;

	//premesteno iz public
	void wait ();
	void signal();
};


#endif /* KERNELEV_H_ */
