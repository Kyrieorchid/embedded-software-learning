#闭包
#返回函数不要引用任何循环变量，或者后续会发生变化的变量。
#使用闭包时，对外层变量赋值前，需要先使用nonlocal声明该变量不是当前函数的局部变量。
'''使用闭包时，外层函数相当于是“全局”，
内层函数是局部，会保存“全局”变量的值'''
def createCounter():
    n = 0
    def counter():
        nonlocal n
        n = n + 1
        return n
    return counter


# 测试:
counterA = createCounter()
print(counterA(), counterA(), counterA(), counterA(), counterA()) # 1 2 3 4 5
counterB = createCounter()
if [counterB(), counterB(), counterB(), counterB()] == [1, 2, 3, 4]:
    print('测试通过!')
else:
    print('测试失败!')