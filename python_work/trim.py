#利用切片操作，实现一个trim()函数，去除字符串首尾的空格
def trim(s):
    first, last, flag = 0, 0, 0
    for i in range(len(s)):
        if((s[i] != ' ') and not flag):
            first = i
            flag = 1
        if((s[i] != ' ') and flag):
            last = i+1
    return s[first:last]

# 测试:
if trim('hello  ') != 'hello':
    print('测试失败!')
elif trim('  hello') != 'hello':
    print('测试失败!')
elif trim('  hello  ') != 'hello':
    print('测试失败!')
elif trim('  hello  world  ') != 'hello  world':
    print('测试失败!')
elif trim('') != '':
    print('测试失败!')
elif trim('    ') != '':
    print('测试失败!')
else:
    print('测试成功!')