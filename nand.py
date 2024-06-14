# パーセプトロンのNAND回路からすべての論理回路をつくる

x1 = int(input('１か０を入力してください x1: '))
x2 = int(input('１か０を入力してください x2: '))

def NAND(x1, x2): # パーセプトロンのNAND回路
    if x1 * x2 >= 1:
        y = 0
    else:
        y = 1
    return y
    
"""  
デフォルトの論理回路で書くと
def nand(x1, x2):
    return not (x1 and x2)
"""

def AND(x1, x2):
    return NAND(NAND(x1, x2), NAND(x1, x2))
    
def OR(x1, x2):
    return NAND(NAND(x1, x1), NAND(x2, x2))    

def XOR(x1, x2):
    return NAND(NAND(NAND(x1, x2),x2), NAND(x1,NAND(x1, x2)))
    
def NOR(x1, x2):
    return NAND(NAND(NAND(x1, x1), NAND(x2, x2)), NAND(NAND(x1, x1), NAND(x2, x2)))

print('AND=' + str(AND(x1, x2))) # AND
print('OR=' + str(OR(x1, x2))) # OR
print('NAND=' + str(NAND(x1, x2))) # NAND
print('NOR=' + str(NOR(x1, x2))) # NOR

print('XOR=' + str(XOR(x1, x2))) # XOR



x = int(input('１を０で入力してください x= '))

def NOT(x):
    return NAND(x, x)
    
print('NOT=' + str(NOT(x))) # NOT=NOT(x)

