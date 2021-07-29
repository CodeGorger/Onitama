import time
import threading
from tkinter import *
import socket
#import fcntl, os
import OnitamaMessages




class DisconnectedView:

    def __init__(self):
        self._username = 'Unknown Player'
        self._serverIp = '127.0.0.1'
        self._serverPort = '13337'
        self._quitStatus = 1
        # self._serverSocket

    def GetQuitStatus(self):
        return self._quitStatus

    def _tcpConnect(self, inIpAddress, inPort):
        try:
            # create an INET, STREAMing socket
            self._serverSocket = \
                socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            # now connect to the server
            self._serverSocket.connect((inIpAddress, int(inPort)))
            self._serverSocket.setblocking(0)
            # fcntl.fcntl(self._serverSocket, fcntl.F_SETFL, os.O_NONBLOCK)
            return 0

        except OSError as err:
            print("({0}:{1}) OS error, TCP Connect: {2}".
                  format(inIpAddress, inPort, err))
            return 1

        print("Unknown TCP Connect Error")
        return 2

    def _connectToServer(self):
        self._username = self._entryUsername.get()
        self._serverIp = self._entryServerIp.get()
        self._serverPort = self._entryServerPort.get()
        print("Trying to connect to ({s_ip}:{s_port})".
              format(s_ip=self._serverIp, s_port=self._serverPort))

        # 1. Verbindung aufbauen via TCP!
        rc = self._tcpConnect(self._serverIp, self._serverPort)

        # 1.a Bei fehlschlag abbrechen
        if rc != 0:
            print("Failed to connect to ({s_ip}:{s_port})".
                  format(s_ip=self._serverIp, s_port=self._serverPort))
            return
        else:
            print("Connected to ({s_ip}:{s_port})".
                  format(s_ip=self._serverIp, s_port=self._serverPort))

        # 2. Create and send a Greeting Message
        greetingM = OnitamaMessages.GreetingMessage()
        greetingM.SetPlayerName(self._username)
        msgLength = len(greetingM.ToString())
        sentLength = self._serverSocket.send(greetingM.ToString().encode())
        if msgLength != sentLength:
            print("Sent only {0} chars of message {1}. Aborting...".
                  format(sentLength, greetingM.ToString()))
            self._quitStatus = 2
        else:
            print("Sent greeting message '{0}'.".format(greetingM.ToString()))
            self._quitStatus = 0

        self._tkOnitamaClientWindow.destroy()


    def GetUsername(self):
        return self._username


    def GetSocket(self):
        return self._serverSocket


    def Display(self):
        self._quitStatus = 1
        self._tkOnitamaClientWindow = Tk()
        self._tkOnitamaClientWindow.minsize(300, 150)
        self._tkOnitamaClientWindow.title('Onitama Client')
        self._tkOnitamaClientWindow.geometry('400x400')

        # Label für die Anzeige der Daten
        labelUsername = Label(master=self._tkOnitamaClientWindow,
                              text='Username',
                              fg='white', bg='gray',
                              font=('Arial', 10))
        labelUsername.place(x=5, y=5, width=120, height=20)
        self._entryUsername = Entry(master=self._tkOnitamaClientWindow)
        self._entryUsername.insert(END, self._username)
        # self._textboxUsername.bind("<Key>", _check_key)
        self._entryUsername.place(x=130, y=5, width=120, height=20)

        labelServerIp = Label(master=self._tkOnitamaClientWindow,
                              text='Server Ip',
                              fg='white', bg='gray',
                              font=('Arial', 10))
        labelServerIp.place(x=5, y=30, width=120, height=20)
        self._entryServerIp = Entry(master=self._tkOnitamaClientWindow)
        self._entryServerIp.insert(END, self._serverIp)
        # self._entryServerIp.bind("<Key>", _check_key)
        self._entryServerIp.place(x=130, y=30, width=120, height=20)

        labelServerPort = Label(master=self._tkOnitamaClientWindow,
                                text='Server Port',
                                fg='white', bg='gray',
                                font=('Arial', 10))
        labelServerPort.place(x=5, y=55, width=120, height=20)
        self._entryServerPort = Entry(master=self._tkOnitamaClientWindow)
        self._entryServerPort.insert(END, self._serverPort)
        # self._entryServerPort.bind("<Key>", _check_key)
        self._entryServerPort.place(x=130, y=55, width=120, height=20)

        buttonConnect = Button(master=self._tkOnitamaClientWindow,
                               text="Connect",
                               command=self._connectToServer)
        buttonConnect.place(x=5, y=80, width=120, height=20)


        self._tkOnitamaClientWindow.mainloop()

