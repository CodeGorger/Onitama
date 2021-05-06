
def ParseInt(inInputString):
    try: 
        ret=int(inInputString)
        return ret
    except ValueError:
        return 666
        
class Menu:
    
    _playerName = 'Unknown Player'
    _serverIp = '127.0.0.1'
    _sessionName = 'Unknown Session'
    
    # _menuState will say which sub menu the general menu is in
    # 'Start Menu'; 'Lobby Menu'; 'Session Menu'
    _menuState = 'Start Menu'
    
    #def __init__(self):
        
    def SetPlayerName(self, inPName):
        self._playerName = inPName
        
    def SetServerIp(self, inServer):
        self._serverIp = inServer
        
    def SetSessionName(self, inSession):
        self._sessionName = inSession
        
    def DisplayStartMenu(self):
        print( "Welcome to Onitama, ", self._playerName, " !")
        print( "" )
        print( "1. Set Player Name(", self._playerName, ")" )
        print( "2. Set Server Ip(", self._serverIp, ")" )
        print( "3. Join Server" )
        return input("?>")
    
    def DisplayLobbyMenu(self):
        print( "You are in the Lobby of Server, ", 
              self._serverIp, " !")
        print( "" )
        print( "1. Display Session List" )
        #print( "2. Display Player List" )
        print( "3. Create/Join Session" )
        return input("?>")
        
    def DisplaySessionMenu(self):
        print( "You are in the Session", 
              self._sessionName, "of Server", self._serverIp)
        print( "1. Display Opponent" )
        print( "2. Start Session" )
        print( "3. Leave Session" )
        return input("?>")
    
        
    def QuestionPlayerName(self):
        print("What is your desired nick name?")
        self.SetPlayerName(input("?>"))
        
    def QuestionServerIp(self):
        print("What server ip do you desired to connect to?")
        self.SetServerIp(input("?>"))
        
    def QuestionSessionName(self):
        print("What is the sessions name your desire to join ?")
        self.SetSessionName(input("?>"))
    
    def ConnectToServer(self):
        # TODO(Simon): TCP connection stuff
        # TODO(Simon): self.SendGreeting();
        # TODO(Simon): Start Thread for recv buffer of session list
        erfolg=True
        if erfolg:
            self._menuState = 'Lobby Menu'
        else:
            input( "1 Irgendwas ging niä. Tut mir leed! Weeter mit äny key (zum Beeschpiel Endor)" )
            
    def DisplaySessionList(self):
        for s in self._sessionList:
            print(s)
        input( "Back with Enter." )
    
    def CreateJoinSession(self):
        # TODO(Simon): send connect to _sessionName
        # TODO(Simon): Start Thread for recv buffer of oppo name
        erfolg=True
        if erfolg:
            self._menuState = 'Session Menu'
        else:
            input( "2 Irgendwasch ging nisch. Tut mir leed! Weeter mit äny key (zum Beeschpiel Endor)" )
            
    def DisplayOpponent(self):
        print("Opponent Name:", self._opponentName)
        input( "Back with Enter." )
        
    def StartSession(self):
        #TODO(Simon): Write this
        print("Dunno what to do here")
        
    def DisplayMenu(self):
        while True:
            if 'Start Menu'==self._menuState:
                tmpMenuCode=ParseInt(self.DisplayStartMenu())
                if 1==tmpMenuCode:
                    self.QuestionPlayerName()
                elif 2==tmpMenuCode:
                    self.QuestionServerIp()
                elif 3==tmpMenuCode:
                    self.ConnectToServer()
            
            elif 'Lobby Menu'==self._menuState:
                tmpMenuCode=ParseInt(self.DisplayLobbyMenu())
                if 1==tmpMenuCode:            
                    self.DisplaySessionList()
                elif 3==tmpMenuCode:            
                    self.CreateJoinSession()
                
            elif 'Session Menu'==self._menuState:            
                tmpMenuCode=ParseInt(self.DisplaySessionMenu())
                if 1==tmpMenuCode:            
                    self.DisplayOpponent()
                elif 2==tmpMenuCode:            
                    self.StartSession()
                elif 3==tmpMenuCode:          
                    self._menuState = 'Lobby Menu'
            else:
                self._menuState = 'Start Menu'
        
        
if __name__ == "__main__":
    m=Menu()
    m.DisplayMenu()
        
        
                
        
        
        
        
        
        
        
        
        