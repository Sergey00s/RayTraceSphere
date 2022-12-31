from PIL import Image

# Open the PPM image
for i in range(0, 1):
    with Image.open(f'frames/new.ppm') as im:
        # Save the image as a PNG file
        im.save(f'frames/image.png', 'PNG')
        print(i)
    