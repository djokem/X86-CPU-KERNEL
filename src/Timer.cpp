/*
 * Timer.cpp
 *
 *  Created on: Jul 24, 2018
 *      Author: OS1
 */
#include <dos.h>
#include <iostream.h>
#include "Pcb.h"
#include "QUEUE.H"
#include "SCHEDULE.H"
#include "Thread.h"
// Zabranjuje prekide
#define lock asm cli
// Dozvoljava prekide
#define unlock asm sti

unsigned oldTimerOFF, oldTimerSEG; // stara prekidna rutinp
PCB* mainPCB = 0;

unsigned tbp;
unsigned tsp;
unsigned tss;
extern PCB* running;
extern int req4consw;
extern int counter;
extern int GlobalFlag;
extern Time timeToSleep;
extern PCB* idleThread;
extern void idle();
extern Queue* sleepQueue;

void ready(){
	if(running->state != PCB::IDLE)
		Scheduler::put(running);
	running = Scheduler::get();
}


//extern void tick();
void interrupt timer(){
	if(!req4consw){
		sleepQueue->decrement();
		counter--;
	}
	if((counter == 0 || req4consw)){
#ifndef BCC_BLOCK_IGNORE
			lock
			asm{
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}
			unlock
#endif
			running->sp = tsp;
			running->bp = tbp;
			running->ss = tss;

		//	switch(GlobalFlag){
		//	case 1:
			//	ready();
			//	break;
			//case 2:
		//		//toSleep();
		//		break;
		//	case 3:
		//		running = Scheduler::get();
		//		break;
		//	}

			if(running->state != PCB::IDLE && running->state == PCB::READY)
				Scheduler::put(running);
			running = Scheduler::get();
			if(running == 0){
				running = idleThread;
			}

			tsp = running->sp;
			tss = running->ss;
			tbp = running->bp;
	#ifndef BCC_BLOCK_IGNORE
			lock
			asm {
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}
			unlock
	#endif
			counter = running->timeSlice;
	}
	GlobalFlag = 1;
	req4consw = 0;
	if(!req4consw) asm int 60h;
}


// postavlja novu prekidnu rutinu
void inic(){
#ifndef BCC_BLOCK_IGNORE
	idleThread->createContext(idle,4096);
	asm{
		cli
		push es
		push ax

		mov ax,0   //  ; inicijalizuje rutinu za tajmer
		mov es,ax

		mov ax, word ptr es:0022h //; pamti staru rutinu
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer	 //postavlja
		mov word ptr es:0020h, offset timer //novu rutinu

		mov ax, oldTimerSEG	 //	postavlja staru rutinu
		mov word ptr es:0182h, ax //; na int 60h
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
#endif
}

// vraca staru prekidnu rutinu
void restore(){
#ifndef BCC_BLOCK_IGNORE
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
#endif
}




