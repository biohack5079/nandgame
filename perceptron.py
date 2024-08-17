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
print('ゲームクリア')

