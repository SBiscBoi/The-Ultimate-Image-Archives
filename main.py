import random
import sys
from PIL import Image

sys.set_int_max_str_digits(100000) #if i don't do this i get an error?

width = 1920
height = 1080

input = "1" #input goes here for now

num1 = 0
num2 = 1

#fibonacci time
while len(input) != (width*height*3):
    input = input + str(num1)
    temp = num1 + num2
    num1 = num2
    num2 = temp
    if len(input) > (width*height*3):
        input = input[0:(width*height*3)] #shorten to (width*height)*3 length and break loop(hopefully)

p = 0
while p < len(input):
    if int(input[p:(p+3)]) >= 256:
        input = input[:p] + str(int(input[p:(p+3)]) % 255) + input[p+1:]
    p += 3 #takes forever, might be optimizable
p = 0 #reset to save some memory and not create new varible because this is about to be used again

arr = [[0 for c in range(3)] for r in range(width*height)] #storage

for row in range(len(arr)):
    for col in range(len(arr[0])):
        arr[row][col] = input[p:(p+3)]
        p+=3 #see?


img = Image.new("RGB", (width, height))
pixles = img.load()

for i in range(width):
    for j in range(height):
        pixles[i, j] = (arr[i*j][0], arr[i*j][1], arr[i*j][2]) #does this work? no. no it doesn't

img.show()
