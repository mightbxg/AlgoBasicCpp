#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import json

# parameters
# y=ax+b
a = 0.5
b = 10.0
x_min = 10.0
x_max = 490.0
num = 50
noise_scale = 2.0
filename = "pts.json"

# generate data
x = np.linspace(x_min, x_max, num)
y = a*x+b
x = x+np.random.normal(0, noise_scale, size=num)
y = y+np.random.normal(0, noise_scale, size=num)

# add outliers
y_min = a*x_min+b
y_max = a*x_max+b
indices = np.random.choice(np.arange(num), replace=False, size=int(num*0.2))
y[indices] = np.random.random(indices.shape[0]) * (y_max-y_min) + y_min

# save to yaml file
data = {'x':x.tolist(), 'y':y.tolist()}
with open(filename, 'w') as f:
    json.dump(data, f)
print('pts saved to file:', filename)

# visualize
plt.scatter(x, y, marker='.')
plt.savefig('pts.png')
#plt.show()
