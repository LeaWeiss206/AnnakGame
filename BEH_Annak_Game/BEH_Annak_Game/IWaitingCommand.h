#pragma once
class IWaitingCommand
{
private:
	//int wait;
public:
	//IWaitingCommand(int wait);
	virtual bool execute()=0;
};

