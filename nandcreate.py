# パーセプトロンのNAND回路からすべての論理回路をつくる  

import numpy as np

x = int(input('１か０を入力してください x: '))
y = int(input('１か０を入力してください y: '))

def NAND(x, y):
    r = np.array([x, y])
    w = np.array([-1, -1])
    s = -1.5  
    if np.sum(w * r) - s > 0:
        z = 1
    else:
        z = 0
    return z
    
"""  
デフォルトの論理回路で書くと
def nand(x, y):
    return not (x and y)
"""

def AND(x, y):
    return NAND(NAND(x, y), NAND(x, y))
    
def OR(x, y):
    return NAND(NAND(x, x), NAND(y, y))    

def XOR(x, y):
    return NAND(NAND(NAND(x, y),y), NAND(x,NAND(x, y)))
    
def NOR(x, y):
    return NAND(NAND(NAND(x, y), NAND(x, y)), NAND(NAND(x, y), NAND(x, y)))

print('AND=' + str(AND(x, y))) # AND
print('OR=' + str(OR(x, y))) # OR
print('NAND=' + str(NAND(x, y))) # NAND
print('NOR=' + str(NOR(x, y))) # NOR

print('XOR=' + str(XOR(x, y))) # XOR



x = int(input('１か０を入力してください x= '))

def NOT(x):
    return NAND(x, x)
    
print('NOT=' + str(NOT(x))) # NOT=NOT(x)
