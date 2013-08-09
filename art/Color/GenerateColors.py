import sys
import colorsys
import json
from PIL import Image
             
"""
Color Chart

fill		-	L: 0.5	-	S: 0.5
outline		-	L: 0.35	-	S: 0.9
arrow		-	L: 0.8	-	S: 0.5
piece		-	L: 0.55	-	S: 0.3
background	-	L: 0.4	-	S: 0.4
"""

def saveAsColor( colorName, r, g, b, scheme ):
	rInt = int(r*255)
	gInt = int(g*255)
	bInt = int(b*255)
	scheme[colorName] = [rInt, gInt, bInt, 255]
	return (rInt, gInt, bInt)
	

colorNum = int(sys.argv[1])
print 'Generating ' + str(colorNum) + ' colors...'
increment = 1 / float(colorNum)
pixelList = []
colorSchemes = []
hueList = []

for i in range(colorNum):
	hueList.append( increment * i )
	
for hueValue in hueList:
	colorScheme = {}

	#fill
	r, g, b = colorsys.hls_to_rgb(hueValue, 0.5, 0.5)
	pixelList.append( saveAsColor('fill', r, g, b, colorScheme ) )
	
	#outline
	r, g, b = colorsys.hls_to_rgb(hueValue, 0.35, 0.9)
	pixelList.append( saveAsColor('outline', r, g, b, colorScheme ) )
	
	#arrow
	r, g, b = colorsys.hls_to_rgb(hueValue, 0.8, 0.5)
	pixelList.append( saveAsColor('arrow', r, g, b, colorScheme ) )
	
	#piece
	r, g, b = colorsys.hls_to_rgb(hueValue, 0.55, 0.3)
	pixelList.append( saveAsColor('piece', r, g, b, colorScheme ) )
	
	#background
	r, g, b = colorsys.hls_to_rgb(hueValue, 0.4, 0.4)
	pixelList.append( saveAsColor('background', r, g, b, colorScheme ) )
	
	colorSchemes.append( colorScheme )
	
data = { 'colors' : colorSchemes }
json.dump(data, open('colors.json', 'wb'), sort_keys=True, indent=4, separators=(',', ': '))
print 'Generating colors complete! Check colors.json file.'

im = Image.new("RGB", (5, colorNum), "white")
im.putdata(pixelList)
im = im.resize((50, colorNum * 10))
im.save('schemes.png')

print 'Schemes images saved!'