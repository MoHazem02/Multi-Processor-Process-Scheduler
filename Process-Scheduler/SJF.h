#pragma once
#include "PROCESSOR.h"
#include "LinkedPriorityQueue.h"
#include "Scheduler.h"
class SJF : public PROCESSOR
{
private:
	LinkedPriorityQueue<PROCESS*>RDY;
public:
	SJF(Scheduler* scheduler);
	void ScheduleAlgo() override;
	bool PromoteProcess(int x);
	PROCESS* removeTopOfMyRDY() override;
	void addToMyRdy(PROCESS*process);  //Schedular class will set RDYLIST
	void PrintMyReady() override;
	int CalculateExpectedFinish() override;
	int CalculateTRT() override;
};

