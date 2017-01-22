#!/usr/local/bin/python
 
import Tkinter
  
root = Tkinter.Tk()
  
  
l1 = Tkinter.Label(root, text="Hello", background="red")
l2 = Tkinter.Label(root, text="World!", background="#6699ff")
  
l1.pack()
l2.pack()

root.mainloop()
