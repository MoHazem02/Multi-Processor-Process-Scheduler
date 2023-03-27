#include "UI.h"
#include<iostream>
using namespace std;
void UI::printInteractive(int Time, PROCESSOR** ProccessorList, int ProcessorsCount, LinkedQueue<PROCESS*> BLK, int BSize, LinkedQueue<PROCESS*> RUN, int RSize, LinkedQueue<PROCESS*> TRM, int TSize)
{
	cout << "Current Timestep:" << Time << "\n"
		"-------------  RDY processes  -------------" << endl;
	for (int i = 0; i < ProcessorsCount; i++)
	{
		cout << "processor " << i + 1 << " [" << ProccessorList[i]->type << "]: " <<
			ProccessorList[i]->RSIZE << " RDY: ";
		for (int j = 0; j < RSize; j++)
		{
			PrintQueue(ProccessorList[j]);
		}
	}
	cout << "------------ - BLK processes------------ - " << endl;
	cout << BSize << " BLK: "; PrintQueue(BLK);
	cout << "\n------------ - RUN processes------------ - " << endl;
	cout << RSize << " RUN: "; PrintQueue(RUN);
	cout << "\n------------ - TRM processes------------ - " << endl;
	cout << TSize << " TRM: "; PrintQueue(TRM);
	cout << "PRESS ANY KEY TO MOVE TO NEXT STEP !" << endl;
}
void UI::printStepByStep(int Time, PROCESSOR** ProccessorList, int ProcessorsCount, LinkedQueue<PROCESS*> BLK, int BSize, LinkedQueue<PROCESS*> RUN, int RSize, LinkedQueue<PROCESS*> TRM, int TSize)
{
	cout << "Current Timestep:" << Time << "\n"
		"-------------  RDY processes  -------------" << endl;
	for (int i = 0; i < ProcessorsCount; i++)
	{
		cout << "processor " << i + 1 << " [" << ProccessorList[i]->type << "]: " <<
			ProccessorList[i]->RSIZE << " RDY: ";
		for (int j = 0; j < RSize; j++)
		{
			PrintQueue(ProccessorList[j]);
		}
	}
	cout << "------------ - BLK processes------------ - " << endl;
	cout << BSize << " BLK: "; PrintQueue(BLK);
	cout << "\n------------ - RUN processes------------ - " << endl;
	cout << RSize << " RUN: "; PrintQueue(RUN);
	cout << "\n------------ - TRM processes------------ - " << endl;
	cout << TSize << " TRM: "; PrintQueue(TRM);
}
enum UI::MODE
{
	INTERACTIVE,
	StepByStep,
	Silent
};
void UI::PrintQueue(PROCESSOR* P)
{
	LinkedQueue<PROCESS*> Q2 = P->RDY;
	PROCESS* tmp;
	while (!P->RDY.isEmpty())
	{
		P->RDY.dequeue(tmp);
		cout << tmp->ID << ", ";
		Q2.enqueue(tmp);
	}
	cout << endl;
	P->RDY = Q2;
}

void UI::PrintQueue(LinkedQueue<PROCESS*> Q)
{
	LinkedQueue<PROCESS*> Q2 = Q;
	PROCESS* tmp;
	while (!Q.isEmpty())
	{
		Q.dequeue(tmp);
		cout << tmp->ID << ", ";
		Q2.enqueue(tmp);
	}
	cout << endl;
	Q = Q2;
}
