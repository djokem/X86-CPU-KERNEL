/*
 * IVTEntry.h
 *
 *  Created on: Aug 11, 2018
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_



typedef unsigned char IVTNo;
typedef void interrupt (*InterruptRoutine)(...);

class KernelEv;

class IVTEntry{
private:
	static IVTEntry** IVTable;
	IVTNo ivtNo;
	InterruptRoutine oldIR;
	KernelEv* myKernelEv;
public:
	IVTEntry(IVTNo no, InterruptRoutine newIR);
	~IVTEntry();
	static IVTEntry* getIVTable();
	void signal();
	void callOldIR();
protected:
	friend class KernelEv;
};

#endif /* IVTENTRY_H_ */
