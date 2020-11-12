/*
 * Global.cpp
 *
 *  Created on: Jul 24, 2018
 *      Author: OS1
 */
#include "Pcb.h"
#include "QUEUE.H"
#include "Thread.h"
#include "Semaphor.h"
#include <iostream.h>
volatile int id = 0;
volatile int req4consw = 0;
volatile int counter = 2;
volatile int GlobalFlag = 1;
volatile PCB* running = new PCB(0,PCB::StartThrad);
volatile Queue* sleepQueue = new Queue();
volatile Time timeToSleep = 10;
volatile int ID = 0;
int EVENTKLIK = 0;

int PCB::NEW = 0;
int PCB::READY = 1;
int PCB::BLOCKED = 2;
int PCB::StartThrad = 3;
int PCB::IDLE = 4;
int PCB::DONE = 5;
int PCB::SLEEP = 6;

void idle(){
	while(1){
			for (int k = 0; k<10000; ++k)
				for (int j = 0; j <30000; ++j)
					for(int s = 0; s<3000;++s);
	}
}
volatile PCB* idleThread = new PCB(1,PCB::IDLE);
