/*
 * BlockQ.cpp
 *
 *  Created on: Jul 25, 2018
 *      Author: OS1
 */
#include "BlockQ.h"
#include "Pcb.h"
int BlockQ::isEmpty(){
	if(br != 0)
		return 0;
	return 1;
}

PCB* BlockQ::take(){
	if(head){
		Elemn *hlp = head;
		PCB* p = hlp->member;
		p->state = PCB::READY;
		head= head->next;
		hlp->next = 0;
		delete hlp;
		br--;
		return p;
	}
	return 0;
}

void BlockQ::append(PCB* pcb){

	pcb->state = PCB::BLOCKED;
	if(head)
		last = last->next = new Elemn(pcb);
	else
		head = last = new Elemn(pcb);
	br++;
}
