#include "PROCESSOR.h"
#include "Scheduler.h"

PROCESSOR::PROCESSOR(Scheduler* sch)
{
	ExpectedFinishTime = 0;
	PLoad = 0;
	PUtil = 0;
	RSIZE = 0;
	RUN = nullptr;
	RunningInSched = false;
	SchedPtr = sch;
	TotalBusyTime = 0;
	TotalIdleTime = 0;
	CooldownTimer = 0;
}

int PROCESSOR::getRSIZE()
{
	return RSIZE;
}

string PROCESSOR::getType()
{
	return TYPE;
}

PROCESS* PROCESSOR::getCurrentlyRunning()
{
	return RUN;
}
void PROCESSOR:: setState(bool s) {
	STATE = s;
}
bool PROCESSOR::getState()
{
	return STATE;
}

void PROCESSOR::ResetRunningProcess(int x)
{
	if (RUN)
	{
		if (RUN->get_PID() == x)
		{
			STATE = 0;
			RUN = nullptr;
			RunningInSched = 0;
		}
	}
	
}

void PROCESSOR::setRunningInSched(int x)
{
	if (!x)
	{
		RunningInSched = false;
		return;
	}
	RunningInSched = true;
}

bool PROCESSOR::getRunningInSched()
{
	return RunningInSched;
}
int PROCESSOR::getExpectedFinishTime()
{
	return ExpectedFinishTime;
}
void PROCESSOR::KillRun()
{
	RUN = nullptr;
}
float PROCESSOR::getPLoad() const
{
	return PLoad;
}

float PROCESSOR::getPUtil() const
{
	return PUtil;
}

void PROCESSOR::CalculatePLoad(int TRT)
{
	PLoad = (float(TotalBusyTime) / TRT)*100;
}

void PROCESSOR::CalculatePUtil()
{
	PUtil = (TotalBusyTime * 1.0 / (TotalBusyTime + TotalIdleTime))*100;
}

void PROCESSOR::setCooldown(int x)
{
	CooldownTimer = x;
}

int PROCESSOR::getCooldown() const
{
	return CooldownTimer;
}

void PROCESSOR::decrementCooldown()
{
	CooldownTimer--;
}

void PROCESSOR::STOP(const int n)
{

}

PROCESSOR::~PROCESSOR()
{
}
