from PIL import Image

image = Image.open('./images/ship.png')

image.save('./images/ship.bmp', 'BMP')
