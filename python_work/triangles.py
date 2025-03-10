#使用generator生成器,生成10行杨辉三角
# def triangles():
#     L1 = [1]
#     L2 = [1, 1]
#     P = L2
#     yield L1
#     yield L2
#     while True:
#         C = [].copy()
#         C.append(1)
#         for i in range(1, len(P)):
#             C.append(P[i] + P[i-1])
#         C.append(1)
#         P = C
#         yield C

# def triangles():
#     l=[1]
#     num=0
#     yield l
#     while True:
#         l = [1] + [l[i]+l[i+1] for i in range(num)] + [1]
#         yield l
#         num+=1

def triangles():
    row = [1]
    while True:
        yield row
        row = [ x + y for x,y in zip([0]+row,row+[0])]

n = 0
results = []
for t in triangles():
    results.append(t)
    n = n + 1
    if n == 10:
        break

for t in results:
    print(t)

if results == [
    [1],
    [1, 1],
    [1, 2, 1],
    [1, 3, 3, 1],
    [1, 4, 6, 4, 1],
    [1, 5, 10, 10, 5, 1],
    [1, 6, 15, 20, 15, 6, 1],
    [1, 7, 21, 35, 35, 21, 7, 1],
    [1, 8, 28, 56, 70, 56, 28, 8, 1],
    [1, 9, 36, 84, 126, 126, 84, 36, 9, 1]
]:
    print('测试通过!')
else:
    print('测试失败!')
