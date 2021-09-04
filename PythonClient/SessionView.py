import time
import threading
from tkinter import *
import socket
import errno
import OnitamaMessages


class SessionView:

    def __init__(self):
        self._quitStatus = 200
        self._username = ""
        self._sessionname = ""
        self._allIncomingTcpData = ""
        self._isClosing = False

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

    def GetGameStartMessage(self):
        return self._gameStartMessage

    def _processingIncomingMessages(self):
        while not self._isClosing:
            print("Processing session info message")
            self._allIncomingTcpData = \
                self._allIncomingTcpData + self.ReadAllQueuedTcpData()

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
                if OnitamaMessages.SessionInformationMessage == type(MsgObject):
                    # self._oppoName = MsgObject.GetOppoName()
                    self._entryOpponentName.config(text=MsgObject.GetOppoName())
                    if MsgObject.IsHost():
                        self._infoMessage.set("You are the host.")
                        self._buttonStart.place(x=275, y=80, width=120, height=20)
                    else:
                        self._infoMessage.set("You are the guest.")
                        self._buttonStart.place_forget()

                # It was a start game message, another one we need here
                # process it ...
                if OnitamaMessages.GamestartMessage == type(MsgObject):
                    self._gameStartMessage = MsgObject
                    self._quitStatus = 205
                    self._tkOnitamaClientWindow.destroy()

                del MsgObject
                # print(self._allIncomingTcpData)

                # See if there are further messages in the string to be processed
                MessageDto = OnitamaMessages.ParseMessage(self._allIncomingTcpData)
                parseSuccess = MessageDto.GetResult()

            # We processed the entire incoming string
            # Let the thread take a break and give some space to others
            time.sleep(1)

    def SetSessionName(self, inSessionname):
        self._sessionname = inSessionname

    def SetSocket(self, inServerSocket):
        self._serverSocket = inServerSocket

    def SetUserName(self, inUsername):
        self._username = inUsername

    def _leaveSession(self):
        LeaveSessionM = OnitamaMessages.LeaveSessionMessage()
        msgLength = len(LeaveSessionM.ToString())
        sentLength = self._serverSocket.send(LeaveSessionM.ToString().encode())
        if msgLength != sentLength:
            print("Sent only {0} chars of message {1}. Aborting...".
                  format(sentLength, LeaveSessionM.ToString()))
            self._quitStatus = 203
        else:
            print("Sent leave session message '{0}'.".format(LeaveSessionM.ToString()))
            self._quitStatus = 201
        self._tkOnitamaClientWindow.destroy()

    def _startSession(self):
        GamestartRequestM = OnitamaMessages.GamestartRequestMessage()
        msgLength = len(GamestartRequestM.ToString())
        sentLength = self._serverSocket.send(GamestartRequestM.ToString().encode())
        if msgLength != sentLength:
            print("Sent only {0} chars of message {1}. Aborting...".
                  format(sentLength, GamestartRequestM.ToString()))
        #     self._quitStatus = 204
        else:
            print("Sent start session message '{0}'.".format(GamestartRequestM.ToString()))
        #     self._quitStatus = 202
        # self._tkOnitamaClientWindow.destroy()

    def GetQuitStatus(self):
        return self._quitStatus

    def Display(self):
        self._isClosing = False
        self._quitStatus = 200
        self._tkOnitamaClientWindow = Tk()

        self._tkOnitamaClientWindow.minsize(400, 150)
        self._tkOnitamaClientWindow.title('Onitama Client')
        self._tkOnitamaClientWindow.geometry('400x150')

        welcomeMessage = self._username + ", you are in session " + self._sessionname + "."
        self._infoMessage = StringVar(self._tkOnitamaClientWindow)
        self._infoMessage.set("")

        # Label für die Anzeige der Daten
        labelWelcome = Label(master=self._tkOnitamaClientWindow,
                             text=welcomeMessage,
                             fg='white', bg='gray',
                             font=('Arial', 10))
        labelWelcome.place(x=5, y=5, width=390, height=20)

        labelInfo = Label(master=self._tkOnitamaClientWindow,
                             textvariable=self._infoMessage,
                             fg='white', bg='gray',
                             font=('Arial', 10))
        labelInfo.place(x=5, y=30, width=390, height=20)

        labelOpponentName = Label(master=self._tkOnitamaClientWindow,
                                 text='Opponent:',
                                 fg='white', bg='gray',
                                 font=('Arial', 10))
        labelOpponentName.place(x=5, y=55, width=120, height=20)

        self._entryOpponentName = Label(master=self._tkOnitamaClientWindow,
                                 text="",
                                 fg='white', bg='gray',
                                 font=('Arial', 10))
        self._entryOpponentName.place(x=130, y=55, width=265, height=20)

        buttonLeave = Button(master=self._tkOnitamaClientWindow,
                            text="Leave Session",
                            command=self._leaveSession)
        buttonLeave.place(x=5, y=80, width=120, height=20)

        self._buttonStart = Button(master=self._tkOnitamaClientWindow,
                                  text="Start Session",
                                  command=self._startSession)
        self._buttonStart.place(x=275, y=80, width=120, height=20)
        self._buttonStart.pack_forget()

        self._sessionInfoThread = threading.Thread(target=self._processingIncomingMessages)
        self._sessionInfoThread.start()

        self._tkOnitamaClientWindow.mainloop()

        if (200 == self._quitStatus):
            self._serverSocket.close()

        self._isClosing = True
