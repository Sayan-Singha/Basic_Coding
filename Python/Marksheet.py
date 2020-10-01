#!/usr/bin/python
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
PROGRAM TO STIMULATE THE FUNCTIONALITY OF STUDENT'S MARKSHEET
USING TKINTER [GUI DESIGNING PACKAGE]
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Created by :~   RAKTIM SAHA
                CSE/18068/379
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

from tkinter import *
import tkinter
import tkinter.messagebox
import re


def CalcCredit():

    NAME = studentName.get()
    ROLL_NO = 'CSE/'+studentRoll.get()+'/'+regNo.get()
    GRADE_1 = Grade_1.get()
    GRADE_2 = Grade_2.get()
    GRADE_3 = Grade_3.get()
    GRADE_4 = Grade_4.get()
    #print(GRADE_1,GRADE_2,GRADE_3,GRADE_4)
    Match_Roll = re.findall(r'[\d+]',studentRoll.get())
    Match_Reg = re.findall(r'[\d+]',regNo.get())

    if not Match_Roll:
        tkinter.messagebox.showwarning( "Error!", "Only enter Numerics in Roll Number!")
    if not Match_Reg:
        tkinter.messagebox.showwarning( "Error!", "Only enter Numerics in Registration Number!")

    if GRADE_1 == '' or GRADE_2 == '' or GRADE_3 == '' or GRADE_4 == '':
        tkinter.messagebox.showerror( "Error!", "No grade can remain empty!")
    if NAME == '' and studentRoll.get() == '' and regNo.get() == '':
        tkinter.messagebox.showerror( "Error!", "Enter Student details!")
    elif studentRoll.get() == '' and regNo.get() == '':
        tkinter.messagebox.showerror( "Error!", "Enter Roll & Registration Number!")
    elif NAME == '' and regNo.get() == '':
        tkinter.messagebox.showerror( "Error!", "Enter Name & Registration Number!")
    elif studentRoll.get() == '' and NAME == '':
        tkinter.messagebox.showerror( "Error!", "Enter Name & Roll Number!")
    elif NAME == '':
        tkinter.messagebox.showerror( "Error!", "Enter Name!")
    elif studentRoll.get() == '':
        tkinter.messagebox.showerror( "Error!", "Enter Roll Number!")
    elif regNo.get() == '':
        tkinter.messagebox.showerror( "Error!", "Enter Registration Number!")

    else:

        g1,g2,g3,g4 = 0,0,0,0

        if GRADE_1 == 'a' or GRADE_1 == 'A':
            g1=10
        elif GRADE_1 == 'b' or GRADE_1 == 'B':
            g1=9
        elif GRADE_1 == 'c' or GRADE_1 == 'C':
            g1=8
        elif GRADE_1 == 'd' or GRADE_1 == 'D':
            g1=7
        elif GRADE_1 == 'e' or GRADE_1 == 'E':
            g1=6
        elif GRADE_1 == 'f' or GRADE_1 == 'F':
            g1=5
        elif GRADE_1 == 'p' or GRADE_1 == 'P':
            g1=2
        else:
            tkinter.messagebox.showwarning( "Error!", "Grade must be within Range! [A-F & P]")
            return

        if GRADE_2 == 'a' or GRADE_2 == 'A':
            g2=10
        elif GRADE_2 == 'b' or GRADE_2 == 'B':
            g2=9
        elif GRADE_2 == 'c' or GRADE_2 == 'C':
            g2=8
        elif GRADE_2 == 'd' or GRADE_2 == 'D':
            g2=7
        elif GRADE_2 == 'e' or GRADE_2 == 'E':
            g2=6
        elif GRADE_2 == 'f' or GRADE_2 == 'F':
            g2=5
        elif GRADE_2 == 'p' or GRADE_2 == 'P':
            g2=2
        else:
            tkinter.messagebox.showwarning( "Error!", "Grade must be within Range! [A-F & P]")
            return

        if GRADE_3 == 'a' or GRADE_3 == 'A':
            g3=10
        elif GRADE_3 == 'b' or GRADE_3 == 'B':
            g3=9
        elif GRADE_3 == 'c' or GRADE_3 == 'C':
            g3=8
        elif GRADE_3 == 'd' or GRADE_3 == 'D':
            g3=7
        elif GRADE_3 == 'e' or GRADE_3 == 'E':
            g3=6
        elif GRADE_3 == 'f' or GRADE_3 == 'F':
            g3=5
        elif GRADE_3 == 'p' or GRADE_3 == 'P':
            g3=2
        else:
            tkinter.messagebox.showwarning( "Error!", "Grade must be within Range! [A-F & P]")
            return

        if GRADE_4 == 'a' or GRADE_4 == 'A':
            g4=10
        elif GRADE_4 == 'b' or GRADE_4 == 'B':
            g4=9
        elif GRADE_4 == 'c' or GRADE_4 == 'C':
            g4=8
        elif GRADE_4 == 'd' or GRADE_4 == 'D':
            g4=7
        elif GRADE_4 == 'e' or GRADE_4 == 'E':
            g4=6
        elif GRADE_4 == 'f' or GRADE_4 == 'F':
            g4=5
        elif GRADE_4 == 'p' or GRADE_4 == 'P':
            g4=2
        else:
            tkinter.messagebox.showwarning( "Error!", "Grade must be within Range! [A-F & P]")
            return


        cr1=g1*4
        cr2=g2*4
        cr3=g3*3
        cr4=g4*4

        SGPA = ((cr1+cr2+cr3+cr4)/150)*100

        Obt_1["text"]=cr1
        Obt_2["text"]=cr2
        Obt_3["text"]=cr3
        Obt_4["text"]=cr4

        tkinter.messagebox.showinfo( "Result!", "Name: " + NAME + "\nRoll No.: " + ROLL_NO + "\nTotal Credit Obtained = " + str(cr1+cr2+cr3+cr4) + "\nSGPA = " + str(SGPA))

