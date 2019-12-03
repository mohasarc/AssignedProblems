import numpy as np
import matplotlib.pyplot as plt

# change file name to the name of the file containing XY-values
data = np.loadtxt('theoretical.txt')
for column in data.T:
  plt.plot(data[:,0], column)

plt.show()