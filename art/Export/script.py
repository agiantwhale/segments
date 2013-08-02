import glob, Image, os

png_files = glob.iglob("*.png")

def save_image(image, name, dir):
	directory = os.getcwd() + '/' + dir + '/'
	if not os.path.exists(directory):
		os.mkdir(directory)
	image.save(directory + name)
	print " -- " + dir + " saved successfully!"

for data in png_files:
	im = Image.open(data)
	print "Processing " + data
	original_width, original_height = im.size
	save_image(im, data, 'HDR')
	hd = im.resize( (int(original_width * 0.5), int(original_height * 0.5)), Image.ANTIALIAS )
	save_image(hd, data, 'HD')
	sd = im.resize( (int(original_width * 0.25), int(original_height * 0.25)), Image.ANTIALIAS )
	save_image(sd, data, 'SD')

print "Processing complete!"