import threading
#from _thread import start_new_thread
import time
import Menu
import socket
import queue

def ParseInt(inInputString):
    try: 
        ret=int(inInputString)
        return ret
    except ValueError:
        return 666
        


KillAllThreads = False
ServerSocket = None
TcpInQueue = queue.Queue()
TcpOutQueue = queue.Queue()


def SendAllOfTcpInQueue():
    while not TcpInQueue.empty():
        rawDataMessage = s.recv(BUFFER_SIZE)
    
def SendAllOfTcpOutQueue():
    while not TcpOutQueue.empty():
        msg=TcpOutQueue.get(False)
        ServerSocket.send(msg.ToString())
    
    
def TcpMessagesThread(serverIp):
    global KillAllThreads
    global ServerSocket
    global TcpInQueue
    global TcpOutQueue
    loopCounter=0
    while not KillAllThreads:
        SendAllOfTcpOutQueue()
        SendAllOfTcpInQueue()
        
        loopCounter+=1
        if 999999==(loopCounter%1000000):
            # print("I002: TcpMessagesThread running...")
            loopCounter=0
    
    try:
        ServerSocket.close()
        print("I003: ServerSocket closed")
    except OSError as err:
        print("E003: OS error, TCP Close: {0}".format(err))
    
    print("I004: TcpMessagesThread stopped")
       
        
def HandleMenu(m):
    global KillAllThreads
    while True:
        if 'Start Menu'==m._menuState:
            tmpMenuCode=ParseInt(m.DisplayStartMenu())
            if 1==tmpMenuCode:
                m.QuestionPlayerName()
            elif 2==tmpMenuCode:
                m.QuestionServerIp()
            elif 3==tmpMenuCode:
                m.QuestionServerPort()
            elif 4==tmpMenuCode:
                EstablishConnectionToServer(m)
            elif 5==tmpMenuCode:
                KillAllThreads=True
                break
        
        elif 'Lobby Menu'==m._menuState:
            tmpMenuCode=ParseInt(m.DisplayLobbyMenu())
            if 1==tmpMenuCode:            
                m.DisplaySessionList()
            elif 3==tmpMenuCode:            
                m.CreateJoinSession()
            elif 4==tmpMenuCode:       
                KillAllThreads=True
                break
            
        elif 'Session Menu'==m._menuState:            
            tmpMenuCode=ParseInt(m.DisplaySessionMenu())
            if 1==tmpMenuCode:            
                m.DisplayOpponent()
            elif 2==tmpMenuCode:            
                m.StartSession()
            elif 3==tmpMenuCode:          
                m._menuState = 'Lobby Menu'
        else:
            m._menuState = 'Start Menu'
    

def TcpConnect(inIpAddress, inPort):
    global ServerSocket
    try:
        # create an INET, STREAMing socket
        ServerSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # now connect to the server
        ServerSocket.connect((inIpAddress, inPort))
        print("I001: TCP Connetion Established")
        return 0
    
    except OSError as err:
        print("E001: (", 
              inIpAddress, inPort,
              ") OS error, TCP Connect: {0}".format(err))
        return 1
    
    print("E002: Unknown TCP Connect Error")
    return 2
        
    
    
def EstablishConnectionToServer(m):
    #1. Verbindung aufbauen via TCP!
    rc=TcpConnect(m.GetServerIp(), m.GetServerPort())
    
    #1.a Bei fehlschlag abbrechen
    if rc != 0:
        return 
    
    #2. TcpMessageThread starten
    thread = threading.Thread(target=TcpMessagesThread,
                              args=(m.GetServerIp(),))
    thread.start()
    
    #TODO(Simon): 3. Enque Nachricht für Greeting
    
    #TODO(Simon): 4. Auf die Liste der Session warten
    #TODO(Simon): 4.a Wenn für 5s keine Liste ankam abbrechen
    m.SetConnectedToServer()


if __name__ == "__main__":    
    m=Menu.Menu()
    HandleMenu(m)
        
    

        
        
        
        
        
        
        
        