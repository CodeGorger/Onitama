
#include <iostream>
#include <chrono>
#include <thread>
#include "AcceptThread/AcceptThread.h"
#include "LobbyThread/LobbyThread.h"

int main()
{

    //std::string inMessageContent = "";
    //int firstComma = inMessageContent.find_first_of(',');
    //std::cout << firstComma << std::endl;
    //std::string cutParameter = inMessageContent.substr(0, firstComma);
    //std::cout << cutParameter << std::endl;
    //std::string contentRest = inMessageContent.substr(firstComma + 1);
    //std::cout << contentRest << std::endl;




    AcceptThread acceptThread = AcceptThread();
    acceptThread.Start();

    LobbyThread lobbyThread = LobbyThread();
    lobbyThread.SetConnectionInputQueue(acceptThread.GetOutputQueue());
    lobbyThread.Start();

    while (true)
    {
        std::string line;
        std::getline(std::cin, line);

        if ("shutdown" == line)
        {
            std::cout << "Accept thread shutting down." << std::endl;
            acceptThread.Shutdown();

            std::cout << "Lobby thread shutting down." << std::endl;
            lobbyThread.Shutdown();
            //TODO(Simon): Also shutdown all game threads...
            break;
        }
        else
        {
            std::cout << "Unknown command: \"" << line << "\"." << std::endl;
        }
    }
    return 0;
}
