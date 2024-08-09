# int関数パーセプトロン

import numpy as np


x = int(input('１か０を入力してください x: '))
y = int(input('１か０を入力してください y: '))
r = np.array([x, y])
w = np.array([1, 1])



# int関数
def f(x):
    return np.where(x > 0, 2, -2) 
  
s = 3 #threshold
m = 2*np.dot(w,r) - s
print('符号に注目してください')
print('andパーセプトロンの値')
print(m)
print('関数パーセプトロンの値')
print(f(m))
s = 1 #threshold
m = 2*np.dot(w,r) - s
print('orパーセプトロンの値')
print(m)
print('関数パーセプトロンの値')
print(f(m))

s = -3 #threshold
m = 2*np.dot(-w,r) - s
print('nandパーセプトロンの値')
print(m)
print('関数パーセプトロンの値')
print(f(m))

s = -1 #threshold
m = 2*np.dot(-w,r) - s
print('norパーセプトロンの値')
print(m)
print('関数パーセプトロンの値')
print(f(m))
  

def AND(x, y):
    r = np.array([x, y])
    w = np.array([1, 1])
    s = 3 #threshold
    m = 2*np.dot(w,r) - s
        
    if f(m) > 0:
        z = 1
    else:
        z = 0
    return z
    
def OR(x, y):
    r = np.array([x, y])
    w = np.array([1, 1])
    s = 1 #threshold
    m = 2*np.dot(w,r) - s
        
    if f(m) > 0:
        z = 1
    else:
        z = 0
    return z

def NAND(x, y):
    r = np.array([x, y])
    w = np.array([-1, -1])
    s = -3 #threshold
    m = 2*np.dot(w,r) - s
        
    if f(m) > 0:
        z = 1
    else:
        z = 0
    return z

def NOR(x, y):
    r = np.array([x, y])
    w = np.array([-1, -1])
    s = -1 #threshold
    m = 2*np.dot(w,r) - s
        
    if f(m) > 0:
        z = 1
    else:
        z = 0
    return z

print('単層')
print('AND=' + str(AND(x, y))) # AND
print('OR=' + str(OR(x, y))) # OR
print('NAND=' + str(NAND(x, y))) # NAND
print('NOR=' + str(NOR(x, y))) # NOR


def AND(x, y):
    return NAND(NAND(x, y), NAND(x, y))
    
def OR(x, y):
    return NAND(NAND(x, x), NAND(y, y))    

def XOR(x, y):
    return NAND(NAND(NAND(x, y),y), NAND(x,NAND(x, y)))
    
def NOR(x, y):
    return NAND( NAND(NAND(x, x), NAND(y, y)), NAND(NAND(x, x), NAND(y, y)) )



print('多層')
print('AND=' + str(AND(x, y))) # AND
print('OR=' + str(OR(x, y))) # OR
print('NAND=' + str(NAND(x, y))) # NAND
print('NOR=' + str(NOR(x, y))) # NOR

print('XOR=' + str(XOR(x, y))) # XOR



x = int(input('１か０を入力してください x= '))

def NOT(x):
    return NAND(x, x)
    
print('NOT=' + str(NOT(x))) # NOT=NOT(x)

print('関数を表示します')
import matplotlib.pylab as plt
x = np.arange(-10.0, 10.0, 0.01)
y = f(x)
plt.plot(x, y)
plt.show()
