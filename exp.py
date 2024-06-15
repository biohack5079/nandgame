import numpy as np

"""
パーセプトロンから論理回路
"""

def AND(X1, X2):
    a = 1
    b = 1
    c = 1.0001
    x = np.array([X1, X2])
    w = np.array([a, b])
    
    if np.sum(w * x) > c:
        y = 1
    else:
        y = 0
    return y
    
def OR(X1, X2):
    a = 1
    b = 1
    c = 0.9999
    x = np.array([X1, X2])
    w = np.array([a, b])
    if np.sum(w * x) > c:
        y = 1
    else:
        y = 0
    return y

def NAND(X1, X2):
    a = -1
    b = -1
    c = -1.001
    x = np.array([X1, X2])
    w = np.array([a, b])
    if np.sum(w * x) > c:
        y = 1
    else:
        y = 0
    return y
    
"""
ＮＡＮＤで構成
"""
  

def XOR(x1, x2):
    return NAND(NAND(NAND(x1, x2),x2), NAND(x1,NAND(x1, x2)))
    
def NOR(x1, x2):
    return NAND(NAND(NAND(x1, x1), NAND(x2, x2)), NAND(NAND(x1, x1), NAND(x2, x2)))
    
print('AND(1, 1)=' + str(AND(1, 1)) + ' AND(1, 0)=' + str(AND(1, 0)) + ' AND(0, 0)=' + str(AND(0, 0))) 
print('OR(1, 1)=' + str(OR(1, 1)) + ' OR(1, 0)=' + str(OR(1, 0)) + ' OR(0, 0)=' + str(OR(0, 0)))
print('NAND(1, 1)=' + str(NAND(1, 1)) + ' NAND(1, 0)=' + str(NAND(1, 0)) + ' NAND(0, 0)=' + str(NAND(0, 0)))
print('NOR(1, 1)=' + str(NOR(1, 1)) + ' NOR(1, 0)=' + str(NOR(1, 0)) + ' NOR(0, 0)=' + str(NOR(0, 0)))
print('XOR(1, 1)=' + str(XOR(1, 1)) + ' XOR(1, 0)=' + str(XOR(1, 0)) + ' XOR(0, 0)=' + str(XOR(0, 0)))

