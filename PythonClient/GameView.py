import time
import threading
from tkinter import *
import socket
import errno
import OnitamaMessages
import OnitamaEngine


class GameView:

    def __init__(self):
        self._quitStatus = 300
        self._sessionName = "Test Session Name"
        self._isClosing = False
        self._allIncomingTcpData = ""
        self._gameEngine = OnitamaEngine.OnitamaEngine()

    def GetQuitStatus(self):
        return self._quitStatus

    def SetSocket(self, inServerSocket):
        self._serverSocket = inServerSocket

    def SetUserName(self, inUserName):
        self._username = inUserName

    def _disconnectFromServer(self):
        self._quitStatus = 301
        self._tkOnitamaClientWindow.destroy()

    def _buttonSubmitTurn(self):
        print("def _buttonSubmitTurn(self):")

    def _processingSessionListMsg(self):
        while not self._isClosing:
            time.sleep(0.1)

    def SetStartMessage(self, inStartMessage):
        self._startMessage = inStartMessage

    def ReadAllQueuedTcpData(self):
        ret = ''
        err = 0
        i = 0
        while err == 0:
            i = i+1
            try:
                ret = ret + self._serverSocket.recv(4096).decode()
            except socket.error as e:
                err = e.args[0]
                if err == errno.EAGAIN or err == errno.EWOULDBLOCK:
                    break
                else:
                    # a "real" error occurred
                    print(e)
                    print('Terminating ... ')
                    sys.exit(1)
            # print('{0}. err: {1}'.format(i, err))
        return ret

    def _processingIncomingMessages(self):
        """This is my first doc string."""
        while not self._isClosing:
            print("Processing session info message")
            self._allIncomingTcpData = \
                self._allIncomingTcpData + self.ReadAllQueuedTcpData()
            print("_allIncomingTcpData", self._allIncomingTcpData)

            # First potential readable message
            MessageDto = OnitamaMessages.ParseMessage(self._allIncomingTcpData)
            parseSuccess = MessageDto.GetResult()

            while OnitamaMessages.MessageStringResult_Complete == parseSuccess:
                print("Parsed message successfully")

                # The first message has been successfully cut off
                self._allIncomingTcpData = MessageDto.GetRest()

                # It was possible to parse the message
                MsgObject = MessageDto.GetOnitamaMessage()

                # It was a session list message, the one we need here
                # process it ...
                if OnitamaMessages.GameoverMessage == type(MsgObject):
                    self._quitStatus = 302
                    self._tkOnitamaClientWindow.destroy()

                if OnitamaMessages.InvalidMoveMessage == type(MsgObject):
                    self._statusMessage.set("Invalid move ({0}). {1}.".format(
                        MsgObject.GetTheMove(),
                        MsgObject.GetReason()))

                if OnitamaMessages.TimeoutWarningMessage == type(MsgObject):
                    self._statusMessage.set(
                        "It is your turn ({0}s Left).".
                            format(MsgObject.GetTurnTimeLeftInS()))

                if OnitamaMessages.WaitingOtherPlayerMessage == type(MsgObject):
                    self._statusMessage.set(
                        "It is {1}'s turn ({0}s Left).".
                            format(MsgObject.GetTimeLeftInS(), self._oppoName.get()))

                if OnitamaMessages.MoveMessage == type(MsgObject):

                    # self._oppoName = MsgObject.GetOppoName()
                    self._entryOpponentName.config(text=MsgObject.GetOppoName())
                    if MsgObject.IsHost():
                        self._infoMessage.set("You are the host.")
                        self._buttonStart.place(x=275, y=80, width=120, height=20)
                    else:
                        self._infoMessage.set("You are the guest.")
                        self._buttonStart.place_forget()

                del MsgObject
                # print(self._allIncomingTcpData)

                # See if there are further messages in the string to be processed
                MessageDto = OnitamaMessages.ParseMessage(self._allIncomingTcpData)
                parseSuccess = MessageDto.GetResult()


            self._gameBoard.set(self._gameEngine.PrintBoard())
            # We processed the entire incoming string
            # Let the thread take a break and give some space to others
            time.sleep(1)

    def Display(self):
        self._isClosing = False
        self._quitStatus = 300
        self._tkOnitamaClientWindow = Tk()

        self._gameEngine = OnitamaEngine.OnitamaEngine()

        self._gameEngine.SetCurrentCardCenter(self._startMessage.GetCenterCard())
        if self._startMessage.GetIsRedPlayer():
            self._gameEngine.SetCurrentCardsRed(
                self._startMessage.GetCard1(),
                self._startMessage.GetCard2())
            self._gameEngine.SetCurrentCardsBlue(
                self._startMessage.GetOppoCard1(),
                self._startMessage.GetOppoCard2())
        else:
            self._gameEngine.SetCurrentCardsRed(
                self._startMessage.GetOppoCard1(),
                self._startMessage.GetOppoCard2())
            self._gameEngine.SetCurrentCardsBlue(
                self._startMessage.GetCard1(),
                self._startMessage.GetCard2())

        self._tkOnitamaClientWindow.minsize(450, 500)
        self._tkOnitamaClientWindow.title('Onitama Client')
        self._tkOnitamaClientWindow.geometry('450x500')

        self._oppoCard1 = StringVar(self._tkOnitamaClientWindow)
        self._oppoCard1.set(self._startMessage.GetOppoCard1())
        self._oppoCard2 = StringVar(self._tkOnitamaClientWindow)
        self._oppoCard2.set(self._startMessage.GetOppoCard2())
        self._ownCard1 = StringVar(self._tkOnitamaClientWindow)
        self._ownCard1.set(self._startMessage.GetCard1())
        self._ownCard2 = StringVar(self._tkOnitamaClientWindow)
        self._ownCard2.set(self._startMessage.GetCard2())
        self._centerCard = StringVar(self._tkOnitamaClientWindow)
        self._centerCard.set(self._startMessage.GetCenterCard())
        self._oppoName = StringVar(self._tkOnitamaClientWindow)
        self._oppoName.set(self._startMessage.GetOppoName())
        self._statusMessage = StringVar(self._tkOnitamaClientWindow)

        self._gameBoard = StringVar(self._gameBoard.PrintBoardAndAxes())

        # Label für die Anzeige der Daten
        labelStatus = Label(master=self._tkOnitamaClientWindow,
                            textvariable=self._statusMessage,
                            fg='white', bg='gray',
                            font=('Arial', 10))
        labelStatus.place(x=5, y=5, width=390, height=20)

        textOppoCard1 = Label(master=self._tkOnitamaClientWindow,
                              textvariable=self._oppoCard1)
        textOppoCard1.place(x=110, y=30, width=100, height=100)

        textOppoCard2 = Label(master=self._tkOnitamaClientWindow,
                              textvariable=self._oppoCard2)
        textOppoCard2.place(x=215, y=30, width=100, height=100)

        textOppoCardPrev = Label(master=self._tkOnitamaClientWindow,
                                textvariable=self._centerCard)
        textOppoCardPrev.place(x=5, y=200, width=100, height=100)

        textGameBoard = Text(master=self._tkOnitamaClientWindow)
        textGameBoard.insert(END, "textGameBoard")
        textGameBoard.place(x=110, y=135, width=205, height=205)

        textOwnCard1 = Label(master=self._tkOnitamaClientWindow,
                            textvariable=self._ownCard1)
        textOwnCard1.place(x=110, y=345, width=100, height=100)

        textOwnCard2 = Label(master=self._tkOnitamaClientWindow,
                            textvariable=self._ownCard2)
        textOwnCard2.place(x=215, y=345, width=100, height=100)

        textOwnCardPrev = Label(master=self._tkOnitamaClientWindow,
                               textvariable=self._centerCard)
        textOwnCardPrev.place(x=320, y=200, width=100, height=100)

        buttonSubmitTurn = Button(master=self._tkOnitamaClientWindow,
                                  text="Submit Turn",
                                  command=self._buttonSubmitTurn)
        buttonSubmitTurn.place(x=5, y=450, width=140, height=20)

        buttonDisconnect = Button(master=self._tkOnitamaClientWindow,
                                  text="Disconnect (Concede)",
                                  command=self._disconnectFromServer)
        buttonDisconnect.place(x=5, y=475, width=140, height=20)

        self._sessionInfoThread = threading.Thread(target=self._processingIncomingMessages)
        self._sessionInfoThread.start()

        self._tkOnitamaClientWindow.mainloop()

        if (300==self._quitStatus):
            self._serverSocket.close()

        self._isClosing = True
