from PIL import Image, ImageDraw


image = Image.open('test-map64.jpg')
width = image.size[0]  # ширина
height = image.size[1]  # высота
print(height,"*",width)
pix = image.load()
f = open('map.txt', 'w')
list=[]
temp_list = []
temp = 0
for x in range(width):
   if x != 0:
      list.append(temp_list)
      temp_list = []
   for y in range(height):
      r = pix[x, y][0]  #узнаём значение красного цвета пикселя
      g = pix[x, y][1]  #зелёного
      b = pix[x, y][2]  #синего
      sr = (r + g + b)
      if sr >= 100:
         temp = 1
      else:
         temp = 0
      temp_list.append(temp)
list.append(temp_list)
for item in list:
   f.write("\n")
   for i in item:
      f.write("%s" % str(i))
f.close()



