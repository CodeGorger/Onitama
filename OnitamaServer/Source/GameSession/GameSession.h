#ifndef _GAMESESSION_H_
#define _GAMESESSION_H_

#include <string>
#include "../ConnEntity/ConnEntity.h"

class GameSession
{
public:
	GameSession();
	std::string GetSessionName();
	void SetSessionName(std::string inSessionName);
	void SetConnEntityA(ConnEntity inConnectionEntity);
	void SetConnEntityB(ConnEntity inConnectionEntity);
	bool ReadStartRequestSessionMessage();
	bool HasTwoPlayer();

	ConnEntity GetPlayerA();
	ConnEntity GetPlayerB();

private:

	// Name of the session to assign players
	// to one game
	std::string _sessionName;

	// Starting player or 
	// the one taking the seat after this one left without starting
	// Player Red
	ConnEntity _connEntityA;

	// Joining player or 
	// the one joined last
	// Player Blue
	ConnEntity _connEntityB;
};

#endif