/*
 * BlockQ.h
 *
 *  Created on: Jul 25, 2018
 *      Author: OS1
 */

#ifndef BLOCKQ_H_
#define BLOCKQ_H_
#include "Pcb.h"

class Elemn{
public:
	PCB *member;
	Elemn *next;
	Elemn(PCB *m){
		member = m;
		next = 0;
	}
};

class BlockQ {
protected:
	Elemn *head;
	Elemn *last;
public:
	int br;
	BlockQ(){
		head = last = 0; br = 0;
	}
	void append(PCB *mem);
	PCB* take();
	int isEmpty();
};


#endif /* BLOCKQ_H_ */
