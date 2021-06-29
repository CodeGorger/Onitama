#ifndef _READMOVEINFODTO_H_
#define _READMOVEINFODTO_H_

//#include <MoveInformation/MoveInformation.h>
#include <OnitamaEngineLib.h>

class ReadMoveInfoDto
{
public:

	ReadMoveInfoDto()
		: _retStatus(999)
	{
	}

	ReadMoveInfoDto(
		int inRetStatus)
		: _retStatus(inRetStatus)
	{
	}

	ReadMoveInfoDto(
		int inRetStatus,
		MoveInformation inMove )
		:_move(inMove)
		, _retStatus(inRetStatus)
	{
	}

	MoveInformation GetMoveInfo()
	{
		return _move;
	}

	int GetReturnStatus()
	{
		return _retStatus;
	}

private:
	MoveInformation _move;
	int _retStatus;
};


#endif