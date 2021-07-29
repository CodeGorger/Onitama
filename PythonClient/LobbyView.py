import time
import threading
from tkinter import *
import socket
import errno
import OnitamaMessages


class LobbyView:

    def __init__(self):
        self._quitStatus = 100
        # self._sessionName = StringVar()
        self._isClosing = False
        self._allIncomingTcpData = ''

    def GetQuitStatus(self):
        return self._quitStatus

    def GetSessionName(self):
        return self._sessionName.get()

    def SetSocket(self, inServerSocket):
        self._serverSocket = inServerSocket

    def SetUserName(self, inUserName):
        self._username = inUserName

    def _disconnectFromServer(self):
        self._quitStatus = 101
        self._tkOnitamaClientWindow.destroy()

    def _joinSession(self):
        print("Attempting to join session {0}.".format(self._entrySessionName.get()))

        joinSessionM = OnitamaMessages.JoinSessionMessage()
        joinSessionM.SetSessionName(self._entrySessionName.get())
        msgLength = len(joinSessionM.ToString())
        sentLength = self._serverSocket.send(joinSessionM.ToString().encode())
        if msgLength != sentLength:
            print("Sent only {0} chars of message {1}. Aborting...".
                  format(sentLength, joinSessionM.ToString()))
            self._quitStatus = 2
        else:
            print("Sent join session message '{0}'.".format(joinSessionM.ToString()))
            self._quitStatus = 0
        self._quitStatus = 102
        self._tkOnitamaClientWindow.destroy()

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

    def _processingSessionListMsg(self):
        while not self._isClosing:
            print("Processing session list message")
            self._allIncomingTcpData = \
                self._allIncomingTcpData + self.ReadAllQueuedTcpData()

            # First potential readable message
            MessageDto = OnitamaMessages.ParseMessage(self._allIncomingTcpData)
            parseSuccess = MessageDto.GetResult()
            #print("parseSuccess: ", parseSuccess)
            #print("_allIncomingTcpData: ", self._allIncomingTcpData)
            while OnitamaMessages.MessageStringResult_Complete == parseSuccess:
                print("Parsed message successfully")

                # The first message has been successfully cut off
                self._allIncomingTcpData = MessageDto.GetRest()

                # It was possible to parse the message
                MsgObject = MessageDto.GetOnitamaMessage()

                # It was a session list message, the one we need here
                # process it ...
                if OnitamaMessages.SessionListMessage == type(MsgObject):
                    self._listboxSessionList.delete(0, END)
                    sessions = MsgObject.GetSessionNames()
                    # Refresh the list ...
                    for s in sessions:
                        self._listboxSessionList.insert(END, s)

                del MsgObject

                # See if there are further messages in the string to be processed
                MessageDto = OnitamaMessages.ParseMessage(self._allIncomingTcpData)
                parseSuccess = MessageDto.GetResult()

            # We processed the entire incoming string
            # Let the thread take a break and give some space to others
            time.sleep(1)

    def OnSessionListSelect(self, event):
        selection = event.widget.curselection()
        if selection:
            index = selection[0]
            self._sessionName.set(event.widget.get(index))
        else:
            self._sessionName.set("")

        #self._entrySessionName.delete(0, END)
        #self._entrySessionName.insert(END, self._sessionName)

    def Display(self):
        self._isClosing = False
        self._quitStatus = 100
        self._tkOnitamaClientWindow = Tk()

        self._tkOnitamaClientWindow.minsize(400, 285)
        self._tkOnitamaClientWindow.title('Onitama Client')
        self._tkOnitamaClientWindow.geometry('400x285')

        welcomeMessage = "Welcome " + self._username

        self._sessionName = StringVar(self._tkOnitamaClientWindow)

        # Label für die Anzeige der Daten
        labelWelcome = Label(master=self._tkOnitamaClientWindow,
                             text=welcomeMessage,
                             fg='white', bg='gray',
                             font=('Arial', 10))
        labelWelcome.place(x=5, y=5, width=390, height=20)
        self._listboxSessionList = Listbox(master=self._tkOnitamaClientWindow)
        self._listboxSessionList.place(x=5, y=30, width=390, height=200)
        self._listboxSessionList.bind("<<ListboxSelect>>", self.OnSessionListSelect)

        labelSessionName = Label(master=self._tkOnitamaClientWindow,
                                 text='Session to Join:',
                                 fg='white', bg='gray',
                                 font=('Arial', 10))
        labelSessionName.place(x=5, y=235, width=120, height=20)

        self._entrySessionName = Entry(master=self._tkOnitamaClientWindow, textvariable=self._sessionName)
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
