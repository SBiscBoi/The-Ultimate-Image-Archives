from PIL import Image
import subprocess
import tkinter

def generate(inp):
    width = 1920 #default 1920
    height = 1080 #default 1080

    #write input to file to be read later
    input = str(inp)
    inpFile = open("inputFile.txt", "w")
    if(input.isdigit()):
        print("Writing digit")
        inpFile.write(input)
    else:
        print("Converting")
        newInput = ""
        for i in input:
            newInput += str(ord(i))
        #print(newInput)
        print("Writing ASCII Values")
        inpFile.write(newInput)
    inpFile.close()

    #run c++ prog
    subprocess.run(["g++", "main.cpp"],shell = True)
    subprocess.run("a.exe")

    #output stuff
    file = open("arrayCont.txt" , "r")
    line = file.readline()

    img = Image.new("RGB", (width, height))
    pixles = img.load()

    temp = 0
    for i in range(width):
        for j in range(height):
            try:
                pixles[i, j] = (int(line[(temp):(temp)+3]), int(line[(temp)+4:(temp)+7]), int(line[(temp)+8:(temp)+11])) #does this work?
                temp += 12
            except ValueError:
                print(temp)
                pixles[i, j] = 0
    img.show()

def initWindow(window):
    if isinstance(window, tkinter.Tk):
        #formatting
        root.title("The Ultimate Image Archives") # sets window title
        root.geometry("512x256") # sets window size (width + "x" + height)
        root.resizable(False, False) # set wether the window can be resized by the user on the x and y axises
        #interactable elements/widgits
        #title text
        titleText = tkinter.Text(root)
        titleText.insert('insert', "The Ultimate Image Archives") # make it say stuff
        titleText.configure(font=("Times New Roman", 32), state='disabled') # set font and size
        titleText.pack()
        #seed/input box
        seedLabel = tkinter.Label(root, text="Seed", font=("Courier", 12)) #TODO: make label look pretty
        seedLabel.pack()
        seedLabel.place(bordermode='inside', anchor='n', relx=0.35, rely=0.4)

        inputVar = tkinter.StringVar() #actual variable

        seedInputArea = tkinter.Entry(root, textvariable=inputVar, width=35)
        seedInputArea.pack()
        seedInputArea.place(bordermode='inside', anchor='n', relx=0.65, rely=0.41)
        #generate image button
        generateButton = tkinter.Button(root, text="Make me a picture!", command=lambda: generate(inputVar.get())) #creates a button
        generateButton.pack() #makes it show i guess?
        generateButton.place(bordermode='inside', anchor='n', relx=0.5, rely=0.75) #moves to appropiate position

    else:
        print("Error, not valid tkinter window")
        raise SystemExit

root = tkinter.Tk() # instantiates tkinter window
initWindow(root) #sets everything up
root.mainloop() #makes the window run i guess?