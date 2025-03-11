#迭代，返回列表中最大最小值tuple(min, max)
def findMinAndMax(L):
    if L == []:
        return (None, None)
    min = max = L[0]
    for item in L:
        min = item if item < min else min
        max = item if item > max else max
    assert(min <= max)

    return (min, max)

# 测试
if findMinAndMax([]) != (None, None):
    print('测试失败!')
elif findMinAndMax([7]) != (7, 7):
    print('测试失败!')
elif findMinAndMax([7, 1]) != (1, 7):
    print('测试失败!')
elif findMinAndMax([7, 1, 3, 9, 5]) != (1, 9):
    print('测试失败!')
else:
    print('测试成功!')
