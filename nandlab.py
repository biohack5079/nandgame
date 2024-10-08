
# NANDからXNORを創るゲーム


import numpy as np

#テスト
x = int(input('１か０を入力してください x: '))
y = int(input('１か０を入力してください y: '))
r = np.array([x, y])
w = np.array([2, 2]) 


# sigmoid関数
def f(x):
    return 4/(1 + np.exp(-x))-2

#テスト

#AND  
s= 3 #threshold
m = np.dot(w,r) - s
print('符号に注目してください')
print('andパーセプトロンの値')
print(m)
print('関数パーセプトロンの値')
print(f(m))

#OR
s = 1 #threshold
m = np.dot(w,r) - s
print('orパーセプトロンの値')
print(m)
print('関数パーセプトロンの値')
print(f(m))

#NAND
s = -3 #threshold
m = np.dot(-w,r) - s
print('nandパーセプトロンの値')
print(m)
print('関数パーセプトロンの値')
print(f(m))

#NOR
s = -1 #threshold
m = np.dot(-w,r) - s
print('norパーセプトロンの値')
print(m)
print('関数パーセプトロンの値')
print(f(m))



def AND(x, y):
    a=0
    b=0
    r = np.array([x, y, 1]) #1はダミー
    w = np.array([2, 2, 2*b-3]) #weight+bias
    m = np.dot(w*(1-2*a), r)
    return np.where(f(m) > 0, 1, 0)
    
def OR(x, y):
    a=0
    b=1
    r = np.array([x, y, 1]) #1はダミー
    w = np.array([2, 2, 2*b-3]) #weight+bias
    m = np.dot(w*(1-2*a), r)
    return np.where(f(m) > 0, 1, 0)

def NAND(x, y):
    a=1
    b=0
    r = np.array([x, y, 1]) #1はダミー
    w = np.array([2, 2, 2*b-3]) #weight+bias
    m = np.dot(w*(1-2*a), r)
    return np.where(f(m) > 0, 1, 0)
    
def NOR(x, y):
    a=1
    b=1
    r = np.array([x, y, 1]) #1はダミー
    w = np.array([2, 2, 2*b-3]) #weight+bias
    m = np.dot(w*(1-2*a), r)
    return np.where(f(m) > 0, 1, 0)



print('単層')
print('AND=' + str(AND(x, y))) # AND
print('OR=' + str(OR(x, y))) # OR
print('NAND=' + str(NAND(x, y))) # NAND
print('NOR=' + str(NOR(x, y))) # NOR




def NAND(x, y):
    return 1-x*y # =1-xy

def AND(x, y):
    return NAND(NAND(x, y), NAND(x, y)) # =xy
    
def OR(x, y):
    return NAND(NAND(x, x), NAND(y, y)) # =x+y-xy 
    
def NOR(x, y):
    return NAND( NAND(NAND(x, x), NAND(y, y)), NAND(NAND(x, x), NAND(y, y)) ) # =xy-x-y+1

def XOR(x, y):
    return NAND(NAND(NAND(x, y),y), NAND(x,NAND(x, y))) # =x+y-2xy

def XNOR(x, y):
    return NAND( NAND(NAND(NAND(x, y),y), NAND(x,NAND(x, y))) , NAND(NAND(NAND(x, y),y), NAND(x,NAND(x, y))) ) # =1+2xy-x-y




print('多層')
print('AND=' + str(AND(x, y))) # AND
print('OR=' + str(OR(x, y))) # OR
print('NAND=' + str(NAND(x, y))) # NAND
print('NOR=' + str(NOR(x, y))) # NOR

print('XOR=' + str(XOR(x, y))) # XOR
print('XNOR=' + str(XNOR(x, y))) # XNOR



z = int(input('１か０を入力してください z= '))

def NOT(z):
    return NAND(z, z) #1-z
    
print('NOT(z)=' + str(NOT(z))) # NOT=NOT(z)

if str(XNOR(x, y)) == '0' or str(XNOR(x, y)) == '1':
    print('ゲームクリア')
else:
    print('ゲームオーバー！')
    print('活性化関数をかまします。')

    import matplotlib.pylab as plt
    x = np.arange(-10.0, 10.0, 0.1)
    z = f(x)
    plt.plot(x, z)
    plt.show()
    z = f(XNOR(x, y))
    plt.plot(x, z)
    plt.show()
    
    