#if __name__ == "__main__":

top = Tk()
top.configure(background="light green")
top.title("Marksheet")


def NewFile():
    studentName.delete(first=0, last=len(studentName.get()))
    studentRoll.delete(first=0, last=len(studentRoll.get()))
    regNo.delete(first=0, last=len(regNo.get()))
    Grade_1.delete(first=0, last=len(Grade_1.get()))
    Grade_2.delete(first=0, last=len(Grade_2.get()))
    Grade_3.delete(first=0, last=len(Grade_3.get()))
    Grade_4.delete(first=0, last=len(Grade_4.get()))
    top.mainloop()

def ShowAbout():
    messagebox.showinfo( "About", "\tCredit and SGPA calculator\n\t      by ~ Raktim Saha\n\nEnter details and click on calculate button!")


#####################################################



menubar = Menu(top)
filemenu = Menu(menubar, tearoff=0)
# the tearoff property helps to seperate out the menu from the menubar [0/1]

filemenu.add_command(label="New",command=NewFile)
filemenu.add_command(label="Save")
filemenu.add_command(label="Close", command=top.quit)

filemenu.add_separator()

filemenu.add_command(label="Exit", command=top.quit)

menubar.add_cascade(label="File", menu=filemenu)

editmenu = Menu(menubar, tearoff=0)
editmenu.add_command(label="Undo")

editmenu.add_separator()

editmenu.add_command(label="Cut")
editmenu.add_command(label="Copy")
editmenu.add_command(label="Paste")
editmenu.add_command(label="Delete")
editmenu.add_command(label="Select All")

menubar.add_cascade(label="Edit", menu=editmenu)

helpmenu = Menu(menubar, tearoff=0)
helpmenu.add_command(label="About...", command=ShowAbout)
menubar.add_cascade(label="Help", menu=helpmenu)

top.config(menu=menubar)







#####################################################



Heading = Label(top, text=" MARKSHEET ", font=('algerian',30,'bold italic'), background="light green", justify="center")
Heading.grid(row=0, column=2)

emptyLabel = Label(top, bg="light green")
emptyLabel.grid(ipady=20)

Name = Label(top, text="Student's Name: ", font=('Times New Roman',12,'bold italic'), background="light green")
Name.grid(row=2, column=0)

studentName = Entry(top,font=('arial',12,'bold'), bd=5,insertwidth=4,bg="powder blue")
studentName.grid(row=2, column=0, columnspan=3)

emptyLabel = Label(top, bg="light green")
emptyLabel.grid(ipady=20)

Roll = Label(top, text="Roll No.: ", font=('Times New Roman',12,'bold italic'), background="light green")
Roll.grid(row=3, column=0)

studentRoll = Entry(top,font=('arial',12,'bold'), bd=5,insertwidth=4,bg="powder blue", justify='right')
studentRoll.grid(row=3, column=0, columnspan=3)


Reg = Label(top, text="Registration No.: ", font=('Times New Roman',12,'bold italic'), background="light green")
Reg.grid(row=3, column=2)

