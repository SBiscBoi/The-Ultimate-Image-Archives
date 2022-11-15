from PIL import Image
import subprocess

width = 1920 #default 1920
height = 1080 #default 1080

#write input to file to be read later
input = "" #INPUT GOES HERE
inpFile = open("inputFile.txt", "w") #create a new file to send the input to the c++ file

#if empty, assume 0
if(input == ""):
    input = "0"

#IF the input is purely digits, then there is no need to convert to ASCII values and it can be directly passed to the c++ file
#OTHERWISE there must be a character other than a digit and all characters in the input must be converted to ASCII values
if(input.isdigit()):
    inpFile.write(input) #write to input file used by c++ prog
else:
    #this part could be done in the c++ portion later for speed
    newInput = ""
    for i in input: #each char in string
        newInput += str(ord(i)) #grab ASCII value, cast to string
    inpFile.write(newInput) #NOW write to input file used by c++ prog
inpFile.close() #good practice

#run c++ prog
subprocess.run(["g++", "main.cpp"],shell = True) #not quite sure what "shell = True" does but StackOverflow said it was good so i'm not gonna ask questions
subprocess.run("a.exe") #run the compiled c++ file to generate the color values of the final image

#output stuff
file = open("arrayCont.txt" , "r") #open output file from c++ executable
line = file.readline()

img = Image.new("RGB", (width, height))
pixles = img.load()

temp = 0 #acts as a soirt of cursor
for i in range(width):
    for j in range(height):
        try:
            pixles[i, j] = (int(line[(temp):(temp)+3]), int(line[(temp)+4:(temp)+7]), int(line[(temp)+8:(temp)+11])) #set current pixel color based off 3, 3-digit numbers in the file starting from "temp" (aka the cursor).  these 3 numbers correspond to the Red, Green, and Blue values of the pixel.
            temp += 12 #foward cursor by 12 slots to read next 3 values.
        except ValueError: #if something somehow goes incredibly wrong, just set the pixel to black.
            pixles[i, j] = 0

img.show() #finally, display the complete image.
