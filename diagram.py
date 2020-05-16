import matplotlib.pyplot as plt
import numpy as np
import os

# create data
x0 = []
y0 = []
for a in range(200):
    x0.append(np.random.randint(-100, 100))
    y0.append(np.random.randint(-100, 100))

new_list = [str(x0[i]) +';' + str(y0[i]) + '\n' for i in range(len(x0))]
with open('sample.txt', 'w') as f:
    f.writelines(new_list)

x = []
y = []
for a in range(200):
    x.append(np.random.randint(-100, 100))
    y.append(np.random.randint(-100, 100))

new_list = [str(x[i]) +';' + str(y[i]) + '\n' for i in range(len(x))]
with open('testing.txt', 'w') as f:
    f.writelines(new_list)

os.system("cat testing.txt | ./kkmeans 8 sample.txt 1")

f = open("results.txt","r")
n = int(f.readline())
A = []
B = []
C = []
for h in range(n):
    s = f.readline()
    a,b = s.split(' ')
    A.append(int(a))
    B.append(1)
    C.append(int(b))
colors = np.random.rand(n)
# use the scatter function
plt.scatter(A, B, C,c=colors)
plt.show()