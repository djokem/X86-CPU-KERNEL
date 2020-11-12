/*
 * Event.h
 *
 *  Created on: Aug 11, 2018
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "IVTEntry.h"
#include <iostream.h>
#define PREPAREENTRY(ivtno,old) \
void interrupt routine##ivtno(...); \
IVTEntry ent##ivtno(ivtno,&routine##ivtno); \
void interrupt routine##ivtno(...) { \
	if (old) ent##ivtno.callOldIR(); \
	ent##ivtno.signal(); \
}


class KernelEv;
typedef unsigned char IVTNo;
class Event{
public:
	Event(IVTNo ivtNo);
	~Event();
	void wait();
	KernelEv* getMyImpl();
protected:
	friend class KernelEv;
	void signal();
private:
	KernelEv* myImpl;
};



#endif /* EVENT_H_ */
