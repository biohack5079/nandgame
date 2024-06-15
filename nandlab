import numpy as np

"""
パーセプトロンから論理回路
"""

def AND(x, y):
    a = 1
    b = 1
    c = 1.5
    r = np.array([x, y])
    w = np.array([a, b])
    
    if np.sum(w * r) > c:
        z = 1
    else:
        z = 0
    return z
    
def OR(x, y):
    a = 1
    b = 1
    c = 0.5
    r = np.array([x, y])
    w = np.array([a, b])
    if np.sum(w * r) > c:
        z = 1
    else:
        z = 0
    return z

def NAND(x, y):
    a = -1
    b = -1
    c = -1.5
    r = np.array([x, y])
    w = np.array([a, b])
    if np.sum(w * r) > c:
        z = 1
    else:
        z = 0
    return z

def NOR(x, y):
    a = -1
    b = -1
    c = -0.5
    r = np.array([x, y])
    w = np.array([a, b])
    if np.sum(w * r) > c:
        z = 1
    else:
        z = 0
    return z


"""
ＮＡＮＤでＸＯＲを構成
"""


def XOR(x, y):
    return NAND(NAND(NAND(x, y),y), NAND(x,NAND(x, y)))

   
    
print('AND(1, 1)=' + str(AND(1, 1)) + ' AND(1, 0)=' + str(AND(1, 0)) + ' AND(0, 0)=' + str(AND(0, 0))) 
print('OR(1, 1)=' + str(OR(1, 1)) + ' OR(1, 0)=' + str(OR(1, 0)) + ' OR(0, 0)=' + str(OR(0, 0)))
print('NAND(1, 1)=' + str(NAND(1, 1)) + ' NAND(1, 0)=' + str(NAND(1, 0)) + ' NAND(0, 0)=' + str(NAND(0, 0)))
print('NOR(1, 1)=' + str(NOR(1, 1)) + ' NOR(1, 0)=' + str(NOR(1, 0)) + ' NOR(0, 0)=' + str(NOR(0, 0)))
print('XOR(1, 1)=' + str(XOR(1, 1)) + ' XOR(1, 0)=' + str(XOR(1, 0)) + ' XOR(0, 0)=' + str(XOR(0, 0)))
