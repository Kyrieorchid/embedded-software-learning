from PIL import Image

image = Image.open('./images/alien.png')

image.save('./images/alien.bmp', 'BMP')
