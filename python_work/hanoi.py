#A上n个移动到C上，若只有1个则直接移动，n个就先把（n-1）移动到B
#递归：要把（n-1）移动到B，则先把（n-2）移动到C ...
def hanoi(n, a, b, c):
    if n == 1:
        print(a, "->", c)
    else:
        hanoi(n-1, a, c, b)
        hanoi(1, a, b, c)
        hanoi(n-1, b, a, c)

hanoi(3, 'A', 'B', 'C')
