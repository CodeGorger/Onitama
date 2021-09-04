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
	void SetConnEntityRed(std::shared_ptr<ConnEntity> inConnectionEntity);
	void SetConnEntityBlue(std::shared_ptr<ConnEntity> inConnectionEntity);
	
	//TODO(Simon): This should be an enum...
	// -1 ... B wishes to leave the session
	// -2 ... A wishes to leave the session
	// -3 ... A & B wishes to leave the session
	// -4 ... A wishes to start the session
	//  1 ... Error
	int ReadStartRequestAndLeaveSessionMessages();

	bool HasTwoPlayer();

	std::shared_ptr<ConnEntity> GetPlayerRed();
	std::shared_ptr<ConnEntity> GetPlayerBlue();

	// If both _connEntityA and _connEntityB are closed return true
	bool CheckConnectionsIfClosed();

private:

	// Name of the session to assign players
	// to one game
	std::string _sessionName;

	// Starting player or 
	// the one taking the seat after this one left without starting
	// Player Red
	std::shared_ptr<ConnEntity> _connEntityRed;

	// Joining player or 
	// the one joined last
	// Player Blue
	std::shared_ptr<ConnEntity> _connEntityBlue;


	std::shared_ptr<spdlog::logger> l;
};

#endif