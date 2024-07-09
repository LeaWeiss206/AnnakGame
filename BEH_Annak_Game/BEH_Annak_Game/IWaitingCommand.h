#pragma once
class IWaitingCommand
{	
public:
	//IWaitingCommand(int wait);
	virtual bool execute()=0;
	bool finished;
};

