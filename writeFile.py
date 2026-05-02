import subprocess
from PIL import Image
path = raw_input("path: ")
output = raw_input("output path: ")
file = Image.open(path)
w, h = file.size
pixels = file.convert("RGBA")
pixelArray = [[0 for y in range(w)] for x in range(h)]
for one in range(h):
	for two in range(w):
		r,g,b,a = pixels.getpixel((two,one))
		pixelArray[one][two] = str(r) + " " + str(g) + " " + str(b) + " " + str(a) + " "
file2 = open(output,"w")
for a in range(h):
	for b in range(w):
		file2.write(pixelArray[a][b])
file2.close()
subprocess.check_call(["editFile.exe", str(output), str(w), str(h)])
