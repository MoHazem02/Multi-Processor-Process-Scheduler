#include "SJF.h"

SJF::SJF(Scheduler* sc):PROCESSOR(sc)
{
	STATE = 0;
	RUN = nullptr;
	TYPE = "SJF";
	RSIZE = 0;
	PLoad = 0;
	PUtil = 0;
	TotalBusyTime = 0;
	CooldownTimer = 0;
}

void SJF::ScheduleAlgo()
{
	if (!RUN)
		TotalIdleTime++;
	else
		TotalBusyTime++;

	if (!RUN && RDY.isEmpty())
		return;
	
	if (SchedPtr->random() < 10)
	{
		STOP(SchedPtr->getCoolTime());
		return;
	}

	if (!RUN && !RDY.isEmpty())  //if the processor is IDLE 
	{
		PROCESS* HighestPriorityPROCESS;  
			if (RDY.dequeue(HighestPriorityPROCESS)) 
			{
				RUN = HighestPriorityPROCESS;
				RUN->set_starttime(SchedPtr->get_TIMESTEP());//set start time if process didn't start CPU before 
				STATE = 1;
				RSIZE--;
				ExpectedFinishTime -= HighestPriorityPROCESS->getlastCT();
				SchedPtr->increment_runningcount();
				if (HighestPriorityPROCESS->get_RT() == -1)
					HighestPriorityPROCESS->set_RT(SchedPtr->get_TIMESTEP() - HighestPriorityPROCESS->get_AT());
			}
	}
	else // if there is a process running in the CPU
	{	
		if (SchedPtr->Process_completion(RUN))
		{
			RUN = nullptr;
			STATE = 0;
			return;
		}
		if (SchedPtr->IO_requesthandling(RUN))
		{
			RUN = nullptr;
			STATE = 0;
			return;
		}
	}
		if(RUN) 
		RUN->incrementCountsteps(1);
}

void SJF::addToMyRdy(PROCESS* process)
{
	RDY.enqueue(process, process->get_CT());
	ExpectedFinishTime += process->get_CT()-process->get_countsteps();
	process->setlastCT(process->get_CT() - process->get_countsteps());
	RSIZE++;
}

bool SJF::PromoteProcess()
{
	if (!STATE && !RDY.isEmpty())// the processor is IDLE
	{
		PROCESS* toberun;
		//If RDY.peek() exists I want to check if the timestep is equal AT, if this is the case return false
		if (RDY.dequeue(toberun))
		{
			RUN = toberun;
			STATE = 1;
			RSIZE--;
			ExpectedFinishTime -= toberun->getlastCT();
			return true;
		}
	}
	return false;
}

PROCESS* SJF::removeTopOfMyRDY()
{
	PROCESS* top = nullptr;
	if (RDY.dequeue(top)) {
		ExpectedFinishTime -= top->getlastCT();
		RSIZE--;
	}
	return top;
}

void  SJF::PrintMyReady() 
{
	RDY.printContents();
}

void SJF::STOP(const int x)
{
	CooldownTimer = x;
	if (RUN)
	{
		SchedPtr->FindShortestProcessor()->addToMyRdy(RUN);
		SchedPtr->decrement_runningcount();
		RUN = NULL;
	}
	while (!RDY.isEmpty())
	{
		PROCESS* temp;
		RDY.dequeue(temp);
		SchedPtr->FindShortestProcessor()->addToMyRdy(temp);
		RSIZE--;
	}
	ExpectedFinishTime = 0;
}

