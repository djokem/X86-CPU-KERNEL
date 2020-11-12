/*
 * Test.cpp
 *
 *  Created on: Jul 24, 2018
 *      Author: OS1
 */


#include <iostream.h>
#include "Timer.h"
#include "Thread.h"
#include "Pcb.h"
#include "Semaphor.h"
#include "Event.h"
#include "Queue.h"


//PREPAREENTRY(9,0);
Semaphore* sem = new Semaphore();
class Nit: public Thread{
public:
	char im;

	Nit(char a, StackSize st, Time t):Thread(st,t){
		im = a;
	}
	void run(){
		if(im == 'B'){
			for (int i = 0; i < 15; ++i) {
				cout<<"u "<< im <<": i = "<<i<<endl;
				Thread::sleep(10);
			}
		}
		else if(im == 'C'){
			for (int i = 0; i < 15; ++i) {
				cout<<"u "<< im <<": i = "<<i<<endl;
				Thread::sleep(20);
			}
		}
		else if(im == 'D'){
					for (int i = 0; i < 15; ++i) {
						cout<<"u "<< im <<": i = "<<i<<endl;
						Thread::sleep(40);
					}
				}
		else{
				for (int i = 0; i < 15; ++i) {
					cout<<"u "<< im <<": i = "<<i<<endl;
					Thread::sleep(10);
				}
		}
	}
	~Nit();
};

Nit::~Nit(){
	waitToComplete();
}

extern int userMain(int argc, char* argv[]);
extern PCB* running;
extern int GlobalFlag;
extern Queue* sleepQueue;
extern Time timeToSleep;
int main(int argc, char* argv[]){

	/*
	Nit* n2 = new Nit('C',4096,1);
	Nit* n3 = new Nit('D',4096,1);
	Nit* n1 = new Nit('B',4096,1);

	Nit* n4 = new Nit('A',4096,1);
	Nit* n5 = new Nit('E',4096,1);
	Nit* n6 = new Nit('F',4096,1);
	Nit* n7 = new Nit('G',4096,1);
	Nit* n8 = new Nit('H',4096,1);
	Nit* n9 = new Nit('J',4096,1);
	Nit* n10 = new Nit('I',4096,1);
	Nit* n11 = new Nit('K',4096,1);
	Nit* n12 = new Nit('L',4096,1);
	Nit* n13 = new Nit('M',4096,1);
	Nit* n14 = new Nit('N',4096,1);
	Nit* n15 = new Nit('O',4096,1);
	Nit* n16 = new Nit('P',4096,1);
	Nit* n17 = new Nit('R',4096,1);
	Nit* n18 = new Nit('S',4096,1);
	Nit* n19 = new Nit('T',4096,1);
	Nit* n20 = new Nit('U',4096,1);
*/
//	cout<<running->getID()<<endl;
	inic();
	//dispatch();
	int a = userMain(argc,argv);
	delete sleepQueue;


	/*
	n3->start();
	n1->start();
	n2->start();

	n4->start();
	n5->start();
	n6->start();
	n7->start();
	n8->start();
	n9->start();
	n10->start();
	n11->start();
	n12->start();
	n13->start();
	n14->start();
	n15->start();
	n16->start();
	n17->start();
	n18->start();
	n19->start();
	n20->start();

	for (int i = 0; i < 20; ++i) {
		cout<<"u main: "<<i<<endl;
				for (int k = 0; k<10000; ++k)
					for (int j = 0; j <30000; ++j);
	}

/*
	delete n2;
	delete n3;
	delete n1;

	delete n4;
	delete n5;
	delete n6;
	delete n7;
	delete n8;
	delete n9;
	delete n10;
	delete n11;
	delete n12;
	delete n13;
	delete n14;
	delete n15;
	delete n16;
	delete n17;
	delete n18;
	delete n19;
	delete n20;
*/
	restore();
}
