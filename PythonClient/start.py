from LobbyView import LobbyView
from DisconnectedView import DisconnectedView
from GameView import GameView

state = 0
userquit = False
# 0 ... disconnected
# 1 ... lobby

dv = DisconnectedView()
lv = LobbyView()
gv = GameView()

while not userquit:
    if 0 == state: # disconnected
        dv.Display()
        if dv.GetQuitStatus() == 1:
            # Closed with X
            userquit = True
            print("if dv.GetQuitStatus() == 1:")
        elif dv.GetQuitStatus() == 0:
            # Pressed Connect successfully
            state = 1
            print("elif dv.GetQuitStatus() == 0:")
    elif 1 == state: # lobby
        lv.SetSocket(dv.GetSocket())
        lv.SetUserName(dv.GetUsername())
        lv.Display()
        if lv.GetQuitStatus() == 100:
            # Closed with X
            userquit = True
            print("if lv.GetQuitStatus() == 100:")
        elif lv.GetQuitStatus() == 101:
            # Pressed Disconnect
            state = 0
            print("elif lv.GetQuitStatus() == 101:")
        elif lv.GetQuitStatus() == 102:
            state = 2
            print("TODO(Simon): State/View - Session")