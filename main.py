from PIL import Image
import subprocess

width = 1920 #default 1920
height = 1080 #default 1080

#write input to file to be read later
input = "123"
inpFile = open("inputFile.txt", "w")
if(input.isdigit()):
    inpFile.write(input)
else:
    newInput = ""
    for i in input:
        newInput += str(ord(i))
    #print(newInput)
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
