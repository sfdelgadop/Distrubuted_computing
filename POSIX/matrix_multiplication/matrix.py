import numpy as np
from random import random

size = 512

m1 = np.random.rand(size, size)
m2 = np.random.rand(size, size)

result = m1 @ m2

def write_matrix(f, m, name):

    f.write('double {}[SIZE][SIZE] = {{\n'.format(name))

    for i in range(size-1):
        f.write('\t{')
        for v in m[i][:-1]:
            f.write('{:0.8f}, '.format(v))
        f.write('{:0.8f}}},\n'.format(m[i][-1]))

    f.write('\t{')
    for v in m[-1][:-1]:
        f.write('{:0.8f}, '.format(v))
    f.write('{:0.8f}}}\n'.format(m[i][-1]))

    f.write('};\n\n')

with open('matrix.h', 'w+') as f:

    f.write('#ifndef MATRIX\n')
    f.write('#define MATRIX\n')
    f.write('#define SIZE {}\n\n'.format(size))
    f.write('double result[SIZE][SIZE];\n')

    write_matrix(f, m1, 'm1')
    write_matrix(f, m2, 'm2')

    f.write('#endif')
    
# print(result)