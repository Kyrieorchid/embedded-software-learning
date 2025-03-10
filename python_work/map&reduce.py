# map(fn, iterable): 将函数应用到iterable，返回iterator
# reduce(fn, iterable): 将函数应用到iterable，
#   这个fn必须接收两个参数，reduce把结果和序列下一元素作为新的
#   入参做累计计算
from functools import reduce

def normalize(name):
        return name[0].upper() + name[1:].lower()

# 测试:
L1 = ['adam', 'LISA', 'barT']
L2 = list(map(normalize, L1))
print(L2)

###################################################################

def prod(L):
    return reduce(lambda x, y : x * y, L)

print('3 * 5 * 7 * 9 =', prod([3, 5, 7, 9]))
if prod([3, 5, 7, 9]) == 945:
    print('测试成功!')
else:
    print('测试失败!')

###########################################################

DIGITS = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}

def char2num(s):
    return DIGITS[s]

def str2float(s):
    L = s.split('.')
    n = pow(10, len(L[1]))
    sint = reduce(lambda x, y : x * 10 + y, map(char2num, ''.join(L)))
    return sint / n

print('str2float(\'123.456\') =', str2float('123.456'))
if abs(str2float('123.456') - 123.456) < 0.00001:
    print('测试成功!')
else:
    print('测试失败!')
    