#!/usr/local/bin/python

import Tkinter
import tkMessageBox
import sudoku
import sys

def check():

    truth = 1

    answerkeys = answerhash.keys()

    for i in range(len(answerkeys)):
        (row, column) = answerkeys[i]
        if answerhash[answerkeys[i]].get() == "":
            truth = 0
        elif int(answerhash[answerkeys[i]].get()) != solution[row][column]:
            truth = 0

    if truth == 1:
        tkMessageBox.showinfo('Congratulations', 'Your solution is correct')
    else:
        tkMessageBox.showinfo('Sorry', 'Your solution is not correct')

def quit():

    ans = tkMessageBox.askyesno('Confirm', 'Are you sure you want to quit?')
    if ans == 1:
        sys.exit()

def new_game():

    ans = tkMessageBox.askyesno('Confirm', 'Are you sure you want to start a new game?')

    if ans == 1:
        (problem, solution) = sudoku.get_puzzle()

        for i in range(0, 3):
            for j in range(len(problem[i])):
                if j in first:
                    bgcolor = blueback
                else:
                    bgcolor = whiteback

                if problem[i][j] == 0:
                    e = Tkinter.Entry(top, width=2, background=bgcolor, relief="raised", borderwidth=1, font=('Helvetica', 18), justify="center", foreground="#999999")
                    answerhash[(i, j)] = e
                    e.grid(row=i+1, column=j+1)
                else:
                    l = Tkinter.Label(top, text=problem[i][j], width=2, background=bgcolor, borderwidth=1, font=('Helvetica', 18), justify="center")
                    l.grid(row=i+1, column=j+1)

        for i in range(3, 6):
            for j in range(len(problem[i])):
                if j in second:
                    bgcolor = blueback
                else:
                    bgcolor = whiteback

                if problem[i][j] == 0:
                    e = Tkinter.Entry(top, width=2, background=bgcolor, relief="raised", borderwidth=1, font=('Helvetica', 18), justify="center", foreground="#999999")
                    answerhash[(i, j)] = e
                    e.grid(row=i+1, column=j+1)
                else:
                    l = Tkinter.Label(top, text=problem[i][j], width=2, background=bgcolor, borderwidth=1, font=('Helvetica', 18), justify="center")
                    l.grid(row=i+1, column=j+1)

        for i in range(6, 9):
            for j in range(len(problem[i])):
                if j in third:
                    bgcolor = blueback
                else:
                    bgcolor = whiteback

                if problem[i][j] == 0:
                    e = Tkinter.Entry(top, width=2, background=bgcolor, relief="raised", borderwidth=1, font=('Helvetica', 18), justify="center", foreground="#999999")
                    answerhash[(i, j)] = e
                    e.grid(row=i+1, column=j+1)
                else:
                    l = Tkinter.Label(top, text=problem[i][j], width=2, background=bgcolor, borderwidth=1, font=('Helvetica', 18), justify="center")
                    l.grid(row=i+1, column=j+1)

def solve():

    # NOTE: Change it so that if keeps some of them as entry boxes, or just use a different color of label?
    ans = tkMessageBox.askyesno('Confirm', 'Are you sure you want to solve the current game?')

    if ans == 1:

        for i in range(0, 3):
            for j in range(len(solution[i])):
                if j in first:
                    bgcolor = blueback
                else:
                    bgcolor = whiteback

                l = Tkinter.Label(top, text=solution[i][j], width=2, background=bgcolor, borderwidth=1, font=('Helvetica', 18), justify="center")
                l.grid(row=i+1, column=j+1)

        for i in range(3, 6):
            for j in range(len(solution[i])):
                if j in second:
                    bgcolor = blueback
                else:
                    bgcolor = whiteback

                l = Tkinter.Label(top, text=solution[i][j], width=2, background=bgcolor, borderwidth=1, font=('Helvetica', 18), justify="center")
                l.grid(row=i+1, column=j+1)

        for i in range(6, 9):
            for j in range(len(solution[i])):
                if j in third:
                    bgcolor = blueback
                else:
                    bgcolor = whiteback

                l = Tkinter.Label(top, text=solution[i][j], width=2, background=bgcolor, borderwidth=1, font=('Helvetica', 18), justify="center")
                l.grid(row=i+1, column=j+1)

# - Cubes

first = [0, 1, 2, 6, 7, 8]
second = [3, 4, 5]
third = [0, 1, 2, 6, 7, 8]

blueback = "#e8eefa"
whiteback = "#ffffff"

answerhash = {(0, 0): "First Entry"}
answerhash.clear()

# - Begin Building GUI

root = Tkinter.Tk()
root.title("Sudoku")

(problem, solution) = sudoku.get_puzzle()

# - Build Top Frame -

top = Tkinter.Frame(root)
top.pack(expand="no")

for i in range(0, 3):
    for j in range(len(problem[i])):
        if j in first:
            bgcolor = blueback
        else:
            bgcolor = whiteback

        if problem[i][j] == 0:
            e = Tkinter.Entry(top, width=2, background=bgcolor, relief="raised", borderwidth=1, font=('Helvetica', 18), justify="center", foreground="#999999")
            answerhash[(i, j)] = e
            e.grid(row=i+1, column=j+1)
        else:
            l = Tkinter.Label(top, text=problem[i][j], width=2, background=bgcolor, borderwidth=1, font=('Helvetica', 18), justify="center")
            l.grid(row=i+1, column=j+1)

for i in range(3, 6):
    for j in range(len(problem[i])):
        if j in second:
            bgcolor = blueback
        else:
            bgcolor = whiteback

        if problem[i][j] == 0:
            e = Tkinter.Entry(top, width=2, background=bgcolor, relief="raised", borderwidth=1, font=('Helvetica', 18), justify="center", foreground="#999999")
            answerhash[(i, j)] = e
            e.grid(row=i+1, column=j+1)
        else:
            l = Tkinter.Label(top, text=problem[i][j], width=2, background=bgcolor, borderwidth=1, font=('Helvetica', 18), justify="center")
            l.grid(row=i+1, column=j+1)

for i in range(6, 9):
    for j in range(len(problem[i])):
        if j in third:
            bgcolor = blueback
        else:
            bgcolor = whiteback

        if problem[i][j] == 0:
            e = Tkinter.Entry(top, width=2, background=bgcolor, relief="raised", borderwidth=1, font=('Helvetica', 18), justify="center", foreground="#999999")
            answerhash[(i, j)] = e
            e.grid(row=i+1, column=j+1)
        else:
            l = Tkinter.Label(top, text=problem[i][j], width=2, background=bgcolor, borderwidth=1, font=('Helvetica', 18), justify="center")
            l.grid(row=i+1, column=j+1)

# - Build Bottom Frame -

bottom = Tkinter.Frame(root)
bottom.pack(expand="no")

bCheck = Tkinter.Button(root, text="Check", command=check, font=('Helvetica', 16))
bNGame = Tkinter.Button(root, text="New Game", command=new_game, font=('Helvetica', 16))
bSolve = Tkinter.Button(root, text="Solve", command=solve, font=('Helvetica', 16))
bQuit = Tkinter.Button(root, text="Quit", command=quit, font=('Helvetica', 16))

bCheck.pack(fill="x")
bNGame.pack(fill="x")
bSolve.pack(fill="x")
bQuit.pack(fill="x")

root.mainloop()
