#!/usr/local/bin/python

import Tkinter
import tkMessageBox
import httplib

def get_request():

    if eHost.get() == "":
        tkMessageBox.showinfo('Missing Information', 'You Must Specify A Host')
    elif eResource.get() == "":
        tkMessageBox.showinfo('Missing Information', 'You Must Specify A Resource')
    else:
        if ePort.get() == "":
            port = 80
        else:
            port = int(ePort.get())

        if port != 443:
            port = 80

        try:

            conn = httplib.HTTPConnection(eHost.get() + ":" + str(port))
            conn.request("GET", eResource.get() + eQString.get())

            r1 = conn.getresponse()
            data1 = r1.read()

            eStatus.delete('0', "end")
            eStatus.insert('0', str(r1.status) + " " + r1.reason)

            tContents.delete('0.0', "end")
            tContents.insert('0.0', data1)

            conn.close()

        except:
            tkMessageBox.showerror('Error', 'Unable to fulfill Request')
            eHost.delete('0', "end")
            eResource.delete('0', "end")

# - Begin Building GUI

root = Tkinter.Tk()
root.title("Web Client")

# - Build Top Frame -

top = Tkinter.Frame(root)
top.pack(expand="yes", fill="x")

lRequest = Tkinter.Label(top, text="Request", anchor="w", font=('Arial', 16, 'bold'))
lHost = Tkinter.Label(top, text="Host:")
lResource = Tkinter.Label(top, text="Resource:")
lQString = Tkinter.Label(top, text="Query String:")
lPort = Tkinter.Label(top, text="Port:")

eHost = Tkinter.Entry(top)
eResource = Tkinter.Entry(top)
eQString = Tkinter.Entry(top)
ePort =  Tkinter.Entry(top, width=4)

bSubmit = Tkinter.Button(root, text="Submit Request", anchor="center", command=get_request)
bSubmit.pack()

lRequest.grid(row=0, column=0, sticky="w", columnspan=3)
lHost.grid(row=1, column=0, sticky="e")
lResource.grid(row=2, column=0, sticky="e")
lQString.grid(row=3, column=0, sticky="e")
lPort.grid(row=1, column=2)

eHost.grid(row=1, column=1, sticky="news")
ePort.grid(row=1, column=3) 
eResource.grid(row=2, column=1, sticky="news", columnspan=3)
eQString.grid(row=3, column=1, sticky="news", columnspan=3)

top.columnconfigure(0, weight=0)
top.columnconfigure(1, weight=1)
top.columnconfigure(2, weight=0)
top.columnconfigure(3, weight=0)

# - Build Bottom Frame -

bottom = Tkinter.Frame(root)
bottom.pack(expand="yes", fill="both")

lReponse = Tkinter.Label(bottom, text="Reponse", anchor="w", font=('Arial', 16, 'bold'))
lStatus = Tkinter.Label(bottom, text="Status:")
lContents = Tkinter.Label(bottom, text="Content:")

eStatus = Tkinter.Entry(bottom)
tContents = Tkinter.Text(bottom, relief="sunken", wrap = Tkinter.NONE)

tvContentsbar = Tkinter.Scrollbar(bottom)
tvContentsbar.config(command=tContents.yview)
tContents.config(yscrollcommand=tvContentsbar.set)

thContentsbar = Tkinter.Scrollbar(bottom, orient='horizontal')
thContentsbar.config(command=tContents.xview)
tContents.config(xscrollcommand=thContentsbar.set)

lReponse.grid(row=0, column=0, sticky="w", columnspan=3)
lStatus.grid(row=1, column=0, sticky="e")
lContents.grid(row=2, column=0, sticky="ne")
eStatus.grid(row=1, column=1, sticky="news", columnspan=2)
tContents.grid(row=2, column=1, sticky="news")
tvContentsbar.grid(row=2, column=3, sticky="ns")
thContentsbar.grid(row=3, column=1, sticky="ew", columnspan=2)

bottom.columnconfigure(0, weight=0)
bottom.columnconfigure(1, weight=1)

root.mainloop()
