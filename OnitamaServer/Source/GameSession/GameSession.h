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
	void SetConnEntityA(std::shared_ptr<ConnEntity> inConnectionEntity);
	void SetConnEntityB(std::shared_ptr<ConnEntity> inConnectionEntity);
	bool ReadStartRequestSessionMessage();
	bool HasTwoPlayer();

	std::shared_ptr<ConnEntity> GetPlayerA();
	std::shared_ptr<ConnEntity> GetPlayerB();

	// If both _connEntityA and _connEntityB are closed return true
	bool CheckConnectionsIfClosed();

private:

	// Name of the session to assign players
	// to one game
	std::string _sessionName;

	// Starting player or 
	// the one taking the seat after this one left without starting
	// Player Red
	std::shared_ptr<ConnEntity> _connEntityA;

	// Joining player or 
	// the one joined last
	// Player Blue
	std::shared_ptr<ConnEntity> _connEntityB;
};

#endif