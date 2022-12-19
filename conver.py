from PIL import Image

# Open the PPM image
for i in range(0, 100):
    with Image.open(f'frames/image{i}.ppm') as im:
        # Save the image as a PNG file
        im.save(f'real/image{i}.png', 'PNG')
        print(i)
    