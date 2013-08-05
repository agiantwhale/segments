import glob, Image, os

def saveInFolder(data, name, scale):
	im = Image.open(data)
	print "Processing " + data + " Scale: " + name
	original_width, original_height = im.size
	output_dir = os.getcwd() + '/' + name + '/'
	if not os.path.exists(output_dir):
		os.mkdir(output_dir)
	resized = im.resize((int(original_width * scale), int(original_height * scale)), Image.ANTIALIAS)
	resized.save(output_dir + data)

png_files = glob.iglob("*.png")

for data in png_files:
	#iOS
	saveInFolder(data, 'HDR', 1)
	saveInFolder(data, 'HD', 0.5)
	saveInFolder(data, 'SD', 0.25)

	#Android
	saveInFolder(data, 'xlarge', 0.5625)
	saveInFolder(data, 'large', 0.375)
	saveInFolder(data, 'normal', 0.2625)
	saveInFolder(data, 'small', 0.1875)

print "Processing complete!"