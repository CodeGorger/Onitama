import time
import threading
from tkinter import *
import socket
import OnitamaMessages


class GameView:

    def __init__(self):
        self._quitStatus = 200
        self._sessionName = "Test Session Name"
        self._isClosing = False

    def GetQuitStatus(self):
        return self._quitStatus


    def SetSocket(self, inServerSocket):
        self._serverSocket = inServerSocket


    def SetUserName(self, inUserName):
        self._username = inUserName


    def _disconnectFromServer(self):
        self._quitStatus = 201
        self._tkOnitamaClientWindow.destroy()


    def _buttonSubmitTurn(self):
        print("def _buttonSubmitTurn(self):")


    def _processingSessionListMsg(self):
        while not self._isClosing:
            time.sleep(0.1)


    def Display(self):
        self._quitStatus = 200
        self._tkOnitamaClientWindow = Tk()

        self._tkOnitamaClientWindow.minsize(450, 500)
        self._tkOnitamaClientWindow.title('Onitama Client')
        self._tkOnitamaClientWindow.geometry('450x500')

        statusMessage = "Status TODO Players Turn (30s Left)"

        # Label für die Anzeige der Daten
        labelStatus = Label(master=self._tkOnitamaClientWindow,
                              text=statusMessage,
                              fg='white', bg='gray',
                              font=('Arial', 10))
        labelStatus.place(x=5, y=5, width=390, height=20)

        textOppoCard1 = Text(master=self._tkOnitamaClientWindow)
        textOppoCard1.insert(END, "textOppoCard1")
        textOppoCard1.place(x=110, y=30, width=100, height=100)

        textOppoCard2 = Text(master=self._tkOnitamaClientWindow)
        textOppoCard2.insert(END, "textOppoCard2")
        textOppoCard2.place(x=215, y=30, width=100, height=100)

        textOppoCardPrev = Text(master=self._tkOnitamaClientWindow)
        textOppoCardPrev.insert(END, "textOppoCardPrev")
        textOppoCardPrev.place(x=5, y=200, width=100, height=100)

        textGameBoard = Text(master=self._tkOnitamaClientWindow)
        textGameBoard.insert(END, "textGameBoard")
        textGameBoard.place(x=110, y=135, width=205, height=205)

        textOwnCard1 = Text(master=self._tkOnitamaClientWindow)
        textOwnCard1.insert(END, "textOwnCard1")
        textOwnCard1.place(x=110, y=345, width=100, height=100)

        textOwnCard2 = Text(master=self._tkOnitamaClientWindow)
        textOwnCard2.insert(END, "textOwnCard2")
        textOwnCard2.place(x=215, y=345, width=100, height=100)

        textOwnCardPrev = Text(master=self._tkOnitamaClientWindow)
        textOwnCardPrev.insert(END, "textOwnCardPrev")
        textOwnCardPrev.place(x=320, y=200, width=100, height=100)



        buttonSubmitTurn = Button(master=self._tkOnitamaClientWindow,
                               text="Submit Turn",
                               command=self._buttonSubmitTurn)
        buttonSubmitTurn.place(x=5, y=450, width=140, height=20)

        buttonDisconnect = Button(master=self._tkOnitamaClientWindow,
                               text="Disconnect (Concede)",
                               command=self._disconnectFromServer)
        buttonDisconnect.place(x=5, y=475, width=140, height=20)


        # self._sessionListThread = threading.Thread(target=self._processingSessionListMsg)
        # self._sessionListThread.start()
        #
        self._tkOnitamaClientWindow.mainloop()
        #
        # if (101==self._quitStatus or 100==self._quitStatus):
        #     self._serverSocket.close()
        #
        # self._isClosing = True