regNo = Entry(top,font=('arial',12,'bold'), bd=5,insertwidth=4,bg="powder blue", justify='right')
regNo.grid(row=3, column=2, columnspan=3)




    # TABLE

emptyLabel = Label(top, bg="light green")
emptyLabel.grid(ipady=50)

Sl = Label(top, text="Sl. No.", font=('Noto Serif',12,'bold italic'), background="light blue")
Sl.grid(row=10, ipadx=50)

Sub_cd = Label(top, text="Subject Code", font=('Noto Serif',12,'bold italic'), background="light blue")
Sub_cd.grid(row=10,column=1, ipadx=50)

Grade = Label(top, text="Grade", font=('Noto Serif',12,'bold italic'), background="light blue")
Grade.grid(row=10,column=2, ipadx=110)

Crd = Label(top, text="Subject Credit", font=('Noto Serif',12,'bold italic'), background="light blue")
Crd.grid(row=10,column=3, ipadx=50)

Obt = Label(top, text="Credit Obtained", font=('Noto Serif',12,'bold italic'), background="light blue")
Obt.grid(row=10,column=4, ipadx=50)



S_1 = Label(top, text="1", font=('Comic Sans',12,'italic'), background="light green")
S_1.grid(row=12, ipadx=50, ipady=10)
S_1 = Label(top, text="2", font=('Comic Sans',12,'italic'), background="light green")
S_1.grid(row=13, ipadx=50, ipady=10)
S_1 = Label(top, text="3", font=('Comic Sans',12,'italic'), background="light green")
S_1.grid(row=14, ipadx=50, ipady=10)
S_1 = Label(top, text="4", font=('Comic Sans',12,'italic'), background="light green")
S_1.grid(row=15, ipadx=50, ipady=10)


Code = Label(top, text="CS 201", font=('Comic Sans',12,'italic'), background="light green")
Code.grid(row=12, column=1, ipadx=50)
Code = Label(top, text="CS 202", font=('Comic Sans',12,'italic'), background="light green")
Code.grid(row=13, column=1, ipadx=50)
Code = Label(top, text="MA 201", font=('Comic Sans',12,'italic'), background="light green")
Code.grid(row=14, column=1, ipadx=50)
Code = Label(top, text="EC 201", font=('Comic Sans',12,'italic'), background="light green")
Code.grid(row=15, column=1, ipadx=50)


Grade_1 = Entry(top, font=('Comic Sans',12,'italic'), background="light yellow", justify='center')
Grade_1.grid(row=12, column=2)
gd1=Grade_1.get()
Grade_2 = Entry(top, font=('Comic Sans',12,'italic'), background="light yellow", justify='center')
Grade_2.grid(row=13, column=2)
gd2=Grade_2.get()
Grade_3 = Entry(top, font=('Comic Sans',12,'italic'), background="light yellow", justify='center')
Grade_3.grid(row=14, column=2)
gd3=Grade_3.get()
Grade_4 = Entry(top, font=('Comic Sans',12,'italic'), background="light yellow", justify='center')
Grade_4.grid(row=15, column=2)
gd4a=Grade_4.get()


Code = Label(top, text="4", font=('Comic Sans',12,'italic'), background="light green")
Code.grid(row=12, column=3, ipadx=50)
Code = Label(top, text="4", font=('Comic Sans',12,'italic'), background="light green")
Code.grid(row=13, column=3, ipadx=50)
Code = Label(top, text="3", font=('Comic Sans',12,'italic'), background="light green")
Code.grid(row=14, column=3, ipadx=50)
Code = Label(top, text="4", font=('Comic Sans',12,'italic'), background="light green")
Code.grid(row=15, column=3, ipadx=50)


Obt_1 = Label(top, text="-", font=('Comic Sans',12,'italic'), background="light green")
Obt_1.grid(row=12, column=4, ipadx=50)
Obt_2 = Label(top, text="-", font=('Comic Sans',12,'italic'), background="light green")
Obt_2.grid(row=13, column=4, ipadx=50)
Obt_3 = Label(top, text="-", font=('Comic Sans',12,'italic'), background="light green")
Obt_3.grid(row=14, column=4, ipadx=50)
Obt_4 = Label(top, text="-", font=('Comic Sans',12,'italic'), background="light green")
Obt_4.grid(row=15, column=4, ipadx=50)


SUBMIT = Button(top, padx=10, bd=5, font=('arial',12,'bold'), text='Calculate Result', fg='blue', command=lambda: CalcCredit(), height=1, width=11)
SUBMIT.grid(row=16, column=2, pady=50)



top.grid()
top.geometry("1050x700")
top.mainloop()

