import random
import sys
from PIL import Image

width = 1920
height = 1080

file = open("C:\\Users\\Owner\\Desktop\\The-Ultimate-Image-Archives-master\\The-Ultimate-Image-Archives-master\\arrayCont.txt" , "r")
line = file.readline()

img = Image.new("RGB", (width, height))
pixles = img.load()

for i in range(width):
    for j in range(height):
        
        pixles[i, j] = (int(line[(i*j)*4:(i*j)*4+4]), int(line[(i*j)*4+4:(i*j)*4+8]), int(line[(i*j)*4+8:(i*j)*4+12])) #does this work?

img.show()
