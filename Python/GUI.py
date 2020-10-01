#!/usr/bin/python


from tkinter import *
import tkinter
import tkinter.messagebox


top = Tk()
top.title("Marksheet")


############################################################################
# MENU BAR

menubar = Menu(top)
filemenu = Menu(menubar, tearoff=0)
# the tearoff property helps to seperate out the menu from the menubar [0/1]

filemenu.add_command(label="New")
filemenu.add_command(label="Open")
filemenu.add_command(label="Save")
filemenu.add_command(label="Save as...")
filemenu.add_command(label="Close")

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
helpmenu.add_command(label="Help Index")
helpmenu.add_command(label="About...")
menubar.add_cascade(label="Help", menu=helpmenu)

top.config(menu=menubar)

#menubar.pack() can't execute as menu is a top level window


#################################################################



# FRAME

frame = Frame(top)	# subframe of the main window "top"
frame.pack()


# ANOTHER FRAME

frm = Frame(top)	# independent subframe of the main window "top"
frm.pack()

# AND ANOTHER FRAME

fm = Frame(frm)		# dependent subframe of the frame "frm"
fm.pack(side = BOTTOM)	# also, "fm" contents will float at the bottom of the parent frame "frm"


# BUTTON

# function definition to be called on button click
def calculateMarks():
   tkinter.messagebox.showinfo( "Hello Python", "Hello World!")	# show textbox

# button variable
B = Button(top, text ="Calculate Credit and SGPA", command = calculateMarks)



# TEXTBOX & LABEL

# L1 is the label (text to be displayed alongside the textbox)
L1 = Label(frame, text="Student's Name")	# frame selects the frame variable as parent window
#L1.grid(row=1,column=0)
L1.pack( side = LEFT)

ch = ''
# E1 is the entry box (textbox)
E1 = Entry(frame,font=('arial',20,'bold'), bd=5,insertwidth=4,bg="powder blue", justify='right')#.grid(columnspan=4)	# bd is the border width	frame selects that frame as parent
E1.pack(side = RIGHT)


# CHECKBOXES

# labels are shown to display texts
L0 = Label(frm, text="Media Preference :- ")
L0.pack( side = TOP)	# this label will show on the top of the specified frame "frm"


# variables to store the values selected from the checkboxes
CheckVar1 = IntVar()
CheckVar2 = IntVar()

# checkbutton variables (parent_window, display_text,check_variable,checked_value,unchecked_val)

C1 = Checkbutton(frm,text = "Music", variable = CheckVar1, onvalue = 1, offvalue = 0, height=1, width = 5)

C2 = Checkbutton(frm,text = "Video", variable = CheckVar2, onvalue = 1, offvalue = 0, height=1, width = 5)

# packing of the checkboxes along with positions in the designated frame
C1.pack(side = LEFT)
C2.pack(side = RIGHT)


B.pack()


# RADIO BUTTONS

L = Label(fm, text="Gender: ")
L.pack( side = TOP)

# function definition to be called on radio check
def sel():
   selection = "You selected the option " + str(var.get())	# stores the generated string

# var is the variable name with default function .get() to read the variable value

   label.config(text = selection)	# sets a label with the string text


var = IntVar()	# variable to store the selected option from radio check



# radio buttons (parent_window, display, check_variable, check_value, command)
R1 = Radiobutton(fm, text="Male", variable=var, value=1, command=sel)
R1.pack(side = LEFT)	# floats left of the frame

R3 = Radiobutton(fm, text="Other", variable=var, value=3, command=sel)
R3.pack( side = RIGHT)	# floats right of the frame

R2 = Radiobutton(fm, text="Female", variable=var, value=2, command=sel)
R2.pack( )


label = Label(top)	# initialising a label in the frame ( defined in sel() )
label.pack()


# main frame (or window) loop - marks the end of the window contents
top.mainloop()

