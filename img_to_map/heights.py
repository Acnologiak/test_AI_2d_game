import matplotlib.pyplot as plt

import numpy as np

thermal_array = []
thermal_map = open("thermal_map.txt")
for line in thermal_map:
    thermal_array.append([int(element) for element in line.split(" ")[:-1]])

n = len(thermal_array)
m = len(thermal_array[0])
u, v = np.mgrid[-int(m/2):int(m/2):64j, -int(n/2):int(n/2):64j]
x = u
y = v

z = np.array([[thermal_array[i][j] for i in range(len(u[0]))] for j in range(len(u))])
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

cmap_list = ['viridis', 'plasma', 'inferno', 'magma', 'cividis', 'Greys', 'Purples', 'Blues', 'Greens', 'Oranges',
             'Reds', 'YlOrBr', 'YlOrRd', 'OrRd', 'PuRd', 'RdPu', 'BuPu', 'GnBu', 'PuBu', 'YlGnBu', 'PuBuGn', 'BuGn',
             'YlGn', 'binary', 'gist_yarg', 'gist_gray', 'gray', 'bone', 'pink', 'spring', 'summer', 'autumn', 'winter',
             'cool', 'Wistia', 'hot', 'afmhot', 'gist_heat', 'copper', 'PiYG', 'PRGn', 'BrBG', 'PuOr', 'RdGy', 'RdBu',
             'RdYlBu', 'RdYlGn', 'Spectral', 'coolwarm', 'bwr', 'seismic', 'twilight', 'twilight_shifted', 'hsv',
             'Pastel1', 'Pastel2', 'Paired', 'Accent', 'Dark2', 'Set1', 'Set2', 'Set3', 'tab10', 'tab20', 'tab20b',
             'tab20c', 'flag', 'prism', 'ocean', 'gist_earth', 'terrain', 'gist_stern', 'gnuplot', 'gnuplot2', 'CMRmap',
             'cubehelix', 'brg', 'gist_rainbow', 'rainbow', 'jet', 'turbo', 'nipy_spectral', 'gist_ncar']
"""
for i in range(len(cmap_list)):
    try:
        ax.plot_surface(x, y, z, cmap=cmap_list[i])
        plt.savefig(f'thermal_map{i+1}.png')
    except:
        pass

"""
print(len(cmap_list))
ax.plot_surface(x, y, z, cmap="hot")
plt.show()
