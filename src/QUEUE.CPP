#include "Pcb.h"
#include "QUEUE.H"
#include "SCHEDULE.H"
#include <iostream.h>
extern PCB* running;
int Queue::isEmpty(){
	if(br != 0)
		return 0;
	return 1;
}

void Queue::decrement(){
	asm cli;
	if(head){
		head->blTime--;
		if(head->blTime == 0){
			while(head != 0 && head->blTime == 0){
				PCB* p = this->take();
				p->state = PCB::READY;
				Scheduler::put(p);
				p = 0;
			}
		}
	}
	asm sti;
}

void Queue::append(PCB *mem, Time ti){
	asm cli;
	mem->state = PCB::SLEEP;
	if(head){
		Elem* novi = new Elem(mem,ti+cnt);
		Elem* pom = head;

		if(novi->blTime < head->blTime){ // Ubacivanje na pocetak
			novi->next = head;
			head->blTime = novi->blTime;
			head = novi;
		}
		else{
			Elem *pok = 0;
			pom = head;
			Time sum = 0;
			while(pom != 0 && (novi->blTime >= (sum+pom->blTime))){ // Trazenje pozicije u redu
				sum+=pom->blTime;
				pok = pom;
				pom = pom->next;
			}

			Time newTime = novi->blTime - sum;
			novi->blTime = newTime;

			if(pom == 0)//ako je na poslednjem mestu
				last = (last->next = novi);
			else{//ako je u sredini
				pok->next = novi;
				novi->next = pom;
				if(newTime!=0)
					pom->blTime -= newTime;
			}
		}
	}
	else
		last = head = new Elem(mem, ti);
	br++;
	asm sti;
}

Queue::~Queue(){
	if(head){
		while(head != 0){
			Elem *p = head;
			head = head->next;
			delete p;
		}
		head = last = 0;
	}
}

PCB* Queue::take(){
	Elem *hlp = head;
	PCB* p = hlp->member;
	head = head->next;
	hlp->next = 0;
	delete hlp;
	br--;
	return p;
}
