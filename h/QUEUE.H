/*
 * QUEUE.H
 *
 *  Created on: Aug 18, 2017
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "PCB.H"

class Elem{
public:
	PCB *member;
	Time blTime;
	Elem *next;
	Elem(PCB *m, Time t = 10){
		member = m;
		next = 0;
		blTime = t;
	}
};

class Queue {
protected:
	Elem *head;
	Elem *last;
public:
	int br;
	Queue(){
		head = last = 0; br = cnt = 0;
	}
	void append(PCB *mem, Time ti = 10);
	PCB* take();
	int isEmpty();
	Time readFirst(){
		if(head != 0)
			return head->blTime;
		return 0;
	}
	void decrement();
	~Queue();
private:
	Time cnt;
};


#endif /* QUEUE_H_ */
