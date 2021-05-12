


#include <iostream>
#include <chrono>
#include <thread>
#include "AcceptThread/AcceptThread.h"
#include "LobbyThread/LobbyThread.h"


//TODO(Simon): At some point it is important to have the threads not 
//             run on any std::queue<T> but to make it thread proof.

int main()
{
    AcceptThread acceptThread = AcceptThread();
    acceptThread.Start();

    LobbyThread lobbyThread = LobbyThread();
    lobbyThread.SetConnectionInputQueue(acceptThread.GetOutputQueue());
    lobbyThread.Start();
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //acceptThread.Shutdown();

}
