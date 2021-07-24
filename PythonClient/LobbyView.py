import time
import threading
from tkinter import *
import socket
import errno
import OnitamaMessages


class LobbyView:

    def __init__(self):
        self._quitStatus = 100
        self._sessionName = "Test Session Name"
        self.TestDrecksVar = 0
        self._isClosing = False

    def GetQuitStatus(self):
        return self._quitStatus

    def SetSocket(self, inServerSocket):
        self._serverSocket = inServerSocket

    def SetUserName(self, inUserName):
        self._username = inUserName

    def _disconnectFromServer(self):
        self._quitStatus = 101
        self._tkOnitamaClientWindow.destroy()

    def _joinSession(self):
        self._quitStatus = 102
        self._tkOnitamaClientWindow.destroy()

    def ReadAllQueuedTcpData(self):
        ret = ''
        err = 0
        while err == 0:
            try:
                ret = ret + self._serverSocket.recv(4096)
            except socket.error as e:
                err = e.args[0]
                if err == errno.EAGAIN or err == errno.EWOULDBLOCK:
                    break
                else:
                    # a "real" error occurred
                    print(e)
                    print('Terminating ... ')
                    sys.exit(1)
        return ret

    def _processingSessionListMsg(self):
        while not self._isClosing:
            self.allIncomingTcpData = \
                self.allIncomingTcpData + self.ReadAllQueuedTcpData()

            # First potential readable message
            MessageDto = OnitamaMessages.ParseMessage(self.allIncomingTcpData)
            parseSuccess = MessageDto.GetResult()
            self.allIncomingTcpData = MessageDto.GetRest()
            while MessageDto.MessageStringResult_Complete == parseSuccess:
                # It was possible to parse the message
                MsgObject = MessageDto.GetOnitamaMessage()

                # It was a session list message, the one we need here
                # process it ...
                if MessageDto.SessionListMessage == type(MsgObject):
                    self._listboxSessionList.delete(0, END)
                    # Refresh the list ...

                # See if there are further messages in the string to be processed
                MessageDto = OnitamaMessages.ParseMessage(self.allIncomingTcpData)
                parseSuccess = MessageDto.GetResult()
                self.allIncomingTcpData = MessageDto.GetRest()

            # We processed the entire incoming string
            # Let the thread take a break and give some space to others
            time.sleep(1)

    def Display(self):
        self._quitStatus = 100
        self._tkOnitamaClientWindow = Tk()

        self._tkOnitamaClientWindow.minsize(400, 285)
        self._tkOnitamaClientWindow.title('Onitama Client')
        self._tkOnitamaClientWindow.geometry('400x285')

        welcomeMessage = "Welcome " + self._username
        sessionList = "Todo TestString Session 1", "Todo TestString Session 2", "aa", "bb", "c", "d", "e", "f", "h", "i", "j", "k", "l", "m"

        # Label für die Anzeige der Daten
        labelWelcome = Label(master=self._tkOnitamaClientWindow,
                             text=welcomeMessage,
                             fg='white', bg='gray',
                             font=('Arial', 10))
        labelWelcome.place(x=5, y=5, width=390, height=20)
        self._listboxSessionList = Listbox(master=self._tkOnitamaClientWindow)
        self._listboxSessionList.place(x=5, y=30, width=390, height=200)

        labelSessionName = Label(master=self._tkOnitamaClientWindow,
                                 text='Session to Join:',
                                 fg='white', bg='gray',
                                 font=('Arial', 10))
        labelSessionName.place(x=5, y=235, width=120, height=20)

        self._entrySessionName = Entry(master=self._tkOnitamaClientWindow)
        self._entrySessionName.insert(END, self._sessionName)
        self._entrySessionName.place(x=130, y=235, width=265, height=20)

        buttonJoin = Button(master=self._tkOnitamaClientWindow,
                            text="Join Session",
                            command=self._joinSession)
        buttonJoin.place(x=5, y=260, width=120, height=20)

        buttonDisconnect = Button(master=self._tkOnitamaClientWindow,
                                  text="Disconnect",
                                  command=self._disconnectFromServer)
        buttonDisconnect.place(x=275, y=260, width=120, height=20)

        self._sessionListThread = threading.Thread(target=self._processingSessionListMsg)
        self._sessionListThread.start()

        self._tkOnitamaClientWindow.mainloop()

        if (101 == self._quitStatus or 100 == self._quitStatus):
            self._serverSocket.close()

        self._isClosing = True
