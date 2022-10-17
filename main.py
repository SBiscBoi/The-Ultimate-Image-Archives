import random
from PIL import Image

width = 1920
height = 1080

img = Image.new("RGB", (width, height))
pixles = img.load()

for i in range(width):
    for j in range(height):
        pixles[i, j] = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)) #impliment whole seed thing later

img.show()
