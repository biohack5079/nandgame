#論理回路学習ゲーム

import numpy as np

#活性化関数(シグモイド)
def f(x):
    return 4 / (1 + np.exp(-x)) -2
    


def p(r, w): #パーセプトロン
    m = np.dot(r, w) #内積 2x+2y+s
    return f(m) #活性化関数を作用


#テスト
x = int(input('１か０を入力してください x: '))
y = int(input('１か０を入力してください y: '))
b = int(input('１でOR,０でANDになります。b: '))
a = int(input('１でNOR,NAND,０でそのまま a: '))


s = 2*b-3
r = np.array([x, y, 1]) #入力値ベクトル
w = np.array([2, 2, s]) #重みの基底値
w = w*(1-2*a) #符号を反転

print(str(np.dot(r, w))+' #パーセプトロンから出る値') #内積 2x+2y+s
print(str(p(r, w))+' #活性化関数かました値')


# もう1度step関数をかます
def f(x):
    return np.where(x > 0, 1, 0)
    
print(str(p(r, w))+'   #ステップ関数でリセットした値(真偽値)')


#多層化された論理回路の挙動

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
    

#活性化関数(シグモイド)
def f(x):
    return 4 / (1 + np.exp(-x)) -2

print('多層化された論理回路の挙動')
print('AND=' + str(AND(x, y))) # AND
print('OR=' + str(OR(x, y))) # OR
print('NAND=' + str(NAND(x, y))) # NAND
print('NOR=' + str(NOR(x, y))) # NOR

print('XOR=' + str(XOR(x, y))) # XOR
print('XNOR=' + str(XNOR(x, y))) # XNOR

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
